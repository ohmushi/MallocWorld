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


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdint.h>

#if defined(WIN32)
    #include <windows.h>
    #include <direct.h>
    #define MALLOCWORLD_PATH_CONFIG_FILE "resources\\config.yaml"
    #define PATH_SEPARATOR "\\"
    #define getcwd _getcwd
#else
    #include <unistd.h>
    #define MALLOCWORLD_PATH_CONFIG_FILE "resources/config.yaml"
    #define PATH_SEPARATOR "/"
#endif

#ifndef PATH_MAX
#define PATH_MAX 255
#endif

typedef struct IntArray {
    int size;
    int* array;
}IntArray;

#define NUMBER_OF_INT_CONFIG 21
typedef struct IntConfig{
    const char* key;
    int value;
}IntConfig;

#define NUMBER_OF_INT_ARRAY_CONFIG 7
#define INT_ARRAY_CONFIG_MAX_SIZE 20
typedef struct IntArrayConfig{
    const char* key;
    int array[INT_ARRAY_CONFIG_MAX_SIZE];
    int arraySize;
}IntArrayConfig;

#define NUMBER_OF_STRING_CONFIG 1
#define STRING_CONFIG_MAX_SIZE 255
typedef struct StringConfig{
    const char* key;
    char value[STRING_CONFIG_MAX_SIZE];
}StringConfig;


char* getProjectDirectory();
char* getConfigFilePath();
FILE* openConfigFile();
char* findStringValueInConfigFile(char* key);
int findIntValueInConfigFile(char* key);
char* trim(char* input);
int8_t isWhiteSpace(char c);
int8_t isTheGoodKey(char* key, char* line);
IntArray* findIntArrayInConfigFile(char* key);
void freeIntArrayConfig(IntArrayConfig* array);
int8_t countCharInString(char* string, char searched);
IntArray* stringToArray(char* string);
void freeIntArray(IntArray* array);

#endif //MALLOCWORLD_CONFIG_H