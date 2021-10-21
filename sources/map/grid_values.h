//
// Filename: grid_values.h
//
// Made by Théo Omnès on 10 oct. 2021.
//
// Description:

#ifndef MALLOCWORLD_GRID_VALUES_H
#define MALLOCWORLD_GRID_VALUES_H

#endif //MALLOCWORLD_GRID_VALUES_H

//TODO 12 -> 98 monsters
typedef enum GridValues{
    PortalTwoThree = -3,
    PortalOneTwo,
    Wall,
    Ground = 0,
    Player,
    NPC,
    PlantZoneOne,
    RockZoneOne,
    WoodZoneOne,
    PlantZoneTwo,
    RockZoneTwo,
    WoodZoneTwo,
    PlantZoneThree,
    RockZoneThree,
    WoodZoneThree,

    FinalBoss = 99,
    GridValueError = -100
}GridValues;