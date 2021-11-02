//
// Created by Théo Omnès on 23/10/2021.
//

#include "test_turn_based.h"

#ifndef MALLOCWORLD_TURNBASED_H
#include "../turn_based.h"
#endif


void testTurnBased() {
    printf("\n=== Test Turn Based ===\n");
    testGetThePlayerPossibleActionsGround();
    testThePlayerActionTalkToNpc();
}

Map* MAP;
Player* PLAYER;

/**
 * create 3 zones of 5x5 with the player in the center of the zone 1 and the portals
 *  -- ZONE 1 --          -- ZONE 2 --          -- ZONE 3 --
 *  0   0   0   0   0  |  0   0   0   0   0  |  0   0   0   0   0
 *  0   0   0   0   0  |  0   0   0   0   0  |  0   0   0   0   0
 *  0   0   1   0   0  |  0   0   0   0   0  |  0   0   0   0   0
 *  0   0   0   0  -2  | -2   0   0   0  -3  | -3   0   0   0   0
 *  0   0   0   0   0  |  0   0   0   0   0  |  0   0   0   0   0
 */
void setUpTurnBased(const char* testName, Location* playerLocation) {
    printf("%s", testName);
    Zone** zones = malloc(sizeof(Zone*) * 3);
    for(int i = 0; i < 3; i += 1) {
        zones[i] = newZone(i + 1, 5, 5, 0, -1);
    }
    zones[0]->grid[3][4] = PortalOneTwo;
    zones[1]->grid[3][0] = PortalOneTwo;
    zones[1]->grid[3][4] = PortalTwoThree;
    zones[2]->grid[3][0] = PortalTwoThree;

    PLAYER = newCharacter(0, 1, 100, playerLocation, newBag(10,20));
    int x = PLAYER->location->x;
    int y = PLAYER->location->y;
    int zone = PLAYER->location->zoneId - 1;
    zones[zone]->grid[y][x] = PlayerCell;

    MAP = newMap(3, zones);
}

void afterTurnBased() {
    freeMap(MAP);
    freeCharacter(PLAYER);
}

/**
 * The possible actions is an array of 4 function pointers
 * 0 0 0
 * 0 1 0
 * 0 0 0
 * actions: [ &moveLeft() , &moveRight(), &moveUp() , &moveDown() ]
 *
 */
void testGetThePlayerPossibleActionsGround() {
    setUpTurnBased("Test Get The Player Possible Actions With Ground Around",
          newLocation(2,2,1));

    int p = 0;

    updatePlayerPossibleActions(PLAYER, MAP);
    p += assertEqualsAddress(&moveLeft, PLAYER->actions[Left]);
    p += assertEqualsAddress(&moveRight, PLAYER->actions[Right]);
    p += assertEqualsAddress(&moveUp, PLAYER->actions[Up]);
    p += assertEqualsAddress(&moveDown, PLAYER->actions[Down]);

    printResultTest(p, 4);
    afterTurnBased();
}

/**
 * 0 0 0
 * 0 1 2
 * 0 0 0
 * right action = talkToNpc
 */
void testThePlayerActionTalkToNpc() {
    setUpTurnBased("Test The Player Action Talk To NPC",
                   newLocation(1,1,1));
    setZoneValueAtPosition(MAP->zones[0], 2, 1, NPC);
    int p = 0;

    updatePlayerPossibleActions(PLAYER, MAP);
    p += assertEqualsAddress(&talkToNPC, PLAYER->actions[Right]);

    printResultTest(p, 1);
    afterTurnBased();
}

