/*
aPACK reimplementation
Written by and copyright (C) Joel Yliluoma in 2011; http://iki.fi/bisqwit/

This program reimplements the compression and decompression
algorithm used by Joergen Ibsen's aPACK version 1.0.
Specifically, its default algorithm, which is an LZ variant...

With the following modification: End of compressed stream
is indicated the same way as in aPLib, rather than the way
it is done in aPACK.

*/
#include <algorithm>
#include <vector>
#include <cstdio>
#include <assert.h>
#include <cstring>

#include <unistd.h>
#include <stdlib.h>

#ifdef _OPENMP
# include <omp.h>
#endif
#include <map>

bool DoVerySlow = false;

const size_t MaxDistance = 0x7FFF;

struct EncodingParams
{
    unsigned n_calls;
    unsigned call_mask;
    unsigned constbyte;
    unsigned constbyte2;
    unsigned literalbits;
    bool     appends;
    unsigned offsconstmask; // 1 = +1, 2 = -1, 4 = +2
    bool     useliteraltable;

    unsigned MaxLiteralOffset() const
    {
        unsigned m = (1 << literalbits); // 1..16 (encoded as 0..15)
        if(constbyte != 0x100) m -= 1; // 1..15
        if(constbyte2 != 0x100) m -= 1;
        if(offsconstmask & 1)  m -= 1; // 1..14 (encoded as 2..15)
        if(offsconstmask & 2)  m -= 1;
        if(offsconstmask & 4)  m -= 1;
        return m;
    }
    size_t LiteralIndex() const
    {
        size_t result = 0;
        if(offsconstmask & 1) ++result;
        if(offsconstmask & 2) ++result;
        if(offsconstmask & 4) ++result;
        return 0;
    }
    size_t Literal2Index() const
    {
        size_t result = 0;
        if(offsconstmask & 1) ++result;
        if(offsconstmask & 2) ++result;
        if(offsconstmask & 4) ++result;
        if(constbyte != 0x100) ++result;
        return 0;
    }
    size_t OffsConstPlusIndex() const
    {
        return 0;
    }
    size_t OffsConstMinusIndex() const
    {
        size_t result = 0;
        if(offsconstmask & 1) ++result;
        return result;
    }
    size_t OffsConstPlusTwoIndex() const
    {
        size_t result = 0;
        if(offsconstmask & 1) ++result;
        if(offsconstmask & 2) ++result;
        return result;
    }
    size_t LiteralOffset(size_t o) const
    {
        o -= 1; // 1..15 -> 0..14
        if(constbyte != 0x100) ++o; // back to 1..15
        if(constbyte2 != 0x100) ++o;
        if(offsconstmask & 1) ++o;
        if(offsconstmask & 2) ++o;
        if(offsconstmask & 4) ++o;
        return o;
    }
};

namespace
{
    static size_t MatchingLength
        (const unsigned char* in1,
         size_t size,
         const unsigned char* in2)
    {
        // Trivial implementation would be:
        //   return std::mismatch(in1,in1+size, in2).second-in2;
        // However this function attempts to gain something
        // by comparing sizeof(unsigned) bytes at time instead
        // of 1 byte at time.
        size_t len = 0;
        typedef size_t T;
        const size_t intsize = sizeof(T);
        const T*const p1 = reinterpret_cast<const T*>(in1);
        const T*const p2 = reinterpret_cast<const T*>(in2);
        while(size >= intsize && p1[len] == p2[len]) { ++len; size -= intsize; }
        len *= intsize;
        while(size > 0 && in1[len] == in2[len]) { --size; ++len; }
        return len;
    }

    static unsigned GammaScore(size_t value)
    {
        assert(value >= 2);
        unsigned highest_bit = 0x80000000u;
        while(highest_bit != 0
           && !(value & highest_bit))
            highest_bit >>= 1;
        if(value & highest_bit)
            highest_bit >>= 1;
        unsigned num_bits_sent = 0;
        for(; ; ++num_bits_sent)
        {
            ++num_bits_sent;
            highest_bit >>= 1;
            if(!highest_bit) break;
        }
        return ++num_bits_sent;
    }

    static unsigned Cost(size_t offset, size_t length, size_t prev_offset, size_t default_cost)
    {
        if(length < 2) return default_cost;
        if(offset == prev_offset)
        {
            // Penalty of an append
            const unsigned GammaScore2  = 2;
            return 2 + GammaScore2 + GammaScore(length);
        }
        if(length >= 2 && length <= 3 && offset >= 1 && offset <= 0x7F)
        {
            // Penalty of a short match
            return 3 + 8;
        }
        // Penalty of a long match
        if(offset <= 0x7F && length < 4) return 100; // Penalize illegal combination

        size_t tmp = offset + 0x300, tmp2 = length;
        if(offset <= 0x7F) tmp2 -= 2;
        return 2 + 8 + GammaScore(tmp >> 8) + GammaScore(tmp2);
    }
}

class Apack
{
public:
    std::vector<unsigned char> result;
    unsigned BitsRemaining, BitsPosition;
    std::vector<unsigned> GammaSummary, GammaSummary2;

    unsigned char LiteralsInOrderOfCommonness[256]; // commonness# -> literal
    unsigned LiteralIndices[256];                   // literal -> commonness#
    unsigned NumUsedLiterals;

private:
    // First: copy length, second: begin offset
    std::vector< std::pair<size_t,size_t> > MaxMatchLen;
    std::vector< unsigned char >            DefaultCost;
    std::vector< std::pair<size_t,size_t> > Decisions;
    std::vector<bool> bomb; // bytes which must be encoded verbatim
                            // due to containing author's name

    std::vector<unsigned short> MatchCache;

private:
    size_t TestMatch(const std::vector<unsigned char>& source,
                     size_t pos1,
                     size_t pos2,
                     size_t limit)
    {
        if(pos2 > pos1) { size_t tmp = pos1; pos1=pos2; pos2=tmp; }
        const size_t p = pos1 * source.size() + pos2;
        if(MatchCache[p]) return MatchCache[p] - 1;

        size_t result = MatchingLength(&source[pos1], limit, &source[pos2]);
        MatchCache[ p ] = 1+result;
        return result;
    }

