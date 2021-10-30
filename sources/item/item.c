//
// Filename: bag.c
//
// Made by Théo Omnès on 24 oct. 2021.
//
// Description:
//

#include "item.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


Item* newItem(ItemId id, char* name, bool isStackable, int16_t durability, void* object, ItemType type) {
    Item* item = malloc(sizeof(Item));
    *item = newStructItem(id, name, isStackable, durability, object, type);
    return item;
}

Item newStructItem(ItemId id, char* name, bool isStackable, int16_t durability, void* object, ItemType type) {
    Item item;
    item.name = malloc(sizeof(char) * strlen(name));
    strcpy(item.name, name);
    item.id = id;
    item.isStackable = isStackable;
    item.object = object;
    item.durability = durability;
    item.maxDurability = durability;
    item.type = type;
    return item;
}


void printItem(Item item) {
    printf("{%d} - %s", item.id, item.name);
}

void freeItem(Item* item) {
    if(NULL == item) {
        return;
    }
    // TODO free object
    free(item);
}