//
// Filename: test_movement.c
//
// Made by Théo Omnès on 16 oct. 2021.
//
// Description:
//

#include "test_movement.h"

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
void setUpMovement(const char* testName, Location* playerLocation) {
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

void afterMovement() {
    freeMap(MAP);
    freePlayer(PLAYER);
}

void testMovement() {
    printf("\n=== Test Movement ===\n");
    testMoveUp();
    testMoveUpEdges();
    testMoveRight();
    testMoveRightEdges();
    testChangeZoneOneToTwo();
    testChangeZoneTwoToOne();
    testChangeZoneThreeToTwo();
    testPlayerTakePortalOneToTwo();
    testPlayerTakePortalTwoToOne();
    testPlayerTakePortalTwoToThree();
    testPlayerTakePortalOneToTwoButHisLevelIsTooLow();
    testGetThePlayerSurroundings();
    testGetThePlayerSurroundingsAtEdge();
}

void testMoveUp() {
    setUpMovement("Test Move Up", newLocation(2,2,1));

    int p = 0;
    bool hasMoved = moveUp(PLAYER, MAP);

    p += assertEqualsBool(true, hasMoved);
    p += assertEqualsInt(Ground, MAP->zones[0]->grid[2][2]); // player is gone
    p += assertEqualsInt(PlayerCell, MAP->zones[0]->grid[1][2]); // player moved up

    printResultTest(p, 3);
    afterMovement();
}

void testMoveUpEdges() {
    setUpMovement("Test Move Up On The Map Edge", newLocation(2,0,1));

    int p = 0;
    bool hasMoved = moveUp(PLAYER, MAP);

    p += assertEqualsBool(false, hasMoved);
    p += assertEqualsInt(PlayerCell, MAP->zones[0]->grid[0][2]); // player didn't move

    printResultTest(p, 2);
    afterMovement();
}

void testMoveRight() {
    setUpMovement("Test Move Right", newLocation(2,2,1));

    int p = 0;
    bool hasMoved = moveRight(PLAYER, MAP);

    p += assertEqualsBool(true, hasMoved);
    p += assertEqualsInt(Ground, MAP->zones[0]->grid[2][2]); // now ground, player moved
    p += assertEqualsInt(PlayerCell, MAP->zones[0]->grid[2][3]); // player now right

    printResultTest(p, 3);
    afterMovement();
}

void testMoveRightEdges() {
    setUpMovement("Test Move Right On The Map Edge", newLocation(4,2,1));

    int p = 0;
    bool hasMoved = moveRight(PLAYER, MAP);

    p += assertEqualsBool(false, hasMoved);
    p += assertEqualsInt(PlayerCell, MAP->zones[0]->grid[2][4]); // player didn't move

    printResultTest(p, 2);
    afterMovement();
}

void testChangeZoneOneToTwo() {
    setUpMovement("Test Change Zone One To Two", newLocation(0,0,1));

    int p = 0;
    bool hasChanged = playerChangeZone(PLAYER->location, getZoneById(MAP, 2));

    p += assertEqualsBool(true, hasChanged);
    p += assertEqualsInt(2, PLAYER->location->zoneId); // changed zone
    p += assertEqualsPoint(0, 3, PLAYER->location->x, PLAYER->location->y);

    printResultTest(p, 3);
    afterMovement();
}

void testChangeZoneTwoToOne() {
    setUpMovement("Test Change Zone Two To One", newLocation(0,0,2));

    int p = 0;
    bool hasChanged = playerChangeZone(PLAYER->location, getZoneById(MAP, 1));

    p += assertEqualsBool(true, hasChanged);
    p += assertEqualsInt(1, PLAYER->location->zoneId); // changed zone
    p += assertEqualsPoint(4, 3, PLAYER->location->x, PLAYER->location->y);

    printResultTest(p, 3);
    afterMovement();
}

void testChangeZoneThreeToTwo() {
    setUpMovement("Test Change Zone Three To Two", newLocation(0,0,3));

    int p = 0;
    bool hasChanged = playerChangeZone(PLAYER->location, getZoneById(MAP, 2));

    p += assertEqualsBool(true, hasChanged);
    p += assertEqualsInt(2, PLAYER->location->zoneId); // changed zone
    p += assertEqualsPoint(4, 3, PLAYER->location->x, PLAYER->location->y);

    printResultTest(p, 3);
    afterMovement();
}

void testPlayerTakePortalOneToTwo() {
    setUpMovement("tests Player Take Portal One To Two", newLocation(3,3,1));

    int p = 0;
    bool hasChanged = playerTakesPortal(PLAYER, MAP, Right);

    p += assertEqualsBool(true, hasChanged);
    p += assertEqualsInt(2, PLAYER->location->zoneId);
    p += assertEqualsPoint(0, 3, PLAYER->location->x, PLAYER->location->y);

    printResultTest(p, 3);
    afterMovement();
}

void testPlayerTakePortalTwoToOne() {
    setUpMovement("tests Player Take Portal Two To One", newLocation(1,3,2));

    int p = 0;
    bool hasChanged = playerTakesPortal(PLAYER, MAP, Left);

    p += assertEqualsBool(true, hasChanged);
    p += assertEqualsInt(1, PLAYER->location->zoneId);
    p += assertEqualsPoint(4, 3, PLAYER->location->x, PLAYER->location->y);

    printResultTest(p, 3);
    afterMovement();
}

void testPlayerTakePortalTwoToThree() {
    setUpMovement("tests Player Take Portal Two To Three", newLocation(3,3,2));

    int p = 0;
    bool hasChanged = playerTakesPortal(PLAYER, MAP, Right);

    p += assertEqualsBool(true, hasChanged);
    p += assertEqualsInt(3, PLAYER->location->zoneId);
    p += assertEqualsPoint(0, 3, PLAYER->location->x, PLAYER->location->y);

    printResultTest(p, 3);
    afterMovement();
}

void testPlayerTakePortalOneToTwoButHisLevelIsTooLow() {
    setUpMovement("tests Player Take Portal One To Two But His Level Is Too Low",
          newLocation(3,3,1));
    PLAYER->level = 1;
    MAP->zones[1]->minLevel = 3;

    int p = 0;
    bool hasChanged = playerTakesPortal(PLAYER, MAP, Right);

    p += assertEqualsBool(false, hasChanged);
    p += assertEqualsInt(1, PLAYER->location->zoneId);
    p += assertEqualsPoint(2, 2, PLAYER->location->x, PLAYER->location->y);

    printResultTest(p, 3);
    afterMovement();
}
/*
 *  -- ZONE 1 --
 *  0   0   0   0   0                 PlantZoneOne
 *  0   0   3   0   0                     ^
 *  0   4   1   0   0  RockZoneOne  <   player   >  Ground
 *  0   0   2   0  -2                     v
 *  0   0   0   0   0                    NPC
 */
void testGetThePlayerSurroundings() {
    setUpMovement("tests Get The Player Surroundings",
          newLocation(2,2,1));
    setZoneValueAtPosition(MAP->zones[0], 2, 1, PlantZoneOne);
    setZoneValueAtPosition(MAP->zones[0], 1, 2, RockZoneOne);
    setZoneValueAtPosition(MAP->zones[0], 2, 3, NPC);

    int p = 0;
    CellValue* surroundings = getPlayerSurroundings(PLAYER, MAP);

    p += assertEqualsInt(PlantZoneOne, surroundings[Up]);
    p += assertEqualsInt(RockZoneOne, surroundings[Left]);
    p += assertEqualsInt(NPC, surroundings[Down]);
    p += assertEqualsInt(Ground, surroundings[Right]);

    printResultTest(p, 4);
    afterMovement();
}

/*
 *  -- ZONE 1 --
 *  0   0   0   0   0                   PlantZoneOne
 *  0   0   0   0   0                        ^
 *  0   0   0   0   0  GridValueError  <   player   >  NPC
 *  3   0   0   0  -2                        v
 *  1   2   0   0   0                  GridValueError
 */
void testGetThePlayerSurroundingsAtEdge() {
    setUpMovement("tests Get The Player Surroundings At Edge",
          newLocation(0,4,1));
    setZoneValueAtPosition(MAP->zones[0], 0, 3, PlantZoneOne);
    setZoneValueAtPosition(MAP->zones[0], 1, 4, NPC);

    int p = 0;
    CellValue* surroundings = getPlayerSurroundings(PLAYER, MAP);

    p += assertEqualsInt(PlantZoneOne, surroundings[Up]);
    p += assertEqualsInt(NPC, surroundings[Right]);
    p += assertEqualsInt(GridValueError, surroundings[Left]);
    p += assertEqualsInt(GridValueError, surroundings[Down]);

    printResultTest(p, 4);
    afterMovement();
}





























//