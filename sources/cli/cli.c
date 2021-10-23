//
// Created by Théo Omnès on 23/10/2021.
//

#ifdef _WIN32
#include <conio.h>
#else
#include <stdio.h>
#define clrscr() printf("\e[1;1H\e[2J")
#endif

#include <unistd.h>

#include "cli.h"


Direction getPlayerDirectionByCli() {
    char input;
    scanf("%c", &input);
    switch (input) {
        case 'z': return Up;
        case 'q': return Left;
        case 'd': return Right;
        case 's': return Down;
        case 'x': return -1;
        default: return getPlayerDirectionByCli();
    }
}

void displayZoneCli(Zone zone) {
    clrscr();
    printZone(zone);
}