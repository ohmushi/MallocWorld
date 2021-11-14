//
// Created by Théo Omnès on 14/11/2021.
//

#include "start.h"

Map* initMap() {
    Map* map = createMap();
    fillMapWithResourcesProcedurally(map);
    return map;
}

void fillMapWithResourcesProcedurally(Map* map) {
    for(int i = 0; i < map->numberOfZones; i += 1) {
        fillZoneWithResourcesProcedurally(map->zones[i]);
    }
}

void fillZoneWithResourcesProcedurally(Zone* zone) {
    /*int x, y;
    for(y = 0; y < zone->numberRows; y += 1){
        for(x = 0; x < zone->numberColumns; x += 1) {
            int value = (int)(perlin(x, y, 0.1, 2) * 100);

        }
    }*/
}

void addResourcesInZoneProcedurally(Zone* zone, CellValue resource) {
    Zone* layer = newZone(zone->id, zone->numberRows, zone->numberColumns, Ground, 0);
}