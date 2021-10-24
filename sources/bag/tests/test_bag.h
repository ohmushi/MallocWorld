//
// Created by Théo Omnès on 24/10/2021.
//

#ifndef MALLOCWORLD_TEST_BAG_H
#define MALLOCWORLD_TEST_BAG_H

#endif //MALLOCWORLD_TEST_BAG_H

#ifndef MALLOCWORLD_TEST_H
#include "../../tests/test.h"
#endif

#ifndef MALLOCWORLD_BAG_H
#include "../bag.h"
#endif


void testBag();
void setUpBag();
void afterBag();
void testAddItemInEmptyBag();
void testAddItemInBagWithStack();
void testAddItemInBagNotStackable();
void testAddItemInFullBag();
void testAddItemInBagButSlotsAreFull();
void testAddStackableItemInBagButTheFirstSlotIsFull();
void testRemoveStackableItemsFromBag();
void testRemoveStackableItemsInDifferentSlotsFromBag();