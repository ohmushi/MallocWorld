//
// Filename: movement.c
//
// Made by Théo Omnès on 16 oct. 2021.
//
// Description:
//


#include "movement.h"

bool moveUp(Character* player, Map* map) {
    if(player == NULL || map == NULL) {
        return false;
    }
    if(player->location->y == 0 || !isPlayerLocationAndMapMatch(player,map)) {
        return false;
    }

    Location* location = player->location;
    Zone* zoneAtPlayerCurrentPosition = getZoneById(map, location->zoneId);

    setGridValueAtPosition(zoneAtPlayerCurrentPosition, location->x, location->y, Ground);
    player->location->y -= 1;
    setGridValueAtPosition(zoneAtPlayerCurrentPosition, location->x, location->y, Player);

    return isPlayerLocationAndMapMatch(player, map);
}

bool moveDown(Character* player, Map* map) {
    if(player == NULL || map == NULL) {
        return false;
    }

    Location* location = player->location;
    Zone* zoneAtPlayerCurrentPosition = getZoneById(map, location->zoneId);
    int zoneHeight = zoneAtPlayerCurrentPosition->numberRows;
    if(location->y == zoneHeight - 1 || !isPlayerLocationAndMapMatch(player,map)) {
        return false;
    }

    setGridValueAtPosition(zoneAtPlayerCurrentPosition, location->x, location->y, Ground);
    player->location->y += 1;
    setGridValueAtPosition(zoneAtPlayerCurrentPosition, location->x, location->y, Player);

    return isPlayerLocationAndMapMatch(player, map);
}

/**
 * check if at player location (x,y) at a zone
 * the map value is Player (1)
 * @param player
 * @param map
 * @return True if at the player position (x,y), the grid value is Player(1), false else
 */
bool isPlayerLocationAndMapMatch(Character* player, Map* map) {
    //TODO handle a error if not match
    Zone* zoneOfPlayerLocation = getZoneById(map, player->location->zoneId);
    int16_t x = player->location->x;
    int16_t y = player->location->y;
    GridValues mapValueAtPlayerPosition = (GridValues)zoneOfPlayerLocation->grid[y][x];
    return (bool) mapValueAtPlayerPosition == Player;
}
