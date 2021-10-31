//
// Created by Théo Omnès on 29/10/2021.
//

#include "tool.h"
#include <stdlib.h>
#include "../../config/config.h"

/**
 * TODO remove the object in item
 * @return Item corresponding of the searched Tool, with the Tool* in the item.object
 */
Item newTool(ItemId id, char* name) {
    Tool* tool = malloc(sizeof(Tool));
    *tool = getToolByItemId(id);
    if(tool->itemId == Empty) {
        return newStructItem(Empty, "", false, 0, tool, ToolType);
    }
    return newStructItem(id, name, false, tool->durability, tool, ToolType);
}

/**
 * @return The struct Tool of the parameters
 */
Tool newStructTool(ItemId id, Material material, ToolFamily family, int16_t durability) {
    Tool tool;
    tool.itemId = id;
    tool.material = material;
    tool.family = family;
    tool.durability = durability;
    return tool;
}

/**
 *
 * @param toTest
 * @param minimum
 * @return True if the material >= minimumMaterial
 */
bool isMaterialHardEnough(Material toTest, Material minimum) {
    return toTest >= minimum;
}

/**
 * Fetch if the tools file the Tool characteristics
 * @param id The ItemId of the searched Tool
 * @return The struct Tool searched
 */
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

/**
 * Open with the wanted mode (r,w,a) the tools file
 * by default in "/resources/tools.txt"
 * @param mode
 * @return
 */
FILE* openToolsFile(const char* mode) {
    char* path = getToolsFileAbsolutePath();
    FILE* toolsFile = fopen(path, mode);
    free(path);
    return toolsFile;
}

/**
 * Get the absolute path in FS of the tools file
 * concatenate the directory absolute path with the tools file relative path
 * by default in "/resources/tools.txt"
 * @return
 */
char* getToolsFileAbsolutePath() {
    char* projectDirectory = getProjectDirectory();
    char* path = malloc(sizeof(char) * PATH_MAX);
    sprintf(path, "%s" PATH_SEPARATOR "%s", projectDirectory, "resources/tools.txt");
    free(projectDirectory);
    return path;
}

/**
 * Display in stdout the Tool
 */
void printTool(Tool tool) {
    printf("\n-- Tool %d --", tool.itemId);
    printf("\nMaterial: %d", tool.material);
    printf("\nFamily: %d", tool.family);
    printf("\nDurability: %d\n", tool.durability);
}