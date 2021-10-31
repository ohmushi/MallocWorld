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

// config.h
#ifndef MALLOCWORLD_CONFIG_H
#include "../config/config.h"
#endif //MALLOCWORLD_CONFIG_H

// bag.h
#ifndef MALLOCWORLD_BAG_H
#include "../bag/bag.h"
#endif //MALLOCWORLD_BAG_H

// location.h
#ifndef MALLOCWORLD_LOCATION_H
#include "../movement/location.h"
#endif //MALLOCWORLD_LOCATION_H

// map.h
#ifndef MALLOCWORLD_MAP_H
#include "../map/map.h"
#endif //MALLOCWORLD_MAP_H



typedef struct Character{
    int16_t experience;
    int16_t level;
    int16_t healthPoints;
    Bag* bag;
    Location* location;
    void (*actions[4])(struct Character*, struct Map*); //left, right, up, down
} Character;




Character* newCharacter(int16_t experience, int16_t level, int16_t healthPoints, Location* location, Bag* bag);
void printCharacter(Character character);
void freeCharacter(Character* character);
Character* createCharacter(Location* location);

#endif //MALLOCWORLD_CHARACTER_H