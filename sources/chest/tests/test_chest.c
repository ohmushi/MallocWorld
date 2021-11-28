//
// Created by Théo Omnès on 23/10/2021.
//

#include "test_chest.h"

Chest* CHEST;

void testChest() {
    printf("\n=== Test Chest ===\n");

    testAddItemsInChest();
}

void setUpChest(const char* testName) {
    printf("%s", testName);
    CHEST = NULL;
}

void afterChest() {
    while(CHEST != NULL) {
        Chest* remove = CHEST;
        CHEST = CHEST->next;
        free(remove);
    }
    CHEST = NULL;
}

void testAddItemsInChest() {
    setUpChest("Test Add Items In Chest");
    int p = 0;

    p += assertEqualsInt(10, addItemsInChest(Diamond, 10, &CHEST));
    p += assertEqualsInt(8, addItemsInChest(Diamond, 8, &CHEST));
    p += assertEqualsInt(18, CHEST->slot.quantity);

    printResultTest(p, 3);
    afterChest();
}