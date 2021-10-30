//
// Created by Théo Omnès on 29/10/2021.
//

#include "tool.h"
#include <stdlib.h>
#include "../../config/config.h"

Item newTool(ItemId id, char* name) {
    Tool* tool = malloc(sizeof(Tool));
    *tool = getToolByItemId(id);
    if(tool->itemId == Empty) {
        return newStructItem(Empty, "", false, 0, tool, ToolType);
    }
    return newStructItem(id, name, false, tool->durability, tool, ToolType);
}

Tool newStructTool(ItemId id, Material material, ToolFamily family, int16_t durability) {
    Tool tool;
    tool.itemId = id;
    tool.material = material;
    tool.family = family;
    tool.durability = durability;
    return tool;
}

bool isMaterialHardEnough(Material toTest, Material minimum) {
    return toTest >= minimum;
}

Tool getToolByItemId(ItemId id) {
    FILE* toolFile = openToolsFile("r");
    char line[255];
    while(fgets(line, 255,toolFile) , !feof(toolFile)) {
        Tool tool = newStructTool(Empty, -1, -1, 0);
        if(line[0] != '#' && strlen(line) > 2) {
            sscanf(line, "%d;%d;%d;%hd", &tool.itemId, &tool.material, &tool.family, &tool.durability);
            if(tool.itemId == id) {
                return tool;
            }
        }
    }
    return newStructTool(Empty, -1, -1, 0);
}

FILE* openToolsFile(const char* mode) {
    char* path = getToolsFileAbsolutePath();
    FILE* toolsFile = fopen(path, mode);
    free(path);
    return toolsFile;
}

char* getToolsFileAbsolutePath() {
    char* projectDirectory = getProjectDirectory();
    char* path = malloc(sizeof(char) * PATH_MAX);
    sprintf(path, "%s" PATH_SEPARATOR "%s", projectDirectory, "resources/tools.txt");
    free(projectDirectory);
    return path;
}

void printTool(Tool tool) {
    printf("\n-- Tool %d --", tool.itemId);
    printf("\nMaterial: %d", tool.material);
    printf("\nFamily: %d", tool.family);
    printf("\nDurability: %d\n", tool.durability);
}