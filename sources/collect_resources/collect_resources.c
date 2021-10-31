//
// Created by Théo Omnès on 27/10/2021.
//

#include "collect_resources.h"

/**
 * Open the collect resources file in read mode
 * The collect resource file contains the information of the collect
 * (cf struct CollectResourceInfo)
 * @return the FILE* of the collect resources file in read mode
 */
FILE* openCollectResourcesFile() {
    char path[PATH_MAX];
    char* projectDirectoryAbsolutePath = getProjectDirectory();
    sprintf(path, "%s%s%s", projectDirectoryAbsolutePath, PATH_SEPARATOR, "resources/collect_resources.txt");
    free(projectDirectoryAbsolutePath);
    return fopen(path, "r");
}

/**
 * Loop in the collect resources file and
 * get the grid cell collect information
 * (cf. struct CollectResourceInfo)
 * @param resourceToCollect GridValue
 * @return Struct CollectResourceInfo or a collect info of a GridValueError if not found
 */
CollectResourceInfo getCollectInfoByGridValue(CellValue resourceToCollect) {
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

/**
 * Convert a line of the collect resources file to a struct CollectResourceInfo
 * @param line String to convert
 * @return The converted string into a CollectResourceInfo
 */
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

/**
 * Display on stdout the information of the cell value collect
 */
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

/**
 * Check if a player is able to collect a resource:
 * if the tool in his hand is able to collect
 * @return True if the player is able to collect the resource, false if not
 */
bool isPlayerAbleToCollectResource(Character* player, CellValue resource) {
    CollectResourceInfo collectInfo = getCollectInfoByGridValue(resource);
    int8_t playerHand = player->bag->currentSlot;
    Item currentTool = player->bag->slots[playerHand]->item;
    return isToolAbleToCollectResource(currentTool, collectInfo);
}

/**
 * Check if a tool is able to collect a resource:
 *  - if the tool is of the good family (Pickaxe, Axe, Billhook)
 *  - if the material is hard enough (diamond is harder than wood)
 *  - if the tool has enough durability to collect
 */
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

/**
 * if the player is able to collect the resource,
 * generate a random number of item collected (in the specific range of the resource),
 * add the items in the bag and replace the cell value of the resource by Ground
 * //TODO add in the respawn loop
 * @param direction Direction in which the resource is located
 */
void collectResource(Character* player, Map* map, Direction direction) {
    CellValue toCollect = getGridValueToCollect(player, map, direction);
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

/**
 * @return an int in the given range [lower,upper]
 */
int randomIntInRange(int lowerBound, int upperBound) {
    return rand() % (upperBound - lowerBound + 1) + lowerBound;
}

/**
 * @return The CellValue in a direction from the location of the player
 */
CellValue getGridValueToCollect(Character* player, Map* map, Direction direction) {
    Location locationToCollect = getLocationInDirection(*player->location, direction);
    return getZoneValueAtPosition(*getZoneById(map, player->location->zoneId), locationToCollect.x, locationToCollect.y);
}

/**
 * Replace the CellValue in a direction from the location of the player by Ground
 */
void removeCellAfterCollect(Character* player, Map* map, Direction direction) {
    Location locationToCollect = getLocationInDirection(*player->location, direction);
    setZoneValueAtPosition(getZoneById(map, player->location->zoneId), locationToCollect.x, locationToCollect.y, Ground);
}

/**
 * Remove durability of the tool depending the usury of the resource to collect
 * @param toolSlot Slot which contains the tool to use
 * @param usury Double 0 <= usury <= 1, meaning the percentage of the max durability removed
 * @return The removed durability of the tool
 */
int applyCollectUsuryOnTool(BagSlot* toolSlot, double usury) {
    Item tool = toolSlot->item;
    int durabilityRemoved = (int)(usury * tool.maxDurability);
    toolSlot->item.durability = tool.durability - durabilityRemoved;
    return durabilityRemoved;
}