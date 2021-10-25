//
// Created by Théo Omnès on 23/10/2021.
//

#ifdef _WIN32
#define clrscr() system("cls")
#else
#include <stdio.h>
#define clrscr() printf("\e[1;1H\e[2J")
#include <unistd.h>
#endif



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

void displayMenu(char* menuName, char* message, int8_t numberOfOptions, char* options[]) {
    clrscr();
    printf("\n=== %s ===\n", menuName);
    printf("\n - %s\n", message);
    for(int i = 0; i < numberOfOptions; i += 1) {
        printf("\n%d.  %s", i, options[i]);
    }
    printf("\n");
}