#include <stdio.h>
#include <pwd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[])
{
        struct passwd *getpwnam(), *pwentry;
        if (argc < 2) {
                (void) fprintf(stderr, "Usage: user name expected\n");
                exit (0);
        }
        pwentry = getpwnam(argv[1]);
        if( pwentry == (struct passwd *)NULL ){
                (void) fprint(stderr,"Can't find %s in pwd file\n",argv[1]);
                exit (0);
        } else {
          printf("%d\n",pwentry->pw_uid);
        }

}
