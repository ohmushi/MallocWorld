//
// Created by kontc on 15/11/2021.
//

#ifndef MALLOCWORLD_RESOURCES_REAPPEARANCE_H
#define MALLOCWORLD_RESOURCES_REAPPEARANCE_H

#include <stdlib.h>
#include <stdbool.h>
#include "../config/config.h"
#include "../movement/location.h"
#include "../map/cell.h"

typedef struct ToRespawn{
    Location location;
    CellValue cell;
    int remainingTurns;
    struct ToRespawn *next;
}ToRespawn;

void addResourceToRespawnList(CellValue resource, ToRespawn** respawn, Location location);
int findResourcesRespawnTime();
void printRespawnList(ToRespawn* list);
void updateRespawnList(ToRespawn* head);
void updateToRespawnList(ToRespawn* head);
void removeRespawnedCellsFromToRespawnList(ToRespawn** head, Location playerLocation);
void removeToRespawnNodes(ToRespawn** head, Location playerLocation);
bool toRespawnNodeMustBeRemoved(ToRespawn* node, Location playerLocation);


#endif //MALLOCWORLD_RESOURCES_REAPPEARANCE_H