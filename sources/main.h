//
// Filename: main.h
//
// Made by Théo Omnès on 09 oct. 2021.
//
// Description:
//

#ifndef MALLOCWORLD_MAIN_H
#define MALLOCWORLD_MAIN_H

#endif //MALLOCWORLD_MAIN_H

#include "map/map.h"
#include "player/player.h"
#include "turn_based/turn_based.h"
#include "npc/npc.h"
#include "collect_resources/collect_resources.h"
#include "start/start.h"


// tests
#include "movement/tests/test_movement.h"
#include "turn_based/tests/test_turn_based.h"
#include "bag/tests/test_bag.h"
#include "npc/tests/test_npc.h"
#include "collect_resources/tests/test_collect_resources.h"
#include "craft/tests/test_craft.h"
#include "player/tests/test_player.h"
#include "monster/test_monster/test_monster.h"
#include "item/tests/test_item.h"

typedef struct Mallocworld {
    Player* player;
    Map* map;
} Mallocworld;


void mallocworld();
void freeMallocWorld(Mallocworld world);
Mallocworld newMallocWorld(Player* player, Map* map);
Mallocworld initGame();
void callTests(bool lunchWithTests);