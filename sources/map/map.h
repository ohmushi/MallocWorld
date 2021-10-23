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

#ifndef MALLOCWORLD_ZONE_H
#include "../zone/zone.h"
#endif //MALLOCWORLD_ZONE_H

#include <stdint.h>

typedef struct Map{
    int8_t numberOfZones;
    Zone** zones;
}Map;



// Map
Map* newMap(int8_t numberOfZones, Zone** zones);
void printMap(Map map);
void freeMap(Map* map);
int8_t findNumberOfZones();
Map* createMap();
Zone* getZoneById(Map* map, int8_t zoneId);