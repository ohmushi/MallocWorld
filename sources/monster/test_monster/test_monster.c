//
// Created by Théo Omnès on 01/11/2021.
//

#include "test_monster.h"

Player* PLAYER;

void testMonster() {
    printf("\n== Test Monster ==\n");

    testFindMonsterById();
    testSetPlayerHandToWeapon();
    testGetThePlayerWeapons();
    testMonsterTakesDamages();

    //testFight();
}

void setUpMonster(char* testName) {
    printf("%s", testName);
    PLAYER = newCharacter(0, 1, 100, newLocation(1,1,1), newBag(5,10));
}

void afterMonster() {
    freeCharacter(PLAYER);
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

void testGetThePlayerWeapons() {
    setUpMonster("Test Get The Player's Weapons");
    setItemAndQuantityAtSlotIndexInBag(findItemById(WoodSword),1, 0, PLAYER->bag);
    setItemAndQuantityAtSlotIndexInBag(findItemById(WoodPickaxe),1, 1, PLAYER->bag); // tool but not weapon
    setItemAndQuantityAtSlotIndexInBag(findItemById(DiamondSword),1, 2, PLAYER->bag);

    int p = 0;
    ItemList weaponsOfPlayer = getPlayerAvailableWeapons(PLAYER);

    p += assertEqualsInt(2, getItemListSize(weaponsOfPlayer));
    p += assertEqualsInt(WoodSword, weaponsOfPlayer.list[0].id);
    p += assertEqualsInt(DiamondSword, weaponsOfPlayer.list[1].id);


    printResultTest(p, 3);
    afterMonster();
}

void testFight() {
    setUpMonster("Test Player Fight Monster");
    setItemAndQuantityAtSlotIndexInBag(findItemById(WoodSword),1, 0, PLAYER->bag);

    playerChoosesItsWeapon(PLAYER);
    playerFightMonster(PLAYER, findMonsterById(MonsterZoneOneA));

    afterMonster();
}

void testMonsterTakesDamages() {
    setUpMonster("Test Monster Takes Damages");
    Monster monster = findMonsterById(MonsterZoneOneA);
    monster.currentHealthPoints = 10;
    int p = assertEqualsInt(5, monsterTakesDamages(&monster, 5));
    p += assertEqualsInt(5, monster.currentHealthPoints);

    p += assertEqualsInt(5, monsterTakesDamages(&monster, 8));
    p += assertEqualsInt(0, monster.currentHealthPoints);

    printResultTest(p, 4);
    afterMonster();
}