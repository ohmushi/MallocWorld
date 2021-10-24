//
// Filename: bag.c
//
// Made by Théo Omnès on 09 oct. 2021.
//
// Description:
//

#include "bag.h"
#include <stdio.h>




BagSlot* newBagSlot(Item* item, int8_t quantity) {
    BagSlot* bagSlot = malloc(sizeof(BagSlot));
    bagSlot->item = item;
    bagSlot->capacity = findBagSlotCapacity();
    bagSlot->quantity = quantity;
    return bagSlot;
}

void printSlot(BagSlot slot) {
    if(slot.item == NULL) {
        printf("{0}{0 - empty}{0}");
        return;
    }
    // TODO durability
    printf("{%d}{%d - %s}{*durability*}",
           slot.quantity,
           slot.item->id,
           slot.item->name);
}

Bag* newBag(int8_t capacity) {
    Bag* bag = malloc(sizeof(Bag));
    bag->capacity = capacity;
    bag->slots = malloc(sizeof(BagSlot) * capacity);
    for(int i = 0; i < capacity; i++) {
        setBagSlotAtIndex(bag, i, newBagSlot(NULL, 0));
    }
    return bag;
}

void printBag(Bag bag) {
    printf("\n-- INVENTORY --\n");
    for(int i = 0; i < bag.capacity; i+= 1) {
        printSlot(*bag.slots[i]);
        printf("\n");
    }
}


void freeBagSlot(BagSlot* bagSlot) {
    if(bagSlot == NULL) {
        return;
    }
    freeItem(bagSlot->item);
    bagSlot->item = NULL;
    free(bagSlot);
}

/*
 * free all the slots of the inventory
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

void setBagSlotAtIndex(Bag* bag, int index, BagSlot* slot) {
    if(index < 0 || index >= bag->capacity) {
        return;
    }
    bag->slots[index] = slot;
}

BagSlot* getBagSlotAtIndex(Bag* bag, int index) {
    if(index < 0 || index >= bag->capacity) {
        NULL;
    }
    return bag->slots[index];
}

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
    availableSlot->quantity += 1;
    availableSlot->item = itemToAdd;
    return true;
}

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