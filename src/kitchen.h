#ifndef KITCHEN_H
#define KITCHEN_H 

#include <stdbool.h> 

typedef struct {
    char name[20];
}Ingredient;

typedef struct {
    char name[20];
    Ingredient requiredIngredients[10];
}Recipe;

typedef struct {
    char name[20];
    int quantity;
}Equipment;

typedef struct {
    char name[20];
    int completedRecipes;
    bool usingOven;
    Ingredient ingredientsAcquired[10];
    Equipment equipmentAcquired[3];
    Recipe recipes[5];
}Baker;

typedef struct {
    bool in_use;
    Ingredient ingredients[3];
}Refrigerator ;

typedef struct {
    bool in_use;
    Ingredient ingredients[6];
}Pantry;

typedef struct {
    bool in_use;
}Oven;

typedef struct {
    Baker *bakers;
    Refrigerator *refrigerators;
    Equipment *equipment;
    Pantry pantry;
    Oven oven;
}Kitchen;

#endif
