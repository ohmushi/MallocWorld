//
// Created by Théo Omnès on 24/10/2021.
//

#ifndef MALLOCWORLD_ITEM_H
#define MALLOCWORLD_ITEM_H

#endif //MALLOCWORLD_ITEM_H

#ifndef MALLOCWORLD_ITEM_ID_H
#include "item_id.h"
#endif //MALLOCWORLD_ITEM_ID_H

#ifndef MALLOCWORLD_ITEM_TYPES_H
#include "item_type.h"
#endif //MALLOCWORLD_ITEM_TYPES_H

#include <stdint.h>
#include <stdbool.h>

typedef struct Item {
    ItemId id;
    char* name;
    ItemType type;
    int16_t durability;
    bool isStackable;
    void* object; // might be Armor, Heal, Resource, tool or Weapon
}Item;


Item* newItem(ItemId id, char* name, ItemType type, bool isStackable, void* object);
void freeItem(Item* item);
void printItem(Item item);