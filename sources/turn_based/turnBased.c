//
// Created by Théo Omnès on 23/10/2021.
//

#include "turnBased.h"

void gameLoop(Character* player, Map* map) {
    int32_t turn = 0;
    while(1) {
        printf("turn %d\n", turn);
        displayZone(*getZoneById(map, player->location->zoneId));
        updatePlayerPossibleActions(player, map);
        Direction nextDirection = getPlayerDirection();
        if(nextDirection == -1) {
            break;
        }
        if(player->actions[nextDirection] != NULL) {
            (*player->actions[nextDirection])(player, map);
        }
        turn += 1;
    }

    freeMap(map);
    freeCharacter(player);
}

Direction getPlayerDirection() {
    return getPlayerDirectionByCli();
}

void displayZone(Zone zone){
    displayZoneCli(zone);
}