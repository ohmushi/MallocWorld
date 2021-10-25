//
// Created by Théo Omnès on 24/10/2021.
//

#include "test_bag.h"

Bag* BAG;
Item* WOODSWORD;
Item* FIR;

void testBag() {
    //add in bag
    testAddItemInEmptyBag();
    testAddItemInBagWithStack();
    testAddItemInBagNotStackable();
    testAddItemInFullBag();
    testAddItemInBagButSlotsAreFull();
    testAddStackableItemInBagButTheFirstSlotIsFull();

    //remove from bag
    testRemoveStackableItemsFromBag();
    testRemoveStackableItemsInDifferentSlotsFromBag();
}

void setUpBag() {
    BAG = newBag(5, 20);
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

    p += assertEqualsBool(true, addItemInBag(BAG, WOODSWORD));
    p += assertEqualsInt(1, BAG->slots[0]->quantity);
    p += assertEqualsInt(WoodSword, BAG->slots[0]->item->id);
    p += assertEqualsAddress(WOODSWORD, BAG->slots[0]->item);
    printResultTest(p, 4);
    afterBag();
}

void testAddItemInBagWithStack() {
    printf("Test Add Item In Bag With Stack");
    setUpBag();
    BAG->slots[0]->quantity = 1;
    BAG->slots[0]->item = newItem(FirTree, "sapin 1", Resource, true, NULL);
    int p = 0;

    Item* secondFir = newItem(FirTree, "sapin 1", Resource, true, NULL);
    p += assertEqualsBool(true, addItemInBag(BAG, secondFir));
    p += assertEqualsInt(2, BAG->slots[0]->quantity);
    p += assertEqualsInt(FirTree, BAG->slots[0]->item->id);
    p += assertEqualsAddress(secondFir, BAG->slots[0]->item);

    printResultTest(p, 4);
    afterBag();
}

void testAddItemInBagNotStackable() {
    printf("Test Add Item In Bag Not Stackable");
    setUpBag();
    BAG->slots[0]->quantity = 1;
    BAG->slots[0]->item = WOODSWORD;
    Item* SecondWoodSword = newItem(WoodSword, "2e épée en bois", Weapon, false, NULL);
    int p = 0;

    p += assertEqualsBool(true, addItemInBag(BAG, SecondWoodSword));
    p += assertEqualsInt(1, BAG->slots[0]->quantity);
    p += assertEqualsInt(1, BAG->slots[1]->quantity);
    p += assertEqualsInt(WoodSword, BAG->slots[0]->item->id);
    p += assertEqualsInt(WoodSword, BAG->slots[1]->item->id);
    p += assertEqualsAddress(WOODSWORD, BAG->slots[0]->item);
    p += assertEqualsAddress(SecondWoodSword, BAG->slots[1]->item);

    printResultTest(p, 7);
    afterBag();
}

void testAddItemInFullBag() {
    printf("Test Add Item In Full Bag");
    setUpBag();
    BAG->capacity = 1;
    BAG->slots[0]->quantity = BAG->slots[0]->capacity;
    BAG->slots[0]->item = FIR;

    int p = assertEqualsBool(false, addItemInBag(BAG, WOODSWORD));
    printResultTest(p, 1);
    afterBag();
}

void testAddItemInBagButSlotsAreFull() {
    printf("Test Add Item In Bag But Slots Are Full");
    setUpBag();
    Bag* bag = newBag(2, 5);
    bag->slots[0]->quantity = 5;
    bag->slots[0]->item = FIR;
    bag->slots[1]->quantity = 1;
    bag->slots[1]->item = WOODSWORD;

    int p = assertEqualsBool(false, addItemInBag(bag, FIR));

    printResultTest(p, 1);
    afterBag();
}

void testAddStackableItemInBagButTheFirstSlotIsFull() {
    printf("Test Add Stackable Item In Bag But The First Slot Is Full");
    setUpBag();
    Bag* bag = newBag(2, 5);
    bag->slots[0]->quantity = 5;
    bag->slots[0]->item = FIR;

    int p = assertEqualsBool(true, addItemInBag(bag, FIR));
    p += assertEqualsInt(5, bag->slots[0]->quantity);
    p += assertEqualsInt(1, bag->slots[1]->quantity);
    p += assertEqualsInt(FirTree, bag->slots[1]->item->id);

    printResultTest(p, 4);
    afterBag();
}

void testRemoveStackableItemsFromBag() {
    printf("Test Remove Stackable Items From Bag");
    setUpBag();
    BAG->slots[0]->quantity = 3;
    BAG->slots[0]->item = FIR;

    int p = assertEqualsInt(2, removeItemsFromBag(BAG, FirTree, 2));
    p += assertEqualsInt(1, BAG->slots[0]->quantity);
    p += assertEqualsInt(1, removeItemsFromBag(BAG, FirTree, 10));

    printResultTest(p,3);
    afterBag();
}

void testRemoveStackableItemsInDifferentSlotsFromBag() {
    printf("Test Remove Stackable Items In Different Slots From Bag");
    setUpBag();
    Item* fir1 = newItem(FirTree, "sapin 1", Resource, true, NULL);
    Item* fir2 = newItem(FirTree, "sapin 2", Resource, true, NULL);
    BAG->slots[0]->quantity = 3;
    BAG->slots[0]->item = fir1;
    BAG->slots[1]->quantity = 3;
    BAG->slots[1]->item = fir2;

    int p = assertEqualsInt(5, removeItemsFromBag(BAG, FirTree, 5));
    p += assertEqualsInt(0, BAG->slots[0]->quantity);
    p += assertEqualsInt(1, BAG->slots[1]->quantity);

    printResultTest(p,3);
    afterBag();
}