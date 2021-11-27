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
    testPlayerAttacksMonster();
    testPlayerTakesPotion();
    testPlayerKilledMonster();

    //testFight();
}

void setUpMonster(char* testName) {
    printf("%s", testName);
    PLAYER = newPlayer(0, 1, 100, newLocation(1, 1, 1), newBag(5, 10));
}

void afterMonster() {
    freePlayer(PLAYER);
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
    Item woodSword = newWeapon(WoodSword);
    woodSword.durability = 2;
    Item potion = newHeal(HealingPotionOne);
    Monster monster = findMonsterById(MonsterZoneOneA);
    monster.currentHealthPoints = 10;
    PLAYER->bag->slots[0]->item = woodSword;
    PLAYER->bag->slots[1]->item = potion;
    PLAYER->bag->slots[1]->quantity = 2;
    PLAYER->bag->currentSlot = 0;

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

void testPlayerAttacksMonster() {
    setUpMonster("Test Player Attacks Monster");
    Item woodSword = newWeapon(WoodSword);
    Monster monster = findMonsterById(MonsterZoneOneA);
    monster.currentHealthPoints = 10;
    PLAYER->bag->slots[0]->item = woodSword;
    PLAYER->bag->currentSlot = 0;

    playerAttacksMonster(PLAYER, &monster);
    int p = assertEqualsInt(9, monster.currentHealthPoints);
    p += assertEqualsInt(9, PLAYER->bag->slots[0]->item.durability);

    printResultTest(p, 2);
    afterMonster();
}

void testPlayerTakesPotion() {
    setUpMonster("Test Player Takes Potion");
    Heal potionOne = findHealById(HealingPotionOne);
    PLAYER->healthPoints = 10;
    PLAYER->maxHealthPoints = 50;

    int p = assertEqualsInt(10, PLAYER->healthPoints);
    playerTakesPotion(PLAYER, potionOne);
    p += assertEqualsInt(40, PLAYER->healthPoints);
    playerTakesPotion(PLAYER, potionOne);
    p += assertEqualsInt(50, PLAYER->healthPoints);

    printResultTest(p, 3);
    afterMonster();
}

void testPlayerKilledMonster() {
    setUpMonster("Test Player Killed Monster");
    Monster monster = findMonsterById(MonsterZoneOneA);
    Zone** zone = malloc(sizeof(Zone*));
    zone[0] = newZone(1, 5, 5, Ground, 0);
    Map* map = newMap(1, zone);
    setZoneValueAtPosition(map->zones[0], 2, 1, MonsterZoneOneA);

    playerKilledMonster(PLAYER, monster, map, Right);

    int p = assertEqualsInt( 10, PLAYER->experience);
    p += assertEqualsInt(Ground, getZoneValueAtPosition(*map->zones[0], 2, 1));

    printResultTest(p, 2);
    freeMap(map);
    afterMonster();
}