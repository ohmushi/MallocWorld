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
BagSlot* newBagSlot(Item item, int8_t quantity, int8_t capacity) {
    BagSlot* bagSlot = malloc(sizeof(BagSlot));
    bagSlot->capacity = capacity;
    bagSlot->quantity = quantity;
    bagSlot->item = item;
    return bagSlot;
}

/**
 * Print in stdout a slot with the format {quantity}{id - name}{durability}
 * @param slot
 */
void printSlot(BagSlot slot) {
    printf("{%d}{%d - %s}{%d}",
           slot.quantity,
           slot.item.id,
           slot.item.name,
           slot.item.durability);
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
        Item empty = {Empty};
        setBagSlotAtIndex(bag, i, newBagSlot(empty, 0, slotsCapacity));
    }
    return bag;
}

/**
 * allocate a stuct Bag with data found in config file
 * bag capacity (number of slots) : "bag_size"
 * slots capacity (number of items max in one slot) : "bag_slot_capacity"
 */
Bag* createBag() {
    return newBag(
            findBagCapacity(),
            findBagSlotCapacity()
            );
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
 * @return the quantity added
 */
int addItemsInBag(Bag* bag, Item itemToAdd, int quantityToAdd) {
    if(quantityToAdd <= 0) {
        return 0;
    }
    if(itemToAdd.isStackable) {
        return addStackableItemsInBag(bag, itemToAdd, quantityToAdd);
    } else {
        return addNotStackableItemsInBag(bag, itemToAdd, quantityToAdd);
    }
}

/**
 * Add items which are stackable (more than one item in a slot) in a bag (array of slots)
 * First loop on the slots already containing the same itemId than the item to add
 * and add the whanted quantity until the slot is full then pass to the next slot.
 * Once the slots of the same ItemId are full, loop on the empty slots and fill them
 * @return the total quantity of items added
 */
int addStackableItemsInBag(Bag* bag, Item itemToAdd, int quantityToAdd) {
    int added = 0;
    bool* mask = searchSlotsByItemId(bag, itemToAdd.id);
    int addedOnThisSlot = 0;
    for(int i = 0; i < bag->capacity; i += 1) {
        BagSlot* slot = bag->slots[i];
        if(mask[i] == true) {
            addedOnThisSlot = addStackableItemsInSlot(slot, itemToAdd.id, quantityToAdd);
            quantityToAdd -= addedOnThisSlot;
            added += addedOnThisSlot;
        }
    }
    BagSlot* availableSlot = NULL;
    while(quantityToAdd > 0 && (availableSlot = searchFirstEmptySlotInBag(bag)) != NULL) {
        addedOnThisSlot = addStackableItemsInSlot(availableSlot,itemToAdd.id, quantityToAdd);
        quantityToAdd -= addedOnThisSlot;
        added += addedOnThisSlot;
    }
    free(mask);
    return added;
}

/**
 * Add items which are stackable (more than one item in a slot) in a particular slot
 * The quantity added is limited by the slot capacity.
 * @param slot to add in
 * @return the quantity added in this slot (max = slot capacity - start slot quantity)
 */
int addStackableItemsInSlot(BagSlot* slot, ItemId itemId, int quantityToAdd) {
    int addedOnThisSlot = 0;
    if(slot->quantity + quantityToAdd >= slot->capacity) {
        addedOnThisSlot = slot->capacity - slot->quantity;
        slot->quantity = slot->capacity;
    } else {
        slot->quantity += quantityToAdd;
        addedOnThisSlot = quantityToAdd;
    }
    slot->item.id = itemId;
    return addedOnThisSlot;
}

/**
 * Add items which are not stackable (max one item by slot) in a bag.
 * Loop on every empty slot and add the item until all items are added
 * or no more empty slots are found.
 * @return the quantity of items added (and slots newly occupied because 1 item not stackable = 1 slot)
 */
int addNotStackableItemsInBag(Bag* bag, Item itemToAdd, int quantityToAdd) {
    int added = 0;
    BagSlot* availableSlot;
    while(quantityToAdd > 0  && (availableSlot = searchFirstEmptySlotInBag(bag)) != NULL ) {
        availableSlot->item = itemToAdd;
        added += 1;
        availableSlot->quantity = 1;
        quantityToAdd -= 1;
    }
    return added;
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
        if(slot->item.id == Empty) {
            slot->quantity = 0;
            return slot;
        }
    }
    return NULL;
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
    int16_t removed = 0;
    BagSlot* slot;
    for(int i = 0; i < bag->capacity; i += 1) {
        if(maskOfSlots[i] == true) {
            slot = bag->slots[i];
            if(slot->quantity <= quantityToRemove) {
                quantityToRemove -= slot->quantity;
                removed += slot->quantity;
                slot->quantity = 0;
                slot->item.id = Empty;
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

/**
 * Search in a bag the slots which contains an item with a certain ItemId.
 * @return a boolean mask of the slots :
 * - true fot the slot contains the same ItemId
 * - false for the slot do not contains the same ItemId
 */
bool* searchSlotsByItemId(Bag* bag, ItemId itemId) {
    bool* mask = malloc(sizeof(int8_t) * bag->capacity);
    BagSlot * slot;
    for(int i = 0; i < bag->capacity; i += 1) {
        slot = bag->slots[i];
        mask[i] = false;
        if(slot->item.id == itemId) {
            mask[i] = true;
        }
    }
    return mask;
}