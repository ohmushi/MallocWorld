//
// Created by Théo Omnès on 27/10/2021.
//

#ifndef MALLOCWORLD_COLLECT_RESOURCES_H
#define MALLOCWORLD_COLLECT_RESOURCES_H


#include <stdio.h>
#include <string.h>

#include "../config/config.h"
#include "../map/cell.h"
#include "../item/item_id.h"
#include "../tests/test.h"
#include "../player/player.h"
#include "../item/tool/tool.h"
#include "../movement/movement.h"
#include "../item/craft_resource/craft_resource.h"
#include "../random/random.h"



#define NUMBER_OF_COLLECTABLE_RESOURCES 9

typedef struct CollectResourceInfo {
    CellValue gridResource;
    ItemId collectedResource;
    int minQuantityCollected;
    int maxQuantityCollected;
    double collectUsury;
    ItemId minTool;
} CollectResourceInfo;


FILE* openCollectResourcesFile();
CollectResourceInfo getCollectInfoByGridValue(CellValue resourceToCollect);
CollectResourceInfo convertCollectInfoLineToStruct(char* line);
void printCollectResourceInfo(CollectResourceInfo collectInfo);
bool isPlayerAbleToCollectResource(Player* player, CellValue resource);
bool isToolAbleToCollectResource(Item tool, CollectResourceInfo collectInfo);
void collectResource(Player* player, Map* map, Direction direction);
CellValue getGridValueToCollect(Player* player, Map* map, Direction direction);
void removeCellAfterCollect(Player* player, Map* map, Direction direction);
int applyCollectUsuryOnTool(BagSlot* toolSlot, double usury);
void displayPlayerCannotCollectResource();

#endif //MALLOCWORLD_COLLECT_RESOURCES_H