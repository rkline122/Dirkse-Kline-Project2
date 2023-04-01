#include <string.h>
#include <time.h>
#include "utils.h"

void bakeRecipe(Baker *baker, char* recipe, int bakeTime){
    printf("Baker %d is getting ingredients for %s.\n", baker->id, recipe);
    
    sem_wait(&pantry_sem);
    printf("Baker %d is using the pantry.\n", baker->id);
    sleep(1);
    sem_post(&pantry_sem);
    printf("Baker %d is done using the pantry.\n", baker->id);

    // Pizza dough doesn't need the refrigerator
    if(strcmp(recipe, "pizza dough") != 0){
        sem_wait(&refrigerator_sem);
        printf("Baker %d is using the refrigerator.\n", baker->id);    
        sleep(1);
        sem_post(&refrigerator_sem);
        printf("Baker %d is done using the refrigerator.\n", baker->id);
    }
    mixAndBake(baker, recipe, bakeTime);
}


void mixAndBake(Baker *baker, char* recipe, int bakeTime){
    srand(time(NULL));
    int ramsey = rand() % 10;

    printf("Baker %d is gathering equipment for mixing.\n", baker->id);
    sem_wait(&mixer_sem);
    sem_wait(&bowl_sem);
    sem_wait(&spoon_sem);

    printf("Baker %d is mixing ingredients.\n", baker->id);
    sleep(3);
    printf("Baker %d is done mixing ingredients.\n", baker->id);

    sem_post(&mixer_sem);
    sem_post(&bowl_sem);
    sem_post(&spoon_sem);

    // 30% Chance of Baker being "Ramsey-ed" and having to start the recipe over from scratch
    if(ramsey < 3){
        printf("[Chef Ramsay]: Baker %d! Stop, stop, stop! What on earth is this monstrosity? It looks like it's been through a bloody tornado! Start over!\n", baker->id);
        printf("[Baker %d]: Yes Chef!\n", baker->id);
        bakeRecipe(baker, recipe, bakeTime);
        return;
    }

    printf("Baker %d is ready to put %s in the oven.\n", baker->id, recipe);
    sem_wait(&oven_sem);
    printf("Baker %d is using the oven.\n", baker->id);
    sleep(bakeTime);
    sem_post(&oven_sem);

    printf("Baker %d is done baking %s.\n", baker->id, recipe);
}