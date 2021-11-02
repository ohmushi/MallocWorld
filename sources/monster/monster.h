//
// Created by Théo Omnès on 01/11/2021.
//

#ifndef MALLOCWORLD_MONSTER_H
#define MALLOCWORLD_MONSTER_H

#include <string.h>

#include "../map/map.h"
#include "../character/character.h"
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
bool playerHasWeapons(Character* player);
bool isThereAtLeastOneWeaponInBag(Bag* bag);
bool playerChoosesItsWeapon(Character* player);
int setPlayerHandToChosenWeapon(Character* player, Item weapon);
ItemList getPlayerWeapons(Character* player);
void displayWeaponsMenu(ItemList weapons);
char** getWeaponMenuOptionFromItemList(ItemList weapons);
void freeStringArray(char** array, int arraySize);
Item getWeaponMenuChoice(ItemList weapons);
void playerStartsFightWithMonster(Character* player, Monster monster);
bool playerCanFightMonster(Character* player, Monster monster);

#endif //MALLOCWORLD_MONSTER_H
