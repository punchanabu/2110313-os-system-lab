#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* infinite_print(void* data)
{
    char *str;
    str = (char*)data;
    while(1)
    {
        printf("%s\n",str);
        sleep(1);
    }
}

int main(int argc, char *argv[])
{

    if (argc < 2) {
        printf("usage: thread_sol1 arg1 arg2\n");
        return 0;
    }

    pthread_t t1,t2;
    pthread_create(&t1,NULL,infinite_print,argv[1]);
    pthread_create(&t2,NULL,infinite_print,argv[2]);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    return 0;
}