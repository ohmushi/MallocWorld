//
// Filename: bag.c
//
// Made by Théo Omnès on 09 oct. 2021.
//
// Description:
//

#include "bag.h"

Item* newItem(ItemId id, char* name, ItemType type, void* object) {
    Item* item = malloc(sizeof(Item));
    item->name = malloc(sizeof(char) * strlen(name));
    strcpy(item->name, name);
    item->type = type;
    item->object = object;
    return item;
}

BagSlot* newBagSlot(Item* item, int8_t quantity) {
    BagSlot* bagSlot = malloc(sizeof(BagSlot));
    bagSlot->item = item;
    bagSlot->quantity = quantity;
    return bagSlot;
}

Bag* newBag(int8_t capacity, BagSlot** slots) {
    Bag* bag = malloc(sizeof(Bag));
    bag->capacity = capacity;
    bag->slots = malloc(sizeof(BagSlot) * capacity);
    bag->slots = slots;
    return bag;
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

void freeBag(Bag* bag) {
    for(int i = 0; i < bag->capacity; i++) {
        freeBagSlot(bag->slots[i]);
    }
}