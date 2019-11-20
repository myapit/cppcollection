#include <time.h>
char*d="AAAA########+++///9999AA Good %s!\n\0morning\0day\0afternoon\0evening\0night";
int main()/* revision 8*/{time_t t=time(0);return printf(d+25,d+d[localtime(&t)->tm_hour]);}
