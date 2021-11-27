//
// Filename: tests.h
//
// Made by Théo Omnès on 09 oct. 2021.
//
// Description:
//

#ifndef MALLOCWORLD_TEST_H
#define MALLOCWORLD_TEST_H

#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include <stdbool.h>
#include "../cli/cli.h"

int assertEqualsInt(int expected, int actual);
int assertEqualsString(char* expected, char* actual);
void printResultTest(int passed, int shouldHavePassed);
int assertEqualsBool(bool expected, bool actual);
int assertEqualsPoint(int expectedX,int expectedY, int actualX, int actualY);
int assertEqualsAddress(void* expected, void* actual);
int assertBetweenInt(int lowerBound, int upperBound, int actual);

#endif //MALLOCWORLD_TEST_H