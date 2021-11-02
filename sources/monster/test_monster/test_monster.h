//
// Created by Théo Omnès on 01/11/2021.
//

#ifndef MALLOCWORLD_TEST_MONSTER_H
#define MALLOCWORLD_TEST_MONSTER_H

#include "../../tests/test.h"
#include "../monster.h"

void testMonster();
void setUpMonster(char* testName);
void afterMonster();

void testFindMonsterById();
void testSetPlayerHandToWeapon();
void testGetThePlayerWeapons();
void testFight();
void testMonsterTakesDamages();
void testPlayerAttacksMonster();


#endif //MALLOCWORLD_TEST_MONSTER_H