    void CreateAuxLiteralTables(const unsigned LiteralUsageTable[256])
    {
        NumUsedLiterals = 0;
        for(unsigned a=0; a<256; ++a)
        {
            LiteralIndices[a] = 9999;
            if(LiteralUsageTable[a])
                LiteralsInOrderOfCommonness[NumUsedLiterals++] = a;
        }
        for(unsigned j=1; j<NumUsedLiterals; ++j)
        {
            unsigned k = LiteralsInOrderOfCommonness[j], i;
            for(i=j; i>=1 && LiteralUsageTable[LiteralsInOrderOfCommonness[i-1]]
                           < LiteralUsageTable[k]; --i)
                LiteralsInOrderOfCommonness[i] = LiteralsInOrderOfCommonness[i-1];
            LiteralsInOrderOfCommonness[i] = k;
        }
        for(unsigned j=0; j<NumUsedLiterals; ++j)
            LiteralIndices[ LiteralsInOrderOfCommonness[j] ] = j;
    }

    void AnalyzeSource(
        const std::vector<unsigned char>& source,
        const EncodingParams& params)
    {
        const size_t endpos  = source.size();
        MaxMatchLen.resize(endpos);
        DefaultCost.resize(endpos);
        Decisions.resize(endpos);
        bomb.resize(endpos);

        unsigned LiteralUsageTable[256] = { 0 }; // literal -> num times encoded
        for(size_t a=0; a<source.size(); ++a)
            LiteralUsageTable[ source[a] ] += 1;
        CreateAuxLiteralTables(LiteralUsageTable);

        MatchCache.resize(endpos * endpos);

        // Find out all prospects
        for(size_t a=0; a<endpos; ++a)
        {
            unsigned default_cost = params.useliteraltable
                ? 1 + GammaScore( LiteralIndices[ source[a] ] + 2 )
                : 9;
            unsigned better_cost = 9999;

            if(source[a] == params.constbyte)
                better_cost = 3 + params.literalbits;
            else if(source[a] == params.constbyte2)
                better_cost = 3 + params.literalbits;
            else if((params.offsconstmask & 1) && source[a] == ((source[a-1]+1)&0xFF))
                better_cost = 3 + params.literalbits;
            else if((params.offsconstmask & 2) && source[a] == ((source[a-1]-1)&0xFF))
                better_cost = 3 + params.literalbits;
            else if((params.offsconstmask & 4) && source[a] == ((source[a-1]+2)&0xFF))
                better_cost = 3 + params.literalbits;
            else
                for(size_t offset = 1; a >= offset && offset <= params.MaxLiteralOffset(); ++offset)
                    if(source[a] == source[a-offset])
                        { better_cost = 3 + params.literalbits; break; }
            DefaultCost[a] = std::min(default_cost, better_cost);

            size_t limit = endpos - a;
            size_t longest = 1, where = 0;
            for(size_t test = a-std::min(a,MaxDistance); test<a; ++test)
            {
                size_t matchlen = TestMatch(source, test,a, limit);
                if(matchlen > longest)
                {
                    longest = matchlen;
                    where   = test;
                }
            }
            MaxMatchLen[a].first  = longest;
            MaxMatchLen[a].second = where;
        }
        if(!params.useliteraltable)
        {
            static const char* const MagicWords[] =
            {
                "bisqwit"/*, "Joel Yliluoma"*/, "Joel", "Yliluoma"
            };
            for(unsigned tokenno=0; tokenno < sizeof(MagicWords)/sizeof(*MagicWords); ++tokenno)
            {
                const char* const token = MagicWords[tokenno];
                const size_t token_size = strlen(token);

                size_t begin = 0;
                while(begin + token_size <= source.size())
                {
                    void* p = memmem( &source[begin], source.size()-begin,
                                      token, token_size);
                    if(!p) break;
                    size_t found_pos = (const unsigned char*)p - &source[0];
                    for(unsigned a=0; a<token_size; ++a)
                    {
                        MaxMatchLen[found_pos + a].first = 1;
                        bomb[found_pos + a] = true;
                        DefaultCost[found_pos + a] = 9;
                    }
                    begin = found_pos + token_size;
                }
            }

            // Update match-cache for bombs
            for(size_t a=0; a<endpos; ++a)
            {
                size_t limit = endpos-a;
                for(size_t test=0; test<a; ++test)
                {
                    size_t len = TestMatch(source, a,test, limit);
                    for(size_t p=0; p<len; ++p)
                    {
                        if(bomb[test+p])
                        {
                            MatchCache[a * endpos + test] = p;
                            break;
                        }
                    }
                }
            }
        }
    }

