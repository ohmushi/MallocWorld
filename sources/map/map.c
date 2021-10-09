//
// Filename: map.c
//
// Made by Théo Omnès on 09/10/2021.
//
// Description:
//

#include "map.h"
#include <stdlib.h>
#include <stdio.h>

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

void fillArrayTwoDim(int8_t** array, int16_t numberRows, int16_t numberColumns, int8_t defaultValue){
    for(int16_t i = 0; i < numberRows; i++) {
        for(int16_t j = 0; j < numberColumns; j++) {
            array[i][j] = defaultValue;
        }
    }
}

int8_t** newGrid(int16_t numberRows, int16_t numberColumns, int8_t defaultValue) {
    int8_t** grid = newArrayTwoDim(numberRows, numberColumns);
    fillArrayTwoDim(grid, numberRows, numberColumns, defaultValue);
    return grid;
}

void printGrid(int8_t** grid, int16_t numberRows, int16_t numberColumns) {
    for(int16_t i = 0; i < numberRows; i++) {
        for(int16_t j = 0; j < numberColumns; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
}

Zone* newZone(int8_t numberZone, int16_t numberRows, int16_t numberColumns, int8_t defaultValue) {
    if(numberRows <= 1 || numberColumns <= 1){
        return NULL;
    }
    Zone* zone = malloc(sizeof(Zone));
    if(zone == NULL){
        return NULL;
    }
    zone->numberZone = numberZone;
    zone->numberRows = numberRows;
    zone->numberColumns = numberColumns;
    zone->grid = newGrid(numberRows, numberColumns, defaultValue);
    return zone;
}

void printZone(Zone zone) {
    printf("-- ZONE %d --\n", zone.numberZone);
    printGrid(zone.grid, zone.numberRows, zone.numberColumns);
}

//TODO not let the size of the grid fix
Map* newMap(){
    Map* map = malloc(sizeof(Map));
    for(int i = 0; i < 3; i++){
        map->zonesList[i] = newZone( i+1, 4 , 4 , 0);
    }
    return map;
}

void printMap(Map map){
    printf("\n=== MAP ===\n");
    for(int i = 0; i < 3; i++){
        printZone( *(map.zonesList[i]) );
    }
}