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

/**
 * malloc a structure Character and init it with the params values
 */
Character* newCharacter(int16_t experience, int16_t level, int16_t healthPoints, Location* location){
    Character* character = malloc(sizeof(Character));
    if(character == NULL){
        return NULL;
    }

    character->experience = experience;
    character->level = level;
    character->healthPoints = healthPoints;
    character->location = location;
    //TODO inventory -> { woodSword , woodPick , woodAxe , woodBillhook , 0 , 0 , 0 , 0 , 0 , 0 }
    //TODO weapon
    //TODO armor

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
    if(character == NULL) {
        return;
    }
    if(character->location != NULL) {
        freeLocation(character->location);
    }
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


Character* createCharacter(Location* location) {
    return newCharacter(
            findPlayerStartXP(),
            findPlayerStartLevel(),
            findPlayerStartHP(),
            location
            );
}