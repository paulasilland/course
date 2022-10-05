#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <libgen.h>
#include <dirent.h>
#include <pwd.h>
extern errno;

#define TRASH ".trash"


int check_and_create_folder(char * folder)
{
    struct stat st;
    if ( stat(folder,&st) == -1 ){
        if (ENOENT == errno) { 
            int res = mkdir(folder, 0700);
            if (res ==-1) printf("%s.\n", strerror(errno));
            return res;
        }
    }
    return 0;
}

void join_path(char* path, char* begin, char* end){
       strcat(path,begin);
       strcat(path,"/");
       strcat(path,end);
}

int
main(int argc, char* argv[]){

        uid_t uid = getuid();
        struct passwd *pwd;
        
        if ((pwd = getpwuid(uid)) != NULL){

            const char *homedir = pwd->pw_dir;

            char *trash_path = malloc(
                strlen(homedir) + strlen(TRASH)+1);
            join_path(trash_path, homedir, TRASH);

            if (check_and_create_folder(trash_path)==0)
            {

                for (int i=1; i<argc; i++) {
                    
                    printf("[%d] ::: sending to the trash: %s \n", i,argv[i]);
                    struct stat st;

                    if ( stat(argv[i],&st) == -1 ){
                         printf("    ::: ...we cannot find it. Error:%s.\n", strerror(errno));
                         return -1;
                    }
                    else
                    {
                        char *name = basename(argv[i]);
                        char *to = malloc (strlen(TRASH) + 1 + strlen(name) );
                        *to = '\0';

                        join_path(to, TRASH, name);

                        printf("    ::: from (original): %s to (final): %s.\n", argv[i], to);

                        if (rename(argv[i], to) == -1){
                            printf("    ::: ...we cannot send it to the trash. Error:%s.\n", strerror(errno));
                        } 
                        free(to);
                    }

                }

            } 
            else 
            { 
                // Error with recyclerbin folder.
                printf("Exiting... erros with the recyclerbin!\n");
                return -1;
            }
            free(trash_path);
        }
        else {
            //Error obtaining the current user information.
            printf("Exiting... erros with getting user information!\n");
            return -1;
        }

        return 0;
}