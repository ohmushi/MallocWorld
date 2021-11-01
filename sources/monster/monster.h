//
// Created by Théo Omnès on 01/11/2021.
//

#ifndef MALLOCWORLD_MONSTER_H
#define MALLOCWORLD_MONSTER_H

#include "../map/map.h"
#include "../character/character.h"

typedef struct Monster {
    CellValue id;
    short currentHealthPoints;
    short maxHealthPoints;
    short damage;
    short experience;
    short zone;
} Monster;

Monster findMonsterById(CellValue id);
bool playerHasWeapons(Character* player);
bool isThereAtLeastOneWeaponInBag(Bag* bag);
void playerChoosesItsWeapon(Character* player);
int setPlayerHandToChosenWeapon(Character* player, Item weapon);

#endif //MALLOCWORLD_MONSTER_H
