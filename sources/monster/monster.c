//
// Created by Théo Omnès on 01/11/2021.
//

#include "monster.h"

const Monster MONSTERS[NUMBER_OF_MONSTERS] = {
        {MonsterZoneOneA, 10,10, 10, 10, 1},
        {MonsterZoneOneB, 12,12, 9, 6, 1},
        {MonsterZoneOneC, 20,20, 20, 17, 1},
};

/**
 * Get the monster by id in the list of monsters
 */
Monster findMonsterById(CellValue id) {
    for(int i = 0; i < NUMBER_OF_MONSTERS; i += 1) {
        if(MONSTERS[i].id == id) {
            return MONSTERS[i];
        }
    }
    Monster notFound = {GridValueError, 0, 0, 0, 0, 0};
    return notFound;
}

/**
 * start a fight between the player and a monster
 * the fight start if the player own at least one weapon, he choose its weapon.
 * while the player and the monster are alive, the fight goes on, unless the player run away
 * At each of its turn, the player chose between attack, heal or run away.
 */
void playerStartsFightWithMonster(Character* player, Monster monster) {
    if(!playerHasWeapons(player)) {
        return;
    }
    playerChoosesItsWeapon(player);
    bool fightGoesOn = true;
    while(fightGoesOn) {

        fightGoesOn = player->healthPoints > 0 && monster.currentHealthPoints > 0;
    }
}

/**
 * @return True if the player own at least one weapon in its bag, false if not
 */
bool playerHasWeapons(Character* player) {
    if(NULL == player) {
        return false;
    }
    return isThereAtLeastOneWeaponInBag(player->bag);
}

/**
 * @return True if in all the slots of the bag, there is at least one item of type Weapon,
 * false if not
 */
bool isThereAtLeastOneWeaponInBag(Bag* bag) {
    if(NULL == bag) {
        return false;
    }
    return countItemsInBagByItemType(bag, WeaponType) > 0;
}

/**
 * Display menu of all the weapons in the player bag.
 * The player chose one so the player's hand (currentSlot) is set at the weapon
 * @param player
 */
void playerChoosesItsWeapon(Character* player) {
    if(!player) {
        return;
    }
    //get all the weapons of the bag
    // display menu of them
    // player choose one
    // set the hand to the good index
}

/**
 * Search the index of the weapon in the bag and set
 * the player's "Hand" (currentSlot) to this index
 */
int setPlayerHandToChosenWeapon(Character* player, Item weapon) {
    if(!player || !(player->bag)) {
        return -1;
    }
    int index = getFirstSlotIndexInBagByItemId(player->bag, weapon.id);
    if(!bagContainsTheSlotIndex(player->bag, index)) {
        return -1;
    }
    return player->bag->currentSlot = index;
}