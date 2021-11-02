//
// Filename: character.c
//
// Made by Théo Omnès on 09 oct. 2021.
//
// Description:
// The character is the player in game, in this file we can create one
// and handle its actions

#include "character.h"
#include <stdio.h>

const Level LEVELS[NUMBER_OF_LEVELS] = {
        {1, 0, 10},
        {2, 10, 20},
        {3, 20, 30},
        {4, 30, 40},
        {5, 40, 50},
        {6, 50, 60},
        {7, 50, 70},
        {8, 50, 80},
        {9, 75, 90},
        {10, 75, 100}
};

/**
 * malloc a structure Character and init it with the params values
 */
Character* newCharacter(int16_t experience, int16_t level, int16_t healthPoints, Location* location, Bag* bag){
    Character* character = malloc(sizeof(Character));
    if(NULL == character){
        return NULL;
    }
    character->experience = experience;
    character->level = level;
    character->healthPoints = healthPoints;
    character->maxHealthPoints = healthPoints;
    character->location = location;
    character->bag = bag;
    return character;
}

/**
 * print the values of a Character
 * For debug purposes
 */
void printCharacter(Character character){
    printf("-- PLAYER --\n"
           "level: %d\n"
           "experience: %d\n"
           "HP: %d\n"
           "Location: (%d,%d) in zone %d"
           "-------------",
           character.level, character.experience, character.healthPoints,
           character.location->x, character.location->y, character.location->zoneId);
}

/*
 * free a struct Character and set the pointer to NULL
 */
void freeCharacter(Character* character) {
    if(NULL == character) {
        return;
    }
    if(character->location != NULL) {
        freeLocation(character->location);
    }
    freeBag(character->bag);
    free(character);
}

/**
 * Find the start level of the player
 * @return the level found or 1 by default
 */
int8_t findPlayerStartLevel() {
    int8_t level = findIntValueInConfigFile("player_start_level");
    return level < 1 ? 1 : level;
}

/**
 * Find the start health points of the player
 * @return the level found or 100 by default
 */
int8_t findPlayerStartHP() {
    int8_t level = findIntValueInConfigFile("player_start_HP");
    return level < 1 ? 100 : level;
}

/**
 * Find the start experience points of the player
 * @return the level found or 100 by default
 */
int8_t findPlayerStartXP() {
    int8_t level = findIntValueInConfigFile("player_start_XP");
    return level < 0 ? 0 : level;
}

/**
 * allocate a struct Character with data found in config file
 * start experiences point : "player_start_XP"
 * start level : "player_start_level"
 * start HP : "player_start_HP"
 * @param location
 * @return
 */
Character* createCharacter(Location* location) {
    return newCharacter(
            findPlayerStartXP(),
            findPlayerStartLevel(),
            findPlayerStartHP(),
            location,
            createBag()
            );
}

/**
 * Add one level to the player and add health points to him
 * @return The new level of the player or -1 if error
 */
int16_t playerLevelUp(Character* player) {
    if(NULL != player) {
        int16_t newLevel = player->level + 1;
        player->level = newLevel;
        player->maxHealthPoints += findTheGainOfHealthPointsByLevel(newLevel);
        player->healthPoints = player->maxHealthPoints;
        return newLevel;
    }
    return -1;
}

/**
 * The player gain experiences points and might level up
 * if the new experiences points are above the required points for the next level
 * @return The experience points gained or -1 if error
 */
int16_t playerGainExperiencePoints(Character* player, int16_t gainedExperience) {
    if(NULL == player) {
        return -1;
    }
    int16_t experiencePointsAfterGain = player->experience + gainedExperience;
    Level nextLevel = getNextLevel(player->level);
    bool isExperiencePointsAboveNextLevel = experiencePointsAfterGain >= nextLevel.requiredExperiencePoints;
    if(isExperiencePointsAboveNextLevel) {
        player->experience = experiencePointsAfterGain - nextLevel.requiredExperiencePoints;
        playerLevelUp(player);
    } else {
        player->experience += gainedExperience;
    }
    return gainedExperience;
}

/**
 * @return The health points gained when the player gain the level or 0 if not found
 */
int16_t findTheGainOfHealthPointsByLevel(int16_t level) {
    for(int i = 0; i < NUMBER_OF_LEVELS; i += 1) {
        if(LEVELS[i].level == level) {
            return LEVELS[i].healthPoints;
        }
    }
    return 0; // not found
}

/**
 * @return The required experience to gain the level or INT16_MAX if not found
 */
int16_t findTheRequiredExperiencePointsByLevel(int16_t level) {
    for(int i = 0; i < NUMBER_OF_LEVELS; i += 1) {
        if(LEVELS[i].level == level) {
            return LEVELS[i].requiredExperiencePoints;
        }
    }
    return INT16_MAX; // not found
}

/**
 * Find in the list of Levels
 */
Level findLevel(int16_t level) {
    for(int i = 0; i < NUMBER_OF_LEVELS; i += 1) {
        if(LEVELS[i].level == level) {
            return LEVELS[i];
        }
    }
    Level notFound = {-1, -1, -1};
    return notFound;
}

/**
 * Find in the list of Levels the next one given
 */
Level getNextLevel(int16_t currentLevel) {
    return findLevel(currentLevel + 1);
}