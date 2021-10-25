//
// Filename: bag.c
//
// Made by Théo Omnès on 09 oct. 2021.
//
// Description:
//

#include "bag.h"
#include <stdio.h>



/**
 * Allocate a struct BagSlot with the item, the quantity of this item,
 * and the capacity of storage in this new slot
 */
BagSlot* newBagSlot(Item* item, int8_t quantity, int8_t capacity) {
    BagSlot* bagSlot = malloc(sizeof(BagSlot));
    bagSlot->item = item;
    bagSlot->capacity = capacity;
    bagSlot->quantity = quantity;
    return bagSlot;
}

/**
 * Print in stdout a slot with the format {quantity}{id - name}{durability}
 * @param slot
 */
void printSlot(BagSlot slot) {
    if(slot.item == NULL) {
        printf("{0}{0 - empty}{0}");
        return;
    }
    printf("{%d}{%d - %s}{%d}",
           slot.quantity,
           slot.item->id,
           slot.item->name,
           slot.item->durability);
}

/**
 * allocate a struct Bag.
 * The array of slots is fill with slot which have item to NULL
 * @param bagCapacity is the number of slots in the bag
 * @param slotsCapacity is the max quantity of each slot
 */
Bag* newBag(int8_t bagCapacity, int8_t slotsCapacity) {
    Bag* bag = malloc(sizeof(Bag));
    bag->capacity = bagCapacity;
    bag->slots = malloc(sizeof(BagSlot) * bagCapacity);
    for(int i = 0; i < bagCapacity; i++) {
        setBagSlotAtIndex(bag, i, newBagSlot(NULL, 0, slotsCapacity));
    }
    return bag;
}

/**
 * Print in stdout each slot of a Bag
 * @param bag to print
 */
void printBag(Bag bag) {
    printf("\n-- INVENTORY --\n");
    for(int i = 0; i < bag.capacity; i+= 1) {
        printSlot(*bag.slots[i]);
        printf("\n");
    }
}

/**
 * free the item in a BagSlot, then free the slot given.
 * You don't need to free the item inside the slot after.
 * @param bagSlot
 */
void freeBagSlot(BagSlot* bagSlot) {
    if(bagSlot == NULL) {
        return;
    }
    freeItem(bagSlot->item);
    bagSlot->item = NULL;
    free(bagSlot);
}

/**
 * free all the slots of a Bag, then free the struct Bag given.
 * You don't need to free the slots or the items inside the bag after.
 * @param bagSlot to free
 */
void freeBag(Bag* bag) {
    if(bag == NULL) {
        return;
    }
    for(int i = 0; i < bag->capacity; i++) {
        freeBagSlot(bag->slots[i]);
    }
}

/**
 * fetch the config file with the key "bag_size"
 * @return The found size of the inventory or 10 by default
 */
int8_t findBagCapacity() {
    int8_t capacity = findIntValueInConfigFile("bag_size");
    return capacity > 0 ? capacity : 10;
}

/**
 * fetch the config file with the key "bag_slot_capacity"
 * @return The found capacity of the item stack in inventory or 20 by default
 */
int8_t findBagSlotCapacity() {
    int8_t capacity = findIntValueInConfigFile("bag_slot_capacity");
    return capacity > 0 ? capacity : 20;
}

/**
 * Free the slot at the given position then affect the new slot
 * in the array of slots of the bag
 * @param bag
 * @param index
 * @param slot
 */
void setBagSlotAtIndex(Bag* bag, int index, BagSlot* slot) {
    if(index < 0 || index >= bag->capacity) {
        return;
    }
    freeBagSlot(bag->slots[index]);
    bag->slots[index] = slot;
}

/**
 * Get the value of the array of slots of a Bag at the given index
 */
BagSlot* getBagSlotAtIndex(Bag* bag, int index) {
    if(index < 0 || index >= bag->capacity) {
        NULL;
    }
    return bag->slots[index];
}

