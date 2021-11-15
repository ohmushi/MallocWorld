//
// Created by kontc on 15/11/2021.
//

#ifndef MALLOCWORLD_RESOURCES_REAPPEARANCE_H
#define MALLOCWORLD_RESOURCES_REAPPEARANCE_H

#endif //MALLOCWORLD_RESOURCES_REAPPEARANCE_H



#include "../movement/location.h"
#include "../map/cell_value.h"

typedef struct Respawns{
    Location location;
    CellValue cell;
    int remainingTurns;
    struct Respawns *next;

}Respawns;
int linkedMechanism();