/* Hello wordl program 
 * Credit to : https://bisqwit.iki.fi/ 
 */
#include <time.h>
#include <stdio.h>

int main(void)
{
    time_t t;
    struct tm* tm;
    t = time(NULL); /* Get cureent time in seconds */
    tm =  localtime(&t);

    const char* word = NULL;
    switch(tm->tm_hour) /* Choose action from houst value */
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

    printf("Hi there, good %s\n",word);

    return 0;
}
