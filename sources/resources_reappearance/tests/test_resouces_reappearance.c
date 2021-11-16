//
// Created by Théo Omnès on 16/11/2021.
//

#include "test_resouces_reappearance.h"


void testResourcesReappearance() {
    printf("\n=== Test Resources Reappearance ===\n");
    testAddInRespawnList();
}

void setUpReappearance(const char* testName) {
    printf("\n%s", testName);
}

void afterReappearance() {

}

void testAddInRespawnList() {
    setUpReappearance("Test Add In Respawn List");
    int p = 0;

    Respawns* linkedList = NULL;
    Location location = {3,3,1};
    addResourceToRespawnList(WoodZoneOne, &linkedList, location);
    addResourceToRespawnList(RockZoneTwo, &linkedList, location);
    addResourceToRespawnList(PlantZoneThree, &linkedList, location);

    p += assertEqualsInt(PlantZoneThree, linkedList->cell);
    p += assertEqualsInt(RockZoneTwo, linkedList->next->cell);
    p += assertEqualsInt(WoodZoneOne, linkedList->next->next->cell);

    printResultTest(p, 3);
    afterReappearance();
}