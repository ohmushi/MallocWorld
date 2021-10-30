//
// Filename: movement.h
//
// Made by Théo Omnès on 16 oct. 2021.
//
// Description:
//

#ifndef MALLOCWORLD_MOVEMENT_H
#define MALLOCWORLD_MOVEMENT_H


#ifndef MALLOCWORLD_CHARACTER_H
#include "../character/character.h"
#endif //MALLOCWORLD_CHARACTER_H

#ifndef MALLOCWORLD_MAP_H
#include "../map/map.h"
#endif //MALLOCWORLD_MAP_H



#include <stdbool.h>

typedef enum Direction {
    Left = 0,
    Right = 1,
    Up = 2,
    Down = 3
}Direction;

bool moveUp(Character* player, Map* map);
bool moveDown(Character* player, Map* map);
bool moveRight(Character* player, Map* map);
bool moveLeft(Character* player, Map* map);
bool isPlayerLocationAndMapMatch(Location* location, Map* map);
int8_t* getDirectionTranslation(Direction direction);
bool moveCharacter(Direction direction, Location* playerLocation, Map* map);
bool playerChangeZone(Location* playerLocation, Zone* zoneDestination);
int8_t getDestinationZoneId(int8_t currentZoneId, GridValues portal);
bool playerTakesPortal(Character* player, Map* map, GridValues portal);
GridValues* getPlayerSurroundings(Character* player, Map* map);
void* getWalkAction(Direction direction);
Location getLocationInDirection(Location beforeMove, Direction direction);

#endif //MALLOCWORLD_MOVEMENT_H