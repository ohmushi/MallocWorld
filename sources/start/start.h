//
// Created by Théo Omnès on 14/11/2021.
//

#ifndef MALLOCWORLD_START_H
#define MALLOCWORLD_START_H

#include "../map/map.h"
#include "../perlin_noise/perlin_noise.h"

Map* initMap();
void fillMapWithResourcesProcedurally(Map* map);
void fillZoneWithResourcesProcedurally(Zone* zone);
IntArray* findZoneResources(int zoneId);
void addResourceInZoneProcedurally(CellValue resource, Zone* zone);
void proceduralZoneFillingWithCell(Zone* zone, Cell cell);
void addLayerToZone(Zone* layer, Zone* zone);

#endif //MALLOCWORLD_START_H
