//
// Filename: main.c
//
// Made by Théo Omnès on 09 oct. 2021.
//
// Description:
//

#include <stdio.h>
#include "main.h"


#include <assert.h>
int main(int argc, char* argv[]) {
    srand((unsigned int) time(NULL));
    callTests(true);
    /*
    Location* l = newLocation(1,1,1);
    Player* p = createCharacter(l);
    Map* map = createMap();
    setZoneValueAtPosition(map->zones[0], l->x, l->y, Player);
    setZoneValueAtPosition(map->zones[0], 5, 5, NPC);
    gameLoop(p, map);
     */


    return 0;
}

void callTests(bool lunchWithTests) {
    if(!lunchWithTests){
        return;
    }
    testBag();
    testCharacter();
    // TODO chest -> string before save in file
    // TODO cli -> stdin
    testCollectResources();
    // TODO config
    testCraft();
    testItem();
    // TODO map
    testMovement();
    testNpc();
    // TODO save
    testTurnBased();
    testMonster();
}