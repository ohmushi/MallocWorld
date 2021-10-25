//
// Created by Théo Omnès on 21/10/2021.
//

#ifndef MALLOCWORLD_NPC_H
#define MALLOCWORLD_NPC_H

#endif //MALLOCWORLD_NPC_H

#ifndef MALLOCWORLD_CHARACTER_H
#include "../character/character.h"
#endif //MALLOCWORLD_CHARACTER_H

#ifndef MALLOCWORLD_CHEST_H
#include "../chest/chest.h"
#endif //MALLOCWORLD_CHEST_H

#ifndef MALLOCWORLD_CLI_H
#include "../cli/cli.h"
#endif

typedef enum NpcMenuChoice {
    Fix,
    Craft,
    Chest,
    Nothing
} NpcMenuChoice;

void talkToNPC(Character* player);
void displayNpcMenu(char* message);
NpcMenuChoice getNpcMenuChoice();