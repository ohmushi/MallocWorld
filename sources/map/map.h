//
// Filename: map.h
//
// Made by Théo Omnès on 09 oct. 2021.
//
// Description:
//

#ifndef MALLOCWORLD_MAP_H
#define MALLOCWORLD_MAP_H

#endif //MALLOCWORLD_MAP_H

#include <stdint.h>
#include "../zone/zone.h"


typedef struct Map{
    int8_t numberOfZones;
    Zone* zonesList[3];
}Map;



// Map
Map* newMap(int8_t numberOfZones);
void printMap(Map map);
void freeMap(Map** map);