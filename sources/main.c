//
// Filename: main.c
//
// Made by Théo Omnès on 09/10/2021.
//
// Description:
//

#include <stdio.h>
#include "main.h"

int main() {

    Map* map = newMap();
    printMap(*map);
    free(map);

    return 0;
}
