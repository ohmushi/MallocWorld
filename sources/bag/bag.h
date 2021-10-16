//
// Filename: bag.h
//
// Made by Théo Omnès on 10 oct. 2021.
//
// Description:
//

#ifndef MALLOCWORLD_BAG_H
#define MALLOCWORLD_BAG_H

#endif //MALLOCWORLD_BAG_H

#include <stdint.h>
#include <stdlib.h>
#include "item_id.h"
#include "item_type.h"
#include <string.h>
#ifndef MALLOCWORLD_CONFIG_H
#include "../config/config.h"
#endif

typedef struct Item {
    ItemId id;
    char* name;
    ItemType type;
    int16_t durability;
    void* object; // might be Armor, Heal, Resource, tool or Weapon
}Item;

/*
 * A Bag slot is a case which can contain
 * one type of item with different quantities ( >= 1 )
 * or be empty
 */
typedef struct BagSlot {
    Item* item;
    int8_t quantity;
} BagSlot;

/*
 * The Bag is the inventory of the character,
 * it's an array of BagSlot of the size bagCapacity
 */
typedef struct Bag {
    int8_t capacity;
    BagSlot** slots;
}Bag;