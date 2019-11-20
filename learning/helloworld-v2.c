/* Hello wordl program 
 * Credit to : https://bisqwit.iki.fi/ 
 * version 2
 */
#include <time.h>
#include <stdio.h>

int main(void)
{
    static const char* const words[] = {"morning.", "day.", "afternoon.", "evening.", };
    static const int per_hour[24] = {4,4,4,4, 0,0,0,0,0,0,0,0, 1,1,1, 2,2,2, 3,3,3,3, 4,4}; /* to array index in words */
    

    time_t t = time(NULL); /* Get cureent time in seconds */
    struct tm* tm =  localtime(&t);

    /*
    const char* word = NULL;
    switch(tm->tm_hour)
    {
        case 4:case 5: case 6: case 7:   
        case 8:case 9: case 10: case 11:
            word = "morning.";
            break;

        case 12:case 13: case 14:
            word = "day.";
            break;

        case 15:case 16:case 17:
            word = "afternoon.";
            break;

        case 18:case 19: case 20: case 21:
            word = "evening.";
            break;
        
       default:
            word = "night.";
            break;
    }
    */

    int greeting_index = per_hour[ tm->tm_hour];
    printf("Hi there, good %s\n",words[greeting_index]);

    return 0;
}
