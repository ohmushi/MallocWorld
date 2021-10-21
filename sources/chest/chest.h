//
// Created by Théo Omnès on 21/10/2021.
//

#ifndef MALLOCWORLD_CHESS_H
#define MALLOCWORLD_CHESS_H

#endif //MALLOCWORLD_CHESS_H

#ifndef MALLOCWORLD_BAG_H
#include "../bag/bag.h"
#endif

#ifndef MALLOCWORLD_SAVE_H
#include "../save/save.h"
#endif

typedef struct ChestSlot {
    ItemId id;
    int16_t quantity;
}ChestSlot;

int addItemsInChest(Item* items, int quantity);
ChestSlot findItemInChest(ItemId id);