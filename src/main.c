#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <strings.h>
#include "kitchen.h"

#define NUM_RECIPES 5

struct Recipe* createRecipes(struct Recipe* recipes, int numRecipes) {
    recipes = (struct Recipe*) malloc(numRecipes * sizeof(struct Recipe));

    struct Recipe cookies = {
        "Cookies",
        .requiredIngredients = {
            {"Flour"},
            {"Sugar"},
            {"Eggs"},
            {"Butter"},
            {"Chocolate Chips"}
        }
    };

    struct Recipe cake = {
        "Cake",
        .requiredIngredients = {
            {"Flour"},
            {"Sugar"},
            {"Eggs"},
            {"Butter"},
            {"Vanilla"}
        }
    };

    recipes[0] = cookies;
    recipes[1] = cake;

    return recipes;
}


int main() {
    int numBakers;
    struct Baker *bakers;
    struct Recipe *recipes = NULL;

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

   
    free(bakers);
    free(recipes);

    return 0;
}
