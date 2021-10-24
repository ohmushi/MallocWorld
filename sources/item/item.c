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


Item* newItem(ItemId id, char* name, ItemType type, bool isStackable, void* object) {
    Item* item = malloc(sizeof(Item));
    item->name = malloc(sizeof(char) * strlen(name));
    strcpy(item->name, name);
    item->id = id;
    item->type = type;
    item->isStackable = isStackable;
    item->object = object;
    return item;
}


void printItem(Item item) {
    printf("{%d} - %s - %d", item.id, item.name, item.type);
}

void freeItem(Item* item) {
    if(item == NULL) {
        return;
    }
    // TODO free object
    free(item);
}