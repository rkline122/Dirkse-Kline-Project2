#ifndef UTILS_H 
#define UTILS_H

#include "utils.h"

struct Recipe* createRecipes(struct Recipe* recipes, int numRecipes) { 
    recipes = (struct Recipe*) malloc(numRecipes * sizeof(struct Recipe)); 
    
    struct Recipe cookies = { 
        "Cookies", 
        .requiredIngredients = { 
            {"Flour"}, 
            {"Sugar"}, 
            {"Milk"}, 
            {"Butter"} 
        } 
    }; 

    struct Recipe pancakes= { 
        "Pancakes", 
        .requiredIngredients = { 
            {"Flour"}, 
            {"Sugar"}, 
            {"Baking Soda"}, 
            {"Salt"}, 
            {"Egg"}, 
            {"Milk"}, 
            {"Butter"} 
        } 
    }; 

    struct Recipe pizzaDough = { 
        "Pizza Dough", 
        .requiredIngredients = { 
            {"Yeast"},
            {"Sugar"},
            {"Salt"}
        }
    };

    struct Recipe softPretzels = {
        "Soft Pretzels",
        .requiredIngredients = {
            {"Flour"},
            {"Sugar"},
            {"Salt"},
            {"Yeast"},
            {"Baking Soda"},
            {"Egg"}
        }
    };

    struct Recipe cinnamonRolls= {
        "Cinnamon Rolls",
        .requiredIngredients = {
            {"Flour"},
            {"Sugar"},
            {"Salt"},
            {"Butter"},
            {"Egg"},
            {"Cinnamon"}
        }
    };

    recipes[0] = cookies;
    recipes[1] = pancakes;
    recipes[2] = pizzaDough;
    recipes[3] = softPretzels;
    recipes[4] = cinnamonRolls;

    return recipes;
}

struct Kitchen createKitchen(){
    struct Kitchen kitchen;

    // Initialize ingredients
    struct Ingredient egg = {"Egg"};
    struct Ingredient milk = {"Milk"};
    struct Ingredient butter = {"Butter"};

    struct Ingredient flour = {"Flour"};
    struct Ingredient sugar = {"Sugar"};
    struct Ingredient yeast = {"Yeast"};
    struct Ingredient bakingSoda = {"Baking Soda"};
    struct Ingredient salt = {"Salt"};
    struct Ingredient cinnamon = {"Cinnamon"};

    // Initialize equipment
    struct Equipment mixer = {"Mixer", 2};
    struct Equipment bowl = {"Bowl", 3};
    struct Equipment spoon = {"Spoon", 5};

    // Initialize oven
    struct Oven oven = {false};

    // Initialize bakers to NULL
    kitchen.bakers = NULL;

    // Allocate memory for refrigerators
    kitchen.refrigerators = calloc(2, sizeof(struct Refrigerator));

    // Allocate memory for equipment
    kitchen.equipment = calloc(3, sizeof(struct Equipment));

    // Initialize refrigerators
    for (int i = 0; i < 2; i++) {
        kitchen.refrigerators[i] = (struct Refrigerator) {
            .in_use = false,
            .ingredients = {
                egg,
                milk,
                butter 
            }
        };
    }

    kitchen.pantry = (struct Pantry) {
        .in_use = false,
        .ingredients = {
            flour,
            sugar,
            yeast,
            bakingSoda,
            salt,
            cinnamon
        }
    };

    kitchen.equipment[0] = mixer;
    kitchen.equipment[1] = bowl;
    kitchen.equipment[2] = spoon;

    kitchen.oven = oven;

    return kitchen;

}


#endif