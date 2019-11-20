#include <sys/time.h>
/* #include <stdio.h> - not needed, guessed prototype for printf() is good enough */
int main(void) /* revision 5 */
{
    static const char* const w[] = {"morning","day","afternoon","evening","night"};
    time_t t = time(0);
    return printf("Good %s!\n", w[ "444400000000111222333344"[ localtime(&t)->tm_hour ] & 7 ] );
}
