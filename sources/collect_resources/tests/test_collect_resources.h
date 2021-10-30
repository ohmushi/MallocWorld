//
// Created by Théo Omnès on 27/10/2021.
//

#ifndef MALLOCWORLD_TEST_COLLECT_RESOURCES_H
#define MALLOCWORLD_TEST_COLLECT_RESOURCES_H

#include "../../tests/test.h"
#include "../collect_resources.h"

void testCollectResources();
void setUpCollectResources();
void afterCollectResources();

//Rock
void testCollectRockZoneOne();
void testCollectRockZoneTwo();
void testCollectRockZoneThree();
void testCollectRockZoneTwoWithWoodPickaxe();

//Wood
void testCollectWoodZoneOne();
void testCollectWoodZoneTwo();
void testCollectWoodZoneThree();
void testCollectWoodZoneThreeWithStoneAxe();

//Plant
void testCollectPlantZoneOne();
void testCollectPlantZoneTwo();
void testCollectPlantZoneThree();
void testCollectPlantZoneOneWithIronBillhook();

#endif //MALLOCWORLD_TEST_COLLECT_RESOURCES_H