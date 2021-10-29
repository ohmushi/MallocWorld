//
// Created by Théo Omnès on 27/10/2021.
//

#include "collect_resources.h"

FILE* openCollectResourcesFile() {
    char path[PATH_MAX];
    char* projectDirectoryAbsolutePath = getProjectDirectory();
    sprintf(path, "%s%s%s", projectDirectoryAbsolutePath, PATH_SEPARATOR, "resources/collect_resources.txt");
    printf("%s", path);
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
    if(item.object == NULL) {
        return NULL;
    }
    Tool* tool = (Tool*)item.object;
    Tool minTool = getToolByItemId(collectInfo.minTool);
    int newDurability = (int)(item.durability - (collectInfo.collectUsury * item.maxDurability));
    return tool->type == minTool.type && tool->material >= minTool.material &&  newDurability > 0;
}