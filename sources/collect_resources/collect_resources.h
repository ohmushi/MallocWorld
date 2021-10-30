//
// Created by Théo Omnès on 27/10/2021.
//

#ifndef MALLOCWORLD_COLLECT_RESOURCES_H
#define MALLOCWORLD_COLLECT_RESOURCES_H


#include <stdio.h>
#include <string.h>

#ifndef MALLOCWORLD_CONFIG_H
#include "../config/config.h"
#endif

#ifndef MALLOCWORLD_GRID_VALUES_H
#include "../map/grid_values.h"
#endif

#ifndef MALLOCWORLD_ITEM_ID_H
#include "../item/item_id.h"
#endif

#ifndef MALLOCWORLD_TEST_H
#include "../tests/test.h"
#endif

#ifndef MALLOCWORLD_CHARACTER_H
#include "../character/character.h"
#endif

#include <time.h>

#include "../item/tool/tool.h"
#include "../movement/movement.h"
#include "../item/craft_resource/craft_resource.h"

typedef struct CollectResourceInfo {
    GridValues gridResource;
    ItemId collectedResource;
    int minQuantityCollected;
    int maxQuantityCollected;
    double collectUsury;
    ItemId minTool;
} CollectResourceInfo;


FILE* openCollectResourcesFile();
CollectResourceInfo getCollectInfoByGridValue(GridValues resourceToCollect);
CollectResourceInfo convertCollectInfoLineToStruct(char* line);
void printCollectResourceInfo(CollectResourceInfo collectInfo);
bool isPlayerAbleToCollectResource(Character* player, GridValues resource);
bool isToolAbleToCollectResource(Item tool, CollectResourceInfo collectInfo);
void collectResource(Character* player, Map* map, Direction direction);
int randomIntInRange(int lowerBound, int upperBound);
GridValues getGridValueToCollect(Character* player, Map* map, Direction direction);
void removeCellAfterCollect(Character* player, Map* map, Direction direction);
int applyCollectUsuryOnTool(BagSlot* toolSlot, double usury);

#endif //MALLOCWORLD_COLLECT_RESOURCES_H