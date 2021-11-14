//
// Created by Théo Omnès on 14/11/2021.
//


#include "cell.h"

const Cell CELLS[MAX_NUMBER_OF_CELL_TYPE] = {
    {PlantZoneOne, 0.4},
    {RockZoneOne, 0.3},
    {WoodZoneOne, 0.7},
    {PlantZoneTwo, 0.4},
    {RockZoneTwo, 0.3},
    {WoodZoneTwo, 0.7},
    {PlantZoneThree, 0.4},
    {RockZoneThree, 0.3},
    {WoodZoneThree, 0.7},
};


double findCellSpawnFrequency(CellValue id) {
    for(int i = 0; i < MAX_NUMBER_OF_CELL_TYPE; i += 1) {
        if(CELLS[i].id == id) {
            return CELLS[i].spawnFrequency;
        }
    }
    return -1.0;
}