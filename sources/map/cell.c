//
// Created by Théo Omnès on 14/11/2021.
//


#include "cell.h"

const Cell CELLS[MAX_NUMBER_OF_CELL_TYPE] = {
    {PlantZoneOne, 0.2},
    {RockZoneOne, 0.2},
    {WoodZoneOne, 0.25},
    {PlantZoneTwo, 0.25},
    {RockZoneTwo, 0.2},
    {WoodZoneTwo, 0.25},
    {PlantZoneThree, 0.25},
    {RockZoneThree, 0.2},
    {WoodZoneThree, 0.25},
};


Cell findCell(CellValue id) {
    for(int i = 0; i < MAX_NUMBER_OF_CELL_TYPE; i += 1) {
        if(CELLS[i].id == id) {
            return CELLS[i];
        }
    }
    Cell notFound = {GridValueError, -1};
    return notFound;
}