//
// Created by Théo Omnès on 01/11/2021.
//

#ifndef MALLOCWORLD_WEAPON_H
#define MALLOCWORLD_WEAPON_H

#define NUMBER_OF_WEAPONS 10

#include "../item.h"

typedef struct Weapon {
    ItemId id;
    int damages;
} Weapon;


Weapon findWeaponById(ItemId id);
Item newWeapon(ItemId id);
int getWeaponDamages(Item item);

#endif //MALLOCWORLD_WEAPON_H
