//
// Created by Théo Omnès on 23/10/2021.
//

#ifndef MALLOCWORLD_TESTTURNBASED_H
#define MALLOCWORLD_TESTTURNBASED_H

#endif //MALLOCWORLD_TESTTURNBASED_H

#ifndef MALLOCWORLD_LOCATION_H
#include "../../movement/location.h"
#endif

#ifndef MALLOCWORLD_TEST_H
#include "../../tests/test.h"
#endif

void testTurnBased();
void setUpTurnBased(const char* testName, Location* playerLocation);
void afterTurnBased();
void testGetThePlayerPossibleActionsGround();
void testThePlayerActionTalkToNpc();