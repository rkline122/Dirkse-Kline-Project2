#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_INGREDIENTS 10

extern sem_t mixer_sem;
extern sem_t pantry_sem;
extern sem_t refrigerator_sem;
extern sem_t bowl_sem;
extern sem_t spoon_sem;
extern sem_t oven_sem;

typedef struct {
    int id;
    pthread_t tid;
    int recipes_completed;
    char* ingredients[MAX_INGREDIENTS];
} Baker;

void mixAndBake(Baker *baker, char* recipe, int bakeTime);
void resetIngredients(Baker *baker);
void bakeRecipe(Baker *baker, char* recipe, int bakeTime);

#endif