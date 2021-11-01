//
// Created by Théo Omnès on 30/10/2021.
//

#include "test_craft.h"

Character* PLAYER;
Bag* BAG;

void testCraft() {
    printf("\n=== Test Craft ===\n");
    testFindCraftRecipe();
    testCraftWoodSword();
    testCraftWoodSwordWithoutIngredients();
    testCraftInTooLowZone();
}

void setUpCraft(char* testName) {
    printf("%s", testName);
    BAG = newBag(5,10);
    PLAYER = newCharacter(1, 1, 100, newLocation(2,2,1), BAG);
}

void afterCraft() {
    freeBag(PLAYER->bag);
}

void testFindCraftRecipe() {
    setUpCraft("Test Count Items In Bag By ItemId");
    int p = 0;

    p += assertEqualsInt(WoodSword, findCraftRecipeByItemIdToCraft(WoodSword).itemId);
    p += assertEqualsInt(IronSpear, findCraftRecipeByItemIdToCraft(IronSpear).itemId);
    p += assertEqualsInt(StoneSpear, findCraftRecipeByItemIdToCraft(StoneSpear).itemId);
    p += assertEqualsInt(HealingPotionTwo, findCraftRecipeByItemIdToCraft(HealingPotionTwo).itemId);
    p += assertEqualsInt(DiamondChestplate, findCraftRecipeByItemIdToCraft(DiamondChestplate).itemId);

    printResultTest(p, 5);
    afterCraft();
}

void testCraftWoodSword() {
    setUpCraft("Test Craft WoodSword");
    PLAYER->bag->slots[0]->item = findItemById(FirTree);
    PLAYER->bag->slots[0]->quantity = 3;

    int p = assertEqualsBool(true, craft(WoodSword, PLAYER));
    p += assertEqualsInt(1, countItemsInBagByItemId(PLAYER->bag, WoodSword));

    printResultTest(p, 2);
    afterCraft();
}

void testCraftWoodSwordWithoutIngredients() {
    setUpCraft("Test Craft WoodSword Without ingredients");

    int p = assertEqualsBool(false, craft(WoodSword, PLAYER));
    p += assertEqualsInt(0, countItemsInBagByItemId(PLAYER->bag, WoodSword));

    printResultTest(p, 2);
    afterCraft();
}

void testCraftInTooLowZone() {
    setUpCraft("Test Craft In A To Low Zone");
    PLAYER->location->zoneId = 1;

    int p = assertEqualsBool(false, craft(DiamondSword, PLAYER)); // should be craft in zone 3
    p += assertEqualsInt(0, countItemsInBagByItemId(PLAYER->bag, WoodSword));

    printResultTest(p, 2);
    afterCraft();
}