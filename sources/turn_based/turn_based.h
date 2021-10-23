//
// Created by Théo Omnès on 23/10/2021.
//

#ifndef MALLOCWORLD_TURNBASED_H
#define MALLOCWORLD_TURNBASED_H

#endif //MALLOCWORLD_TURNBASED_H

#ifndef MALLOCWORLD_MOVEMENT_H
#include "../movement/movement.h"
#endif

#ifndef MALLOCWORLD_CLI_H
#include "../cli/cli.h"
#endif

void gameLoop(Character* player, Map* map);
Direction getPlayerDirection();
void displayZone(Zone zone);
void updatePlayerPossibleActions(Character* player, Map* map);
void* getPlayerPossibleActionByGridValueAndDirection(Character* player, Map* map, Direction direction);