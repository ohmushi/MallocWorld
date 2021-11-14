//
// Created by Théo Omnès on 29/10/2021.
//

#ifndef MALLOCWORLD_TOOL_H
#define MALLOCWORLD_TOOL_H

#include "../item.h"
#include "../material.h"
#include "../../config/config.h"
#include "tool_family.h"
#include <stdio.h>

#define NUMBER_OF_TOOLS 9

typedef struct Tool {
    ItemId itemId;
    Material material;
    ToolFamily family;
    int16_t durability;
} Tool;


Tool newStructTool(ItemId id, Material material, ToolFamily family, int16_t durability);
Item newTool(ItemId id);
bool isMaterialHardEnough(Material toTest, Material minimum);
Tool getToolByItemId(ItemId id);
FILE* openToolsFile(const char* mode);
char* getToolsFileAbsolutePath();
void printTool(Tool tool);


#endif //MALLOCWORLD_TOOL_H
