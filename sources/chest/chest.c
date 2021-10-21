//
// Created by Théo Omnès on 21/10/2021.
//

#include "chest.h"
#include <stdint.h>


int addItemsInChest(Item* items, int quantity) {
    if(quantity < 0) {
        return 0;
    }
    //find item in chest
    //if found setItemInChest
    //if not found insertItemInChest
    return 0;
}

ChestSlot findItemInChest(ItemId id) {
    ChestSlot slot = {0, 0};
    FILE* saveFile = openSaveFileAndSeek("r", "-- STORAGE --");
    char line[255];
    char* formatLine = findStringValueInConfigFile("format_item_chest");
    while(!feof(saveFile)) {
        fgets(line, 255,saveFile);
        sscanf(line, formatLine, &slot.quantity, &slot.id);
        if(slot.id == id) {
            break;
        }
    }
    fclose(saveFile);
    free(formatLine);
    return slot;
}