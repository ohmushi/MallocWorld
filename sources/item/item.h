//
// Created by Théo Omnès on 24/10/2021.
//

#ifndef MALLOCWORLD_ITEM_H
#define MALLOCWORLD_ITEM_H



#include "item_id.h"
#include "tool/tool_type.h"

#include <stdint.h>
#include <stdbool.h>

typedef struct Item {
    ItemId id;
    char* name;
    int16_t durability;
    int16_t maxDurability;
    bool isStackable;
    void* object; // might be Armor, Heal, Resource, tool or Weapon
}Item;


Item* newItem(ItemId id, const char* name, bool isStackable, int16_t durability, void* object);
void freeItem(Item* item);
void printItem(Item item);



#endif //MALLOCWORLD_ITEM_H