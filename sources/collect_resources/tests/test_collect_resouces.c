//
// Created by Théo Omnès on 27/10/2021.
//

#include "test_collect_resouces.h"

Map* MAP;
Character* PLAYER;

void testCollectResources() {
    // call all tests
}

void setUpCollectResources() {
    Zone** zone = malloc(sizeof(Zone));
    zone[0] = newZone(1, 5, 5, Ground, 0);
    MAP = newMap(1, zone);
    PLAYER = newCharacter(100, 1,  10, newLocation(2,2,1), newBag(5, 10));
}

void afterCollectResources() {
    freeMap(MAP);
    freeCharacter(PLAYER);
}

void testCollectRockInZoneOne() {
    printf("Test Collect Rock In Zone One");
    setUpCollectResources();
    int p = 0;

    // assert

    printResultTest(p, 0);
    afterCollectResources();
}