    unsigned DetermineDecision(const std::vector<unsigned char>& source,
                               size_t a,
                               size_t test_last/* = ~size_t(0)*/,
                               unsigned recursion_limit,unsigned max_recursion,
                               const EncodingParams& params)
    {
        const size_t endpos  = source.size();

        unsigned total_cost = 0;

        // Determine decision
        size_t make_fast_when = std::min((a+endpos) / 2, a + 64);
        unsigned n_actions = 0;
        while(a < endpos)
        {
            if(recursion_limit == 2 && max_recursion==3 && (a >= make_fast_when || ++n_actions >= 2))
                recursion_limit -= 1;
            if(recursion_limit == 1 && (a >= make_fast_when || ++n_actions >= 20))
                recursion_limit -= 1;

            unsigned best_cost   = 0;
            unsigned my_cost     = 0;
            size_t   best_eat    = MaxMatchLen[a].first;
            size_t   best_source = MaxMatchLen[a].second;

            if(!recursion_limit)
            {
                // Simply take predefine maximum (be greedy)
                my_cost = Cost(a - MaxMatchLen[a].second,
                               MaxMatchLen[a].first,
                               test_last,
                               DefaultCost[a]);
            }
            else
            {
              #ifdef qq_OPENMP
                omp_lock_t lock;
                omp_init_lock(&lock);
               #pragma omp parallel for \
                    schedule(guided) \
                    default(none) \
                    shared(best_cost,best_eat,best_source,my_cost,source,lock,DoVerySlow,params) \
                    firstprivate(a,recursion_limit,max_recursion,test_last)
              #endif
                for(size_t eating_count = best_eat; eating_count >= 1; --eating_count)
                {
                    if(eating_count < 2)
                    {
                        size_t cheapest_source = MaxMatchLen[a].second;
                        unsigned cheapest_cost = DefaultCost[a];

                        unsigned trailing_cost = cheapest_cost + DetermineDecision(
                            source,
                            a + eating_count,
                            eating_count >= 2 && params.appends ? a-cheapest_source : test_last,
                            recursion_limit - 1, max_recursion, params);

                      #ifdef qq_OPENMP
                        omp_set_lock(&lock);
                       #pragma omp flush(best_cost,best_eat,best_source,my_cost)
                      #endif
                        if(!best_cost || trailing_cost < best_cost)
                        {
                            best_cost   = trailing_cost;
                            best_eat    = eating_count;
                            best_source = cheapest_source;
                            my_cost     = cheapest_cost;
                        }
                      #ifdef qq_OPENMP
                       #pragma omp flush(best_cost,best_eat,best_source,my_cost)
                        omp_unset_lock(&lock);
                      #endif
                    }
                    else if(DoVerySlow
                       && recursion_limit <= 3
                       && eating_count >= 1u << (1u<<recursion_limit)/*
                       && eating_count >= best_eat / 2*/)
                    {
                        for(size_t test=a - std::min(a,MaxDistance); test<a; ++test)
                        {
                            if(TestMatch(source, test,a, eating_count) >= eating_count)
                            {
                                /*for(size_t p=0; p<eating_count; ++p)
                                    if(bomb[test+p]) goto discard_match;*/

                                size_t cheapest_source = test;
                                unsigned cheapest_cost = Cost(a-test, eating_count, test_last, DefaultCost[a]);

                                unsigned trailing_cost = cheapest_cost + DetermineDecision(
                                    source,
                                    a + eating_count,
                                    eating_count >= 2 && params.appends ? a-cheapest_source : test_last,
                                    recursion_limit - 1, max_recursion, params);

                              #ifdef qq_OPENMP
                                omp_set_lock(&lock);
                               #pragma omp flush(best_cost,best_eat,best_source,my_cost)
                              #endif
                                if(!best_cost || trailing_cost < best_cost)
                                {
                                    best_cost   = trailing_cost;
                                    best_eat    = eating_count;
                                    best_source = cheapest_source;
                                    my_cost     = cheapest_cost;
                                }
                              #ifdef qq_OPENMP
                               #pragma omp flush(best_cost,best_eat,best_source,my_cost)
                                omp_unset_lock(&lock);
                              #endif
                            }
                        }
                    }
                    else
                    {
                        size_t cheapest_source = 0;
                        unsigned cheapest_cost = 0;
                        for(size_t test=a - std::min(a,MaxDistance); test<a; ++test)
                            if(TestMatch(source, test,a, eating_count) >= eating_count)
                            {
                                /*for(size_t p=0; p<eating_count; ++p)
                                    if(bomb[test+p]) goto discard_match;*/

                                unsigned cost = Cost(a-test, eating_count, test_last, DefaultCost[a]);
                                if(!cheapest_cost || cost < cheapest_cost)
                                {
                                    cheapest_cost   = cost;
                                    cheapest_source = test;
                                }
                            }

                        unsigned trailing_cost = cheapest_cost + DetermineDecision(
                            source,
                            a + eating_count,
                            eating_count >= 2 && params.appends ? a-cheapest_source : test_last,
                            recursion_limit - 1, max_recursion, params);

                      #ifdef qq_OPENMP
                        omp_set_lock(&lock);
                       #pragma omp flush(best_cost,best_eat,best_source,my_cost)
                      #endif
                        if(!best_cost || trailing_cost < best_cost)
                        {
                            best_cost   = trailing_cost;
                            best_eat    = eating_count;
                            best_source = cheapest_source;
                            my_cost     = cheapest_cost;
                        }
                      #ifdef qq_OPENMP
                       #pragma omp flush(best_cost,best_eat,best_source,my_cost)
                        omp_unset_lock(&lock);
                      #endif
                    }
                }
              #ifdef qq_OPENMP
                omp_destroy_lock(&lock);
              #endif
            }

            Decisions[a].first  = best_eat;
            Decisions[a].second = best_source;
            if(best_eat >= 2 && params.appends) test_last = a - best_source;
            a          += best_eat;
            total_cost += my_cost;
        }

        if(params.useliteraltable)
        {
            // Create literal table
            bool used[256] = { false };
            unsigned NumLit = 0;
            for(size_t p=0; p<endpos; ++p)
            {
                const size_t copy_length = Decisions[p].first;
                if(copy_length >= 2) { p += copy_length-1; continue; }
                if(!used[source[p]]) { used[source[p]] = true; ++NumLit; }
            }
            total_cost += NumLit * 8;
        }
        return total_cost;
    }
public:
    void Compress(
        const std::vector<unsigned char>& source,
        unsigned max_recursion,
        const EncodingParams& params)
    {
        const size_t endpos  = source.size();

        AnalyzeSource(source, params);

        DetermineDecision(source,
            params.useliteraltable ? 0 : 1,
            ~size_t(0), max_recursion, max_recursion, params);

        // Encode the decision
        result.clear();
        BitsRemaining = 0;
        BitsPosition  = 0;
        size_t last_offset = 0;

        size_t readpos = 0;
        if(params.useliteraltable)
        {
            // Create literal table
            unsigned LiteralUsageTable[256] = { 0 }; // literal -> num times encoded
            for(size_t p=0; p<endpos; ++p)
            {
                const size_t copy_length = Decisions[p].first;
                if(copy_length >= 2) { p += copy_length-1; continue; }
                LiteralUsageTable[ source[p] ] += 1;
            }
            CreateAuxLiteralTables(LiteralUsageTable);
            // Progressively reduce the literal table, dropping elements
            // that are never references. At each round, more elements
            // may become available because the indices get smaller.
            for(;;)
            {
                bool used[256] = { false };

                for(size_t p=0; p<endpos; ++p)
                {
                    const size_t copy_length = Decisions[p].first;
                    if(copy_length >= 2) { p += copy_length-1; continue; }
                    unsigned char byte = source[p];
                    unsigned default_cost = 1 + GammaScore( LiteralIndices[ byte ] + 2);
                    if(3 + params.literalbits < default_cost)
                    {
                        bool maybe_bytecopy = false;
                        if(byte == params.constbyte
                        || byte == params.constbyte2
                        || ((params.offsconstmask & 1) && byte == ((source[p-1]+1)&0xFF))
                        || ((params.offsconstmask & 2) && byte == ((source[p-1]-1)&0xFF))
                        || ((params.offsconstmask & 4) && byte == ((source[p-1]+2)&0xFF))
                          )
                            maybe_bytecopy = true;
                        else if(!bomb[p])
                        {
                            for(size_t o=1; p>=o && o<=params.MaxLiteralOffset(); ++o)
                                if(byte == source[p-o])
                                    { maybe_bytecopy = true; break; }
                        }
                        if(maybe_bytecopy) continue;
                    }
                    used[byte] = true;
                }

                unsigned n = NumUsedLiterals;
                for(unsigned a=0; a<256; ++a)
                    if(!used[a])
                        LiteralUsageTable[ a] = 0;
                CreateAuxLiteralTables(LiteralUsageTable);
                if(n == NumUsedLiterals) break;
            }
        }
        else
        {
            result.push_back( source[readpos++] );
            NumUsedLiterals = 0;
        }

        while(readpos < endpos)
        {
            const size_t copy_length = Decisions[readpos].first;
            const size_t copy_begin  = Decisions[readpos].second;

            if(copy_length < 2)
            {
                unsigned char byte = source[readpos];
                unsigned default_cost = params.useliteraltable
                    ? 1 + GammaScore( LiteralIndices[ byte ] + 2)
                    : 9;

                /*fprintf(stderr, "[%u]: literal %02X\n", (unsigned)readpos, byte);*/
                if(3+params.literalbits > default_cost)
                    goto LiteralInAnycase;

                if(byte == params.constbyte)
                    SendByteCopy(params.LiteralIndex(), params.literalbits);
                else if(byte == params.constbyte2)
                    SendByteCopy(params.Literal2Index(), params.literalbits);
                else if((params.offsconstmask & 1) && byte == ((source[readpos-1]+1)&0xFF))
                    SendByteCopy(params.OffsConstPlusIndex(), params.literalbits);
                else if((params.offsconstmask & 2) && byte == ((source[readpos-1]-1)&0xFF))
                    SendByteCopy(params.OffsConstMinusIndex(), params.literalbits);
                else if((params.offsconstmask & 4) && byte == ((source[readpos-1]+2)&0xFF))
                    SendByteCopy(params.OffsConstPlusTwoIndex(), params.literalbits);
                else
                {
                    if(!bomb[readpos])
                    {
                        for(size_t offset = 1;
                            readpos >= offset && offset <= params.MaxLiteralOffset();
                            ++offset)
                        {
                            if(byte == source[readpos-offset])
                                { SendByteCopy( params.LiteralOffset(offset),
                                                params.literalbits);
                                  goto didbytecopy; } // Range: 1..15
                        }
                    }
                LiteralInAnycase:
                    if(params.useliteraltable)
                        SendGammaEncodedLiteral( LiteralIndices[byte] + 2);
                    else
                        SendLiteral(byte);
                didbytecopy:;
                }
                ++readpos;
                continue;
            }

            size_t my_offset = readpos - copy_begin;

            // Append is *always* better than LongMatch. (6 vs 11 bits)
            // ShortMatch is *always* better than LongMatch. (11 vs 12+ bits)
            if(my_offset == last_offset)
            {
                // Length: 2..N
                SendAppendMatch( copy_length, params ); // Range: 1..inf
            }
            else if(copy_length >= 2 && copy_length <= 3
                 && my_offset   >= 1 && my_offset <= 127)
            {
                // Range: 1..127, 2..3
                SendShortMatch( my_offset, copy_length );
            }
            else
            {
                // Length: M..N
                // where M is 1 for offset=80..4FF
                //            2 for offset=500..7CFF
                //            3 for others
                if(my_offset < 0x80) assert(copy_length >= 4);
                else                 assert(copy_length >= 2);
                assert(copy_length < 0x100);
                assert(my_offset   >= 1);
                SendLongMatch( my_offset, copy_length, params );
            }
            if(params.appends) last_offset = my_offset;
            readpos += copy_length;
        }
        SendEnd();
    }
    void Uncompress(
        const std::vector<unsigned char>& source,
        const EncodingParams& params,
        const unsigned char* LiteralTable)
    {
        unsigned tagpos=0, tag=0;
        size_t inpos = 0;

        #define GetBit() \
           ( ( (tagpos%8 ? (tag                  ) << (tagpos++ % 8) \
                         : (tag = source[inpos++]) << (tagpos++ % 8) \
               ) & 0x80) >> 7)

        result.clear();
        size_t last_offs = 0;
    Literal:
        if(!params.useliteraltable)
        {
            result.push_back(source[inpos++]);
        }
        for(;;)
        {
            if(! GetBit() )
            {
                if(!params.useliteraltable)
                {
                    goto Literal; // 0, literal
                }
                // 0, gamma-encoded literal
                unsigned bh = 1; do bh = bh*2 + GetBit(); while( GetBit() );
                unsigned char byte = LiteralTable[bh - 2];
                result.push_back(byte);
                continue;
            }
            if(! GetBit() ) // 10, codepair
            {
                unsigned bh = 1; do bh = bh*2 + GetBit(); while( GetBit() );
                unsigned cx = 1; do cx = cx*2 + GetBit(); while( GetBit() );
                unsigned o = params.appends ? 3 : 2;
                if(bh >= o) // offshi=2, append; otherwise, offslo
                {
                    unsigned bx = ((bh - o) << 8) | source[inpos++];
                    if(bx <= 0x7F) cx += 2;
                    last_offs = bx;
                }
                do result.push_back( result[result.size() - last_offs] );
                while(--cx > 0);
            }
            else if(! GetBit() ) // 110, bytecopy
            {
                unsigned bx = 0;
                for(unsigned bit = params.literalbits; bit-- > 0; )
                    bx |= GetBit() << bit;
                if(params.offsconstmask & 1)
                {
                    if(!bx) { result.push_back( (result.back()+1) & 0xFF ); continue; }
                    --bx;
                }
                if(params.offsconstmask & 2)
                {
                    if(!bx) { result.push_back( (result.back()-1) & 0xFF ); continue; }
                    --bx;
                }
                if(params.offsconstmask & 4)
                {
                    if(!bx) { result.push_back( (result.back()+2) & 0xFF ); continue; }
                    --bx;
                }
                if(params.constbyte < 0100)
                {
                    if(!bx) { result.push_back(params.constbyte); continue; }
                    --bx;
                }
                if(params.constbyte2 < 0100)
                {
                    if(!bx) { result.push_back(params.constbyte2); continue; }
                    --bx;
                }
                ++bx;
                result.push_back( result[result.size() - bx] );
            }
            else // 111, shortmatch
            {
                unsigned bx = source[inpos++];
                unsigned cx = 3 - (bx & 1);
                last_offs = bx >> 1;
                if(!last_offs) break;
                do result.push_back( result[result.size() - last_offs] );
                while(--cx > 0);
            }
        }
        unsigned n_calls = params.n_calls;
        for(size_t a=0; a+3<=result.size() && n_calls > 0; ++a)
        {
            if(((params.call_mask & 1) && result[a] == 0xE8)
            || ((params.call_mask & 2) && result[a] == 0xE9))
            {
                ++a;
                unsigned offset = result[a] | (result[a+1] << 8);
                offset -= (a+0x100);
                result[a]   = offset & 0xFF;
                result[a+1] = offset >> 8;
                --n_calls;
                ++a;
            }
        }
        if(n_calls)
            fprintf(stderr, "%u calls were not found\n", n_calls);
    }
private:
    // Primitives:
    void PrimSendByte(unsigned char value)
    {
        result.push_back(value);
    }
    void PrimSendBit(unsigned char bit)
    {
        if(!BitsRemaining)
            { BitsPosition = result.size();
              PrimSendByte(0x00);
              BitsRemaining = 8; }
        result[BitsPosition] |= bit << --BitsRemaining;
        /*fprintf(stderr, "sending bit: %02X -- tag@%u is now %02X\n", bit, BitsPosition,result[BitsPosition]);*/
    }
    void PrimSendGamma(unsigned value) // The smallest value it can encode is 2.
    {
        unsigned origvalue = value;
        assert(value >= 2);
        unsigned n_bits_sent = 0;
        unsigned highest_bit = 0x80000000u;
        while(highest_bit != 0
           && !(value & highest_bit))
            highest_bit >>= 1;
        if(value & highest_bit)
            highest_bit >>= 1;
        for(; ; PrimSendBit(1))
        {
            n_bits_sent += 2;
            PrimSendBit( !! ( value & highest_bit) );
            highest_bit >>= 1;
            if(!highest_bit) break;
        }
        PrimSendBit(0);

        if(GammaSummary.size() <= n_bits_sent) GammaSummary.resize(n_bits_sent+1);
        GammaSummary[n_bits_sent] += 1;
        if(GammaSummary2.size() <= origvalue) GammaSummary2.resize(origvalue+1);
        GammaSummary2[origvalue] += 1;
    }
public:
    // Actual encodes
    void SendLongMatch(
        unsigned offset,
            // Offset: 0..n
        unsigned len,
            // Len, if offset:
            //    0..7F:    3..any (1 + 2)
            //   80..FFFF:  1..any (1 + 0)
        const EncodingParams& params
    )
    {
        /*fprintf(stderr, "Sending long match: %u %u\n", offset, len);*/
        PrimSendBit(1); PrimSendBit(0);
        unsigned tmp = offset + (params.appends ? 0x300 : 0x200);
        PrimSendGamma(tmp >> 8);
        if(offset <= 127) len -= 2;
        PrimSendGamma(len);
        PrimSendByte(tmp & 0xFF);
    }
    void SendAppendMatch(unsigned len, const EncodingParams& params)
    {
        assert(params.appends);
        /*fprintf(stderr, "Sending APPEND: %u\n", len);*/
        PrimSendBit(1);  PrimSendBit(0);
        PrimSendGamma(2);
        PrimSendGamma(len);
    }
    void SendShortMatch(unsigned offset/*1..127*/, unsigned len/*2..3*/)
    {
        /*fprintf(stderr, "Sending short match: %u %u\n", offset, len);*/
        PrimSendBit(1); PrimSendBit(1); PrimSendBit(1);
        PrimSendByte( (3-len) | (offset << 1) );
    }
    void SendByteCopy(unsigned offset/*1..15*/, unsigned LiteralOffsetBits)
    {
        /*fprintf(stderr, "Sending byte copy: %u\n", offset);*/
        PrimSendBit(1); PrimSendBit(1); PrimSendBit(0);
        for(unsigned bit = LiteralOffsetBits; bit-- > 0; )
            PrimSendBit( (offset >> bit) & 1 );
    }
    void SendGammaEncodedLiteral(unsigned table_index)
    {
        PrimSendBit(0);
        PrimSendGamma(table_index);
    }
    void SendLiteral(unsigned char literal)
    {
        /*fprintf(stderr, "Sending literal: %02X\n", literal);*/
        PrimSendBit(0);
        PrimSendByte(literal);
    }
    void SendEnd()
    {
        //PrimSendBit(1); PrimSendBit(0); PrimSendGamma(0x100);
        // ^ 16 bits
        SendShortMatch(0, 2); // 11 bits
    }
};

