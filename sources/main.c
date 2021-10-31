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
    /*
    Location* l = newLocation(1,1,1);
    Character* p = createCharacter(l);
    Map* map = createMap();
    setZoneValueAtPosition(map->zones[0], l->x, l->y, Player);
    setZoneValueAtPosition(map->zones[0], 5, 5, NPC);
    gameLoop(p, map);
     */


    testCraft();

    return 0;
}
