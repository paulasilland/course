#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>


#define READ_END    0    /* index pipe lectura */
#define WRITE_END   1    /* index pipe escritura */
#define EXIT_FAILURE 1     


int main(int argc, char* argv[]) {
    int fd1[2]; fd2[2];
    FILE *fp; 
    int status, pid;

    char *p1[]= {"grep", "paula", NULL};
    char *p2[]= {"whoami", NULL};
    char *p3[]= {"cat", "/etc/passwd", NULL};

    //Creem el pipe i comprovem que no hi ha hagut errors

    if (pipe(fd1) == -1) {
        perror("Error pipe");
        return EXIT_FAILURE;
    }

    if (pipe(fd2) == -1) {
        perror("Error pipe");
        return EXIT_FAILURE;
    }

    //creem 3 pids, un per cada fill i comprovem que no hi ha hagut errors
    pid_t pid1, pid2, pid3;

    //Per al whoami:
    pid1 = fork();
    if(pid1 == -1){
        perror("Error fork");
        return EXIT_FAILURE;
    }

    else if(pid1 == 0){
        //Fill 1
        //El fill 1 llegeixi el whoami i escrigui el resultat al fitxer user.txt (stdout)
        dup2(fd2[1], STDOUT_FILENO);
        close(fd2[0]);
        close(fd2[1]);
        execvp(p2[0], p2); //Executa whoami

    }
    else{
        waitpid(pid1, 0, 0);
        p1[1] = malloc(sizeof(fd2[0]));
        close(fd2[0]);
        close(fd2[1]);
    }

    //Per al cat:
    pid2 = fork();
    if(pid2 == -1){
        perror("Error fork");
        return EXIT_FAILURE;
    }

    else if(pid2 == 0){
        //Fill 2
        //El fill 2 llegeixi el cat i escrigui el resultat al fitxer user.txt (stdout)
        dup2(fd1[1], STDOUT_FILENO);
        close(fd1[0]);
        close(fd1[1]);
        execvp(p3[0], p3); //Executa cat

    }

    //Per al grep:
    pid3 = fork();
    if(pid3 == -1){
        perror("Error fork");
        return EXIT_FAILURE;
    }

    else if(pid3 == 0){
        //Fill 3
        //El fill 3 llegeixi el grep i escrigui el resultat al fitxer user.txt (stdout)
        dup2(fd1[0], STDIN_FILENO); //Llegeix de l'entrada estàndard
        fp = fopen("user.txt", "w");
        dup2(fileno(fp), STDOUT_FILENO); //Escriu a l'arxiu
        close(fd1[0]);
        close(fd1[1]);
        execvp(p1[0], p1); //Executa grep

    }
   
    waitpid(pid1, 0, 0);
    waitpid(pid2, 0, 0);
    waitpid(pid3, 0, 0);
    return 1; //Finalització correcta
}
