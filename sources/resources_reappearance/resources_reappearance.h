//
// Created by kontc on 15/11/2021.
//

#ifndef MALLOCWORLD_RESOURCES_REAPPEARANCE_H
#define MALLOCWORLD_RESOURCES_REAPPEARANCE_H

#include <stdlib.h>
#include "../config/config.h"
#include "../movement/location.h"
#include "../map/cell.h"

typedef struct toRespawn{
    Location location;
    CellValue cell;
    int remainingTurns;
    struct toRespawn *next;
}toRespawn;

void addResourceToRespawnList(CellValue resource, toRespawn** respawn, Location location);
int findResourcesRespawnTime();
void printRespawnList(toRespawn* list);
void updateRespawnList(toRespawn* head);


#endif //MALLOCWORLD_RESOURCES_REAPPEARANCE_H