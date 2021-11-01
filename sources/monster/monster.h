//
// Created by Théo Omnès on 01/11/2021.
//

#ifndef MALLOCWORLD_MONSTER_H
#define MALLOCWORLD_MONSTER_H

#include "../map/map.h"

typedef struct Monster {
    CellValue id;
    short currentHealthPoints;
    short maxHealthPoints;
    short damage;
    short experience;
    short zone;
} Monster;

#endif //MALLOCWORLD_MONSTER_H
