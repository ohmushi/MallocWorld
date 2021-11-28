//
// Created by Théo Omnès on 23/10/2021.
//


#include "cli.h"


/**
 * Display on stdout the options of a menu.
 * @param options Array of strings of the possible options
 */
void displayMenu(char* menuName, char* message, int8_t numberOfOptions, char* options[]) {
    if(NULL != menuName){
        printf("\n=== %s ===\n", menuName);
    }
    if(NULL != message){
        printf("\n - %s\n", message);
    }
    for(int i = 0; i < numberOfOptions; i += 1) {
        printf("\n%d.  %s", i, options[i]);
    }
    printf("\n");
}


/**
 * Display on stdout the options of a menu with custom bullets.
 */
void displayMenuWithCustomBullet(char* menuName, char* message, int8_t numberOfOptions, char* bullets[], char* options[]) {
    printf("\n=== %s ===\n", menuName);
    if(NULL != message){
        printf("\n - %s\n", message);
    }
    for(int i = 0; i < numberOfOptions; i += 1) {
        printf("\n%s.  %s", bullets[i], options[i]);
    }
    printf("\n");
}

/**
 * Get the string of the ANSI color by the enum Color
 */
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

/**
 * Display on stdout the given string in the wanted color
 * Use the ANSI colors codes
 */
void printInColor(char* string, Color color) {
    const char* ansiColor = getAnsiColor(color);
    printf("%s" "%s" "%s", ansiColor, string, ANSI_COLOR_RESET);
}

/**
 * Display on stdout the message given of the color of the type wanted (cf. enum MessageType)
 */
void printMessageType(char* message, MessageType type) {
    Color color = getColorByMessageType(type);
    printInColor(message, color);
}

/**
 * Map a MessageType to a Color:
 * - Success = Green
 * - Error = Red
 * - Information = Yellow
 * @param type
 * @return
 */
Color getColorByMessageType(MessageType type) {
    switch (type) {
        case Success: return Green;
        case Error: return Red;
        case Information: return Yellow;
        default: return Reset;
    }
}

int getPlayerChoice(int numberOfOptions) {
    int choice = -1;
    while(choice < 0 || choice >= numberOfOptions) {
        fflush(stdin);
        choice = getchar() - '0';
    }
    return choice;
}

char* input (const char* msg) {
    if(msg != NULL) {
        printf("%s", msg);
    }
    fflush(stdin);
    char* str = malloc(sizeof(char) * 100);
    fgets(str, 100, stdin);
    if( str[ strlen(str) - 1 ] == '\n')
        str[ strlen(str) - 1 ] = '\0';
    printf("\n SEED: %s\n", str);
    return str;
}

void displayCliNoGameToRestore() {
    printMessageType("Aucune sauvegarde n'a été trouvée", Neutral);
}