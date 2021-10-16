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

// config.h
#ifndef MALLOCWORLD_CONFIG_H
#include "../config/config.h"
#endif //MALLOCWORLD_CONFIG_H

// Bag.h
#ifndef MALLOCWORLD_BAG_H
#include "../bag/bag.h"
#endif //MALLOCWORLD_BAG_H



typedef struct Character{
    int16_t experience;
    int16_t level;
    int16_t healthPoints;
    Bag* bag;
} Character;




Character* newCharacter(int16_t experience, int16_t level, int16_t healthPoints);
void printCharacter(Character character);
void freeCharacter(Character* character);
Character* createCharacter();