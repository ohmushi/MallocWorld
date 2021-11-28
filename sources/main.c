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
    callTests(false);
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

    setBagSlotItemAtIndex(player->bag, newWeapon(WoodSword), 1, 0);
    setBagSlotItemAtIndex(player->bag, newTool(WoodPickaxe), 1, 1);
    setBagSlotItemAtIndex(player->bag, newTool(WoodBillhook), 1, 2);
    setBagSlotItemAtIndex(player->bag, newTool(WoodAxe), 1, 3);
    player->bag->currentSlot = 0;

    return newMallocWorld(player, map);
}



void callTests(bool lunchWithTests) {
    if(!lunchWithTests){
        return;
    }
    testBag();
    testPlayer();
    // TODO chest -> string before save in file
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