#include "utils.h"
#include <semaphore.h>

int *ranking;
sem_t rankSem;
sem_t mixerSem;
sem_t pantrySem;
sem_t refridgeratorSem;
sem_t bowlSem;
sem_t spoonSem;
sem_t ovenSem;

void *bakerThread(void *arg) {
    Baker *baker = (Baker *)arg;

    // Implement baking process here
    printf("Baker %d is ready to bake!\n", baker->id);
    sleep(1);

    bakeRecipe(baker, "cookies", 5);    
    bakeRecipe(baker, "pancakes", 3);  
    bakeRecipe(baker, "pizza dough", 7);  
    bakeRecipe(baker, "soft pretzels", 2);  
    bakeRecipe(baker, "cinnamon rolls", 5);  
    printf("Baker %d is done!\n", baker->id);

    sem_wait(&rankSem);
    int i = 0;
    while(ranking[i] != 0){
        i++;
    }
    ranking[i] = baker->id;
    sem_post(&rankSem);

    return NULL;
}

int main() {
    int numBakers;

    printf("Enter the number of bakers: ");
    scanf("%d", &numBakers);

    if(numBakers < 1) {
        printf("Invalid number of bakers. Exiting...\n");
        exit(1);
    }else if(numBakers > 20) {  
        printf("Too many bakers. Exiting...\n");
        exit(1);
    }

    // Initialize semaphores
    sem_init(&rankSem, 0, 1);
    sem_init(&mixerSem, 0, 2);
    sem_init(&pantrySem, 0, 1);
    sem_init(&refridgeratorSem, 0, 2);
    sem_init(&bowlSem, 0, 3);
    sem_init(&spoonSem, 0, 5);
    sem_init(&ovenSem, 0, 1);

    Baker *bakers = malloc(sizeof(Baker) * numBakers);
    ranking = (int*)malloc(sizeof(int) * numBakers);

    // Initialize ranking array
    for(int i = 0; i < numBakers; i++){
        ranking[i] = 0;
    }

    // Create baker threads
    for (int i = 0; i < numBakers; i++) {
        bakers[i].id = i + 1;
        pthread_create(&bakers[i].tid, NULL, bakerThread, (void *)&bakers[i]);
    }

    // Join baker threads
    for (int i = 0; i < numBakers; i++) {
        pthread_join(bakers[i].tid, NULL);
    }

    // Print ranking
    printf("\nThe final results are in!\n");
    printf("===========================\n");
    for(int i = 0; i < numBakers; i++){
        switch (i){
        case 0:
            printf("1st Place: Baker %d\n", ranking[i]);
            break;
        case 1:
            printf("2nd Place: Baker %d\n", ranking[i]);
            break;
        case 2:
            printf("3rd Place: Baker %d\n", ranking[i]);
            break;
        default:
            printf("%dth Place: Baker %d\n", i+1, ranking[i]);
            break;
        }
        
    }

    // Destroy semaphores
    sem_destroy(&mixerSem);
    sem_destroy(&pantrySem);
    sem_destroy(&refridgeratorSem);
    sem_destroy(&bowlSem);
    sem_destroy(&spoonSem);
    sem_destroy(&ovenSem);
    sem_destroy(&rankSem);

    free(bakers);
    free(ranking);

    return 0;
}