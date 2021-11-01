//
// Filename: config.h
//
// Made by Théo Omnès on 10 oct. 2021.
//
// Description:
//

#ifndef MALLOCWORLD_CONFIG_H
#define MALLOCWORLD_CONFIG_H


#define MALLOCWORLD_PROJECT_NAME  "MallocWorld"
#define MALLOCWORLD_PATH_CONFIG_FILE "resources/config.yaml"


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdint.h>

#if defined(WIN32)
#define PATH_SEPARATOR "\\"
#define getcwd printf
#else
#include <unistd.h>
#define PATH_SEPARATOR "/"
#endif

#ifndef PATH_MAX
#define PATH_MAX 255
#endif

typedef struct IntArray {
    int size;
    int* array;
}IntArray;

char* getProjectDirectory();
char* getConfigFilePath();
FILE* openConfigFile();
char* findStringValueInConfigFile(char* key);
int findIntValueInConfigFile(char* key);
char* trim(char* input);
int8_t isWhiteSpace(char c);
int8_t isTheGoodKey(char* key, char* line);
IntArray* findIntArrayInConfigFile(char* key);
int8_t countCharInString(char* string, char searched);
IntArray* stringToArray(char* string);
void freeIntArray(IntArray* array);

#endif //MALLOCWORLD_CONFIG_H