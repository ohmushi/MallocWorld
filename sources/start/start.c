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
    IntArray* zoneResources = findZoneResources(zone->id);
    for(int i = 0; i < zoneResources->size; i += 1) {
        addResourceInZoneProcedurally(zoneResources->array[i], zone);
    }
    freeIntArray(zoneResources);
}

IntArray* findZoneResources(int zoneId) {
    char key[100];
    sprintf(key, "zone_%d_resources", zoneId);
    return findIntArrayInConfigFile(key);
}

void addResourceInZoneProcedurally(CellValue resource, Zone* zone) {
    Zone* layer = newZone(zone->id, zone->numberRows, zone->numberColumns, Ground, 0);
    proceduralZoneFillingWithCell(layer, findCell(resource));
    addLayerToZone(layer, zone);
    freeZone(layer);
}

void proceduralZoneFillingWithCell(Zone* zone, Cell cell) {
    int x, y;
    int delta = cell.id * cell.id;
    setSeed(getSeed() + delta);
    for(y = 0; y < zone->numberRows; y += 1){
        for(x = 0; x < zone->numberColumns; x += 1) {
            double scale = 0.2;
            double value = perlin(x, y, scale, 2);
            if (value < cell.spawnFrequency) {
                setZoneValueAtPosition(zone, x, y, cell.id);
            } else {
                setZoneValueAtPosition(zone, x, y, Ground);
            }
        }
    }
    setSeed(getSeed() - delta);
}

void addLayerToZone(Zone* layer, Zone* zone) {
    for(int y = 0; y < zone->numberRows; y += 1) {
        for(int x = 0; x < zone->numberColumns; x += 1) {
            CellValue currentCell = getZoneValueAtPosition(*layer, x, y);
            if(currentCell != Ground) {
                setZoneValueAtPosition(zone, x, y, currentCell);
            }
        }
    }
}


Mallocworld startMenu() {
    int numberOfOptions = 3;
    char* options[] = {
           "Nouvelle partie",
           "Reprendre",
           "Quitter"
    };
    displayMenu("MallocWord", "", numberOfOptions, options);
    int choice = getPlayerChoice(numberOfOptions);
    Mallocworld world = newMallocWorld(NULL, NULL);
    switch (choice) {
        case 0: world = onSelectNewGame(); break;
        case 1: world = onSelectRestoreGame(); break;
        case 2: world = newMallocWorld(NULL, NULL); break;
        default: world = newMallocWorld(NULL, NULL);
    }
    return world;
}

Mallocworld onSelectNewGame() {
    printf("\nNEW GAME !");
    char* seed = input("\nSeed (random if empty): ");
    if (strlen(seed) == 0) {
        setSeed(randomIntInRange(0, 255));
    } else {
        setSeedFromString(seed);
    }
    return initGame();
}

Mallocworld onSelectRestoreGame() {
    Mallocworld world = restoreLastGame();
    if (worldIsEmpty(world)) {
        displayNoGameToRestore();
    }
    return world;
}

void displayNoGameToRestore() {
    displayCliNoGameToRestore();
}

void mallocworld() {
    while(true) {
        Mallocworld world = startMenu();
        if(worldIsEmpty(world)) {
            return;
        }
        newGame(world.player, world.map);
        freeMallocWorld(world);
    }
}

bool worldIsEmpty(Mallocworld world) {
    return NULL == world.player || NULL == world.map;
}

Mallocworld newMallocWorld(Player* player, Map* map) {
    Mallocworld world;
    world.player = player;
    world.map = map;
    return world;
}

void freeMallocWorld(Mallocworld world) {
    freeMap(world.map);
    freePlayer(world.player);
}

Mallocworld restoreLastGame() {
    Player* player = getPlayerFromRestoreFile();
    Map* map = getMapFromRestoreFile();
    return newMallocWorld(player, map);
}