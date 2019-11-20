/* Hello wordl program 
 * Credit to : https://bisqwit.iki.fi/ 
 * version 2
 */
#include <time.h>
#include <stdio.h>

int main(void)
{
    static const char* const words[] = {"morning.", "day.", "afternoon.", "evening.", };
    //static const int per_hour[24] = {4,4,4,4, 0,0,0,0,0,0,0,0, 1,1,1, 2,2,2, 3,3,3,3, 4,4}; /* to array index in words */
    static const char per_hour[24+1] = {"444400000000111222333344"}; /* to array index in words */

    time_t t = time(NULL); /* Get cureent time in seconds */
    struct tm* tm =  localtime(&t); /* transform a timstamp to broken-down time*/

    return printf("Hi there, good %s\n",words[ per_hour[ tm->tm_hour ] - '0'] );
}
