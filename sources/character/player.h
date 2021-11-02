//
// Filename: character.h
//
// Made by Théo Omnès on 09 oct. 2021.
//
// Description:
//

#include <stdint.h>
#include <stdlib.h>

#ifndef MALLOCWORLD_CHARACTER_H
#define MALLOCWORLD_CHARACTER_H

#include "../config/config.h"
#include "../bag/bag.h"
#include "../movement/location.h"
#include "../map/map.h"

#define NUMBER_OF_LEVELS 10
#define NUMBER_OF_FIGHT_ACTIONS 3 // attack, heal or escape

typedef struct Player {
    int16_t experience;
    int16_t level;
    int16_t healthPoints;
    int16_t maxHealthPoints;
    Bag* bag;
    Location* location;
    void (*actions[4])(struct Player*, struct Map*); //left, right, up, down
} Player;

typedef struct Level {
    int16_t level;
    int16_t healthPoints;
    int16_t requiredExperiencePoints;
} Level;



Player* newCharacter(int16_t experience, int16_t level, int16_t healthPoints, Location* location, Bag* bag);
void printCharacter(Player character);
void freeCharacter(Player* character);
Player* createCharacter(Location* location);
int16_t playerLevelUp(Player* player);
int16_t findTheGainOfHealthPointsByLevel(int16_t level);
int16_t findTheRequiredExperiencePointsByLevel(int16_t level);
int16_t playerGainExperiencePoints(Player* player, int16_t gainedExperience);
Level findLevel(int16_t level);
Level getNextLevel(int16_t currentLevel);

#endif //MALLOCWORLD_CHARACTER_H