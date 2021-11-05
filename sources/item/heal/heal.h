//
// Created by Théo Omnès on 04/11/2021.
//

#ifndef MALLOCWORLD_HEAL_H
#define MALLOCWORLD_HEAL_H

#include "../item.h"

#define NUMBER_OF_POTIONS 3

typedef struct Heal{
    ItemId id;
    int restore;
} Heal;

Heal findHealById(ItemId id);
Item newHeal(ItemId id);

#endif //MALLOCWORLD_HEAL_H
