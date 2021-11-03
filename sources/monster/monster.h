//
// Created by Théo Omnès on 01/11/2021.
//

#ifndef MALLOCWORLD_MONSTER_H
#define MALLOCWORLD_MONSTER_H

#define LOSS_OF_WEAPON_DURABILITY_FROM_ATTACK 1
#define ESCAPE_LUCK 0.30

#include <string.h>

#include "../map/map.h"
#include "../character/player.h"
#include "../cli/cli.h"
#include "../item/weapon/weapon.h"
#include "../random/random.h"

typedef struct Monster {
    CellValue id;
    short currentHealthPoints;
    short maxHealthPoints;
    short damage;
    short experience;
    short zone;
} Monster;

typedef enum FightAction {
    Nothing,
    Attack,
    Heal,
    PlayerKillMonster,
    MonsterKillPlayer,
    Escape,
    FailEscape
} FightAction;

Monster findMonsterById(CellValue id);
bool playerHasWeapons(Player* player);
bool isThereAtLeastOneWeaponInBag(Bag* bag);
bool playerChoosesItsWeapon(Player* player);
int setPlayerHandToChosenWeapon(Player* player, Item weapon);
ItemList getPlayerAvailableWeapons(Player* player);
void displayWeaponsMenu(ItemList weapons);
char** getWeaponMenuOptionsFromItemList(ItemList weapons);
void freeStringArray(char** array, int arraySize);
Item getWeaponMenuChoice(ItemList weapons);
void playerStartsFightWithMonster(Player* player, Monster monster);
bool playerCanFightMonster(Player* player, Monster monster);
void playerFightMonster(Player* player, Monster monster);
bool runFightTurn(Player* player, Monster* monster);
FightAction runPlayerFightTurn(Player* player, Monster* monster);
FightAction runMonsterFightTurn(Player* player, Monster* monster);
void* getPlayerFightAction(Player* player);
void displayMenuOfPlayerFightActions();
FightAction playerAttacksMonster(Player* player, Monster* monster);
FightAction playerUseHealPotion(Player* player, Monster* monster);
FightAction playerTryEscapeFight(Player* player, Monster* monster);
void** getPlayerFightPossibleActions(Player* player);
int monsterTakesDamages(Monster* monster, int damages);
bool isMonsterAlive(Monster monster);
void displayEscapeFailed();
void displayEscapeSucceeded();



#endif //MALLOCWORLD_MONSTER_H
