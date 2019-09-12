#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int
main(int argc, char *argv[])
{
    struct passwd pwd;
    struct passwd *result;
    char *buf;
    size_t bufsize;
    int s;

   if (argc != 2) {
        fprintf(stderr, "Usage: %s username\n", argv[0]);
        exit(EXIT_FAILURE);
    }

   bufsize = sysconf(_SC_GETPW_R_SIZE_MAX);
    if (bufsize == -1)          /* Value was indeterminate */
        bufsize = 16384;        /* Should be more than enough */

   buf = malloc(bufsize);
    if (buf == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

   s = getpwnam_r(argv[1], &pwd, buf, bufsize, &result);
    if (result == NULL) {
        if (s == 0)
            printf("Not found\n");
        else {
            errno = s;
            perror("getpwnam_r");
        }
        exit(EXIT_FAILURE);
    }

   printf("Name: %s; UID: %ld\n", pwd.pw_gecos, (long) pwd.pw_uid);
    exit(EXIT_SUCCESS);
} 

/*


#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

struct passwd *getpwnam(const char *name);
uid_t getuid(void);
uid_t geteuid(void);
struct passwd pass;

int main(int argc,char* argv[])
{
    if(argc == 1){
    printf("user: %d\ngroup: %d\n",getuid(),getgid());
    }
    if(argc == 2){
    pass = getpwnam(argv[1]);
     printf("%s   %ld",pass.pw_uid,pass.pw_gid );
    }

    pass = getpwnam(argv[1]);
  if (!pass) {
      fprintf(stderr, "%s: %s.\n", argv[1], strerror(errno));
      return EXIT_FAILURE;
  }

  /* pass->pw_uid has user ID,
     pass->pw_gid has group ID,
     pass->pw_name has user name,
     and so on. */

     /*
    return 0;
}
*/
