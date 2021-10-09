//
// Filename: character.c
//
// Made by Théo Omnès on 09/10/2021.
//
// Description:
//

#include "character.h"
#include "stdio.h"


/**
 *
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

void printCharacter(Character character){
    printf("--character--\n"
           "level: %d\n"
           "experience: %d\n"
           "HP: %d\n"
           "-------------",
           character.level, character.experience, character.healthPoints);
}
