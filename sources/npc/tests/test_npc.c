//
// Created by Théo Omnès on 26/10/2021.
//

#include "test_npc.h"

Bag* BAG;

void testNpc() {

}


void setUpNpc() {
    BAG = newBag(3, 5);

}

void afterNpc() {
    freeBag(BAG);
}


void testStoreItemsInChest() {
    printf("Test Store Items In Chest");
    setUpNpc();
    Item woodSword = {WoodSword, "épée en bois", 100, false, NULL};
    BAG->slots[0]->item = woodSword;


    afterNpc();
}