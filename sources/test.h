//
// Filename: test.h
//
// Made by Théo Omnès on 09 oct. 2021.
//
// Description:
//

#ifndef MALLOCWORLD_TEST_H
#define MALLOCWORLD_TEST_H

#endif //MALLOCWORLD_TEST_H


#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include <stdbool.h>

int assertEqualsInt(int expected, int actual);
int assertEqualsString(char* expected, char* actual);
void printResultTest(int passed, int total);
int assertEqualsBool(bool expected, bool actual);
int assertEqualsPoint(int expectedX,int expectedY, int actualX, int actualY);