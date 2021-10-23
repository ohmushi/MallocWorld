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

    int removed = removeItemsFromChess(2, 8);
    printf("removed: %d", removed);
    return 0;
}
