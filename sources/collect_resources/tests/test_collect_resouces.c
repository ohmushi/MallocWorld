//
// Created by Théo Omnès on 27/10/2021.
//

#include "test_collect_resouces.h"

Map* MAP;
Character* PLAYER;

void testCollectResources() {
    //Rock
    testCollectRockInZoneOne();
    testCollectRockInZoneTwo();
    testCollectRockInZoneThree();

    //Wood
}

void setUpCollectResources() {
    Zone** zones = malloc(sizeof(Zone));
    zones[0] = newZone(1, 5, 5, Ground, 0);
    zones[1] = newZone(2, 5, 5, Ground, 0);
    zones[2] = newZone(3, 5, 5, Ground, 0);
    MAP = newMap(3, zones);
    PLAYER = newCharacter(100, 1,  10, newLocation(2,2,1), newBag(5, 10));
}

void afterCollectResources() {
    freeMap(MAP);
    freeCharacter(PLAYER);
}

void testCollectRockInZoneOne() {
    printf("Test Collect Rock In Zone One");
    setUpCollectResources();
    Item woodPickaxe = {WoodPickaxe, "Pioche en bois", Tool, 10, 10, false, NULL };
    PLAYER->bag->slots[0]->item = woodPickaxe;
    int p = 0;

    p += assertEqualsInt(Stone, PLAYER->bag->slots[1]->item.id);
    p += assertEqualsInt(3, PLAYER->bag->slots[1]->quantity);
    p += assertEqualsInt(9, PLAYER->bag->slots[0]->item.durability); // woodPickaxe

    printResultTest(p, 3);
    afterCollectResources();
}

void testCollectRockInZoneTwo() {
    printf("Test Collect Rock In Zone Two");
    setUpCollectResources();
    Item stonePickaxe = {StonePickaxe, "Pioche en pierre", Tool, 10, 10, false, NULL };
    PLAYER->bag->slots[0]->item = stonePickaxe;
    int p = 0;

    p += assertEqualsInt(Iron, PLAYER->bag->slots[1]->item.id);
    p += assertEqualsInt(3, PLAYER->bag->slots[1]->quantity);
    p += assertEqualsInt(8, PLAYER->bag->slots[0]->item.durability); // stonePickaxe

    printResultTest(p, 3);
    afterCollectResources();
}

void testCollectRockInZoneThree() {
    printf("Test Collect Rock In Zone Three");
    setUpCollectResources();
    Item ironPickaxe = {IronPickaxe, "Pioche en fre", Tool, 10, 10, false, NULL };
    PLAYER->bag->slots[0]->item = ironPickaxe;
    int p = 0;

    p += assertEqualsInt(Diamond, PLAYER->bag->slots[1]->item.id);
    p += assertEqualsInt(3, PLAYER->bag->slots[1]->quantity);
    p += assertEqualsInt(6, PLAYER->bag->slots[0]->item.durability); // ironPickaxe

    printResultTest(p, 3);
    afterCollectResources();
}