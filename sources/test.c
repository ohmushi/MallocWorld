//
// Created by Théo Omnès on 09/10/2021.
//

#include "test.h"

int assertEqualsInt(int expected, int actual) {
    if(expected != actual) {
        printf("FAIL: expected = %d, actual: %d", expected, actual);
    }
    return expected == actual;
}

int assertEqualsString(char* expected, char* actual) {
    if(strcmp(expected,actual) != 0) {
        printf("FAIL: expected = %s, actual: %s", expected, actual);
    }
    return strcmp(expected,actual) == 0;
}