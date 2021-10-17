//
// Filename: location.h
//
// Made by Théo Omnès on 17 oct. 2021.
//
// Description:
//


#ifndef MALLOCWORLD_LOCATION_H
#define MALLOCWORLD_LOCATION_H

#endif //MALLOCWORLD_LOCATION_H

#include <stdint.h>

typedef struct Location {
    int16_t x;
    int16_t y;
    int8_t zoneId;
} Location;

Location* newLocation(int16_t x, int16_t y, int8_t zoneId);