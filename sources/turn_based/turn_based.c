//
// Created by Théo Omnès on 23/10/2021.
//

#include "turn_based.h"

void gameLoop(Character* player, Map* map) {
    int32_t turn = 0;
    while(1) {
        printf("turn %d\n", turn);
        displayZone(*getZoneById(map, player->location->zoneId));
        updatePlayerPossibleActions(player, map);
        Direction nextDirection = getPlayerDirection();
        if(nextDirection == -1) {
            break;
        }
        if(player->actions[nextDirection] != NULL) {
            //TODO : add parameter to the functions: the direction
            (*player->actions[nextDirection])(player, map);
        }
        turn += 1;
    }

    freeMap(map);
    freeCharacter(player);
}

Direction getPlayerDirection() {
    return getPlayerDirectionByCli();
}

void displayZone(Zone zone){
    displayZoneCli(zone);
}

/**
 * Update the pointers of functions corresponding to the actions in the four directions (Left, Right, Up, Down)
 * by checking if the action is possible: the player can move in this direction
 * or the player fulfill the conditions to make the action.
 * If the action is not possible, the value is NULL.
 * ex:
 * 0 0 0
 * 0 1 2
 * 0 -1 0
 * actions[Left] : &moveLeft
 * actions[Right] : &talkToNpc
 * actions[Up] : &moveUp
 * actions[Down] : NULL , wall so impossible to move
 * @param player
 * @param map
 */
void updatePlayerPossibleActions(Character* player, Map* map) {
    player->actions[Left] = getPlayerPossibleActionByGridValueAndDirection(player, map, Left);
    player->actions[Right] = getPlayerPossibleActionByGridValueAndDirection(player, map, Right);
    player->actions[Up] = getPlayerPossibleActionByGridValueAndDirection(player, map, Up);
    player->actions[Down] = getPlayerPossibleActionByGridValueAndDirection(player, map, Down);
}

/**
 * For each value of the enum CellValue, get the function pointer of the action
 * corresponding to the grid value
 * (ex: Ground -> &moveUp or &moveDown or &moveLeft or &moveRight)
 * If the action is NOT possible (the player can't move in this direction,
 * or the player does not meet the conditions to make the action) the value is NULL.
 * (ex: PlantZoneThree -> but doest have the tool to collect)
 * @return Function pointer of the action in the wanted direction
 */
void* getPlayerPossibleActionByGridValueAndDirection(Character* player, Map* map, Direction direction) {
    CellValue* surroundings = getPlayerSurroundings(player, map);
    CellValue value = surroundings[direction];
    free(surroundings);
    switch (value) {
        case PortalTwoThree: return NULL; //TODO
        case PortalOneTwo: return NULL; //TODO
        case Wall: return NULL;
        case Ground: return getWalkAction(direction);
        case Player: return NULL;
        case NPC: return &talkToNPC;
        case PlantZoneOne: return NULL; //TODO
        case RockZoneOne: return NULL; //TODO
        case WoodZoneOne: return NULL; //TODO
        case PlantZoneTwo: return NULL; //TODO
        case RockZoneTwo: return NULL; //TODO
        case WoodZoneTwo: return NULL; //TODO
        case PlantZoneThree: return NULL; //TODO
        case RockZoneThree: return NULL; //TODO
        case WoodZoneThree: return NULL; //TODO

            // TODO monsters

        case GridValueError: return NULL;
        default: return NULL;
    }
}