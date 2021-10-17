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
        printf("\nFAIL: expected: %d, actual: %d", expected, actual);
    }
    return expected == actual;
}

int assertEqualsString(char* expected, char* actual) {
    if(strcmp(expected,actual) != 0) {
        printf("\nFAIL: expected: %s, actual: %s", expected, actual);
    }
    return strcmp(expected,actual) == 0;
}

void printResultTest(int passed, int total) {
    if(passed == total){
        printf(": OK (%d/%d)\n", passed, total);
    }
    else{
        printf("\nFAIL (%d/%d)\n", passed, total );
    }
}

int assertEqualsBool(bool expected, bool actual) {
    char expectedString[10];
    char actualString[10];
    strcpy(expectedString, expected == true ? "true" : "false");
    strcpy(actualString, actual == true ? "true" : "false");
    if(expected != actual) {
        printf("\nFAIL: expected: %s, actual: %s", expectedString, actualString);
    }
    return expected == actual;
}