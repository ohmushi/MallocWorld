//
// Filename: location.c
//
// Made by Théo Omnès on 17 oct. 2021.
//
// Description:
//

#include "location.h"

Location* newLocation(int16_t x, int16_t y, int8_t zoneId) {
    Location* location = malloc(sizeof(Location));
    location->x = x;
    location->y = y;
    location->zoneId = zoneId;
    return location;
}

void freeLocation(Location* location) {
    free(location);
}

bool locationsAreEquals(Location source, Location toCheck) {
    bool zone = source.zoneId == toCheck.zoneId;
    bool x = source.x == toCheck.x;
    bool y = source.y == toCheck.y;
    return zone && x && y;
}