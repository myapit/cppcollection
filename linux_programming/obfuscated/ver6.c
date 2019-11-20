#include <sys/time.h>
int main(void)/* revision 6 */{time_t t=time(0);
static const char*const w[]={"morning","day","afternoon","evening","night"};
return printf("Good %s!\n",w["444400000001112223333444"[(localtime(&t))->tm_hour]&7]);}
