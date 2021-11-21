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

    ToRespawn* toRespawn = NULL;
    Location location = {3,3,1};
    addResourceToRespawnList(WoodZoneOne, &toRespawn, location);
    addResourceToRespawnList(RockZoneTwo, &toRespawn, location);
    addResourceToRespawnList(PlantZoneThree, &toRespawn, location);

    p += assertEqualsInt(PlantZoneThree, toRespawn->cell);
    p += assertEqualsInt(RockZoneTwo, toRespawn->next->cell);
    p += assertEqualsInt(WoodZoneOne, toRespawn->next->next->cell);

    printResultTest(p, 3);
    afterReappearance();
}