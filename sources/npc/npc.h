//
// Created by Théo Omnès on 21/10/2021.
//

#ifndef MALLOCWORLD_NPC_H
#define MALLOCWORLD_NPC_H

#include "../player/player.h"
#include "../chest/chest.h"
#include "../cli/cli.h"
#include "../item/tool/tool.h"
#include "../craft/craft.h"

typedef enum NpcMenuChoice {
    Fix = 0,
    Craft = 1,
    ChestAccess = 2,
    Leave = 3
} NpcMenuChoice;

void talkToNPC(Player* player);
void displayNpcMenu(char* message);
NpcMenuChoice getNpcMenuChoice();
int playerStoreItemsInChest(Player* player, Item item, int16_t quantityToStore);
int playerTakeItemsFromChest(Player* player, Item item, int16_t quantityToRecover);
void fixWeaponsAndToolsInBag(Bag* bag);
bool isNpcMenuChoice(NpcMenuChoice choice);
void onSelectChest(Player* player);
void onSelectCraft(Player* player);
void displayItemCanNotBeCrafted();
void displayBagDoNotContainsIngredients(CraftRecipe recipe);
void displayCraftSucceeded(ItemId crafted);
void displayCraftFailed(ItemId crafted);
void displayNpcChestMenu();
void onSelectStoreItemsInChest(Player* player);
void onSelectTakeItemsFromChest(Player* player);
ItemId getItemIdToTakeFromChest();
ItemId askQuantityCli();
void displayItemsWereTakenFromChest(Item item, int quantityTakenFromChest);
void displayItemIsNotInChest();
Item getItemToStoreInChest(Bag* bag);
void displayItemWhereStoredInChest(Item item, int quantityStoredInChest);
void displayNoItemWhereStoredInChest();

#endif //MALLOCWORLD_NPC_H