//
// Filename: movement.h
//
// Made by Théo Omnès on 16 oct. 2021.
//
// Description:
//

#ifndef MALLOCWORLD_MOVEMENT_H
#define MALLOCWORLD_MOVEMENT_H


#include "../map/map.h"
#include "../player/player.h"
#include "../cli/cli.h"
#include <stdbool.h>

typedef enum Direction {
    Left = 0,
    Right = 1,
    Up = 2,
    Down = 3
}Direction;

bool moveUp(Player* player, Map* map);
bool moveDown(Player* player, Map* map);
bool moveRight(Player* player, Map* map);
bool moveLeft(Player* player, Map* map);
bool isPlayerLocationAndMapMatch(Location* location, Map* map);
int8_t* getDirectionTranslation(Direction direction);
bool moveCharacter(Direction direction, Location* playerLocation, Map* map);
bool playerChangeZone(Location* playerLocation, Zone* zoneDestination);
int8_t getDestinationZoneId(int8_t currentZoneId, CellValue portal);
bool playerTakesPortal(Player* player, Map* map, CellValue portal);
CellValue* getPlayerSurroundings(Player* player, Map* map);
void* getWalkAction(Direction direction);
Location getLocationInDirection(Location beforeMove, Direction direction);
void displayZoneCli(Zone zone);
Direction getPlayerDirectionByCli();

#endif //MALLOCWORLD_MOVEMENT_H