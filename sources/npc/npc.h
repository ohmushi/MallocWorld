//
// Created by Théo Omnès on 21/10/2021.
//

#ifndef MALLOCWORLD_NPC_H
#define MALLOCWORLD_NPC_H

#include "../character/player.h"
#include "../chest/chest.h"
#include "../cli/cli.h"
#include "../item/tool/tool.h"

typedef enum NpcMenuChoice {
    Fix,
    Craft,
    Chest,
    Leave
} NpcMenuChoice;

void talkToNPC(Player* player);
void displayNpcMenu(char* message);
NpcMenuChoice getNpcMenuChoice();
int storeItemsInChest(Bag* bag, Item item, int16_t quantityToStore);
int takeItemsFromChest(Bag* bag, Item item, int16_t quantityToRecover);
void fixWeaponsAndToolsInBag(Bag* bag);

#endif //MALLOCWORLD_NPC_H