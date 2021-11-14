//
// Filename: zone.c
//
// Made by Théo Omnès on 09 oct. 2021.
//
// Description:
// A Zone is a grid where the player can move and interact.
// It is a int8_t grid where objects, walls, NPC, rocks, wood, monsters, etc. are placed.

#include <stdlib.h>
#include "zone.h"

/*
 * create a new two dimensions array of CellValue
 */
int8_t** newArrayTwoDim(int16_t numberRows, int16_t numberColumns){
    int8_t** arrayTwoDim = malloc(sizeof(int8_t*) * numberRows);
    if(NULL == arrayTwoDim){
        return NULL;
    }

    for( int i = 0; i < numberRows; i += 1 ){
        arrayTwoDim[i] = malloc(sizeof(int8_t) * numberColumns);
        if(NULL == arrayTwoDim[i]) {
            for(int j = 0 ; j < i ; j++){
                free(arrayTwoDim[j]);
            }
            free(arrayTwoDim);
            return NULL;
        }
    }
    return arrayTwoDim;
}

/*
 * fill a two dimensions array of int8_t with a defaultValue
 */
void fillArrayTwoDim(int8_t** array, int16_t numberRows, int16_t numberColumns, int8_t defaultValue){
    for(int16_t i = 0; i < numberRows; i++) {
        for(int16_t j = 0; j < numberColumns; j++) {
            array[i][j] = defaultValue;
        }
    }
}

/*
 * create a two dimensions array of int8_t with a defaultValue
 */
int8_t** newGrid(int16_t numberRows, int16_t numberColumns, int8_t defaultValue) {
    int8_t** grid = newArrayTwoDim(numberRows, numberColumns);
    fillArrayTwoDim(grid, numberRows, numberColumns, defaultValue);
    return grid;
}

/**
 * display a two dimensions array of int8_t with on stdout
 */
void printGrid(int8_t** grid, int16_t numberRows, int16_t numberColumns) {
    for(int16_t i = 0; i < numberRows; i++) {
        for(int16_t j = 0; j < numberColumns; j++) {
            printf("%4d", grid[i][j]);
        }
        printf("\n");
    }
}

/*
 * free a two dimensions array of int8_t
 */
void freeArrayTwoDim(int8_t** array, int numberRows){
    if(NULL == array){
        return;
    }
    for(int i = 0; i < numberRows; i += 1) {
        if( array[i] != NULL ) {
            free(array[i]);
        }
    }
    free(array);
}

/**
 * create a new struct Zone which contains :
 * the zone Id, the grid (a two dimensions array of int8_t) and its size (rows, cols)
 * @param numberRows Height of the grid
 * @param numberColumns Width of the grid
 * @param minLevel Minimum player's level to access at the zone
 */
Zone* newZone(int8_t zoneId, int16_t numberRows, int16_t numberColumns, CellValue defaultValue, int8_t minLevel) {
    if(numberRows < 2 || numberColumns < 2){
        return NULL;
    }
    Zone* zone = malloc(sizeof(Zone));
    if(NULL == zone){
        return NULL;
    }
    zone->zoneId = zoneId;
    zone->numberRows = numberRows;
    zone->numberColumns = numberColumns;
    zone->grid = newGrid(numberRows, numberColumns, defaultValue);
    zone->minLevel = minLevel;
    return zone;
}

/**
 *
 * @param idZone
 * @param defaultValue
 * @return Zone
 */
Zone* createZone(int8_t idZone, CellValue defaultValue) {
    int* size = findZoneSize(idZone);
    int8_t minLevel = findZoneMinLevel(idZone);
    return newZone(idZone, size[0], size[1], defaultValue, minLevel);
}

/*
 * display a zone on stdout (for debug purposes)
 * -- ZONE {id} --
 * 0   0   0   0
 * 0   0   0   0
 * 0   0   0   0
 * for a 3x4 zone
 */
void printZone(Zone zone) {
    printf("-- ZONE %d --\n", zone.zoneId);
    printGrid((int8_t**)zone.grid, zone.numberRows, zone.numberColumns);
}

/*
 * free a struct Zone and its grid
 * take the address of the struct Zone (&zone)
 */
void freeZone(Zone* zone){
    if(NULL == zone) {
        return;
    }
    freeArrayTwoDim((int8_t**)zone->grid, zone->numberRows);
    free(zone);
}

/**
 * find the size of a zone in the config file with the key "zone_{id}_size"
 * @param idZone Id of the zone
 * @return [x, y] where x is the number of rows and y of columns ( by default [10,10] )
 */
int* findZoneSize(int8_t idZone) {
    char key[100];
    sprintf(key, "zone_%d_size", idZone);
    IntArray* values = findIntArrayInConfigFile(key);
    // Pour ce genre de condition un peu longue et complexe et qu'on ne comprend pas au premier coup d'oeil
    // Préféré : int descriptionDuBooléen = values == NULL || values->size != 2 || values->array == NULL;
    // Puis on passe dans la condition 
    // if (descriptionDuBooléen) ...
    if(NULL == values || values->size != 2 || NULL == values->array) {
        int* defaultSize = malloc(sizeof(int) * 2);
        defaultSize[0] = 10;
        defaultSize[1] = 10;
        return defaultSize;
    }
    int* dimensions = values->array;
    free(values);
    return dimensions;
}

/**
 * Fetch in the config file the minimum level to access to a zone
 * @return the minimum level to access the zone
 */
int8_t findZoneMinLevel(int8_t zoneId) {
    char key[100] = "";
    sprintf(key, "zone_%d_minimum_level", zoneId);
    return findIntValueInConfigFile(key);
}

/**
 * Set a value in the zone at a specific point (x,y)
 */
void setZoneValueAtPosition(Zone* zone, int16_t x, int16_t y, CellValue value) {
    if (NULL == zone || !isPointInZone(x,y,*zone)) {
        return;
    }
    zone->grid[y][x] = (int8_t) value;
}

/**
 * @return true if a point(x,y) is a valid cell of the grid zone, false if not
 */
bool isPointInZone(int16_t x, int16_t y, Zone zone) {
    bool isXInZone = x >= 0 && x < zone.numberColumns;
    bool isYInZone = y >= 0 && y < zone.numberRows;
    return isXInZone && isYInZone;
}

/**
 * @return The value of a point (x,y) of the zone
 */
CellValue getZoneValueAtPosition(Zone zone, int16_t x, int16_t y) {
    if(!isPointInZone(x,y,zone)) {
        return GridValueError;
    }
    return (CellValue) zone.grid[y][x];
}

/**
 * @return the first position of a grid cell in a zone by the GridValue
 */
Location findTheFirstLocationOfAGridValueInZone(Zone zone, CellValue searchedValue) {
    Location location = {-1,-1,-1};
    for(int y = 0; y < zone.numberRows ; y += 1) {
        for(int x = 0; x < zone.numberColumns; x += 1) {
            if( getZoneValueAtPosition(zone, x, y) == searchedValue ) {
                //found
                location.zoneId = zone.zoneId;
                location.x = x;
                location.y = y;
                return location;
            }
        }
    }

    //not found
    location.zoneId = -1;
    location.x = -1;
    location.y = -1;
    return location;
}