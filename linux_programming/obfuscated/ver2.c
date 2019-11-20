#include <sys/time.h>
#include <stdio.h>
int main(void) /* revision 2 */
{
    static const char* const words[] = {"morning","day","afternoon","evening","night"};
    static const int per_hour[24] = {4,4,4,4, 0,0,0,0,0,0,0,0, 1,1,1, 2,2,2, 3,3,3,3, 4,4};

    time_t t;
    struct tm* tm;
    int greeting_index;

    t = time(NULL);
    tm = localtime(&t);

    greeting_index = per_hour[ tm->tm_hour ];
    printf("Good %s!\n", words[ greeting_index ] );
    return 0;
}
