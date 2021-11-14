//
// Created by Théo Omnès on 02/11/2021.
//

#ifndef MALLOCWORLD_TEST_ITEM_H
#define MALLOCWORLD_TEST_ITEM_H

#include "../../tests/test.h"
#include "../item.h"


void testItem();
void setUpItem(char* testName, ItemId itemId);
void afterItem();

void testItemLosesDurability();

#endif //MALLOCWORLD_TEST_ITEM_H
