//
// Filename: map.c
//
// Made by Théo Omnès on 09 oct. 2021.
//
// Description:
//

#include "map.h"
#include <stdlib.h>
#include <stdio.h>

/*
 * create a struct Map
 * take the number of zones >= 1
 */
Map* newMap(int8_t numberOfZones, Zone** zones){
    if(numberOfZones < 1) {
        return NULL;
    }
    Map* map = malloc(sizeof(Map));
    map->numberOfZones = numberOfZones;
    map->zonesList = zones;
    return map;
}

/*
 * print the zones of the map for debug purposes
 */
void printMap(Map map){
    printf("\n=== MAP ===\n");
    for(int i = 0; i < 3; i++){
        printZone( *(map.zonesList[i]) );
    }
}

/*
 * free a struct Map its Zones and set the pointer to NULL
 * take the Map pointer's address (&map)
 */
void freeMap(Map** map) {
    Map* m = *map;
    if(m == NULL) {
        return;
    }
    for(int i = 0; i < m->numberOfZones; i++) {
        freeZone( m->zonesList[i] );
    }

    free(m);
    m = NULL;
}

Map* createMap() {
    int8_t numberOfZones = findNumberOfZones();
    //Map* map = newMap();
}

int8_t findNumberOfZones() {
    int8_t numberOfZones = findIntValueInConfigFile("number_of_zones");
    return numberOfZones < 1 ? 1 : numberOfZones;
}