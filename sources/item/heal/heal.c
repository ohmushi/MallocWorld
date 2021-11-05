//
// Created by Théo Omnès on 04/11/2021.
//

#include "heal.h"

const Heal HEALS[NUMBER_OF_POTIONS] = {
        {HealingPotionOne, 30},
        {HealingPotionTwo, 80},
        {HealingPotionThree, 200},
};


Heal findHealById(ItemId id) {
    for(int i = 0; i < NUMBER_OF_POTIONS; i += 1) {
        if(HEALS[i].id == id) {
            return HEALS[i];
        }
    }
    Heal notFound = {Empty, 0};
    return notFound;
}

Item newHeal(ItemId id) {
    Item item = findItemById(id);
    Heal* heal = malloc(sizeof(Heal));
    *heal = findHealById(id);
    item.object = heal;
    return item;
}