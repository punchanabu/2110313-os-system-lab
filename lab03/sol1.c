#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pid;
    pid = fork();   

    if (pid == 0) {
        pid = fork();   
        if (pid == 0) {
            printf("This is grandchild process. My PID is %d my parent PID is %d\n", getpid(), getppid());
        }
        else {
            printf("This is child process. My PID is %d my parent PID is %d\n", getpid(), getppid());
            wait(0);
        }
    }
    else {
        printf("This is parent process. My PID is %d\n", getpid());
        wait(0);
    }
    return (0);
}