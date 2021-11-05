//
// Created by Théo Omnès on 24/10/2021.
//

#ifndef MALLOCWORLD_ITEM_H
#define MALLOCWORLD_ITEM_H



#include "item_id.h"
#include "tool/tool_family.h"
#include "item_type.h"
#include "../cli/cli.h"

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

typedef struct ItemList {
    Item* list;
    int* size;
    int maxSize;
} ItemList;

extern const Item ITEMS[NUMBER_OF_ITEMS];


Item* newItem(ItemId id, char* name, bool isStackable, int16_t durability, void* object, ItemType type);
Item newStructItem(ItemId id, char* name, bool isStackable, int16_t durability, void* object, ItemType type);
void freeItem(Item* item);
void printItem(Item item);
Item newEmptyItem();
Item findItemById(ItemId itemId);
ItemList newItemList(int maxSize);
void freeItemList(ItemList itemList);
void appendItemInItemList(Item item, ItemList list);
int getItemListSize(ItemList list);
bool isEmptyItem(Item item);
bool itemsAreEquals(Item first, Item second);
int itemLoseDurability(Item* item, int loss);
bool itemHaveDurability(Item item);
void printItemBroke(Item item);
void displayItemBroke(Item item);

#endif //MALLOCWORLD_ITEM_H