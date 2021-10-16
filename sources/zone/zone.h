//
// Created by Théo Omnès on 10/10/2021.
//

#ifndef MALLOCWORLD_ZONE_H
#define MALLOCWORLD_ZONE_H

#endif //MALLOCWORLD_ZONE_H

#include <stdio.h>
#include <stdint.h>
#include "../map/grid_values.h"

typedef struct Zone {
    int8_t zoneId;
    int16_t numberRows;
    int16_t numberColumns;
    int8_t** grid;
}Zone;


// Grid
int8_t** newArrayTwoDim(int16_t numberRows, int16_t numberColumns);
void fillArrayTwoDim(int8_t** array, int16_t numberRows, int16_t numberColumns, int8_t defaultValue);
int8_t** newGrid(int16_t numberRows, int16_t numberColumns, int8_t defaultValue);
void printGrid(int8_t** grid, int16_t numberRows, int16_t numberColumns);
void freeArrayTwoDim(int8_t** array, int numberRows);


// Zone
Zone* newZone(int8_t zoneId, int16_t numberRows, int16_t numberColumns, GridValues defaultValue);
void printZone(Zone zone);
void freeZone(Zone* zone);