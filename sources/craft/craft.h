//
// Created by Théo Omnès on 30/10/2021.
//

#ifndef MALLOCWORLD_CRAFT_H
#define MALLOCWORLD_CRAFT_H

#include "../player/player.h"
#include "../item/item_id.h"

#define NUMBER_OF_CRAFT_POSSIBILITIES 25
#define MAX_NUMBER_OF_INGREDIENTS_IN_CRAFT_RECIPE 2

typedef struct CraftIngredient {
    ItemId itemId;
    int8_t quantity;
} CraftIngredient;

typedef struct CraftRecipe {
    ItemId itemId;
    CraftIngredient ingredients[MAX_NUMBER_OF_INGREDIENTS_IN_CRAFT_RECIPE];
    int8_t minZone;
} CraftRecipe;


bool craft(ItemId itemToCraft, Player* player);
CraftIngredient newCraftIngredient(ItemId itemId, int8_t quantity);
CraftRecipe newCraftRecipe(ItemId itemToCraft, CraftIngredient ingredients[2], int8_t minZone);
CraftRecipe newEmptyCraftRecipe();
CraftRecipe findCraftRecipeByItemIdToCraft(ItemId searchedItemId);
bool removeCraftIngredientsFromBag(CraftRecipe recipe, Player* player);
bool isBagContainsCraftIngredients(Bag* bag, CraftRecipe recipe);
void printRecipe(CraftRecipe recipe);

#endif //MALLOCWORLD_CRAFT_H
