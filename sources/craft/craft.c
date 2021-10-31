//
// Created by Théo Omnès on 30/10/2021.
//

#include "craft.h"


const CraftRecipe CRAFT_RECIPES[NUMBER_OF_CRAFT_POSSIBILITIES] = {
        {WoodSword, {{FirTree, 3}, {Empty, 0}}, 1},
        {StoneSword, {{FirTree, 2}, {Stone, 3}}, 1},
        {IronSword, {{BeechTree, 2}, {Iron, 4}}, 2},
        {DiamondSword, {{OakTree, 2}, {Diamond, 5}}, 3},
        {StoneSpear, {{FirTree, 3}, {Stone, 4}}, 1},
        {IronSpear, {{BeechTree, 3}, {Iron, 5}}, 2},
        {DiamondSword, {{OakTree, 3}, {Diamond, 6}}, 3},
        {StoneHammer, {{FirTree, 2}, {Stone, 6}}, 1},
        {IronHammer, {{BeechTree, 2}, {Iron, 7}}, 2},
        {DiamondSword, {{OakTree, 2}, {Diamond, 8}}, 3},
        {StoneChestplate, {{Stone, 10}, {Empty, 0}}, 1},
        {IronChestplate, {{Iron, 12}, {Empty, 0}}, 2},
        {DiamondChestplate, {{Diamond, 16}, {Empty, 0}}, 3},
        {WoodPickaxe, {{FirTree, 3}, {Empty, 0}}, 1},
        {StonePickaxe, {{FirTree, 2}, {Stone, 3}}, 1},
        {IronPickaxe, {{BeechTree, 2}, {Iron, 4}}, 2},
        {WoodAxe, {{FirTree, 3}, {Empty, 0}}, 1},
        {StoneAxe, {{FirTree, 2}, {Stone, 3}}, 1},
        {IronAxe, {{BeechTree, 2}, {Iron, 4}}, 2},
        {WoodBillhook, {{FirTree, 3}, {Empty, 0}}, 1},
        {StoneBillhook, {{FirTree, 2}, {Stone, 3}}, 1},
        {IronBillhook, {{BeechTree, 2}, {Iron, 4}}, 2},
        {HealingPotionOne, {{Grass, 2}, {Empty, 0}}, 1},
        {HealingPotionTwo, {{Lavender, 2}, {Empty, 0}}, 2},
        {HealingPotionThree, {{Hemp, 2}, {Empty, 0}}, 3},
};

void printCraft(CraftRecipe recipe) {
    printf("\n-- Craft --");
    for(int i = 0; i < MAX_NUMBER_OF_INGREDIENTS_IN_RECIPE; i += 1) {
        printf("\n{%d}x%d", recipe.ingredients[i].itemId,recipe.ingredients[i].quantity );
    }
    printf("\n");
}

Item craft(ItemId itemToCraft, Character* player) {
    CraftRecipe recipe = findCraftRecipeByItemIdToCraft(itemToCraft);
    bool isPlayerInHighEnoughZone = player->location->zoneId >= recipe.minZone;
    bool isBagContainsCraftIngredients = true; // TODO check if Bag contains ingredients
    if(!isPlayerInHighEnoughZone || !isBagContainsCraftIngredients) {
        return newEmptyItem();
    }
    if(false == removeCraftIngredientsFromBag(recipe, player->bag)) {
        return newEmptyItem();
    }
    return newStructItem(Empty, "item", false, 100, NULL, ToolType);
}

CraftIngredient newCraftIngredient(ItemId itemId, int8_t quantity) {
    CraftIngredient new = {itemId, quantity};
    return new;
}

CraftRecipe newCraftRecipe(ItemId itemToCraft, CraftIngredient ingredients[2], int8_t minZone) {
    CraftRecipe new;
    new.itemId = itemToCraft;
    for(int i = 0; i < MAX_NUMBER_OF_INGREDIENTS_IN_RECIPE; i += 1) {
        new.ingredients[i] = ingredients[i];
    }
    new.minZone = minZone;
    return new;
}

CraftRecipe findCraftRecipeByItemIdToCraft(ItemId searchedItemId) {
    for(int i = 0; i < NUMBER_OF_CRAFT_POSSIBILITIES; i += 1) {
        if(CRAFT_RECIPES[i].itemId == searchedItemId) {
            return CRAFT_RECIPES[i];
        }
    }
    return newCraftRecipe(Empty, 0, 0);
}

bool removeCraftIngredientsFromBag(CraftRecipe recipe, Bag* bag) {
    //loop on recipe ingredients
    //remove items from bag
    return false;
}