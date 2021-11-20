//
// Created by Théo Omnès on 23/10/2021.
//

#include "turn_based.h"

bool newGame(Player* player, Map* map) {
    int32_t turn = 0;
    bool play = true;
    while(play) {
        printf("TURN %d\n\n", turn);
        displayZone(*getZoneById(map, player->location->zoneId));
        updatePlayerPossibleActions(player, map);
        printBag(*player->bag);
        Direction nextDirection = getPlayerDirection();
        if(nextDirection == -1) { // quit the entire game
            play = false;
            break;
        }
        if(player->actions[nextDirection] != NULL) {
            (*player->actions[nextDirection])(player, map, nextDirection);
        }
        if(!playerIsAlive(*player)){ // sta
            break;
        }
        //turn += 1;
        // TODO remove 1 of the remaining turns of each node of the respawn linked list
        //******************
        int updateRespawnList(Respawns** head, int turn);
    }
    return play;
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
void updatePlayerPossibleActions(Player* player, Map* map) {
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
void* getPlayerPossibleActionByGridValueAndDirection(Player* player, Map* map, Direction direction) {
    CellValue value = getCellValueInDirection(player, map, direction);
    switch (value) {
        case PortalTwoThree: return getChangeZoneAction(value);
        case PortalOneTwo: return getChangeZoneAction(value);
        case Ground: return getWalkAction(direction);
        case NPC: return &talkToNPC;
        default: break;
    }
    if(value >= PlantZoneOne && value <= WoodZoneThree) {
        return &collectResource;
    }
    if(isMonster(value)) {
        return getFightAction(player, value);
    }

    return NULL;
}