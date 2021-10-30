//
// Created by Théo Omnès on 27/10/2021.
//

#include "collect_resources.h"

FILE* openCollectResourcesFile() {
    char path[PATH_MAX];
    char* projectDirectoryAbsolutePath = getProjectDirectory();
    sprintf(path, "%s%s%s", projectDirectoryAbsolutePath, PATH_SEPARATOR, "resources/collect_resources.txt");
    free(projectDirectoryAbsolutePath);
    return fopen(path, "r");
}

CollectResourceInfo getCollectInfoByGridValue(GridValues resourceToCollect) {
    FILE* collectResourcesFile = openCollectResourcesFile();
    CollectResourceInfo collectInfo;
    char line[255];
    while(!feof(collectResourcesFile)) {
        fgets(line, 255, collectResourcesFile);
        if(line[0] == '#' || strlen(line) <= 2) {
            continue;
        }
        collectInfo = convertCollectInfoLineToStruct(line);
        if(collectInfo.gridResource == resourceToCollect) {
            return collectInfo;
        }
    }

    fclose(collectResourcesFile);
    CollectResourceInfo notFound = {GridValueError, 0, 0 , 0, 0, 0};
    return notFound;
}

CollectResourceInfo convertCollectInfoLineToStruct(char* line) {
    CollectResourceInfo collectInfo;
    sscanf(line, "%d;%d;%d;%d;%lf;%d",
    &collectInfo.gridResource,
    &collectInfo.collectedResource,
    &collectInfo.minQuantityCollected,
    &collectInfo.maxQuantityCollected,
    &collectInfo.collectUsury,
    &collectInfo.minTool
    );

    return collectInfo;
};

void printCollectResourceInfo(CollectResourceInfo collectInfo) {
    printf(ANSI_COLOR_YELLOW);
    printf("\n-- Collect Resources Info --");
    printf("\nGridValue to collect: %d", collectInfo.gridResource);
    printf("\nItem collected: %d", collectInfo.collectedResource);
    printf("\nCollect [%d,%d] items randomly", collectInfo.minQuantityCollected, collectInfo.maxQuantityCollected);
    printf("\nUsury of the collect: %.2lf", collectInfo.collectUsury);
    printf("\nMinimum tool to collect: %d", collectInfo.minTool);
    printf("\n");
    printf(ANSI_COLOR_RESET);
}

bool isPlayerAbleToCollectResource(Character* player, GridValues resource) {
    CollectResourceInfo collectInfo = getCollectInfoByGridValue(resource);
    int8_t playerHand = player->bag->currentSlot;
    Item currentTool = player->bag->slots[playerHand]->item;
    return isToolAbleToCollectResource(currentTool, collectInfo);
}

bool isToolAbleToCollectResource(Item item, CollectResourceInfo collectInfo) {
    if(NULL == item.object) {
        return NULL;
    }
    Tool* tool = (Tool*)item.object;
    Tool minTool = getToolByItemId(collectInfo.minTool);
    int newDurability = (int)(item.durability - (collectInfo.collectUsury * item.maxDurability));
    bool isToolGoodFamily = tool->family == minTool.family;
    bool isMaterialHardEnough = tool->material >= minTool.material;
    bool isToolHasEnoughDurability = newDurability > 0;
    return isToolGoodFamily && isMaterialHardEnough && isToolHasEnoughDurability ;
}

void collectResource(Character* player, Map* map, Direction direction) {

    GridValues toCollect = getGridValueToCollect(player, map, direction);
    CollectResourceInfo info = getCollectInfoByGridValue(toCollect);

    if(!isPlayerAbleToCollectResource(player, toCollect)) {
        return;
    }
    int numberOfItemCollected = randomIntInRange(info.minQuantityCollected, info.maxQuantityCollected);
    Item collected = newResource(info.collectedResource);
    addItemsInBag(player->bag, collected, numberOfItemCollected);
    applyCollectUsuryOnTool(getCurrentBagSlot(player->bag), info.collectUsury);
    removeCellAfterCollect(player, map, direction);
    //TODO add in the respawn loop
}

int randomIntInRange(int lowerBound, int upperBound) {
    return rand() % (upperBound - lowerBound + 1) + lowerBound;
}

GridValues getGridValueToCollect(Character* player, Map* map, Direction direction) {
    Location locationToCollect = getLocationInDirection(*player->location, direction);
    return getZoneValueAtPosition(*getZoneById(map, player->location->zoneId), locationToCollect.x, locationToCollect.y);
}


void removeCellAfterCollect(Character* player, Map* map, Direction direction) {
    Location locationToCollect = getLocationInDirection(*player->location, direction);
    setZoneValueAtPosition(getZoneById(map, player->location->zoneId), locationToCollect.x, locationToCollect.y, Ground);
}

int applyCollectUsuryOnTool(BagSlot* toolSlot, double usury) {
    Item tool = toolSlot->item;
    int durabilityRemoved = (int)(usury * tool.maxDurability);
    toolSlot->item.durability = tool.durability - durabilityRemoved;
    return durabilityRemoved;
}