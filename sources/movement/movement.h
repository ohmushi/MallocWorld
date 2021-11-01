//
// Filename: movement.h
//
// Made by Théo Omnès on 16 oct. 2021.
//
// Description:
//

#ifndef MALLOCWORLD_MOVEMENT_H
#define MALLOCWORLD_MOVEMENT_H


#include "../character/character.h"
#include "../map/map.h"

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
int8_t getDestinationZoneId(int8_t currentZoneId, CellValue portal);
bool playerTakesPortal(Character* player, Map* map, CellValue portal);
CellValue* getPlayerSurroundings(Character* player, Map* map);
void* getWalkAction(Direction direction);
Location getLocationInDirection(Location beforeMove, Direction direction);

#endif //MALLOCWORLD_MOVEMENT_H