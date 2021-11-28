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
int addItemsInChest(ItemId itemId, int quantityToAdd, Chest** chest) {
    if(quantityToAdd <= 0) {
        return 0;
    }
    bool added = false;
    ChestSlot foundInChest = findItemInChest(itemId, *chest);
    if(foundInChest.id != Empty) {
        added = updateItemQuantityInChest(itemId, foundInChest.quantity + quantityToAdd, chest);
    } else {
        ChestSlot slotToAdd = {itemId, quantityToAdd};
        pushSlotInChest(slotToAdd, chest);
        added = true;
    }
    return added == true ? quantityToAdd : 0;
}

/**
 * Browse the save file until find the item with the wanted Id
 * @return A ChestSlot {idItem, quantity}, if not found, the id is Empty (0)
 */
ChestSlot findItemInChest(ItemId id, Chest* chest) {
    while(chest != NULL) {
        if(chest->slot.id == id) {
            return chest->slot;
        }
        chest = chest->next;
    }
    ChestSlot notFound = {0,0};
    return notFound;
}

/**
 * Find the line of the item in the Save file and
 * replace the quantity with the new one
 * @return True if the Save file has been updated or false if not
 */
bool updateItemQuantityInChest(ItemId itemId, int8_t newQuantity, Chest** chest) {
    ChestSlot oldSlot = findItemInChest(itemId, *chest);
    if(oldSlot.id == Empty) { // Not found
        return false;
    }
    Chest* node = *chest;
    while(node != NULL) {
        if(node->slot.id == itemId) {
            node->slot.quantity = newQuantity;
        }
        node = node->next;
    }
    return true;
}

/**
 * Remove the quantity wanted of a ChestSlot by itemId
 * update the line in the save file with the new quantity
 * @param itemId
 * @param quantityToRemove >= 0
 * @return The quantity removed
 */
int removeItemsFromChest(ItemId itemId, int quantityToRemove, Chest** chest) {
    ChestSlot foundSlot = findItemInChest(itemId, *chest);
    int removed = 0;
    if(quantityToRemove < 0 || foundSlot.id == Empty || foundSlot.quantity < 0) {
        return -1;
    }
    int newQuantity = foundSlot.quantity - quantityToRemove;
    if(newQuantity > 0) {
        updateItemQuantityInChest(itemId, newQuantity, chest);
        return quantityToRemove;
    } else {
        updateItemQuantityInChest(itemId, 0, chest);
        return foundSlot.quantity;
    }
}

ChestSlot newChestSlot(int quantity, ItemId itemId) {
    ChestSlot slot;
    slot.quantity = quantity;
    slot.id = itemId;
    return slot;
}

void pushSlotInChest(ChestSlot slot, Chest** chest) {
    Chest* oldHead = *chest;
    Chest* newHead = malloc(sizeof(Chest));
    newHead->slot = slot;
    newHead->next = oldHead;
    *chest = newHead;
}

void printChest(Chest* chest) {
    while(chest != NULL) {
        printChestSlot(chest->slot);
        chest = chest->next;
    }
}

void printChestSlot(ChestSlot slot) {
    Item item = findItemById(slot.id);
    printf("\n[%d %s] x %d", item.id, item.name, slot.quantity);
}