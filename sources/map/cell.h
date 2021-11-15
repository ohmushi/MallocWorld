//
// Filename: grid_values.h
//
// Made by Théo Omnès on 10 oct. 2021.
//
// Description:

#ifndef MALLOCWORLD_CELL_H
#define MALLOCWORLD_CELL_H

#define MAX_NUMBER_OF_CELL_TYPE 128

typedef enum CellValue{
    PortalTwoThree = -3,
    PortalOneTwo,
    Wall,
    Ground = 0,
    PlayerCell,
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

typedef struct Cell {
    CellValue id;
    double spawnFrequency;
} Cell;

Cell findCell(CellValue id);

#endif //MALLOCWORLD_CELL_H