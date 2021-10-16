//
// Filename: bag.c
//
// Made by Théo Omnès on 09 oct. 2021.
//
// Description:
//

#include "bag.h"
#include <stdio.h>

Item* newItem(ItemId id, char* name, ItemType type, void* object) {
    Item* item = malloc(sizeof(Item));
    item->name = malloc(sizeof(char) * strlen(name));
    strcpy(item->name, name);
    item->type = type;
    item->object = object;
    return item;
}

void printItem(Item item) {
    printf("{%d} - %s - %d", item.id, item.name, item.type);
}

BagSlot* newBagSlot(Item* item, int8_t quantity) {
    BagSlot* bagSlot = malloc(sizeof(BagSlot));
    bagSlot->item = item;
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

Bag* newBag(int8_t capacity, BagSlot** slots) {
    Bag* bag = malloc(sizeof(Bag));
    bag->capacity = capacity;
    bag->slots = malloc(sizeof(BagSlot) * capacity);
    bag->slots = slots;
    return bag;
}

void printBag(Bag bag) {
    printf("\n-- INVENTORY --\n");
    for(int i = 0; i < bag.capacity; i+= 1) {
        printSlot(*bag.slots[i]);
        printf("\n");
    }
}

void freeItem(Item* item) {
    if(item == NULL) {
        return;
    }
    free(item->name);
    // TODO free object
    free(item);
}

void freeBagSlot(BagSlot* bagSlot) {
    freeItem(bagSlot->item);
    bagSlot->item = NULL;
    free(bagSlot);
}

/*
 * free all the slots of the inventory
 */
void freeBag(Bag* bag) {
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