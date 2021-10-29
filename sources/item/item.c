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


Item* newItem(ItemId id, const char* name, bool isStackable, int16_t durability, void* object) {
    Item* item = malloc(sizeof(Item));
    item->name = malloc(sizeof(char) * strlen(name));
    strcpy(item->name, name);
    item->id = id;
    item->isStackable = isStackable;
    item->object = object;
    item->durability = durability;
    item->maxDurability = durability;
    return item;
}


void printItem(Item item) {
    printf("{%d} - %s", item.id, item.name);
}

void freeItem(Item* item) {
    if(item == NULL) {
        return;
    }
    // TODO free object
    free(item);
}