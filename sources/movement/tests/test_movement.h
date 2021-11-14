//
// Filename: test_movement.h
//
// Made by Théo Omnès on 16 oct. 2021.
//
// Description:
//


#ifndef MALLOCWORLD_TEST_MOVEMENT_H
#define MALLOCWORLD_TEST_MOVEMENT_H

#endif //MALLOCWORLD_TEST_MOVEMENT_H

#ifndef MALLOCWORLD_MOVEMENT_H
#include "../movement.h"
#endif //MALLOCWORLD_MOVEMENT_H

#ifndef MALLOCWORLD_TEST_H
#include "../../tests/test.h"
#endif //MALLOCWORLD_TEST_H

#ifndef MALLOCWORLD_MAP_H
#include "../../map/map.h"
#endif //MALLOCWORLD_MAP_H

void testMovement();
void setUpMovement(const char* testName, Location* playerLocation);
void afterMovement();
void testMoveUp();
void testMoveUpEdges();
void testMoveRight();
void testMoveRightEdges();
void testChangeZoneOneToTwo();
void testChangeZoneTwoToOne();
void testChangeZoneThreeToTwo();
void testPlayerTakePortalOneToTwo();
void testPlayerTakePortalTwoToOne();
void testPlayerTakePortalTwoToThree();
void testPlayerTakePortalOneToTwoButHisLevelIsTooLow();
void testGetThePlayerSurroundings();
void testGetThePlayerSurroundingsAtEdge();