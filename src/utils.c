#ifndef UTILS_H 
#define UTILS_H

#include "utils.h"

struct Recipe* createRecipes(struct Recipe* recipes, int numRecipes) { recipes = (struct Recipe*) malloc(numRecipes * sizeof(struct Recipe)); struct Recipe cookies = { "Cookies", .requiredIngredients = { {"Flour"}, {"Sugar"}, {"Milk"}, {"Butter"} } }; struct Recipe pancakes= { "Pancakes", .requiredIngredients = { {"Flour"}, {"Sugar"}, {"Baking Soda"}, {"Salt"}, {"Egg"}, {"Milk"}, {"Butter"} } }; struct Recipe pizzaDough= { "Pizza Dough", .requiredIngredients = { {"Yeast"},
            {"Sugar"},
            {"Salt"}
        }
    };

    struct Recipe softPretzels= {
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

#endif