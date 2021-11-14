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
    //mallocworld();
    return 0;
}


void mallocworld() {
    bool play = true;
    while(play) {
        Mallocworld world = initGame();
        play = newGame(world.player, world.map);
        freeMallocWorld(world);
    }
}

//TODO procedural
Mallocworld initGame() {
    Location* location = newLocation(1,1,1);
    Player* player = createPlayer(location);
    Map* map = createMap();
    setZoneValueAtPosition(map->zones[0], location->x, location->y, PlayerCell);
    setZoneValueAtPosition(map->zones[0], 5, 5, NPC);
    setZoneValueAtPosition(map->zones[0], 3, 1, MonsterZoneOneA);
    setZoneValueAtPosition(map->zones[0], 1, 4, PortalOneTwo);
    setZoneValueAtPosition(map->zones[1], 1, 4, PortalOneTwo);
    setZoneValueAtPosition(map->zones[0], 2, 3, WoodZoneOne);

    player->bag->slots[0]->item = newWeapon(WoodSword);
    player->bag->slots[0]->quantity = 1;

    player->bag->slots[1]->item = newTool(WoodPickaxe);
    player->bag->slots[1]->quantity = 1;

    player->bag->slots[2]->item = newTool(WoodBillhook);
    player->bag->slots[2]->quantity = 1;

    player->bag->slots[2]->item = newTool(WoodAxe);
    player->bag->slots[2]->quantity = 1;

    return newMallocWorld(player, map);
}

Mallocworld newMallocWorld(Player* player, Map* map) {
    Mallocworld world;
    world.player = player;
    world.map = map;
    return world;
}

void freeMallocWorld(Mallocworld world) {
    freeMap(world.map);
    freePlayer(world.player);
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
    testMovement();
    testNpc();
    // TODO test save
    testTurnBased();
    testMonster();
}