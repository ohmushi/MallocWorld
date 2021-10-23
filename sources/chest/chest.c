//
// Created by Théo Omnès on 21/10/2021.
//

#include "chest.h"
#include <stdint.h>


bool addItemsInChest(ItemId itemId, int quantityToAdd) {
    if(quantityToAdd < 0) {
        return 0;
    }
    bool added = false;
    ChestSlot foundInChest = findItemInChest(itemId);
    if(foundInChest.id != Empty) {
        added = updateItemQuantityInChest(itemId, foundInChest.quantity + quantityToAdd);
    } else {
        ChestSlot slotToAdd = {itemId, quantityToAdd};
        added = insertChestSlotInSaveFile(slotToAdd);
    }
    return added;
}

/**
 *
 * @param id
 * @return
 */
ChestSlot findItemInChest(ItemId id) {
    ChestSlot slot = {0, 0};
    FILE* saveFile = openSaveFileAndSearchNextLine("r", "-- STORAGE --");
    char line[255];
    char* formatLine = findStringValueInConfigFile("format_slot_chest");
    while(!feof(saveFile)) {
        fgets(line, 255,saveFile);
        sscanf(line, formatLine, &slot.quantity, &slot.id);
        if(slot.id == id) {
            fclose(saveFile);
            free(formatLine);
            return slot;
        }
    }
    fclose(saveFile);
    free(formatLine);
    ChestSlot notFound = {0,0};
    return notFound;
}

bool updateItemQuantityInChest(ItemId itemId, int8_t newQuantity) {
    char* formatLine = findStringValueInConfigFile("format_slot_chest");
    char newLine[255];
    char oldLine[255];
    ChestSlot oldSlot = findItemInChest(itemId);
    if(oldSlot.id == Empty) {
        return false;
    }

    sprintf(newLine,formatLine, newQuantity, itemId );
    sprintf(oldLine, formatLine, oldSlot.quantity, itemId);
    FILE* saveFile = openSaveFileAndSearch("r+", oldLine);
    fputs(newLine, saveFile);

    fclose(saveFile);
    free(formatLine);
    return true;
}

bool insertChestSlotInSaveFile(ChestSlot slotToAdd) {
    FILE* saveFile = openSaveFile("a+"); //at the end of the file -> inventory is the last section
    if(saveFile == NULL) {
        return false;
    }
    if(findItemInChest(slotToAdd.id).id != Empty) {
        // error -> s-the slot of this item already exists
        return false;
    }

    char* formatLine = findStringValueInConfigFile("format_slot_chest");
    char lineToAdd[100];
    sprintf(lineToAdd, formatLine, slotToAdd.quantity, slotToAdd.id);
    addLineInFile(saveFile, lineToAdd, "");

    free(formatLine);
    fclose(saveFile);
    return true;
}