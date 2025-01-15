#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[])
{

    if (argc < 2) {
        printf("Please enter a UNIX command\n");
        exit(1);
    }   

    pid_t pid;
    pid = fork();
    if (pid < 0) {
        printf("Error : cannot fork\n");
        exit(1);
    }
    else if (pid == 0) {
        execvp(argv[1], &argv[1]);
    }
    else {
        wait(NULL);
    }
    return(0);
}