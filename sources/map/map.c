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
    map->zones = zones;
    return map;
}

/*
 * print the zones of the map for debug purposes
 */
void printMap(Map map){
    printf("\n=== MAP ===\n");
    for(int i = 0; i < map.numberOfZones; i += 1){
        printZone( *(map.zones[i]) );
    }
}

/*
 * free a struct Map its Zones
 */
void freeMap(Map* map) {
    if(map == NULL) {
        return;
    }
    for(int i = 0; i < map->numberOfZones; i++) {
        freeZone( map->zones[i] );
    }
    free(map);
}

Map* createMap() {
    int8_t numberOfZones = findNumberOfZones();
    Zone** zones = malloc(sizeof(Zone*) * numberOfZones);
    char key[100];
    for(int i = 0; i < numberOfZones; i += 1) {
        zones[i] = createZone(i + 1, Ground); // i + 1: zones ids starts to 1
    }
    return newMap(numberOfZones, zones);
}

int8_t findNumberOfZones() {
    int8_t numberOfZones = findIntValueInConfigFile("number_of_zones");
    return numberOfZones < 1 ? 1 : numberOfZones;
}