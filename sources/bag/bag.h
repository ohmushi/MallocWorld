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

#ifndef MALLOCWORLD_ITEM_H
#include "../item/item.h"
#endif

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#ifndef MALLOCWORLD_CONFIG_H
#include "../config/config.h"
#endif


/*
 * A Bag slot is a case which can contain
 * one type of item with different quantities ( >= 1 )
 * or be empty
 */
typedef struct BagSlot {
    Item item;
    int8_t quantity;
    int8_t capacity;
} BagSlot;

/*
 * The Bag is the inventory of the character,
 * it's an array of BagSlot of the size bagCapacity
 */
typedef struct Bag {
    int8_t capacity;
    int8_t currentSlot;
    BagSlot** slots;
}Bag;

BagSlot* newBagSlot(Item item, int8_t quantity, int8_t capacity);
void printSlot(BagSlot slot);
void freeBagSlot(BagSlot* bagSlot);
Bag* newBag(int8_t bagCapacity, int8_t slotsCapacity);
Bag* createBag();
void printBag(Bag bag);
void freeBag(Bag* bag);
int8_t findBagCapacity();
BagSlot* getBagSlotAtIndex(Bag* bag, int index);
void setBagSlotAtIndex(Bag* bag, int index, BagSlot* slot);
int addItemsInBag(Bag* bag, Item itemToAdd, int quantityToAdd);
BagSlot* searchFirstEmptySlotInBag(Bag* bag);
int8_t findBagSlotCapacity();
int removeItemsFromBag(Bag* bag, ItemId itemId, int quantityToRemove);
bool* searchSlotsByItemId(Bag* bag, ItemId itemId);
int addStackableItemsInBag(Bag* bag, Item itemToAdd, int quantityToAdd);
int addNotStackableItemsInBag(Bag* bag, Item itemToAdd, int quantityToAdd);
int addStackableItemsInSlot(BagSlot* slot, ItemId itemId, int quantityToAdd);