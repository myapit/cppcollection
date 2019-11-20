#include <time.h>
char*d="''''--------###===5555'' Good %s!\n\0day\0night\0morning\0evening\0afternoon";
int main()/* revision 8*/{time_t t=time(0);return printf(d+25,d+d[localtime(&t)->tm_hour]);}
