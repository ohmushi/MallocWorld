//
// Created by Théo Omnès on 29/10/2021.
//

#include "tool.h"
#include <stdlib.h>
#include "../../config/config.h"

Item* newTool(ItemId id, const char* name, int16_t durability, Material material, ToolType type) {
    Tool* tool = malloc(sizeof(Tool));
    tool->material = material;
    tool->type = type;
    return newItem(id, name, false,durability, tool);
}

bool isMaterialHardEnough(Material toTest, Material minimum) {
    return toTest >= minimum;
}

Tool getToolByItemId(ItemId id) {
    Tool tool;
    FILE* toolFile = openToolsFile("r");
    char line[255];
    while(fgets(line, 255,toolFile) , !feof(toolFile)) {
        if(line[0] != '#' && strlen(line) > 2) {
            sscanf(line, "%d;%d;%d", &tool.itemId, &tool.material, &tool.type);
            if(tool.itemId == id) {
                return tool;
            }
        }
    }
    return tool;
}

FILE* openToolsFile(const char* mode) {
    char* path = getConfigFilePath();
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