//
// Created by Théo Omnès on 23/10/2021.
//

#ifndef MALLOCWORLD_TURNBASED_H
#define MALLOCWORLD_TURNBASED_H

#endif //MALLOCWORLD_TURNBASED_H

#include "../movement/movement.h"
#include "../cli/cli.h"
#include "../npc/npc.h"
#include "../movement/movement.h"

void gameLoop(Player* player, Map* map);
Direction getPlayerDirection();
void displayZone(Zone zone);
void updatePlayerPossibleActions(Player* player, Map* map);
void* getPlayerPossibleActionByGridValueAndDirection(Player* player, Map* map, Direction direction);