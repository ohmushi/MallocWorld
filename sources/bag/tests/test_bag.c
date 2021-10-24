//
// Created by Théo Omnès on 24/10/2021.
//

#include "test_bag.h"

Bag* BAG;
Item* WOODSWORD;
Item* FIR;

void testBag() {
    testAddItemInEmptyBag();
    testAddItemInBagWithStack();
    testAddItemInBagNotStackable();
}

void setUpBag() {
    BAG = newBag(5);
    WOODSWORD = newItem(WoodSword, "Épée en bois", Weapon, false, NULL);
    FIR = newItem(FirTree, "Sapin", Resource, true, NULL);
}

void afterBag() {
    freeBag(BAG);
}

void testAddItemInEmptyBag() {
    printf("Test Add Item In Empty Bag");
    setUpBag();
    int p = 0;
    addItemInBag(BAG, WOODSWORD);

    p += assertEqualsInt(1, BAG->slots[0]->quantity);
    p += assertEqualsInt(WoodSword, BAG->slots[0]->item->id);
    p += assertEqualsAddress(WOODSWORD, BAG->slots[0]->item);

    printResultTest(p, 3);

    afterBag();
}

void testAddItemInBagWithStack() {
    printf("Test Add Item In Bag With Stack");
    setUpBag();
    BAG->slots[0]->quantity = 1;
    BAG->slots[0]->item = FIR;
    int p = 0;
    addItemInBag(BAG, FIR);

    p += assertEqualsInt(2, BAG->slots[0]->quantity);
    p += assertEqualsInt(FirTree, BAG->slots[0]->item->id);
    p += assertEqualsAddress(FIR, BAG->slots[0]->item);

    printResultTest(p, 3);
    afterBag();
}

void testAddItemInBagNotStackable() {
    printf("Test Add Item In Bag Not Stackable");
    setUpBag();
    BAG->slots[0]->quantity = 1;
    BAG->slots[0]->item = WOODSWORD;
    Item* SecondWoodSword = newItem(WoodSword, "2e épée en bois", Weapon, false, NULL);
    int p = 0;
    addItemInBag(BAG, SecondWoodSword);

    p += assertEqualsInt(1, BAG->slots[0]->quantity);
    p += assertEqualsInt(1, BAG->slots[1]->quantity);
    p += assertEqualsInt(WoodSword, BAG->slots[0]->item->id);
    p += assertEqualsInt(WoodSword, BAG->slots[1]->item->id);
    p += assertEqualsAddress(WOODSWORD, BAG->slots[0]->item);
    p += assertEqualsAddress(SecondWoodSword, BAG->slots[1]->item);

    printResultTest(p, 6);
    afterBag();
}

void testAddItemInFullBag() {
    printf("Test Add Item In Empty Bag");
    setUpBag();

    afterBag();
}

void testAddItemInBagButSlotIsFull() {
    printf("Test Add Item In Empty Bag");
    setUpBag();

    afterBag();
}