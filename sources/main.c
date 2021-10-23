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

    Character* p = createCharacter(newLocation(0,0,1));
    talkToNPC(p);
    return 0;
}
