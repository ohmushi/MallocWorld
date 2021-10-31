//
// Created by Théo Omnès on 30/10/2021.
//

#include "test_craft.h"

Character* PLAYER;
Bag* BAG;

void testCraft() {
    testFindCraftRecipe();
    testCraftWoodSword();
}

void setUpCraft(char* testName) {
    printf("\n%s", testName);
    BAG = newBag(5,10);
    PLAYER = newCharacter(1, 1, 100, newLocation(2,2,1), BAG);
}

void afterCraft() {
    freeBag(BAG);
}

void testFindCraftRecipe() {
    setUpCraft("Test Craft WoodSword");
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
    int p = 0;
    CraftRecipe woodSwordRecipe = findCraftRecipeByItemIdToCraft(WoodSword);

    Item woodSword = craft(woodSwordRecipe, PLAYER);

    p += assertEqualsInt(WoodSword, woodSword.id);
    p += assertEqualsInt(WeaponType, woodSword.type);
    p += assertEqualsBool(false, woodSword.isStackable);

    printResultTest(p, 3);
    afterCraft();
}