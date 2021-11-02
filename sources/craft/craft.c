//
// Created by Théo Omnès on 30/10/2021.
//

#include "craft.h"

/**
 * List of all the craft possibilities in game
 * {
 * ItemIdToCraft : WoodSword
 * Ingredients : [
 *   {ItemId, quantity},
 *   {ItemId, quantity}
 *   ],
 * minZoneOfCraft : 1
 * }
 */
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

/**
 * Display on stdout the recipe of a craft: all the item and
 * their quantity required to craft the item
 * @param recipe
 */
void printCraft(CraftRecipe recipe) {
    printf("\n-- Craft --");
    for(int i = 0; i < MAX_NUMBER_OF_INGREDIENTS_IN_CRAFT_RECIPE; i += 1) {
        printf("\n{%d}x%d", recipe.ingredients[i].itemId,recipe.ingredients[i].quantity );
    }
    printf("\n");
}

/**
 * Find the recipe of the craft.
 * Check if the player is in a good zone to craft the item.
 * Check if the player's bag contains the required ingredients.
 * Remove the ingredients from the player's bag and add the crafted item in the bag
 * @param itemToCraft ItemId of the item to craft
 * @param player the player who craft
 * @return true if the craft succeeded, false if not
 */
bool craft(ItemId itemToCraft, Character* player) {
    CraftRecipe recipe = findCraftRecipeByItemIdToCraft(itemToCraft);
    bool isPlayerInHighEnoughZone = player->location->zoneId >= recipe.minZone;
    if(!isPlayerInHighEnoughZone || !isBagContainsCraftIngredients(player->bag, recipe)) {
        return false;
    }
    Bag* bag = player->bag;
    if(false == removeCraftIngredientsFromBag(recipe, player)) {
        return false;
    }
    Item crafted = findItemById(itemToCraft);
    bool addedInBag = (bool)addItemsInBag(player->bag, crafted, 1);
    return addedInBag;
}

CraftIngredient newCraftIngredient(ItemId itemId, int8_t quantity) {
    CraftIngredient new = {itemId, quantity};
    return new;
}

CraftRecipe newCraftRecipe(ItemId itemToCraft, CraftIngredient ingredients[2], int8_t minZone) {
    CraftRecipe new;
    new.itemId = itemToCraft;
    for(int i = 0; i < MAX_NUMBER_OF_INGREDIENTS_IN_CRAFT_RECIPE; i += 1) {
        new.ingredients[i] = ingredients[i];
    }
    new.minZone = minZone;
    return new;
}

/**
 * Fetch in the list of craft possibilities
 * @return The CraftRecipe to craft the item searched
 */
CraftRecipe findCraftRecipeByItemIdToCraft(ItemId searchedItemId) {
    for(int i = 0; i < NUMBER_OF_CRAFT_POSSIBILITIES; i += 1) {
        if(CRAFT_RECIPES[i].itemId == searchedItemId) {
            return CRAFT_RECIPES[i];
        }
    }
    return newCraftRecipe(Empty, 0, 0);
}

/**
 * Make a copy of the player's bag, remove each ingredients from the copy.
 * If the removal succeeded, replace the player's bag by the copy,
 * if not keep the old bag.
 * @return True if the removal succeeded, false if not.
 */
bool removeCraftIngredientsFromBag(CraftRecipe recipe, Character* player) {
    Bag* bag = player->bag;
    Bag* bagCopy = copyBag(bag);
    for(int i = 0; i < MAX_NUMBER_OF_INGREDIENTS_IN_CRAFT_RECIPE; i += 1) {
        CraftIngredient currentIngredient = recipe.ingredients[i];
        int removed = removeItemsFromBag(bagCopy, currentIngredient.itemId, currentIngredient.quantity);
        if(removed != currentIngredient.quantity) {
            freeBag(bagCopy);
            return false;
        }
    }
    freeBag(bag);
    player->bag = bagCopy;
    return true;
}

/**
 * Loop on each ingredients of the craft recipe and
 * check if the ingredient required quantity is in the bag
 * @return true if the bag contains all the required ingredients, false if not
 */
bool isBagContainsCraftIngredients(Bag* bag, CraftRecipe recipe) {
    for(int i = 0; i < MAX_NUMBER_OF_INGREDIENTS_IN_CRAFT_RECIPE; i += 1) {
        CraftIngredient currentIngredient = recipe.ingredients[i];
        int8_t quantityRequired = currentIngredient.quantity;
        if(currentIngredient.itemId != Empty) {
            int numberOfCurrentIngredientInBag = countItemsInBagByItemId(bag, currentIngredient.itemId);
            if(numberOfCurrentIngredientInBag < quantityRequired) {
                return false;
            }
        }
    }
    return true;
}