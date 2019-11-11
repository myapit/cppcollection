/* Credit to : https://bisqwit.iki.fi/jutut/c_cpp/sort2.cc */
/* An example C++11 program that alphabetically sorts its input lines. */
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

int main()
{
    /* Declare an indexable container for strings. */
    std::vector<std::string> lines;

    /* While stdin is not EOF, read lines. */
    for(std::string s; std::getline(std::cin, s); )
    {
        /* Append it into the vector without making a temporary copy */
        lines.push_back(std::move(s));
    }

    /* Sort the vector */
    std::sort(lines.begin(), lines.end());

    /* Output the contents of the vector */
    for(const auto& s: lines)
        std::cout << s << std::endl;

    /* End. The vector will automatically dispose of itself
     * when it goes out of the scope (denoted by { and }.)
     */
    return 0;
}
