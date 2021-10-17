//
// Filename: test_movement.c
//
// Made by Théo Omnès on 16 oct. 2021.
//
// Description:
//

#include "test_movement.h"

Map* MAP;
Character* PLAYER;

/**
 * create 3 zones of 5x5 with the player in the center of the zone 1 and the portals
 *  -- ZONE 1 --          -- ZONE 2 --          -- ZONE 3 --
 *  0   0   0   0   0  |  0   0   0   0   0  |  0   0   0   0   0
 *  0   0   0   0   0  |  0   0   0   0   0  |  0   0   0   0   0
 *  0   0   1   0   0  |  0   0   0   0   0  |  0   0   0   0   0
 *  0   0   0   0  -2  | -2   0   0   0  -3  | -3   0   0   0   0
 *  0   0   0   0   0  |  0   0   0   0   0  |  0   0   0   0   0
 */
void setUp(const char* testName, Location* playerLocation) {
    printf("\n%s", testName);
    Zone** zones = malloc(sizeof(Zone*) * 3);
    for(int i = 0; i < 3; i += 1) {
        zones[i] = newZone(i + 1, 5, 5, 0);
    }
    zones[0]->grid[3][4] = PortalOneTwo;
    zones[1]->grid[3][0] = PortalOneTwo;
    zones[1]->grid[3][4] = PortalTwoThree;
    zones[2]->grid[3][0] = PortalTwoThree;

    PLAYER = newCharacter(0, 1, 100, playerLocation);
    int x = PLAYER->location->x;
    int y = PLAYER->location->y;
    int zone = PLAYER->location->zoneId - 1;
    zones[zone]->grid[y][x] = Player;

    MAP = newMap(3, zones);
}

void after() {
    freeMap(MAP);
    freeCharacter(PLAYER);
}

void testMoveUp() {
    setUp("Test Move Up", newLocation(2,2,1));

    int p = 0;
    p += assertEqualsInt(Player, MAP->zones[0]->grid[2][2]); // player in the middle
    p += assertEqualsInt(Ground, MAP->zones[0]->grid[1][2]); // Ground above the player

    bool hasMoved = moveUp(PLAYER, MAP);

    p += assertEqualsBool(true, hasMoved);
    p += assertEqualsInt(Ground, MAP->zones[0]->grid[2][2]); // player is gone
    p += assertEqualsInt(Player, MAP->zones[0]->grid[1][2]); // player moved up

    printResultTest(p, 5);
    after();
}

void testMoveUpEdges() {
    setUp("Test Move Up On The Map Edge", newLocation(2,0,1));
    int p = 0;
    p += assertEqualsInt(Player, MAP->zones[0]->grid[0][2]);

    bool hasMoved = moveUp(PLAYER, MAP);

    p += assertEqualsBool(false, hasMoved);
    p += assertEqualsInt(Player, MAP->zones[0]->grid[0][2]); // player didn't move

    printResultTest(p, 3);
    after();
}

void testMoveDown() {
    setUp("Test Move Down", newLocation(2,2,1));

    int p = 0;
    p += assertEqualsInt(Player, MAP->zones[0]->grid[2][2]); // player in the middle
    p += assertEqualsInt(Ground, MAP->zones[0]->grid[3][2]); // Ground below the player

    bool hasMoved = moveDown(PLAYER, MAP);

    p += assertEqualsBool(true, hasMoved);
    p += assertEqualsInt(Ground, MAP->zones[0]->grid[2][2]); // now ground, player moved
    p += assertEqualsInt(Player, MAP->zones[0]->grid[3][2]); // player now down

    printResultTest(p, 5);
    after();
}

void testMoveDownEdges() {
    setUp("Test Move Down On The Map Edge", newLocation(2,4,1));
    int p = 0;
    p += assertEqualsInt(Player, MAP->zones[0]->grid[4][2]);

    bool hasMoved = moveDown(PLAYER, MAP);

    p += assertEqualsBool(false, hasMoved);
    p += assertEqualsInt(Player, MAP->zones[0]->grid[4][2]); // player didn't move

    printResultTest(p, 3);
    after();
}