#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <strings.h>
#include "kitchen.h"
#include "utils.h"

#define NUM_RECIPES 5
#define SHARED_MEMORY_SIZE 100

int *shared_mem; // pointer to shared memory segment

void *bakerThread(void *arg) {
    struct Baker *baker = (struct Baker *)arg;
    printf("Baker %s is starting to bake.\n", baker->name);
    pthread_exit(NULL);
}


int main() {
    key_t key = 1234; // key for shared memory segment
    int shmid;
    int numBakers;
    struct Baker *bakers;
    struct Recipe *recipes = NULL;

    /* Initializing the Recipes */
    recipes = createRecipes(recipes, NUM_RECIPES);

    printf("How many bakers will be competing today? ");
    scanf("%d", &numBakers);

    if(numBakers < 1) {
        printf("You must have at least one baker to compete.\n");
        exit(1);
    }

    /* Initializing the Bakers */
    bakers = (struct Baker*) malloc(numBakers * sizeof(struct Baker));
    
    for (int i = 0; i < numBakers; i++) {
        sprintf(bakers[i].name, "Baker %d", i);
        bakers[i].usingOven = false;
        printf("%s\n", bakers[i].name);
    }

    // create shared memory segment
    if ((shmid = shmget(key, SHARED_MEMORY_SIZE, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    // attach shared memory segment
    if ((shared_mem = shmat(shmid, NULL, 0)) == (int *) -1) {
        perror("shmat");
        exit(1);
    }

    // create baker threads
    pthread_t threads[numBakers];
    for (int i = 0; i < numBakers; i++) {
        if (pthread_create(&threads[i], NULL, bakerThread, (void *)&bakers[i])) {
            perror("pthread_create");
            exit(1);
        }
    }

    // wait for threads to finish
    for (int i = 0; i < numBakers; i++) {
        if (pthread_join(threads[i], NULL)) {
            perror("pthread_join");
            exit(1);
        }
    }

    // detach and remove shared memory segment
    shmdt(shared_mem);
    shmctl(shmid, IPC_RMID, NULL);

    free(bakers);
    free(recipes);

    return 0;
}
