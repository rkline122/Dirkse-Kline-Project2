#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

extern sem_t rankSem;
extern sem_t mixerSem;
extern sem_t pantrySem;
extern sem_t refridgeratorSem;
extern sem_t bowlSem;
extern sem_t spoonSem;
extern sem_t ovenSem;

typedef struct {
    int id;
    pthread_t tid;
} Baker;

void mixAndBake(Baker *baker, char* recipe, int bakeTime);
void bakeRecipe(Baker *baker, char* recipe, int bakeTime);

#endif