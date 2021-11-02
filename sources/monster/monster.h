//
// Created by Théo Omnès on 01/11/2021.
//

#ifndef MALLOCWORLD_MONSTER_H
#define MALLOCWORLD_MONSTER_H

#include <string.h>

#include "../map/map.h"
#include "../character/player.h"
#include "../cli/cli.h"

typedef struct Monster {
    CellValue id;
    short currentHealthPoints;
    short maxHealthPoints;
    short damage;
    short experience;
    short zone;
} Monster;

Monster findMonsterById(CellValue id);
bool playerHasWeapons(Player* player);
bool isThereAtLeastOneWeaponInBag(Bag* bag);
bool playerChoosesItsWeapon(Player* player);
int setPlayerHandToChosenWeapon(Player* player, Item weapon);
ItemList getPlayerWeapons(Player* player);
void displayWeaponsMenu(ItemList weapons);
char** getWeaponMenuOptionFromItemList(ItemList weapons);
void freeStringArray(char** array, int arraySize);
Item getWeaponMenuChoice(ItemList weapons);
void playerStartsFightWithMonster(Player* player, Monster monster);
bool playerCanFightMonster(Player* player, Monster monster);
void playerFightMonster(Player* player, Monster monster);
void runFightTurn(Player* player, Monster* monster);
void runPlayerFightTurn(Player* player, Monster* monster);
void runMonsterFightTurn(Player* player, Monster* monster);
void* getPlayerFightAction(Player* player, Monster monster);
void displayMenuOfPlayerFightActions(void** actions);
void playerAttackMonster(Player* player, Monster* monster);
void playerUseHealPotion(Player* player, Monster* monster);
void playerEscapeFight(Player* player, Monster* monster);
void** getPlayerFightPossibleActions(Player* player, Monster monster);
int getSizeOfFunctionPointerArray(void** array, int maxSize);


#endif //MALLOCWORLD_MONSTER_H
