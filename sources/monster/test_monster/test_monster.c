//
// Created by Théo Omnès on 01/11/2021.
//

#include "test_monster.h"

Character* PLAYER;

void testMonster() {
    printf("\n== Test Monster ==\n");

    testFindMonsterById();
    testSetPlayerHandToWeapon();
}

void setUpMonster(char* testName) {
    printf("%s", testName);
    PLAYER = newCharacter(0, 1, 100, newLocation(1,1,1), newBag(5,10));
}

void afterMonster() {

}

void testFindMonsterById() {
    setUpMonster("Test Find Monster By Id");

    int p = assertEqualsInt(MonsterZoneOneA, findMonsterById(MonsterZoneOneA).id);
    p += assertEqualsInt(MonsterZoneOneB, findMonsterById(MonsterZoneOneB).id);

    printResultTest(p, 2);
    afterMonster();
}

void testSetPlayerHandToWeapon() {
    setUpMonster("Test Set Player Hand To Weapon");
    Item diamondSword = findItemById(DiamondSword);
    PLAYER->bag->slots[3]->item = diamondSword;
    PLAYER->bag->slots[3]->quantity = 1;

    int p = assertEqualsInt(3, setPlayerHandToChosenWeapon(PLAYER, diamondSword));
    p += assertEqualsInt(3, PLAYER->bag->currentSlot);

    // don't find the weapon
    p += assertEqualsInt(-1, setPlayerHandToChosenWeapon(PLAYER, findItemById(StoneSword)));
    p += assertEqualsInt(3, PLAYER->bag->currentSlot); // didn't change

    printResultTest(p, 4);
    afterMonster();
}