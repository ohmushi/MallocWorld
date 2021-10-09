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

    Character* player = newCharacter(0, 1, 100);
    printCharacter(*player);
    free(player);
    return 0;
}
