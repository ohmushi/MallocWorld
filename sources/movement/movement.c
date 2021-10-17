//
// Filename: movement.c
//
// Made by Théo Omnès on 16 oct. 2021.
//
// Description:
//


#include "movement.h"

/**
 * Move the player up in the map
 * @return True if the movement succeeded or False if the destination is inaccessible
 */
bool moveUp(Character* player, Map* map) {
    if(player == NULL || map == NULL) {
        return false;
    }
    return moveCharacter(Up, player->location, map);
}

/**
 * Move the player down in the map
 * @return True if the movement succeeded or False if the destination is inaccessible
 */
bool moveDown(Character* player, Map* map) {
    if(player == NULL || map == NULL) {
        return false;
    }
    return moveCharacter(Down, player->location, map);
}

/**
 * Move the player left in the map
 * @return True if the movement succeeded or False if the destination is inaccessible
 */
bool moveLeft(Character* player, Map* map) {
    if(player == NULL || map == NULL) {
        return false;
    }
    return moveCharacter(Left, player->location, map);
}

/**
 * Move the player right in the map
 * @return True if the movement succeeded or False if the destination is inaccessible
 */
bool moveRight(Character* player, Map* map) {
    if(player == NULL || map == NULL) {
        return false;
    }
    return moveCharacter(Right, player->location, map);
}

/**
 * check if at player location (x,y) at a zone
 * the map value is Player (1)
 * @return True if at the player position (x,y), the grid value is Player(1), false else
 */
bool isPlayerLocationAndMapMatch(Location* location, Map* map) {
    //TODO handle a error if not match
    Zone* zoneOfPlayerLocation = getZoneById(map, location->zoneId);
    int16_t x = location->x;
    int16_t y = location->y;
    GridValues mapValueAtPlayerPosition = (GridValues)zoneOfPlayerLocation->grid[y][x];
    return (bool) mapValueAtPlayerPosition == Player;
}

/**
 * Update the Location and the Map with the new location of the player
 * @param direction Left, Right, Up or Down
 * @return True if the player succeeded to move, false if not (destination not accessible : out of map or not Ground)
 */
bool moveCharacter(Direction direction, Location* playerLocation, Map* map) {
    int8_t* translation = getDirectionTranslation(direction);
    Zone* zone = getZoneById(map, playerLocation->zoneId);
    int16_t newX = playerLocation->x + translation[0];
    int16_t newY =  playerLocation->y + translation[1];

    if( !isPlayerLocationAndMapMatch(playerLocation, map) ||
        newX < 0 || newX >= zone->numberColumns || newY < 0 || newY >= zone->numberRows ||
        getZoneValueAtPosition(zone, newX, newY) != Ground) {
        return false;
    }

    setZoneValueAtPosition(zone, playerLocation->x, playerLocation->y, Ground);
    playerLocation->x = newX;
    playerLocation->y = newY;
    setZoneValueAtPosition(zone, playerLocation->x, playerLocation->y, Player);

    free(translation);
    return isPlayerLocationAndMapMatch(playerLocation, map);
}

/**
 * Get the translation depending of the direction:
 *  - left :    (-1, 0)
 *  - right :   (1, 0)
 *  - up :      (0, -1)
 *  - down :    (0, 1)
 * @param direction Up, Down, Right or Left
 * @return The vertical and horizontal translation in a array [x, y]
 */
int8_t* getDirectionTranslation(Direction direction) {
    int8_t* array = malloc(sizeof(int8_t) * 2);
    if(array == NULL) {
        return NULL;
    }
    switch (direction) {
        case Left:
            array[0] = -1;
            array[1] = 0;
            break;
        case Right:
            array[0] = 1;
            array[1] = 0;
            break;
        case Up:
            array[0] = 0;
            array[1] = -1;
            break;
        case Down:
            array[0] = 0;
            array[1] = 1;
            break;
    }
    return array;
}

bool playerChangeZone(Location* playerLocation, Zone* zoneDestination) {
    GridValues portal = getPortalBetweenTwoZones(playerLocation->zoneId, zoneDestination->zoneId);
    Location destination = findZoneValueLocation(*zoneDestination, portal);
    if(destination.zoneId < 0) {
        return false;
    }
    *playerLocation = destination;
    return true;
}

/**
 * between zone1 and zone2 : PortalOneTwo
 * between zone2 and zone3 : PortalTwoThree
 * @return The portal type between two two zones
 */
GridValues getPortalBetweenTwoZones(int8_t firstZoneId, int8_t secondZoneId) {
    GridValues portal = GridValueError;
    if( (firstZoneId == 1 && secondZoneId == 2) || (firstZoneId == 2 && secondZoneId == 1) ) {
        portal = PortalOneTwo;
    }
    else if( (firstZoneId == 2 && secondZoneId == 3) || (firstZoneId == 3 && secondZoneId == 2) ) {
        portal = PortalTwoThree;
    }
    return portal;
}