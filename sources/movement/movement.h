//
// Filename: movement.h
//
// Made by Théo Omnès on 16 oct. 2021.
//
// Description:
//

#ifndef MALLOCWORLD_MOVEMENT_H
#define MALLOCWORLD_MOVEMENT_H

#endif //MALLOCWORLD_MOVEMENT_H

#ifndef MALLOCWORLD_CHARACTER_H
#include "../character/character.h"
#endif //MALLOCWORLD_CHARACTER_H

#ifndef MALLOCWORLD_MAP_H
#include "../map/map.h"
#endif //MALLOCWORLD_MAP_H



#include <stdbool.h>

bool moveUp(Character* player, Map* map);
bool moveDown(Character* player, Map* map);
bool isPlayerLocationAndMapMatch(Character* player, Map* map);