std::vector<unsigned char> GetAsm(const EncodingParams& params,
    unsigned NumLiterals=0, const unsigned char* LiteralTable=0)
{
    std::vector<unsigned char> result;

  #pragma omp critical(asmlock)
  {
    char tempfn1[64], tempfn2[64];
    std::sprintf(tempfn1, "apack-%d.tm1", getpid());
    std::sprintf(tempfn2, "apack-%d.tm2", getpid());

    FILE* fp = std::fopen(tempfn1, "wt");
    std::fprintf(fp,
"bits 16\n"
"STUB_LENGTH equ 0xD ; (end_stub-begin_stub)\n"
"org 0x7F80 - STUB_LENGTH ; 7F80*2 = FF00; -FF00 = 100. This is why 7F80.\n"
"calls             equ %d\n"
"constbyte         equ 0x%X\n"
"constbyte2        equ 0x%X\n"
"callmask          equ %d\n"
"appends           equ %d\n"
"literaloffsetbits equ 0x%X\n"
"offsconstmask     equ %u\n"
"useliteraltable   equ %u\n"
"literaltable_length equ %u\n"
"\n"
"	begin_stub:\n"
"		mov si,0x100 + STUB_LENGTH\n"
"		mov di,DECOMPRESS\n"
"		mov cx,di\n"
"		cld\n"
"		push di\n"
"		rep movsb\n"
"		ret\n"
"	end_stub:\n"
"DECOMPRESS:\n"
"		neg di ;mov di,0x100\n"
"		push di ; This is the return address to program's start\n"
"	%%if calls <> 0 && callmask <> 0\n"
"		push di ; This is the begin address for calls and jumps conversion\n"
"	%%endif\n"
"		mov si, DATABEGIN\n"
"		mov dl,0x80\n"
"		mov bp, GETBIT\n"
"	%%if appends\n"
"		push ax\n"
"	%%endif\n"
"	%%if useliteraltable=0\n"
"LITERAL:\n"
"		movsb\n"
"	%%endif\n"
"NEXTTAG:\n"
"	%%if useliteraltable=1\n"
"		inc cx\n"
"	%%endif\n"
"		call bp\n"
"		jnc LITERAL\n"
"		call bp\n"
"	%%if useliteraltable=0\n"
"		inc cx\n"
"	%%endif\n"
"		jnc CODEPAIR\n"
"		call bp\n"
"		mov ax, 0x100 >> literaloffsetbits\n"
"		jc SHORTMATCH\n"
"	.fourbits:\n"
"		 call bp\n"
"		 adc al,al\n"
"		jnc .fourbits\n"
"\n"
"	%%if (offsconstmask & 1)\n"
"		%%if ((offsconstmask & (2+4)) || constbyte < 0x100 || constbyte2 < 0x100)\n"
"			jz .offsconst_plus\n"
"			dec ax\n"
"		%%else\n"
"			jnz DOMATCH_AX\n"
"			%%define did_matchjump\n"
"		%%endif\n"
"	%%endif\n"
"	%%if (offsconstmask & 2)\n"
"		%%if ((offsconstmask & (4)) || constbyte < 0x100 || constbyte2 < 0x100)\n"
"			jz .offsconst_minus\n"
"			dec ax\n"
"		%%else\n"
"			jnz DOMATCH_AX\n"
"			%%define did_matchjump\n"
"		%%endif\n"
"	%%endif\n"
"	%%if (offsconstmask & 4)\n"
"		%%if (constbyte < 0x100 || constbyte2 < 0x100)\n"
"			jz .offsconst_plustwo\n"
"			dec ax\n"
"		%%else\n"
"			jnz DOMATCH_AX\n"
"			%%define did_matchjump\n"
"		%%endif\n"
"	%%endif\n"
"	%%if(constbyte < 0x100)\n"
"		%%if(constbyte == 0x00)\n"
"			jz STORE\n"
"		%%elif(constbyte == 0x01 && (offsconstmask & 1))\n"
"			jz .inc_one_store\n"
"		%%elif(constbyte == 0xFF && (offsconstmask & 2))\n"
"			jz .dec_one_store\n"
"		%%elif(constbyte == 0x02 && (offsconstmask & 4))\n"
"			jz .inc_two_store\n"
"		%%else\n"
"			%%if(constbyte2 < 0x100)\n"
"				jz .constbyte\n"
"			%%else\n"
"				jnz DOMATCH_AX\n"
"				%%define did_matchjump\n"
"			%%endif\n"
"			%%define constbyte_needed\n"
"		%%endif\n"
"		%%if (constbyte2 < 0x100)\n"
"			dec ax\n"
"		%%endif\n"
"	%%endif\n"
"	%%if(constbyte2 < 0x100)\n"
"		%%if(constbyte2 == 0x00)\n"
"			jz STORE\n"
"		%%elif(constbyte2 == 0x01 && (offsconstmask & 1))\n"
"			jz .inc_one_store\n"
"		%%elif(constbyte2 == 0xFF && (offsconstmask & 2))\n"
"			jz .dec_one_store\n"
"		%%elif(constbyte2 == 0x02 && (offsconstmask & 4))\n"
"			jz .inc_two_store\n"
"		%%else\n"
"			;jz .constbyte2\n"
"			jnz DOMATCH_AX\n"
"			%%define did_matchjump\n"
"			%%define constbyte2_needed\n"
"		%%endif\n"
"	%%endif\n"
"	%%if(offsconstmask == 0 && constbyte == 0x100 && constbyte2 == 0x100)\n"
"			inc ax ; No literal support, so increase offset range from 0..15 to 1..16\n"
"	%%endif\n"
"	%%ifndef did_matchjump\n"
"			jmp DOMATCH_AX\n"
"	%%endif\n"
"	%%ifdef constbyte2_needed\n"
"	.constbyte2:\n"
"		; At this point, ax is known to be zero.\n"
"		%%if constbyte2 == 1\n"
"			inc ax\n"
"			jmp STORE\n"
"		%%elif constbyte2 == 0xFF\n"
"			dec ax\n"
"			jmp STORE\n"
"		%%elif constbyte2 == 2 && (offsconstmask & 1)\n"
"			inc ax\n"
"			jmp short .inc_one_store ; This is 3 bytes in total, whereas mov al;jmp would be 4.\n"
"		%%elif constbyte2 == 0xFE && (offsconstmask & 2)\n"
"			dec ax\n"
"			jmp short .dec_one_store ; Similar rationale as above.\n"
"		%%else\n"
"			mov al, constbyte2 ; 2 bytes opcode\n"
"			jmp STORE\n"
"		%%endif\n"
"	%%endif\n"
"	%%ifdef constbyte_needed\n"
"	.constbyte:\n"
"		; At this point, ax is known to be zero.\n"
"		%%if constbyte == 1\n"
"			inc ax\n"
"			jmp STORE\n"
"		%%elif constbyte == 0xFF\n"
"			dec ax\n"
"			jmp STORE\n"
"		%%elif constbyte == 2 && (offsconstmask & 1)\n"
"			inc ax\n"
"			jmp short .inc_one_store ; This is 3 bytes in total, whereas mov al;jmp would be 4.\n"
"		%%elif constbyte == 0xFE && (offsconstmask & 2)\n"
"			dec ax\n"
"			jmp short .dec_one_store ; Similar rationale as above.\n"
"		%%else\n"
"			mov al, constbyte ; 2 bytes opcode\n"
"			jmp STORE\n"
"		%%endif\n"
"	%%endif\n"
"	%%if offsconstmask & 4\n"
"	.offsconst_plustwo:\n"
"			mov al, [di-1]\n"
"	.inc_two_store:\n"
"			inc ax\n"
"	.inc_one_store:\n"
"			inc ax\n"
"			jmp STORE\n"
"	%%endif\n"
"	%%if offsconstmask & 2\n"
"	.offsconst_minus:\n"
"			mov al, [di-1] ; Surprisingly this is just 3 bytes.\n"
"	.dec_one_store:\n"
"			dec ax\n"
"			jmp STORE\n"
"	%%endif\n"
"	%%if offsconstmask & 1\n"
"	.offsconst_plus:\n"
"			mov al, [di-1]\n"
"		%%if offsconstmask & 4\n"
"			jmp .inc_one_store\n"
"		%%else\n"
"	.inc_one_store:\n"
"			inc ax\n"
"			jmp STORE\n"
"		%%endif\n"
"	%%endif\n"
"CODEPAIR:\n"
"		mov ah,cl ; = 1\n"
"	.bhloop:\n"
"		call bp\n"
"		adc ah,ah\n"
"		call bp\n"
"		jc .bhloop\n"
"	.cxloop:\n"
"		call bp\n"
"		adc cx,cx\n"
"		call bp\n"
"		jc .cxloop\n"
"	%%if appends\n"
"		sub ah, 3\n"
"		jc DOMATCH_LASTPOS\n"
"	%%else\n"
"	 	sub ah, 2\n"
"	%%endif\n"
"SHORTMATCH:\n"
"		lodsb\n"
"		jnc .waslong\n"
"		 shr al,1\n"
"		 jz OVER\n"
"		 sbb cl,ah\n"
"	.waslong:\n"
"		cmp ax,0x7F\n"
"		ja .long_offs\n"
"		 inc cx\n"
"		 inc cx\n"
"	.long_offs:\n"
"DOMATCH_NEWLASTPOS:\n"
"	%%if appends\n"
"		pop bx ;i.e. discard old lastpos\n"
"		db 0xA8 ; test al, <byte>\n"
"DOMATCH_LASTPOS:\n"
"		pop ax ;restore old lastpos\n"
"		push ax ;save lastpos\n"
"	%%endif\n"
"DOMATCH_AX:\n"
"		neg ax\n"
"		xchg ax,bx\n"
"COPYLOOP:\n"
"		mov al,[bx+di]\n"
"STORE:\n"
"		stosb\n"
"		loop COPYLOOP\n"
"		jmp short NEXTTAG\n"
"	%%if useliteraltable=1\n"
"LITERAL:\n"
"		mov bx,cx\n"
"	.blloop:\n"
"		call bp\n"
"		adc bx,bx\n"
"		call bp\n"
"		jc .blloop\n"
"		mov al,[bx+LITERALTABLE-2]\n"
"		jmp STORE\n"
"	%%endif\n"
"GETBIT:\n"
"		add dl,dl\n"
"		jnz .getbitret\n"
"		mov dl,[si]\n"
"		inc si\n"
"		adc dl,dl\n"
"	.getbitret:\n"
"	%%if (calls <> 0 && callmask <> 0) || appends\n"
"		ret\n"
"	%%endif\n"
"OVER:\n"
"	%%if appends\n"
"		pop ax\n"
"	%%endif\n"
"	%%if calls <> 0 && callmask <> 0\n"
"	 	pop si\n"
"	 .findcalls:\n"
"	%%if calls >= 0x100\n"
"		mov cx, calls\n"
"	%%else\n"
"	 	mov cl, calls\n"
"	%%endif\n"
"	 .findcall:\n"
"	 	lodsb\n"
"	%%if callmask = 3\n"
"		and al,0xFE\n"
"	%%endif\n"
"	%%if callmask = 2\n"
"	 	cmp al, 0xE9\n"
"	%%else\n"
"	 	cmp al, 0xE8\n"
"	%%endif\n"
"	 	jnz .findcall\n"
"	 	sub [si],si\n"
"	 	lodsw\n"
"	 	loop .findcall\n"
"	%%endif ;calls <> 0 && callmask <> 0\n"
"	 	ret\n"
"LITERALTABLE:\n"
"	 	times literaltable_length db 0\n"
"DATABEGIN:\n",
        params.n_calls,
        params.constbyte,
        params.constbyte2,
        params.call_mask,
        params.appends ? 1u : 0u,
        params.literalbits,
        params.offsconstmask,
        params.useliteraltable, NumLiterals);
    std::fclose(fp);

    char command[512];
    std::sprintf(command, "nasm -w+all -O2 %1$s -o %2$s", tempfn1,tempfn2);
    system(command);

    fp = std::fopen(tempfn2, "rb");
    std::fseek(fp, 0, SEEK_END);
    result.resize( ftell(fp) );
    std::rewind(fp);
    std::fread(&result[0], 1, result.size(), fp);
    std::fclose(fp);
    std::remove(tempfn1);
    std::remove(tempfn2);
  }
    if(NumLiterals)
        std::memcpy(&result[result.size() - NumLiterals], LiteralTable, NumLiterals);
    return result;
}

