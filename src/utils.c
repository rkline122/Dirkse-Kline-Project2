#ifndef UTILS_H 
#define UTILS_H

#include "utils.h"

Recipe* createRecipes(Recipe* recipes, int numRecipes) { 
    recipes = (Recipe*) malloc(numRecipes * sizeof(Recipe)); 
    
    Recipe cookies = { 
        "Cookies", 
        .requiredIngredients = { 
            {"Flour"}, 
            {"Sugar"}, 
            {"Milk"}, 
            {"Butter"} 
        } 
    }; 

    Recipe pancakes= { 
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

    Recipe pizzaDough = { 
        "Pizza Dough", 
        .requiredIngredients = { 
            {"Yeast"},
            {"Sugar"},
            {"Salt"}
        }
    };

    Recipe softPretzels = {
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

    Recipe cinnamonRolls= {
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

Kitchen createKitchen(){
    Kitchen kitchen;

    // Initialize ingredients
    Ingredient egg = {"Egg"};
    Ingredient milk = {"Milk"};
    Ingredient butter = {"Butter"};

    Ingredient flour = {"Flour"};
    Ingredient sugar = {"Sugar"};
    Ingredient yeast = {"Yeast"};
    Ingredient bakingSoda = {"Baking Soda"};
    Ingredient salt = {"Salt"};
    Ingredient cinnamon = {"Cinnamon"};

    // Initialize equipment
    Equipment mixer = {"Mixer", 2};
    Equipment bowl = {"Bowl", 3};
    Equipment spoon = {"Spoon", 5};

    // Initialize oven
    Oven oven = {false};

    // Initialize bakers to NULL
    kitchen.bakers = NULL;

    // Allocate memory for refrigerators
    kitchen.refrigerators = calloc(2, sizeof(Refrigerator));

    // Allocate memory for equipment
    kitchen.equipment = calloc(3, sizeof(Equipment));

    // Initialize refrigerators
    for (int i = 0; i < 2; i++) {
        kitchen.refrigerators[i] = (Refrigerator) {
            .in_use = false,
            .ingredients = {
                egg,
                milk,
                butter 
            }
        };
    }

    kitchen.pantry = (Pantry) {
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