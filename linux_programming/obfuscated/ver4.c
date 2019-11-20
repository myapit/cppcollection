#include <sys/time.h>
#include <stdio.h>
int main(void) /* revision 4 */
{
    static const char* const words[] = {"morning","day","afternoon","evening","night"};
    static const char per_hour[24+1] = "444400000000111222333344";
    time_t t = time(NULL);
    struct tm* tm = localtime(&t);
    return printf("Good %s!\n", words[ per_hour[ tm->tm_hour ] - '0' ] );
}
