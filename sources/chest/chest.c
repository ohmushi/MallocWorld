//
// Created by Théo Omnès on 21/10/2021.
//

#include "chest.h"
#include <stdint.h>

/**
 * Add item in the chest, so the save file in the -- STORAGE -- section
 * if the item is already stored, add the quantity to the one in the file
 * else add a line in the save file with the quantity
 * @param itemId
 * @param quantityToAdd > 0
 * @return The quantity added in the chest ( the quantity wanted, or 0 if failed)
 */
int addItemsInChest(ItemId itemId, int quantityToAdd) {
    //TODO refactor : not insert line by line, create a big string, work on it, then insert the entire string in the file
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
    return added == true ? quantityToAdd : 0;
}

/**
 * Browse the save file until find the item with the wanted Id
 * @return A ChestSlot {idItem, quantity}, if not found, the id is Empty (0)
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

/**
 * Find the line of the item in the Save file and
 * replace the quantity with the new one
 * @return True if the Save file has been updated or false if not
 */
bool updateItemQuantityInChest(ItemId itemId, int8_t newQuantity) {
    char* formatLine = findStringValueInConfigFile("format_slot_chest");
    char newLine[255];
    char oldLine[255];
    ChestSlot oldSlot = findItemInChest(itemId);
    if(oldSlot.id == Empty) { // Not found
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

/**
 * Add a line in the save file with the data in slotToAdd
 * Fail if the item to add is already in the storage section
 * @return True if the slot has benn inserted, false if failed
 */
bool insertChestSlotInSaveFile(ChestSlot slotToAdd) {
    FILE* saveFile = openSaveFile("a+"); //at the end of the file -> inventory is the last section
    if(NULL == saveFile) {
        return false;
    }
    if(findItemInChest(slotToAdd.id).id != Empty) {
        // error -> s-the slot of this item already exists
        return false;
    }

    char* formatLine = findStringValueInConfigFile("format_slot_chest");
    char lineToAdd[100];
    sprintf(lineToAdd, formatLine, slotToAdd.quantity, slotToAdd.id);
    addLineInFile(saveFile, lineToAdd, "\n");

    free(formatLine);
    fclose(saveFile);
    return true;
}

/**
 * Remove the quantity wanted of a ChestSlot by itemId
 * update the line in the save file with the new quantity
 * @param itemId
 * @param quantityToRemove >= 0
 * @return The quantity removed
 */
int removeItemsFromChest(ItemId itemId, int quantityToRemove) {
    ChestSlot foundSlot = findItemInChest(itemId);
    int removed = 0;
    if(quantityToRemove < 0 || foundSlot.id == Empty || foundSlot.quantity < 0) {
        return -1;
    }
    int newQuantity = foundSlot.quantity - quantityToRemove;
    if(newQuantity > 0) {
        updateItemQuantityInChest(itemId, newQuantity);
        return quantityToRemove;
    } else {
        updateItemQuantityInChest(itemId, 0);
        return foundSlot.quantity;
    }
}