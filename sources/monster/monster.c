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
void playerStartsFightWithMonster(Player* player, Monster monster) {
    if( !playerCanFightMonster(player, monster)) {
        return;
    }
    if(playerChoosesItsWeapon(player)) {
        playerFightMonster(player, monster);
    }
}

/**
 * Loop while the player and the monster are alive run the fight turn
 */
void playerFightMonster(Player* player, Monster monster) {
    bool fightGoesOn = true;
    while(fightGoesOn) {
        runFightTurn(player, &monster);
        fightGoesOn = player->healthPoints > 0 && monster.currentHealthPoints > 0;
    }
}

/**
 * call the actions of the player : attack the monster, heal himself or escape fight
 * call the monster actions: attack the player
 */
void runFightTurn(Player* player, Monster* monster) {
    runPlayerFightTurn(player, monster);
    runMonsterFightTurn(player, monster);
}

/**
 * Get the player actions and call the action
 */
void runPlayerFightTurn(Player* player, Monster* monster) {
    void (*action)(Player*, Monster*) = getPlayerFightAction(player, *monster);
    if(action != NULL) {
        (*action)(player, monster);
    }
}

//TODO
void runMonsterFightTurn(Player* player, Monster* monster) {
    monster->currentHealthPoints -= 1;
    printf("\nmonster: %d/%d", monster->currentHealthPoints, monster->maxHealthPoints);
}

/**
 * Display the menu of actions of the player in fight: attack, heal of escape
 * and get the choice of the player
 * @return The function pointer of the action chosen by the player
 */
void* getPlayerFightAction(Player* player, Monster monster) {
    void** actions = getPlayerFightPossibleActions(player, monster);
    displayMenuOfPlayerFightActions();
    int choice = -1;
    while(choice < 0 || choice >= NUMBER_OF_FIGHT_ACTIONS) {
        choice = getchar() - '0';
    }
    return actions[choice];
}

/**
 * @return Function pointers array of the player's actions in fight
 * Attack the monster, heal self or try to try to escape
 */
void** getPlayerFightPossibleActions(Player* player, Monster monster) {
    void** actions;
    actions = malloc(sizeof(void*) * NUMBER_OF_FIGHT_ACTIONS);
    for(int i = 0; i < NUMBER_OF_FIGHT_ACTIONS; i += 1) {
        actions[i] = NULL;
    }
    actions[0] = &playerAttackMonster;
    actions[1] = &playerUseHealPotion;
    actions[2] = &playerTryEscapeFight;
    return actions;
}

/**
 * Display the menu of the possible actions for the player in fight
 * - Attack
 * - Use Heal Potion
 * - Escape
 */
void displayMenuOfPlayerFightActions() {
    char* options[] = {"Attaquer", "Utiliser une potion", "Fuir" };
    displayMenu("Fight actions", "Que veux-tu faire ?",NUMBER_OF_FIGHT_ACTIONS, options);
}

// TODO
void playerAttackMonster(Player* player, Monster* monster) {
    printf("\nAttack !");
}

// TODO
void playerUseHealPotion(Player* player, Monster* monster) {
    printf("\nHeal !");
}

// TODO
void playerTryEscapeFight(Player* player, Monster* monster) {
    printf("\nEscape");
}

/**
 * @return True if the monster is valid and the player has at least one weapon
 */
bool playerCanFightMonster(Player* player, Monster monster) {
    return monster.id != GridValueError && playerHasWeapons(player);
}

/**
 * @return True if the player own at least one weapon in its bag, false if not
 */
bool playerHasWeapons(Player* player) {
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
bool playerChoosesItsWeapon(Player* player) {
    ItemList weapons = getPlayerAvailableWeapons(player);
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
int setPlayerHandToChosenWeapon(Player* player, Item weapon) {
    if(!player || !(player->bag)) {
        return -1;
    }
    int index = getSlotIndexOfItem(player->bag, weapon);
    if(!bagContainsTheSlotIndex(player->bag, index)) {
        return -1;
    }
    return player->bag->currentSlot = index;
}

/**
 * Search in the player inventory the items of WeaponType and with a positive durability
 * @return The list of available weapons
 */
ItemList getPlayerAvailableWeapons(Player* player) {
    ItemList list = newItemList(player->bag->capacity);
    BagSlot* slot;
    for(int i = 0; i < player->bag->capacity; i += 1) {
        slot = player->bag->slots[i];
        if(slot->item.type == WeaponType && slot->item.durability > 0) {
            appendItemInItemList(slot->item, list);
        }
    }
    return list;
}

/**
 * Display the available player's weapons in a menu
 * @param weapons
 */
void displayWeaponsMenu(ItemList weapons) {
    char** options = getWeaponMenuOptionsFromItemList(weapons);
    int listSize = getItemListSize(weapons);
    displayMenu("Armes", "Choisis ton arme", listSize, options);
    freeStringArray(options, listSize);
}

/**
 * Get the list of options by weapons
 * @return Array of string of formatted weapons like "name [durability/maxDurability]"
 */
char** getWeaponMenuOptionsFromItemList(ItemList weapons) {
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

/**
 * Free a string array: each string then the array
 */
void freeStringArray(char** array, int arraySize) {
    for(int i = 0; i < arraySize; i += 1) {
        free(array[i]);
    }
    free(array);
}

/**
 * Listen on stdin the choice of the menu of the weapon to fight
 * @param weapons
 * @return
 */
Item getWeaponMenuChoice(ItemList weapons) {
    unsigned char choice = -1;
    while(choice < 0 || choice >= getItemListSize(weapons) ) {
        fflush(stdin);
        choice = getchar() - '0';
    }
    return weapons.list[choice];
}