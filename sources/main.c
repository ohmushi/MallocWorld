//
// Filename: main.c
//
// Made by Théo Omnès on 09 oct. 2021.
//
// Description:
//

#include <stdio.h>
#include "main.h"

int main(int argc, char* argv[]) {

    Map* map = createMap();
    printMap(*map);
    freeMap(map);

    return 0;
}