/**
 * Insert an Item in a bag,
 * If the item is not stackable:
 *  find the first empty slot and insert the item in it
 * If the item is stackable:
 *  find the first slot of the corresponding item type with remaining space (or the first empty slot)
 *  and insert the Item in it
 * @return true if the item has been added, false if not.
 */
bool addItemInBag(Bag* bag, Item* itemToAdd) {
    BagSlot* availableSlot;
    if(itemToAdd->isStackable) {
        availableSlot = searchFirstAvailableSlotByItemtypeInBag(bag, itemToAdd->type);
    } else {
        availableSlot = searchFirstEmptySlotInBag(bag);
    }
    if(availableSlot == NULL) {
        return false;
    }
    freeItem(availableSlot->item);
    availableSlot->quantity += 1;
    availableSlot->item = itemToAdd;
    return true;
}

/**
 * Browse the array of slots of the bag.
 * An empty Slot is a slot with its item set to NULL.
 * @return the first empty slot of the bag, or NULL if no slot is empty.
 */
BagSlot* searchFirstEmptySlotInBag(Bag* bag) {
    BagSlot* slot = NULL;
    for(int i = 0; i < bag->capacity; i += 1) {
        slot = bag->slots[i];
        if(slot->item == NULL) {
            slot->quantity = 0;
            return slot;
        }
    }
    return NULL;
}

/**
 * Get the first slot with remaining space and
 * in it an item that has the type you are looking for.
 * If no one is found, return the first empty slot or NULL if no slot is empty either.
 */
BagSlot* searchFirstAvailableSlotByItemtypeInBag(Bag* bag, ItemType searched) {
    BagSlot* slot = NULL;
    for(int i = 0; i < bag->capacity; i += 1) {
        slot = bag->slots[i];
        if(slot->item != NULL && slot->item->type == searched && slot->quantity < slot->capacity) {
            return slot;
        }
    }
    return searchFirstEmptySlotInBag(bag);
}

/**
 * Search the slots in bag where the searched item is in.
 * For each those slots, remove the quantity while the quantity to remove > 0
 * @return The quantity removed from the bag
 */
int removeItemsFromBag(Bag* bag, ItemId itemId, int quantityToRemove) {
    if(quantityToRemove <= 0) {
        return 0;
    }
    bool* maskOfSlots = searchSlotsByItemId(bag, itemId);
    int16_t numberOfSearchedItemInBag = countNumberOfItemsInBagByItemId(bag, itemId);
    int16_t removed = 0;
    BagSlot* slot;
    for(int i = 0; i < bag->capacity; i += 1) {
        if(maskOfSlots[i] == true) {
            slot = bag->slots[i];
            if(slot->quantity <= quantityToRemove) {
                quantityToRemove -= slot->quantity;
                removed += slot->quantity;
                slot->quantity = 0;
                freeItem(slot->item);
                slot->item = NULL;
            } else {
                slot->quantity -= quantityToRemove;
                removed += quantityToRemove;
                quantityToRemove = 0;
            }
        }
    }

    free(maskOfSlots);
    return removed;
}

bool* searchSlotsByItemId(Bag* bag, ItemId itemId) {
    bool* mask = malloc(sizeof(int8_t) * bag->capacity);
    BagSlot * slot;
    for(int i = 0; i < bag->capacity; i += 1) {
        slot = bag->slots[i];
        mask[i] = false;
        if(slot->item != NULL && slot->item->id == itemId) {
            mask[i] = true;
        }
    }
    return mask;
}

int16_t countNumberOfItemsInBagByItemId(Bag* bag, ItemId itemId) {
    bool* mask = searchSlotsByItemId(bag, itemId);
    int16_t count = 0;
    for (int i = 0; i < bag->capacity;i += 1) {
        if(mask[i] == true) {
            count += bag->slots[i]->quantity;
        }
    }
    return count;
}