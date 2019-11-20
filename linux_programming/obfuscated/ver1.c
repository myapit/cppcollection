#include <sys/time.h>
#include <stdio.h>
int main(void)
{
    time_t t;
    struct tm* tm;

    t = time(NULL); /* Get current time in seconds */
    tm = localtime(&t); /* Transform a timestamp to broken-down time, relative to user's timezone */

    switch(tm->tm_hour) /* Choose action from the hour value */
    {
        case 4:case 5:case 6:case 7:
        case 8:case 9:case 10:case 11:
            printf("Good morning!\n");
            break;
        case 12:case 13:case 14:
            printf("Good day!\n");
            break;
        case 15:case 16:case 17:
            printf("Good afternoon!\n");
            break;
        case 18:case 19:case 20:case 21:
            printf("Good evening!\n");
            break;
        default:
            printf("Good night!\n");
            break;
    }
    return 0;
}
