//
// Created by Théo Omnès on 24/10/2021.
//

#ifndef MALLOCWORLD_ITEM_H
#define MALLOCWORLD_ITEM_H



#include "item_id.h"
#include "tool/tool_family.h"
#include "item_type.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER_OF_ITEMS 34

typedef struct Item {
    ItemId id;
    char* name;
    int16_t durability;
    int16_t maxDurability;
    ItemType type;
    bool isStackable;
    void* object; // might be Armor, Heal, Resource, tool or Weapon
}Item;

extern const Item ITEMS[NUMBER_OF_ITEMS];


Item* newItem(ItemId id, char* name, bool isStackable, int16_t durability, void* object, ItemType type);
Item newStructItem(ItemId id, char* name, bool isStackable, int16_t durability, void* object, ItemType type);
void freeItem(Item* item);
void printItem(Item item);
Item newEmptyItem();


#endif //MALLOCWORLD_ITEM_H