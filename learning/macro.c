#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <linux/limits.h>

////#define EXIT_FAILURE 0
////#define EXIT_SUCCESS 1

// macros
#define FAIL_IF(EXP) ({if(EXP){exit(EXIT_FAILURE);}})
#define FAIL_IF_MSG(EXP,MSG) ({if(EXP){printf(MSG \"n");exit(EXIT_FAILURE);}})


void explore(char *base);//DIR* dir, char* base);

int main (int argc, char *argv[])
{
    char path[PATH_MAX];
    DIR *dir;
    int exitState = 0;
    
    if (argc <= 2) {
        //if (getcwd(path, path_max) == NULL)
        //{
        //    exit(EXIT_FAILURE);
        //}
        FAIL_IF(getcwd(path, PATH_MAX) == NULL);
        
        ////dir = opendir(".");
        
      //  FAIL_IF(dir==NULL);
         
        explore(argv[1]);
        exit(EXIT_SUCCESS);
    }
}

void explore(char *base)
{
    struct dirent *de;
    DIR *dir = opendir(".");

    FAIL_IF(dir==NULL);

    while ((de = readdir(dir)) != NULL)
            printf("%s\n", de->d_name);

    closedir(dir);
}


