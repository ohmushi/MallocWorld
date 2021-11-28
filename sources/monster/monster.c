//
// Created by Théo Omnès on 01/11/2021.
//

#include "monster.h"

const Monster MONSTERS[NUMBER_OF_MONSTERS] = {
        {MonsterZoneOneA, "Monster 1", 10,10, 15, 10, 1},
        {MonsterZoneOneB, "Monster 2", 12,12, 30, 6, 1},
        {MonsterZoneOneC, "Monster 3", 20,20, 50, 17, 1},
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


void playerFightMonsterAction(Player* player, Map* map, Direction direction) {
    CellValue cell = getCellValueInDirection(player, map, direction);
    if(isMonster(cell)){
        Monster monster = findMonsterById(cell);
        playerStartsFightWithMonster(player, monster);
        if(playerIsAlive(*player)) {
            playerKilledMonster(player, monster, map, direction);
        }
    }
}

void playerKilledMonster(Player* player, Monster monster, Map* map, Direction monsterDirection) {
    Location monsterLocation = getLocationInDirection(*player->location, monsterDirection);
    playerGainExperiencePoints(player, monster.experience);
    setCellValueInMapAtLocation(Ground, map, monsterLocation);
}

/**
 * start a fight between the player and a monster
 * the fight start if the player own at least one weapon, he choose its weapon.
 * while the player and the monster are alive, the fight goes on, unless the player run away
 * At each of its turn, the player chose between attack, heal or run away.
 */
void playerStartsFightWithMonster(Player* player, Monster monster) {
    if( !playerCanFightMonster(player, monster)) {
        displayPlayerCannotFight();
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
    Monster* monsterFighter = malloc(sizeof(Monster));
    *monsterFighter = monster;
    while(fightGoesOn) {
        fightGoesOn = runFightTurn(player, monsterFighter);
    }
}

/**
 * call the actions of the player : attack the monster, heal himself or escape fight
 * call the monster actions: attack the player
 * @return True if the fight goes on, false if the fight is over
 */
bool runFightTurn(Player* player, Monster* monster) {
    FightAction playerAction = runPlayerFightTurn(player, monster);
    switch (playerAction) {
        case Attack: displayFightersStates(*player, *monster, "Player");
            break;
        case PlayerKillMonster: return false;
        case MonsterKillsPlayer: return false;
        case PlayerEscape: return false;
        case FailEscape: return true;
        default: break;
    }
    runMonsterFightTurn(player, monster);
    displayFightersStates(*player, *monster, monster->name);
    return playerIsAlive(*player);
}

/**
 * Get the player actions and call the action
 * actions are functions:
 * - playerAttacksMonster
 * - playerUseHealPotion
 * - playerTryEscapeFight
 */
FightAction runPlayerFightTurn(Player* player, Monster* monster) {
    FightAction playerAction = Nothing;
    while(playerAction == Nothing) {
        FightAction (*action)(Player*, Monster*) = getPlayerFightAction(player);
        if(NULL == action) {
            return Nothing;
        }
        playerAction = (*action)(player, monster);
    }
    return playerAction;
}

/**
 * Call the actions of the monster during its turn in fight:
 * The monster hit the player -> the player takes damages
 * @return <Attack> if the player is still alive after the hit, if not return <MonsterKillsPlayer>
 */
FightAction runMonsterFightTurn(Player* player, Monster* monster) {
    playerTakesDamages(player, monster->damage);
    return playerIsAlive(*player) ? Attack : MonsterKillsPlayer;
}

/**
 * Display the menu of actions of the player in fight: attack, heal of escape
 * and get the choice of the player
 * @return The function pointer of the action chosen by the player
 */
void* getPlayerFightAction(Player* player) {
    void** actions = getPlayerFightPossibleActions(player);
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
void** getPlayerFightPossibleActions(Player* player) {
    void** actions;
    actions = malloc(sizeof(void*) * NUMBER_OF_FIGHT_ACTIONS);
    for(int i = 0; i < NUMBER_OF_FIGHT_ACTIONS; i += 1) {
        actions[i] = NULL;
    }
    actions[0] = &playerAttacksMonster;
    actions[1] = &playerUseHealPotion;
    actions[2] = &playerTryEscapeFight;
    actions[3] = &displayBagInFight;
    return actions;
}

/**
 * Display the menu of the possible actions for the player in fight
 * - Attack
 * - Use Heal Potion
 * - PlayerEscape
 */
void displayMenuOfPlayerFightActions() {
    char* options[] = {"HADOKEN !!", "Utiliser une potion", "Fuir", "Voir l'inventaire" };
    displayMenu("Fight actions", "Que veux-tu faire ?",NUMBER_OF_FIGHT_ACTIONS, options);
}

/**
 * Get the current weapon in the player's hand and its damages.
 * Remove the weapon damages to the monster life and remove durability to the weapon
 */
FightAction playerAttacksMonster(Player* player, Monster* monster) {
    Item* weapon = &(getCurrentBagSlot(player->bag)->item);
    int damages = getWeaponDamages(*weapon);
    monsterTakesDamages(monster, damages);
    itemLoseDurability(weapon, LOSS_OF_WEAPON_DURABILITY_FROM_ATTACK);
    if(!itemHaveDurability(*weapon)) {
        displayItemBroke(*weapon);
        playerChoosesItsWeapon(player);
    }
    return Attack;
}

/**
 * Remove a quantity of healthPoints to the monster.
 * @param damages The quantity of healthPoints to be removed from the monster's current healPoints
 * @return The number of healPoints the monster lost
 */
int monsterTakesDamages(Monster* monster, int damages) {
    int removed = 0;
    int healthPointsAfterDamage = monster->currentHealthPoints - damages;
    if(healthPointsAfterDamage > 0) {
        monster->currentHealthPoints = (short)healthPointsAfterDamage;
        removed = damages;
    } else {
        removed = monster->currentHealthPoints;
        monster->currentHealthPoints = 0;
    }
    return removed;
}

bool isMonsterAlive(Monster monster) {
    return monster.currentHealthPoints > 0;
}

/**
 * Display a menu of the player's potions.
 * The player chooses one and take it, it restore a certain
 * amount of healthPoints
 * Remove the potion of the player's inventory
 * @return the fightAction <PlayerHeal>
 */
FightAction playerUseHealPotion(Player* player, Monster* monster) {
    ItemList potions = getPlayerPotions(player);
    if(*(potions.size) < 1) {
        displayPlayerDoNotHavePotions();
        return Nothing;
    }
    displayPotionsMenu(potions);
    Heal potion = getPotionFromMenuChoice(potions);
    playerTakesPotion(player, potion);
    displayPlayerHealHimself(potion.restore);
    removeItemsFromBag(player->bag, potion.id, 1);
    return PlayerHeal;
}

/**
 * When the player choose to escape, he has 30% chance of success.
 * @return PlayerEscape or FailEscape
 */
FightAction playerTryEscapeFight(Player* player, Monster* monster) {
    double random = randomIntInRange(0, 100) / 100.0; // 0 <= random <= 1
    if(random <= ESCAPE_LUCK) {
        displayEscapeSucceeded();
        return PlayerEscape;
    }
    else {
        displayEscapeFailed();
        return FailEscape;
    }
}

/**
 * @return True if the monster is valid and the player has at least one weapon
 */
bool playerCanFightMonster(Player* player, Monster monster) {
    return isMonster(monster.id) && playerHasWeapons(player);
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

/**
 * Display the fact that the player failed to escape during a fight.
 */
void displayEscapeFailed() {
    printMessageType("Tu as échoué à t'enfuir ! (._.)\n", Error);
}

/**
 * Display the fact that the player succeeded to escape during a fight.
 */
void displayEscapeSucceeded() {
    printMessageType("Tu t'es échapé ! \\ (•◡•) /\n", Success);
}

/**
 * Display on stdout the structure Monster
 */
void printMonster(Monster monster) {
    char msg[255];
    sprintf(msg,"-- MONSTER --\n"
           "id: %d\n"
           "HP: (%d/%d)\n"
           "damages: %d\n"
           "XP: %d\n"
           "Zone: %d\n"
           "-------------\n",
           monster.id,
           monster.currentHealthPoints, monster.maxHealthPoints,
           monster.damage,
           monster.experience,
           monster.zone);
    printMessageType(msg, Information);
}

/**
 * Display the menu of the player's potions.
 * Each type of available potion in player's bag is an option.
 * Each option is like : NameOfThePotion [+ ... HP] ... is the restore capacity of the potion
 * @param potions List of potions in the player's bag
 */
void displayPotionsMenu(ItemList potions) {
    char** options = getPotionsMenuOptionsFromItemList(potions);
    int listSize = getItemListSize(potions);
    displayMenu("Potions", "Quelle potion ?", listSize, options);
    freeStringArray(options, listSize);
}

/**
 * Get all the options of the potion menu : each type of available potion in player's bag
 * @param potions List of potions in the player's bag
 * @return String Array of all the options
 */
char** getPotionsMenuOptionsFromItemList(ItemList potions) {
    int listSize = getItemListSize(potions);
    char** options = malloc(sizeof(char*) * listSize);
    for(int i = 0; i < listSize; i += 1) {
        Heal* potion = (Heal*)(potions.list[i].object);
        options[i] = malloc(sizeof(char) * 50);
        sprintf(options[i], "%s [+%d HP]",
                potions.list[i].name,
                potion->restore
        );
    }
    return options;
}

/**
 * Display the player and the monster with their HealPoints
 */
void printFightersStates(Player player, Monster monster, char* attacker) {
    char msg[100];
    sprintf(msg, "\n%s attaque !"
                 "\nJoueur [%d/%d]   VS   [%d/%d] %s \n",
                 attacker,
                 player.healthPoints, player.maxHealthPoints,
                 monster.currentHealthPoints, monster.maxHealthPoints, monster.name);
    printMessageType(msg, Information);
}

/**
 * Get on stdin the choice of the potion the player wants
 * @param potions List of available potions in player's bag
 * @return The Heal structure of the potion that the player chose
 */
Heal getPotionFromMenuChoice(ItemList potions) {
    unsigned char choice = -1;
    int sizeList = getItemListSize(potions);
    if(sizeList < 1) {
        return findHealById(Empty);
    }
    while(choice < 0 || choice >= sizeList) {
        fflush(stdin);
        choice = getchar() - '0';
    }
    Heal* chosen = (Heal*)(potions.list[choice].object);
    return *chosen;
}

/**
 * Add to the player's healPoints the restore capacity of a potion
 */
void playerTakesPotion(Player* player, Heal potion) {
    player->healthPoints += potion.restore;
    if(player->healthPoints > player->maxHealthPoints) {
        player->healthPoints = player->maxHealthPoints;
    }
}

/**
 * display the fact that the player doesn't have any potion in his bag
 */
void displayPlayerDoNotHavePotions() {
    printMessageType("\nTu n'as aucune potion !\n", Error);
}

/**
 * display the healthPoints of the player and the monster in fight
 * with who is attacking
 * @param attacker Name of the one who is attacking the other
 */
void displayFightersStates(Player player, Monster monster, char* attacker) {
    printFightersStates(player, monster, attacker);
}

/**
 * Display the fact that the player is taking a potion.
 * @param restore The quantity of healthPoints given to the player
 */
void displayPlayerHealHimself(int restore) {
    char msg[100];
    sprintf(msg, "\nTu as utilisé un soin: + [%d HP]", restore);
    printMessageType(msg, Success);
}

/**
 * One of the possible player's actions in fight.
 * Display the player's bag.
 * @return the FightAction <Nothing>
 */
FightAction displayBagInFight(Player* player, Monster* monster) {
    Bag bag = *(player->bag);
    displayBag(bag);
    return Nothing;
}

void* getFightAction(Player* player, CellValue monster) {
    bool hasWeapons = getPlayerAvailableWeapons(player).size > 0;
    if(hasWeapons && isMonster(monster)) {
        return &playerFightMonsterAction;
    } else {
        return NULL;
    }
}

bool isMonster(CellValue cell) {
    return cell >= MonsterZoneOneA && cell <= FinalBoss;
}

void displayPlayerCannotFight() {
    printMessageType("Tu ne peux pas te battre", Neutral);
}