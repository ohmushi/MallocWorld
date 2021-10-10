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

#endif //MALLOCWORLD_CHARACTER_H


typedef struct Character{
    int16_t experience;
    int16_t level;
    int16_t healthPoints;
    // TODO inventory
} Character;




Character* newCharacter(int16_t experience, int16_t level, int16_t healthPoints);

void printCharacter(Character character);

void freeCharacter(Character** character);