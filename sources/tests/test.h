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

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int assertEqualsInt(int expected, int actual);
int assertEqualsString(char* expected, char* actual);
void printResultTest(int passed, int total);
int assertEqualsBool(bool expected, bool actual);
int assertEqualsPoint(int expectedX,int expectedY, int actualX, int actualY);
int assertEqualsAddress(void* expected, void* actual);