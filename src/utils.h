#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

extern sem_t rank_sem;
extern sem_t mixer_sem;
extern sem_t pantry_sem;
extern sem_t refrigerator_sem;
extern sem_t bowl_sem;
extern sem_t spoon_sem;
extern sem_t oven_sem;

typedef struct {
    int id;
    pthread_t tid;
} Baker;

void mixAndBake(Baker *baker, char* recipe, int bakeTime);
void bakeRecipe(Baker *baker, char* recipe, int bakeTime);

#endif