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
    return moveCharacter(Up, player->location, map);
}

bool moveDown(Character* player, Map* map) {
    if(player == NULL || map == NULL) {
        return false;
    }
    return moveCharacter(Down, player->location, map);
}

bool moveLeft(Character* player, Map* map) {
    if(player == NULL || map == NULL) {
        return false;
    }
    return moveCharacter(Left, player->location, map);
}

bool moveRight(Character* player, Map* map) {
    if(player == NULL || map == NULL) {
        return false;
    }
    return moveCharacter(Right, player->location, map);
}

/**
 * check if at player location (x,y) at a zone
 * the map value is Player (1)
 * @param player
 * @param map
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

bool moveCharacter(Direction direction, Location* playerLocation, Map* map) {
    int8_t* translation = getDirectionTranslation(direction);
    Zone* zone = getZoneById(map, playerLocation->zoneId);
    int16_t newX = playerLocation->x + translation[0];
    int16_t newY =  playerLocation->y + translation[1];

    if( newX < 0 || newX >= zone->numberColumns || newY< 0 || newY >= zone->numberRows ||
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