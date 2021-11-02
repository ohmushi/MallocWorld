//
// Created by Théo Omnès on 23/10/2021.
//

#ifndef MALLOCWORLD_CLI_H
#define MALLOCWORLD_CLI_H

#include "../movement/movement.h"
#include "../config/config.h"

typedef enum Color {
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
    Cyan,
    Reset
} Color;

typedef enum MessageType {
    Success,
    Error,
    Information
} MessageType;

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

Direction getPlayerDirectionByCli();
void displayZoneCli(Zone zone);
void displayMenu(char* menuName, char* message, int8_t numberOfOptions, char* options[]);
const char* getAnsiColor(Color color);
void printInColor(char* string, Color color);

#endif //MALLOCWORLD_CLI_H