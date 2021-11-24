//
// Created by Théo Omnès on 14/11/2021.
//

#ifndef MALLOCWORLD_START_H
#define MALLOCWORLD_START_H

#include "../map/map.h"
#include "../perlin_noise/perlin_noise.h"
#include "../cli/cli.h"
#include "../turn_based/turn_based.h"

typedef struct Mallocworld {
    Player* player;
    Map* map;
} Mallocworld;

Map* initMap();
void fillMapWithResourcesProcedurally(Map* map);
void fillZoneWithResourcesProcedurally(Zone* zone);
IntArray* findZoneResources(int zoneId);
void addResourceInZoneProcedurally(CellValue resource, Zone* zone);
void proceduralZoneFillingWithCell(Zone* zone, Cell cell);
void addLayerToZone(Zone* layer, Zone* zone);
Mallocworld onSelectNewGame();
Mallocworld onSelectRestoreGame();
void mallocworld();
void freeMallocWorld(Mallocworld world);
Mallocworld newMallocWorld(Player* player, Map* map);
Mallocworld initGame();
Mallocworld startMenu();
bool worldIsEmpty(Mallocworld world);
Mallocworld restoreLastGame();

#endif //MALLOCWORLD_START_H
