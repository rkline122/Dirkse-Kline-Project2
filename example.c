#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMSZ 100 // size of shared memory segment

int *shared_mem; // pointer to shared memory segment


void *calculation_thread(void *arg) {
    int *num = (int *)arg;
    int sum = 0;
    for (int i = 1; i <= *num; i++) {
        sum += i;
    }
    *shared_mem = sum; // write result to shared memory
    pthread_exit(NULL);
}

int main() {
    key_t key = 1234; // key for shared memory segment
    int shmid;
    pthread_t thread;
    int num = 100;

    // create shared memory segment
    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    // attach shared memory segment
    if ((shared_mem = shmat(shmid, NULL, 0)) == (int *) -1) {
        perror("shmat");
        exit(1);
    }

    // create thread to perform calculation
    if (pthread_create(&thread, NULL, calculation_thread, (void *)&num)) {
        perror("pthread_create");
        exit(1);
    }

    // wait for thread to finish
    if (pthread_join(thread, NULL)) {
        perror("pthread_join");
        exit(1);
    }

    // read result from shared memory and print it
    printf("Sum of numbers 1 to %d = %d\n", num, *shared_mem);

    // detach and remove shared memory segment
    shmdt(shared_mem);
    shmctl(shmid, IPC_RMID, NULL);


    return 0;
}
