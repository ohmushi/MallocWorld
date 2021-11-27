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
    //callTests(true);
    mallocworld();
    return 0;
}

Mallocworld initGame() {
    Location* location = newLocation(1,1,1);
    Player* player = createPlayer(location);
    Map* map = initMap();
    setZoneValueAtPosition(map->zones[0], location->x, location->y, PlayerCell);
    setZoneValueAtPosition(map->zones[0], 5, 5, NPC);
    setZoneValueAtPosition(map->zones[0], 3, 1, MonsterZoneOneA);
    setZoneValueAtPosition(map->zones[0], 1, 4, PortalOneTwo);
    setZoneValueAtPosition(map->zones[1], 1, 4, PortalOneTwo);
    setZoneValueAtPosition(map->zones[0], 2, 3, WoodZoneOne);
    setZoneValueAtPosition(map->zones[0], 7, 7, NPC);

    player->bag->slots[0]->item = newWeapon(WoodSword);
    player->bag->slots[0]->quantity = 1;

    player->bag->slots[1]->item = newTool(WoodPickaxe);
    player->bag->slots[1]->quantity = 1;

    player->bag->slots[2]->item = newTool(WoodBillhook);
    player->bag->slots[2]->quantity = 1;

    player->bag->slots[3]->item = newTool(WoodAxe);
    player->bag->slots[3]->quantity = 1;

    player->bag->currentSlot = 3;
    //TODO SELECT HAND

    return newMallocWorld(player, map);
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
    // TODO test config
    testCraft();
    testItem();
    // TODO test map
    //testMovement();
    testNpc();
    // TODO test save
    testTurnBased();
    testMonster();
    testResourcesReappearance();
}