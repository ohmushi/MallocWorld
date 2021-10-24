//
// Created by Théo Omnès on 24/10/2021.
//

#include "test_bag.h"

Bag* BAG;
Item* ITEM;

void testBag() {
    testAddItemInEmptyBag();
}

void setUpBag() {
    BAG = newBag(5);
    ITEM = newItem(WoodSword, "Épée en bois", Weapon, NULL);
}

void afterBag() {
    freeBag(BAG);
    freeItem(ITEM);
}

void testAddItemInEmptyBag() {
    setUpBag();
    int p = 0;
    //addItemInBag

    p += assertEqualsInt(1, BAG->slots[0]->quantity);
//    p += assertEqualsInt(WoodSword, BAG->slots[0]->item->id);
//    p += assertEqualsAddress(ITEM, BAG->slots[0]->item);

    printResultTest(p, 1);

    afterBag();
}

void testAddItemInBagWithSameItemInASlot() {
    setUpBag();
    int p = 0;
    //addItemInBag

    printResultTest(p, 0);
    afterBag();
}

void testAddItemInFullBag() {
    setUpBag();

    afterBag();
}

void testAddItemInBagButSlotIsFull() {
    setUpBag();

    afterBag();
}