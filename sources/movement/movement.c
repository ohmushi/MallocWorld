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
bool moveUp(Player* player, Map* map) {
    if(NULL == player || NULL == map) {
        return false;
    }
    return moveCharacter(Up, player->location, map);
}

/**
 * Move the player down in the map
 * @return True if the movement succeeded or False if the destination is inaccessible
 */
bool moveDown(Player* player, Map* map) {
    if(NULL == player || NULL == map) {
        return false;
    }
    return moveCharacter(Down, player->location, map);
}

/**
 * Move the player left in the map
 * @return True if the movement succeeded or False if the destination is inaccessible
 */
bool moveLeft(Player* player, Map* map) {
    if(NULL == player || NULL == map) {
        return false;
    }
    return moveCharacter(Left, player->location, map);
}

/**
 * Move the player right in the map
 * @return True if the movement succeeded or False if the destination is inaccessible
 */
bool moveRight(Player* player, Map* map) {
    if(NULL == player || NULL == map) {
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
    CellValue mapValueAtPlayerPosition = (CellValue)zoneOfPlayerLocation->grid[y][x];
    return (bool) mapValueAtPlayerPosition == PlayerCell;
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
        getZoneValueAtPosition(*zone, newX, newY) != Ground) {
        return false;
    }

    setZoneValueAtPosition(zone, playerLocation->x, playerLocation->y, Ground);
    playerLocation->x = newX;
    playerLocation->y = newY;
    setZoneValueAtPosition(zone, playerLocation->x, playerLocation->y, PlayerCell);

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
    if(NULL == array) {
        return NULL;
    }
    int8_t possibilities[4][2] = {
            {-1, 0},    // Left
            {1, 0},     // Right
            {0, -1},    // Up
            {0, 1}      // Down
    };
    array[0] = possibilities[direction][0];
    array[1] = possibilities[direction][1];
    return array;
}

/**
 * Update the player location at the portal of the destination zone
 * @return The success of the zone change, if the good portal is found in the destination zone
 */
bool playerChangeZone(Location* playerLocation, Zone* zoneDestination) {
    CellValue portal = getPortalBetweenTwoZones(playerLocation->zoneId, zoneDestination->zoneId);
    Location destination = findTheFirstLocationOfAGridValueInZone(*zoneDestination, portal);
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
CellValue getPortalBetweenTwoZones(int8_t firstZoneId, int8_t secondZoneId) {
    CellValue portal = GridValueError;
    if( (firstZoneId == 1 && secondZoneId == 2) || (firstZoneId == 2 && secondZoneId == 1) ) {
        portal = PortalOneTwo;
    }
    else if( (firstZoneId == 2 && secondZoneId == 3) || (firstZoneId == 3 && secondZoneId == 2) ) {
        portal = PortalTwoThree;
    }
    return portal;
}

/**
 * By an array of the possibilities :
 * Player in zone 1 takes PortalOneTwo --> zone 2
 * Player in zone 2 takes PortalOneTwo --> zone 1
 * Player in zone 2 takes PortalTwoThree --> zone 3
 * Player in zone 3 takes PortalTwoThree --> zone 2
 * @return The id of the portal destination
 */
int8_t getDestinationZoneId(int8_t currentZoneId, CellValue portal) {
    int8_t numberPossibilities = 4;
    int8_t destinationId = -1;
    int8_t possibilities[][3] = {
            {1, PortalOneTwo, 2},
            {2, PortalOneTwo, 1},
            {2, PortalTwoThree, 3},
            {3, PortalTwoThree, 2}
    };
    for(int i = 0; i < numberPossibilities; i += 1) {
        if(possibilities[i][0] == currentZoneId && possibilities[i][1] == portal) {
            return possibilities[i][2];
        }
    }
    return destinationId;
}

/**
 * Update the location of the player depending of the player location and the portal taken
 * block the movement if the player level is lower than the zone's minimum level
 * @param portal taken by the player
 * @return True if the player succeeded to take the portal
 */
bool playerTakesPortal(Player* player, Map* map, CellValue portal) {
    int8_t destinationZoneId = getDestinationZoneId(player->location->zoneId, portal);
    if(player->level < getZoneById(map,destinationZoneId)->minLevel) {
        return false;
    }
    return playerChangeZone(player->location, getZoneById(map, destinationZoneId));
}

/**
 * Get the four cases around the player in a array[4]
 * it is recommended to use the enum Direction for the indexes (Left, Right, Up, Down)
 * The CellValue got if the player is at the edges of the grid is GridValueError
 * @return Array of the four CellValue around the player
 */
CellValue* getPlayerSurroundings(Player* player, Map* map) {
    CellValue* surroundings = malloc(sizeof(CellValue) * 4);
    Zone* zone = getZoneById(map, player->location->zoneId);
    Location* location = player->location;
    if(NULL == surroundings) {
        return NULL;
    }
    surroundings[Left] = getZoneValueAtPosition(*zone, location->x - 1, location->y);
    surroundings[Right] = getZoneValueAtPosition(*zone, location->x + 1, location->y);
    surroundings[Up] = getZoneValueAtPosition(*zone, location->x, location->y - 1);
    surroundings[Down] = getZoneValueAtPosition(*zone, location->x, location->y + 1);
    return surroundings;
}

/**
 * @return Function pointer of the movement depending of the direction:
 */
void* getWalkAction(Direction direction) {
    switch (direction) {
        case Left: return &moveLeft;
        case Right: return &moveRight;
        case Up: return &moveUp;
        case Down:return &moveDown;
        default: return NULL;
    }
    return NULL;
}

/**
 * From a certain Location (x,y), and a direction:
 * get the location of the next grid cell in this direction
 */
Location getLocationInDirection(Location beforeMove, Direction direction) {
    int8_t* translation = getDirectionTranslation(direction);
    Location location;
    location.zoneId = beforeMove.zoneId;
    location.x = beforeMove.x + translation[0];
    location.y = beforeMove.y + translation[1];
    return location;
}

Direction getPlayerDirectionByCli() {
    fflush(stdin);
    char input;
    scanf("%c", &input);
    switch (input) {
        case 'z': return Up;
        case 'q': return Left;
        case 'd': return Right;
        case 's': return Down;
        case 'x': return -1;
        default: return getPlayerDirectionByCli();
    }
}

void displayZoneCli(Zone zone) {
    clrscr();
    printZone(zone);
}