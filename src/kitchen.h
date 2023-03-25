#ifndef KITCHEN_H
#define KITCHEN_H 

#include <stdbool.h> 

struct Ingredient{
    char name[20];
};

struct Recipe{
    char name[20];
    struct Ingredient requiredIngredients[10];
};

struct Equipment{
    char name[20];
    int quantity;
};

struct Baker{
    char name[20];
    int completedRecipes;
    bool usingOven;
    struct Ingredient ingredientsAcquired[10];
    struct Equipment equipmentAcquired[3];
    struct Recipe recipes[5];
};

struct Refrigerator {
    bool in_use;
    struct Ingredient ingredients[3];
};

struct Pantry {
    bool in_use;
    struct Ingredient ingredients[6];
};

struct Oven{
    bool in_use;
};

struct Kitchen{
    struct Baker *bakers;
    struct Refrigerator *refrigerators;
    struct Equipment *equipment;
    struct Pantry pantry;
    struct Oven oven;
};

#endif
