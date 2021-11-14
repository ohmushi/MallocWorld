//
// Created by Théo Omnès on 23/10/2021.
//

#ifndef MALLOCWORLD_CLI_H
#define MALLOCWORLD_CLI_H

#ifdef _WIN32
#define clrscr() system("cls")
#else
#include <stdio.h>
#define clrscr() printf("\e[1;1H\e[2J")
#include <unistd.h>
#endif

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
    Neutral,
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

void displayMenu(char* menuName, char* message, int8_t numberOfOptions, char* options[]);
const char* getAnsiColor(Color color);
void printInColor(char* string, Color color);
void printMessageType(char* message, MessageType type);
Color getColorByMessageType(MessageType type);

#endif //MALLOCWORLD_CLI_H