//
// Created by Théo Omnès on 01/11/2021.
//

#include "weapon.h"

/**
 * List of all the weapons in game
 */
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

/**
 * @return The struct Weapon searched by it's id. If not fount a Weapon with th id <Empty>
 */
Weapon findWeaponById(ItemId id) {
    for(int i = 0; i < NUMBER_OF_WEAPONS; i += 1) {
        if(WEAPONS[i].id == id) {
            return WEAPONS[i];
        }
    }
    Weapon notFound = {Empty, 0};
    return notFound;
}

/**
 * Allocate a struct Weapon and insert it in an Item
 * @return Item of the weapon with the item.object set to the pointer of the allocated struct Weapon
 */
Item newWeapon(ItemId id) {
    Weapon* weapon = malloc(sizeof(Weapon));
    *weapon = findWeaponById(id);
    Item itemWeapon = findItemById(weapon->id);
    itemWeapon.object = weapon;
    return itemWeapon;
}

/**
 * @return the damages that the weapon can inflict. Return 0 damages if the weapon doesn't have durability
 */
int getWeaponDamages(Item item) {
    if(NULL == item.object || item.type != WeaponType || !itemHaveDurability(item)) {
        return 0;
    }
    Weapon* weapon = (Weapon*)item.object;
    return weapon->damages;
}