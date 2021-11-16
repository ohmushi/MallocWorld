//
// Created by kontc on 15/11/2021.
//

#ifndef MALLOCWORLD_RESOURCES_REAPPEARANCE_H
#define MALLOCWORLD_RESOURCES_REAPPEARANCE_H

#include <stdlib.h>
#include "../config/config.h"
#include "../movement/location.h"
#include "../map/cell_value.h"

typedef struct Respawns{
    Location location;
    CellValue cell;
    int remainingTurns;
    struct Respawns *next;
}Respawns;

void addResourceToRespawnList(CellValue resource, Respawns** respawn, Location location);
int findResourcesRespawnTime();
void printRespawnList(Respawns* list);

#endif //MALLOCWORLD_RESOURCES_REAPPEARANCE_H