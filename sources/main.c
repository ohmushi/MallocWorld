//
// Filename: main.c
//
// Made by Théo Omnès on 09 oct. 2021.
//
// Description:
//

#include <stdio.h>
#include "main.h"

int main(int argc, char* argv[]) {

    Location* spawnLocation = newLocation(2, 2, 1);
    Character* player = createCharacter(spawnLocation);
    Map* map = createMap();
    setZoneValueAtPosition(getZoneById(map, spawnLocation->zoneId), spawnLocation->x, spawnLocation->y, Player);
    gameLoop(player, map);
    return 0;
}
