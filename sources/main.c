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

    ChestSlot slot = findItemInChest(0);
    printf("\nqty: %d\nid: %d\n", slot.quantity, slot.id);
    return 0;
}