int main()
{
    std::vector<unsigned char> buffer_orig;
    for(;;)
    {
        size_t end = buffer_orig.size();
        buffer_orig.resize(end + 4096);
        size_t n = std::fread(&buffer_orig[end], 1, 4096, stdin);
        buffer_orig.resize(end + n);
        if(n == 0) break;
    }

    DoVerySlow = false;

    unsigned n_calls_found = 0;
    unsigned n_jumps_found = 0;

    for(size_t a=0; a+3<=buffer_orig.size(); ++a)
    {
        if(buffer_orig[a] == 0xE8)
        {
            ++n_calls_found;
            a += 2;
        }
        else if(buffer_orig[a] == 0xE9)
        {
            ++n_jumps_found;
            a += 2;
        }
    }

    EncodingParams params = {0,0,0x00,0x00,4,true, 0, true};
    Apack          best_packer;
    size_t         best_asm_skip = 0;
    std::vector<unsigned char> best_buffer;

  #ifdef _OPENMP
    omp_set_nested(0);
  #endif

    //fprintf(stderr, "Translated %u calls\n", n_calls_translated);
 #pragma omp parallel for schedule(dynamic,1)
    for(unsigned progress = 0; progress < 8*0x101*0x101*4*4*2*2; ++progress)
    {
        unsigned tv = progress;
        EncodingParams test_params;
        test_params.offsconstmask = tv%8; tv/=8;
        test_params.constbyte   = tv%0x101; tv/=0x101;
        test_params.constbyte2  = tv%0x101; tv/=0x101;
        test_params.call_mask   = tv%4;     tv/=4;
        test_params.literalbits = tv%4+2;   tv/=4;
        test_params.appends     = tv%2;     tv/=2;
        test_params.useliteraltable = 1-tv%2;  tv/=2;
        test_params.n_calls = 0;

        if(test_params.constbyte == 0x100
        && test_params.constbyte2 != 0x100)
            continue;
        if(test_params.constbyte != 0x100
        && test_params.constbyte2 <= test_params.constbyte)
            continue;

        if(test_params.call_mask != 1) continue;
        if(test_params.appends == false) continue;
        //if(test_params.literalbits == 5) continue;
        if(test_params.literalbits != 3) continue;
        if(test_params.useliteraltable) continue;
        //if(!(test_params.offsconstmask & 1)) continue;
        if(test_params.offsconstmask != 0) continue;

        bool byte1ok = test_params.constbyte == 0x00/*
                    || test_params.constbyte == 0x01
                    || test_params.constbyte == 0x02
                    || test_params.constbyte == 0x0E
                    || test_params.constbyte == 0x0F
                    || test_params.constbyte == 0x10
                    || test_params.constbyte == 0xFE
                    || test_params.constbyte == 0xFF
                    || test_params.constbyte == 0x100*/;
        bool byte2ok = /*test_params.constbyte2 == 0x00
                    || test_params.constbyte2 == 0x01
                    || test_params.constbyte2 == 0x02
                    || test_params.constbyte2 == 0x0E
                    || test_params.constbyte2 == 0x0F
                    || test_params.constbyte2 == 0x10
                    || test_params.constbyte2 == 0xFE
                    || test_params.constbyte2 == 0xFF
                    || */test_params.constbyte2 == 0x100;
        if(!byte1ok || !byte2ok) continue;
        /*
        if(test_params.constbyte >= 0x10
        && test_params.constbyte != 0xFF
        && test_params.constbyte != 0x100) continue; // artificial speedup...
        */

                                ////////////
        std::vector<unsigned char> buffer(buffer_orig);
        for(size_t a=0; a+3<=buffer.size(); ++a)
        {
            if(((test_params.call_mask & 1) && buffer[a] == 0xE8)
            || ((test_params.call_mask & 2) && buffer[a] == 0xE9))
            {
                ++a;
                unsigned offset = buffer[a] | (buffer[a+1] << 8);
                offset += (a+0x100);
                buffer[a]   = offset & 0xFF;
                buffer[a+1] = offset >> 8;
                ++a;
                ++test_params.n_calls;
            }
        }

        std::fprintf(stderr, "Trying constbyte=%02X:%02X,literal=%d,callmask=%u(%u calls),appends=%u,offsconst=%u,table=%u(%u) ...\n",
            test_params.constbyte, test_params.constbyte2,
            test_params.literalbits,
            test_params.call_mask,
            test_params.n_calls,
            test_params.appends,
            test_params.offsconstmask,
            test_params.useliteraltable, 0);
        std::fflush(stderr);

        Apack packer;
        packer.Compress(buffer, 3, test_params);
        std::vector<unsigned char> stub = GetAsm(test_params,
            packer.NumUsedLiterals, packer.LiteralsInOrderOfCommonness);
        packer.result.insert(packer.result.begin(), stub.begin(), stub.end());

      #pragma omp critical
      {
        #pragma omp flush(params,best_packer,best_asm_skip,best_buffer)
        unsigned res_size  = best_packer.result.size();
        unsigned test_size = packer.result.size();

        if(!res_size || test_size < res_size)
        {
            std::fprintf(stderr, "%u+%u=%u bytes for constbyte=%02X:%02X,literal=%d,callmask=%u(%u calls),appends=%u,offsconst=%u,table=%u(%u)\n",
                (unsigned) (test_size - stub.size()),
                (unsigned) stub.size(),
                (unsigned) test_size,
                test_params.constbyte, test_params.constbyte2,
                test_params.literalbits,
                test_params.call_mask,
                test_params.n_calls,
                test_params.appends,
                test_params.offsconstmask,
                test_params.useliteraltable, packer.NumUsedLiterals);
            std::fflush(stderr);

            best_packer = packer;
            params      = test_params;
            best_asm_skip = stub.size();
            best_buffer.swap(buffer);

            std::fwrite(&best_packer.result[0], 1, best_packer.result.size(), stdout);
            ftruncate(1, best_packer.result.size());
            std::rewind(stdout);
        }
        #pragma omp flush(params,best_packer,best_asm_skip,best_buffer)
      }
    }

    if(buffer_orig.size() < 2000)
    {
        fprintf(stderr, "Enabling DoVerySlow mode... (single-thread only, sorry)\n");
        DoVerySlow = true;
        best_packer = Apack();
        best_packer.Compress(best_buffer, 3, params);
        std::vector<unsigned char> stub = GetAsm(params,
            best_packer.NumUsedLiterals, best_packer.LiteralsInOrderOfCommonness);
        best_packer.result.insert(best_packer.result.begin(), stub.begin(), stub.end());

        size_t best_size = best_packer.result.size();
        fprintf(stderr, "%u+%u=%u bytes after enabling DoVerySlow mode\n",
            (unsigned) (best_size - stub.size()),
            (unsigned) stub.size(),
            (unsigned) best_size);
    }

    std::fwrite(&best_packer.result[0], 1, best_packer.result.size(), stdout);

#if 1
    Apack unpacker;
    std::vector<unsigned char> dataonly(best_packer.result);
    dataonly.erase(dataonly.begin(), dataonly.begin() + best_asm_skip);
    unpacker.Uncompress(dataonly, params, best_packer.LiteralsInOrderOfCommonness);

    std::vector<unsigned char> decompress( unpacker.result);

    bool ok = true;
    unsigned r = decompress.size();

    if(buffer_orig.size() != r) ok = false;

    for(size_t a=0; a<best_packer.GammaSummary.size(); ++a)
        if(best_packer.GammaSummary[a])
        {
            unsigned min = 1 << a/2;
            unsigned max = min*2 - 1;
            fprintf(stderr, "Sent gamma sequences that encode in %u bits: %u (range: %u..%u)\n",
                (unsigned) a, (unsigned) best_packer.GammaSummary[a],
                min, max
            );
            // 2 bits: 10,11
            // 4 bits: 100,101,110,111,
            // 6 bits: 1000,1001,1010,1011,1100,1101,1110,1111
            for(unsigned m=min; m<=max && m<best_packer.GammaSummary2.size(); ++m)
                if(best_packer.GammaSummary2[m])
                    fprintf(stderr, "[%3u]: %u\n", (unsigned) m, best_packer.GammaSummary2[m]);
        }

    unsigned nmismatch=0, firstfail=~0u, lastfail=~0u;
    for(unsigned a=0; a<r; ++a)
        if(buffer_orig[a] != decompress[a])
        {
            ++nmismatch;
            if(firstfail==~0u) firstfail=a;
            lastfail=a;
        }
    if(nmismatch)
    {
        ok = false;
        fprintf(stderr, "%u failures, within %u..%u range (total size: %u)\n",
            nmismatch,firstfail,lastfail, r);
    }
    if(!ok) fprintf(stderr, "= ERROR\n");
#endif

    return 0;
}
