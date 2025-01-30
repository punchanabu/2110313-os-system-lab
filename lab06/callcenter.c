#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <semaphore.h>

int rand_int(int n)
{
    int r = rand();
    return (r % n) + 1;
}

int main(int argc, char **argv) {
    printf("Starting customer\n");
    sem_t *sem = sem_open("callcenter", 0);

    while (1) {
        int sleep_time = rand_int(3);
        printf("Do something else for %d minutes\n\n", sleep_time);
        sleep(sleep_time);
        printf("Next customer calls the call center, press ten buttons, and listens to silly music.\n");
        time_t t0 = time(NULL);
        sem_wait(sem);

        time_t t = time(NULL) - t0;
        int call_time = rand_int(3)+2;
        printf("After waiting for %ld minutes, an agent accepts the call.  Talk for %d minutes.\n", t, call_time);
        sleep(call_time);

        sem_post(sem);

        printf("Customer ends the call.\n");
    }
}