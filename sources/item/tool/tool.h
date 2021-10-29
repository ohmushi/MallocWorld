//
// Created by Théo Omnès on 29/10/2021.
//

#ifndef MALLOCWORLD_TOOL_H
#define MALLOCWORLD_TOOL_H

#include "../item.h"
#include "../material.h"
#include "tool_type.h"
#include <stdio.h>

typedef struct Tool {
    ItemId itemId;
    Material material;
    ToolType type;
} Tool;


Item* newTool(ItemId id, const char* name, int16_t durability, Material material, ToolType type);
bool isMaterialHardEnough(Material toTest, Material minimum);
Tool getToolByItemId(ItemId id);
FILE* openToolsFile(const char* mode);
char* getToolsFileAbsolutePath();

#endif //MALLOCWORLD_TOOL_H
