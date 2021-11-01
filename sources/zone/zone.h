//
// Created by Théo Omnès on 10/10/2021.
//

#ifndef MALLOCWORLD_ZONE_H
#define MALLOCWORLD_ZONE_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "../map/cell_value.h"
#include "../config/config.h"
#include "../movement/location.h"


typedef struct Zone {
    int8_t zoneId;
    int16_t numberRows;
    int16_t numberColumns;
    int8_t** grid;
    int8_t minLevel;
}Zone;


// Grid
int8_t** newArrayTwoDim(int16_t numberRows, int16_t numberColumns);
void fillArrayTwoDim(int8_t** array, int16_t numberRows, int16_t numberColumns, int8_t defaultValue);
int8_t** newGrid(int16_t numberRows, int16_t numberColumns, int8_t defaultValue);
void printGrid(int8_t** grid, int16_t numberRows, int16_t numberColumns);
void freeArrayTwoDim(int8_t** array, int numberRows);


// Zone
Zone* newZone(int8_t zoneId, int16_t numberRows, int16_t numberColumns, CellValue defaultValue, int8_t minLevel);
void printZone(Zone zone);
void freeZone(Zone* zone);
Zone* createZone(int8_t idZone, CellValue defaultValue);
int* findZoneSize(int8_t idZone);
void setZoneValueAtPosition(Zone* zone, int16_t x, int16_t y, CellValue value);
CellValue getZoneValueAtPosition(Zone zone, int16_t x, int16_t y);
Location findTheFirstLocationOfAGridValueInZone(Zone zone, CellValue searchedValue);
CellValue getPortalBetweenTwoZones(int8_t firstZoneId, int8_t secondZoneId);
int8_t findZoneMinLevel(int8_t zoneId);
bool isPointInZone(int16_t x, int16_t y, Zone zone);

#endif //MALLOCWORLD_ZONE_H