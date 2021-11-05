//
// Created by Théo Omnès on 23/10/2021.
//


#include "cli.h"



void displayMenu(char* menuName, char* message, int8_t numberOfOptions, char* options[]) {
    printf("\n=== %s ===\n", menuName);
    printf("\n - %s\n", message);
    for(int i = 0; i < numberOfOptions; i += 1) {
        printf("\n%d.  %s", i, options[i]);
    }
    printf("\n");
}

const char* getAnsiColor(Color color) {
    switch (color) {
        case Red: return ANSI_COLOR_RED;
        case Green: return ANSI_COLOR_GREEN;
        case Yellow: return ANSI_COLOR_YELLOW;
        case Blue: return ANSI_COLOR_BLUE;
        case Magenta: return ANSI_COLOR_MAGENTA;
        case Cyan: return ANSI_COLOR_CYAN;
        default: return ANSI_COLOR_RESET;
    }
}

void printInColor(char* string, Color color) {
    const char* ansiColor = getAnsiColor(color);
    printf("%s%s" ANSI_COLOR_RESET, ansiColor, string);
}

void printMessageType(char* message, MessageType type) {
    Color color = getColorByMessageType(type);
    printInColor(message, color);
}

Color getColorByMessageType(MessageType type) {
    switch (type) {
        case Success: return Green;
        case Error: return Red;
        case Information: return Yellow;
        default: return Reset;
    }
}