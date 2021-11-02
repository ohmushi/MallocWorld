//
// Created by Théo Omnès on 02/11/2021.
//

#include "test_item.h"

Item ITEM;

void testItem() {
    printf("\n== Test Item ==\n");

    testItemLosesDurability();
}

void setUpItem(char* testName, ItemId itemId) {
    printf("%s", testName);
    ITEM = findItemById(itemId);
}

void afterItem() {
}

void testItemLosesDurability() {
    setUpItem("Test Item Loses Durability", WoodSword);
    ITEM.durability = 10;

    int p = assertEqualsInt(5, itemLosesDurability(&ITEM, 5));
    p += assertEqualsInt(5, ITEM.durability);

    p += assertEqualsInt(5, itemLosesDurability(&ITEM, 8));
    p += assertEqualsInt(0, ITEM.durability);

    printResultTest(p , 4);
    afterItem();
}