//
// Created by Théo Omnès on 29/10/2021.
//

#include "tool.h"
#include <stdlib.h>

const Tool TOOLS[NUMBER_OF_TOOLS] = {
        {WoodPickaxe, WoodMaterial, Pickaxe, 10},
        {StonePickaxe, StoneMaterial, Pickaxe, 10},
        {IronPickaxe, IronMaterial, Pickaxe, 10},
        {WoodBillhook, WoodMaterial, Billhook, 10},
        {StoneBillhook, StoneMaterial, Billhook, 10},
        {IronBillhook, IronMaterial, Billhook, 10},
        {WoodAxe, WoodMaterial, Axe, 10},
        {StoneAxe, StoneMaterial, Axe, 10},
        {IronAxe, IronMaterial, Axe, 10}
};

/**
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
 * Fetch the tools list which contains each Tool characteristics
 * @param id The ItemId of the searched Tool
 * @return The struct Tool searched
 */
Tool getToolByItemId(ItemId id) {
    for(int i = 0; i < NUMBER_OF_TOOLS; i += 1) {
        if(TOOLS[i].itemId == id) {
            return TOOLS[i];
        }
    }
    //not found
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