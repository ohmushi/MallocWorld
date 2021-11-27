//
// Filename: player.h
//
// Made by Théo Omnès on 09 oct. 2021.
//
// Description:
//


#ifndef MALLOCWORLD_PLAYER_H
#define MALLOCWORLD_PLAYER_H

#include <stdint.h>
#include <stdlib.h>

#include "../config/config.h"
#include "../bag/bag.h"
#include "../movement/location.h"
#include "../movement/direction.h"
#include "../map/map.h"
#include "../cli/cli.h"

#define NUMBER_OF_LEVELS 10
#define NUMBER_OF_FIGHT_ACTIONS 4 // attack, heal, escape or see inventory

typedef struct Player {
    int16_t experience;
    int16_t level;
    int16_t healthPoints;
    int16_t maxHealthPoints;
    Bag* bag;
    Location* location;
    void (*actions[4])(struct Player*, struct Map*, Direction); //left, right, up, down
} Player;

typedef struct Level {
    int16_t level;
    int16_t healthPoints;
    int16_t requiredExperiencePoints;
} Level;



Player* newPlayer(int16_t experience, int16_t level, int16_t healthPoints, Location* location, Bag* bag);
void printPlayer(Player character);
void freePlayer(Player* character);
Player* createPlayer(Location* location);
int16_t playerLevelUp(Player* player);
int16_t findTheGainOfHealthPointsByLevel(int16_t level);
int16_t findTheRequiredExperiencePointsByLevel(int16_t level);
int16_t playerGainExperiencePoints(Player* player, int16_t gainedExperience);
Level findLevel(int16_t level);
Level getNextLevel(int16_t currentLevel);
bool playerIsAlive(Player player);
int playerTakesDamages(Player* player, int damages);
ItemList getPlayerPotions(Player* player);

#endif //MALLOCWORLD_PLAYER_H