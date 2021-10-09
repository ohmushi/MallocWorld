//
// Filename: character.c
//
// Made by Théo Omnès on 09/10/2021.
//
// Description:
// The character is the player in game, in this file we can create one
// and handle its actions

#include "character.h"
#include <stdio.h>

/**
 * malloc a structure Character and init it with the params values
 */
Character* newCharacter(int16_t experience, int16_t level, int16_t healthPoints){
    Character* character = malloc(sizeof(Character));
    if(character == NULL){
        return NULL;
    }

    character->experience = experience;
    character->level = level;
    character->healthPoints = healthPoints;
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
    printf("--character--\n"
           "level: %d\n"
           "experience: %d\n"
           "HP: %d\n"
           "-------------",
           character.level, character.experience, character.healthPoints);
}
