//
// Filename: grid_values.h
//
// Made by Théo Omnès on 10 oct. 2021.
//
// Description:

#ifndef MALLOCWORLD_CELL_VALUE_H
#define MALLOCWORLD_CELL_VALUE_H

#define NUMBER_OF_MONSTERS 3

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

    MonsterZoneOneA,
    MonsterZoneOneB,
    MonsterZoneOneC,

    FinalBoss = 99,
    GridValueError = -100
}CellValue;

#endif //MALLOCWORLD_CELL_VALUE_H