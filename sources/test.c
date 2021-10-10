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
        printf("\nFAIL: expected = %d, actual: %d", expected, actual);
    }
    return expected == actual;
}

int assertEqualsString(char* expected, char* actual) {
    if(strcmp(expected,actual) != 0) {
        printf("\nFAIL: expected = %s, actual: %s", expected, actual);
    }
    return strcmp(expected,actual) == 0;
}