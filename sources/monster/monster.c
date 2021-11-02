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
    if( !playerCanFightMonster(player, monster) || !playerChoosesItsWeapon(player)) {
        return;
    }
    bool fightGoesOn = true;
    while(fightGoesOn) {
        player->healthPoints -= 20;
        // run fight turn
        printf("\nfight: %d/%d", player->healthPoints, player->maxHealthPoints);
        fightGoesOn = player->healthPoints > 0 && monster.currentHealthPoints > 0;
    }
}

/**
 * @return True if the monster is valid and the player has at least one weapon
 */
bool playerCanFightMonster(Character* player, Monster monster) {
    return monster.id != GridValueError && playerHasWeapons(player);
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
 * if there is only one weapon, automatically chose the one.
 * The player chose one then the player's hand (currentSlot) is set at the weapon index
 * @param player
 * @return true if the player succeeded to choose a weapon,
 * false if he don't have weapons or if error
 */
bool playerChoosesItsWeapon(Character* player) {
    ItemList weapons = getPlayerWeapons(player);
    int numberOfWeapons = getItemListSize(weapons);
    if(numberOfWeapons < 1 || NULL == player) {
        return false;
    }
    if(numberOfWeapons == 1) {
        setPlayerHandToChosenWeapon(player, weapons.list[0]);
        return true;
    }
    displayWeaponsMenu(weapons);
    Item chosen = getWeaponMenuChoice(weapons);
    if(!isEmptyItem(chosen)) {
        setPlayerHandToChosenWeapon(player, chosen);
    }
    return itemsAreEquals(player->bag->slots[player->bag->currentSlot]->item, chosen);
}

/**
 * Search the index of the weapon in the bag and set
 * the player's "Hand" (currentSlot) to this index
 */
int setPlayerHandToChosenWeapon(Character* player, Item weapon) {
    if(!player || !(player->bag)) {
        return -1;
    }
    int index = getSlotIndexOfItem(player->bag, weapon);
    if(!bagContainsTheSlotIndex(player->bag, index)) {
        return -1;
    }
    return player->bag->currentSlot = index;
}

ItemList getPlayerWeapons(Character* player) {
    ItemList list = newItemList(player->bag->capacity);
    BagSlot* slot;
    for(int i = 0; i < player->bag->capacity; i += 1) {
        slot = player->bag->slots[i];
        if(slot->item.type == WeaponType) {
            appendItemInItemList(slot->item, list);
        }
    }
    return list;
}

void displayWeaponsMenu(ItemList weapons) {
    char** options = getWeaponMenuOptionFromItemList(weapons);
    int listSize = getItemListSize(weapons);
    displayMenu("Armes", "Choisis ton arme", listSize, options);
    freeStringArray(options, listSize);
}

char** getWeaponMenuOptionFromItemList(ItemList weapons) {
    int listSize = getItemListSize(weapons);
    char** options = malloc(sizeof(char*) * listSize);
    for(int i = 0; i < listSize; i += 1) {
        options[i] = malloc(sizeof(char) * 50);
        sprintf(options[i], "%s [%d/%d]",
                weapons.list[i].name,
                weapons.list[i].durability,
                weapons.list[i].maxDurability
        );
    }
    return options;
}

void freeStringArray(char** array, int arraySize) {
    for(int i = 0; i < arraySize; i += 1) {
        free(array[i]);
    }
    free(array);
}

Item getWeaponMenuChoice(ItemList weapons) {
    unsigned char choice = -1;
    while(choice < 0 || choice >= getItemListSize(weapons) ) {
        fflush(stdin);
        choice = getchar() - '0';
    }
    return weapons.list[choice];
}