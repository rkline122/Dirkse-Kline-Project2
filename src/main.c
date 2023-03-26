#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "kitchen.h"
#include "utils.h"
#include <strings.h>

#define NUM_RECIPES 5
#define SHARED_MEMORY_SIZE 100


struct Kitchen *shared_kitchen;

void *memcpy(void *dest, const void *src, size_t n);

void *bakerThread(void *arg) {
    struct Baker *baker = (struct Baker *)arg;

    if(shared_kitchen->oven.in_use == false) {
        printf("Baker %s is using the oven.\n", baker->name);
        shared_kitchen->oven.in_use = true;
        baker->usingOven = true;
    }else{
        printf("Baker %s is waiting for the oven.\n", baker->name);
    }

    pthread_exit(NULL);
}

int main() {
    key_t key = 1234; // key for shared memory segment
    int shmid;
    int numBakers;
    struct Baker *bakers;
    struct Recipe *recipes = NULL;
    struct Kitchen kitchen = createKitchen();

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

    // create shared memory segment for kitchen
    if ((shmid = shmget(key, sizeof(struct Kitchen), IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    // attach shared memory segment for kitchen
    if ((shared_kitchen = shmat(shmid, NULL, 0)) == (struct Kitchen *) -1) {
        perror("shmat");
        exit(1);
    }

    // copy kitchen to shared memory segment
    memcpy(shared_kitchen, &kitchen, sizeof(struct Kitchen));

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

    // detach and remove shared memory segment for kitchen
    shmdt(shared_kitchen);
    shmctl(shmid, IPC_RMID, NULL);

    free(kitchen.refrigerators);
    free(kitchen.equipment);
    free(bakers);
    free(recipes);

    return 0;
}
