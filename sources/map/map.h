//
// Filename: map.h
//
// Made by Théo Omnès on 09 oct. 2021.
//
// Description:
//

#ifndef MALLOCWORLD_MAP_H
#define MALLOCWORLD_MAP_H

#include "../zone/zone.h"
#include <stdint.h>
#include "../ resources_reappearance/resources_reappearance .h"

typedef struct Map{
    int8_t numberOfZones;
    Zone** zones;
    Respawns respawns;

}Map;



// Map // I added as parameter a Respawns not yet implemented->see it after....
Map* newMap(int8_t numberOfZones, Zone** zones, Respawns respawns);
void printMap(Map map);
void freeMap(Map* map);
int8_t findNumberOfZones();
Map* createMap();
Zone* getZoneById(Map* map, int8_t zoneId);
void setCellValueInMapAtLocation(CellValue cell, Map* map, Location location);

#endif //MALLOCWORLD_MAP_H