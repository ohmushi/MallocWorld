//
// Filename: test.c
//
// Made by Théo Omnès on 09 oct. 2021.
//
// Description:
//

#include "test.h"

int assertEqualsInt(int expected, int actual) {
    if(expected != actual) {
        printf(ANSI_COLOR_RED "\nFAIL: expected: %d, actual: %d", expected, actual);
    }
    return expected == actual;
}

int assertEqualsString(char* expected, char* actual) {
    if(strcmp(expected,actual) != 0) {
        printf(ANSI_COLOR_RED "\nFAIL: expected: %s, actual: %s", expected, actual);
    }
    return strcmp(expected,actual) == 0;
}

void printResultTest(int passed, int total) {
    if(passed == total){
        printf(ANSI_COLOR_GREEN " OK (%d/%d)" ANSI_COLOR_RESET "\n", passed, total);
    }
    else{
        printf(ANSI_COLOR_RED "\nFAIL (%d/%d)\n", passed, total );
    }
}

int assertEqualsBool(bool expected, bool actual) {
    char expectedString[10];
    char actualString[10];
    strcpy(expectedString, expected == true ? "true" : "false");
    strcpy(actualString, actual == true ? "true" : "false");
    if(expected != actual) {
        printf(ANSI_COLOR_RED "\nFAIL: expected: %s, actual: %s" ANSI_COLOR_RESET, expectedString, actualString);
    }
    return expected == actual;
}

int assertEqualsPoint(int expectedX,int expectedY, int actualX, int actualY) {
    if(expectedX != actualX || expectedY != actualY) {
        printf(ANSI_COLOR_RED "\nFAIL: expected: (%d,%d), actual: (%d,%d)", expectedX, expectedY, actualX, actualY);
    }
    return expectedX == actualX && expectedY == actualY;
}

int assertEqualsAddress(void* expected, void* actual) {
    if(expected != actual) {
        printf(ANSI_COLOR_RED "\nFAIL: expected: %p, actual: %p", expected, actual);
    }
    return expected == actual;
}