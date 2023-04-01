#include <string.h>
#include "utils.h"

void bakeRecipe(Baker *baker, char* recipe, int bakeTime){
    printf("Baker %d is getting ingredients for %s.\n", baker->id, recipe);
    
    sem_wait(&pantry_sem);
    printf("Baker %d is using the pantry.\n", baker->id);

    sleep(1);
    sem_post(&pantry_sem);
    printf("Baker %d is done using the pantry.\n", baker->id);

    if(strcmp(recipe, "pizza dough") != 0){
        // Pizza dough doesn't need the refrigerator

        sem_wait(&refrigerator_sem);
        printf("Baker %d is using the refrigerator.\n", baker->id);    

        sleep(5);
        sem_post(&refrigerator_sem);
        printf("Baker %d is done using the refrigerator.\n", baker->id);
    }

    mixAndBake(baker, recipe, bakeTime);

    printf("Baker %d is done baking %s.\n", baker->id, recipe);
    resetIngredients(baker);
    baker->recipes_completed++;
}


void mixAndBake(Baker *baker, char* recipe, int bakeTime){
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

    printf("Baker %d is ready to put %s in the oven.\n", baker->id, recipe);
    sem_wait(&oven_sem);
    printf("Baker %d is using the oven.\n", baker->id);
    sleep(bakeTime);
    sem_post(&oven_sem);
}

void resetIngredients(Baker *baker){
    for(int i = 0; i < MAX_INGREDIENTS; i++){
        baker->ingredients[i] = "";
    }
}





