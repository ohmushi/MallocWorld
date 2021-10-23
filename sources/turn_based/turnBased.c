//
// Created by Théo Omnès on 23/10/2021.
//

#include "turnBased.h"

void gameLoop(Character* player, Map* map) {
    int32_t turn = 0;
    updatePlayerPossibleActions(player, map);
    Direction nextDirection = getPlayerDirection();
    (*player->actions[nextDirection])(player, map);
    displayZone(*getZoneById(map, player->location->zoneId));
}

Direction getPlayerDirection() {
    return Up;
}

void displayZone(Zone zone){
    system("clear");
    printZone(zone);
}