#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {  
    pid_t pid;
    pid = fork();
    if (pid == 0) {
        pthread_t t1,t2;
        pthread_create(&t1,NULL,(void *(*)(void *))printf,"First thread from child process\n");
        pthread_create(&t2,NULL,(void *(*)(void *))printf,"Second thread from child process\n");
        pthread_join(t1,NULL);
        pthread_join(t2,NULL);
    } else {
        pthread_t t1,t2;
        pthread_create(&t1,NULL,(void *(*)(void *))printf,"First thread from parent process\n");
        pthread_create(&t2,NULL,(void *(*)(void *))printf,"Second thread from parent process\n");
        pthread_join(t1,NULL);
        pthread_join(t2,NULL);
    }
    return 0;
}