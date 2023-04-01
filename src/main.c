#include "utils.h"

sem_t mixer_sem;
sem_t pantry_sem;
sem_t refrigerator_sem;
sem_t bowl_sem;
sem_t spoon_sem;
sem_t oven_sem;

void *baker_thread(void *arg) {
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

    return NULL;
}

int main() {
    int num_bakers;

    printf("Enter the number of bakers: ");
    scanf("%d", &num_bakers);

    if(num_bakers < 1) {
        printf("Invalid number of bakers. Exiting...\n");
        exit(1);
    }else if(num_bakers > 20) {     // TODO: Check for invalid input (characters, negative numbers, etc.)
        printf("Too many bakers. Exiting...\n");
        exit(1);
    }

    // Initialize semaphores
    sem_init(&mixer_sem, 0, 2);
    sem_init(&pantry_sem, 0, 1);
    sem_init(&refrigerator_sem, 0, 2);
    sem_init(&bowl_sem, 0, 3);
    sem_init(&spoon_sem, 0, 5);
    sem_init(&oven_sem, 0, 1);

    Baker *bakers = malloc(sizeof(Baker) * num_bakers);

    // Create baker threads
    for (int i = 0; i < num_bakers; i++) {
        bakers[i].id = i + 1;
        pthread_create(&bakers[i].tid, NULL, baker_thread, (void *)&bakers[i]);
    }

    // Join baker threads
    for (int i = 0; i < num_bakers; i++) {
        pthread_join(bakers[i].tid, NULL);
    }

    // Destroy semaphores
    sem_destroy(&mixer_sem);
    sem_destroy(&pantry_sem);
    sem_destroy(&refrigerator_sem);
    sem_destroy(&bowl_sem);
    sem_destroy(&spoon_sem);
    sem_destroy(&oven_sem);

    free(bakers);

    return 0;
}