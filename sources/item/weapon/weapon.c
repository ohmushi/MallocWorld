//
// Created by Théo Omnès on 01/11/2021.
//

#include "weapon.h"

const Weapon WEAPONS[NUMBER_OF_WEAPONS] = {
        {WoodSword, 1},
        {StoneSword, 2},
        {StoneSpear, 3},
        {StoneHammer, 4},
        {IronSword, 5},
        {IronSpear, 7},
        {IronHammer, 10},
        {DiamondSword, 10},
        {DiamondSpear, 15},
        {DiamondHammer, 20}
};

Weapon findWeaponById(ItemId id) {
    for(int i = 0; i < NUMBER_OF_WEAPONS; i += 1) {
        if(WEAPONS[i].id == id) {
            return WEAPONS[i];
        }
    }
    Weapon notFound = {Empty, 0};
    return notFound;
}

Item newWeapon(ItemId id) {
    Weapon* weapon = malloc(sizeof(Weapon));
    *weapon = findWeaponById(id);
    Item itemWeapon = findItemById(id);
    itemWeapon.object = weapon;
    return itemWeapon;
}

int getWeaponDamages(Item item) {
    if(NULL == item.object || item.type != WeaponType || !itemHaveDurability(item)) {
        //TODO error not a weapon
        return 0;
    }
    Weapon* weapon = (Weapon*)item.object;
    return weapon->damages;
}