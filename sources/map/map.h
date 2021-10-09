//
// Filename: map.h
//
// Made by Théo Omnès on 09/10/2021.
//
// Description:
//

#ifndef MALLOCWORLD_MAP_H
#define MALLOCWORLD_MAP_H

#endif //MALLOCWORLD_MAP_H

#include <stdint.h>

typedef struct Zone {
    int8_t numberZone;
    int16_t numberRows;
    int16_t numberColumns;
    int8_t** grid;
}Zone;


typedef struct Map{
    Zone* zonesList[3];
}Map;

// Zone
Zone* newZone(int8_t numberZone, int16_t numberRows, int16_t numberColumns, int8_t defaultValue);
int8_t** newArrayTwoDim(int16_t numberRows, int16_t numberColumns);
void fillArrayTwoDim(int8_t** array, int16_t numberRows, int16_t numberColumns, int8_t defaultValue);
int8_t** newGrid(int16_t numberRows, int16_t numberColumns, int8_t defaultValue);
void printGrid(int8_t** grid, int16_t numberRows, int16_t numberColumns);
void printZone(Zone zone);

// Map
Map* newMap();
void printMap(Map map);