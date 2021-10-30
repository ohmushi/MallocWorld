//
// Created by Théo Omnès on 26/10/2021.
//

#include "test_npc.h"

Bag* BAG;

void testNpc() {
    testFixWeaponsAndTools();
}


void setUpNpc() {
    BAG = newBag(5, 10);

}

void afterNpc() {
    freeBag(BAG);
}


void testFixWeaponsAndTools() {
    printf("Test Fix Weapons And Tools");
    setUpNpc();
    Item woodSword = {WoodSword, "Épée en bois", 10, 100, WeaponType, false, NULL};
    Item fir = {FirTree, "Sapin", 0, 100, CraftResourceType, true, NULL};
    Item stonePickaxe = {StonePickaxe, "Pioche en pierre", 0, 100, ToolType, false, NULL};
    BAG->slots[0]->item = woodSword;
    BAG->slots[1]->item = fir;
    BAG->slots[2]->item = stonePickaxe;

    int p = 0;
    fixWeaponsAndToolsInBag(BAG);
    p += assertEqualsInt(100, BAG->slots[0]->item.durability);
    p += assertEqualsInt(0, BAG->slots[1]->item.durability);
    p += assertEqualsInt(100, BAG->slots[2]->item.durability);

    printResultTest(p, 3);
    afterNpc();
}