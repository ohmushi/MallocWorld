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
 * create a new two dimensions array of GridValues
 */
int8_t** newArrayTwoDim(int16_t numberRows, int16_t numberColumns){
    int8_t** arrayTwoDim = malloc(sizeof(int8_t*) * numberRows);
    if(arrayTwoDim == NULL){
        return NULL;
    }

    for( int i = 0; i < numberRows; i += 1 ){
        arrayTwoDim[i] = malloc(sizeof(int8_t) * numberColumns);
        if( arrayTwoDim[i] == NULL ) {
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

/*
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
    if(array == NULL){
        return;
    }
    for(int i = 0; i < numberRows; i += 1) {
        if( array[i] != NULL ) {
            free(array[i]);
        }
    }
    free(array);
}

/*
 * create a new struct Zone which contains :
 * the zone Id, the grid (a two dimensions array of int8_t) and its size (rows, cols)
 * Take the id of the zone, the size (rows, cols) and the default value to fill the grid
 */
Zone* newZone(int8_t zoneId, int16_t numberRows, int16_t numberColumns, GridValues defaultValue) {
    if(numberRows < 4 || numberColumns < 4){
        return NULL;
    }
    Zone* zone = malloc(sizeof(Zone));
    if(zone == NULL){
        return NULL;
    }
    zone->zoneId = zoneId;
    zone->numberRows = numberRows;
    zone->numberColumns = numberColumns;
    zone->grid = newGrid(numberRows, numberColumns, defaultValue);
    return zone;
}

/**
 *
 * @param idZone
 * @param defaultValue
 * @return Zone
 */
Zone* createZone(int8_t idZone, GridValues defaultValue) {
    int* size = findZoneSize(idZone);
    return newZone(idZone, size[0], size[1], defaultValue);
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
    if(zone == NULL) {
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
    if(values == NULL || values->size != 2 || values->array == NULL) {
        int* defaultSize = malloc(sizeof(int) * 2);
        defaultSize[0] = 10;
        defaultSize[1] = 10;
        return defaultSize;
    }
    int* dimensions = values->array;
    free(values);
    return dimensions;
}


void setGridValueAtPosition(Zone* zone, int16_t x, int16_t y, GridValues value) {
    if(zone == NULL || x < 0 || y < 0 || x >= zone->numberColumns || y >= zone->numberRows) {
        return;
    }
    zone->grid[y][x] = (int8_t) value;
}