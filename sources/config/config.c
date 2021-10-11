//
// Filename: config.c
//
// Made by Théo Omnès on 10 oct. 2021.
//
// Description:
//
#include "config.h"

/*
 * Check if a cha is a white space,
 * return 1 for a whitespace, 0 for not
 */
int8_t isWhiteSpace(char c) {
    switch (c) {
        case ' ':
        case '\n':
        case '\t':
        case '\f':
        case '\r':
            return 1;
            break;
        default:
            return 0;
            break;
    }
}

/*
 * trim
 * https://stackoverflow.com/questions/656542/trim-a-string-in-c
 * Remove white space before and after a string
 */
char* trim(char* input) {
    char* start = input;
    while (isWhiteSpace(*start)) { //trim left
        start++;
    }

    char* ptr = start;
    char* end = start;
    while (*(++ptr) != '\0') { //trim right
        if (!isWhiteSpace(*ptr)) { //only move end pointer if char isn't a space
            end = ptr;
        }
    }

    *++end = '\0'; //terminate the trimmed string with a null

    return start;
}



char* getProjectDirectory() {
    char* cwd = malloc(sizeof(char) * PATH_MAX);
    if( getcwd(cwd, PATH_MAX) != NULL) {
        char* cursor = strstr(cwd, MALLOCWORLD_PROJECT_NAME);
        if(cursor == NULL) {
            return NULL;
        }
        int8_t sizeProjectName = strlen(MALLOCWORLD_PROJECT_NAME);
        *(cursor + sizeProjectName) = '\0';
    }
    return cwd;
}

char* getConfigFilePath() {
    char* projectDirectory = getProjectDirectory();
    char* pathConfigFile = malloc(sizeof(char) * (strlen(projectDirectory) + strlen(MALLOCWORLD_PATH_CONFIG_FILE)) );
    sprintf(pathConfigFile, "%s/%s", projectDirectory, MALLOCWORLD_PATH_CONFIG_FILE);
    free(projectDirectory);
    pathConfigFile[strlen(pathConfigFile)] = '\0';
    return pathConfigFile;
}

/*
 * Get the config file in READ Mode
 */
FILE* getConfigFile() {
    char* configFilePath = getConfigFilePath();
    FILE* file = fopen(configFilePath, "r");
    free(configFilePath);

    return file;
}

/*
 * get the value from a line of the yaml file like {key}: {value}
 *
 */
char* getValueInConfigLine(char* line) {
    char value[255];
    value[254] = '\0';
    char* cursor = strchr(line, ':');
    if(strlen(cursor) < 3) {
        return NULL;
    }
    cursor += 1; // ': value' -> ' value\n'
    cursor = trim(cursor);
    char* val = malloc(sizeof(char) * strlen(cursor)+1);
    val[strlen(cursor)] = '\0';
    strcpy(val, cursor);
    return val;
}

/*
 * check if the YAML key is the searched one
 * strstr doesn't work because 'abc' is found in 'abcdef'
 */
int8_t isTheGoodKey(char* key, char* line) {
    char* cpy = malloc(sizeof(char) * strlen(line));
    strcpy(cpy, line);
    char* endOfKey = strchr(cpy, ':');
    if(endOfKey == NULL) {
        return 0;
    }
    *endOfKey = '\0';
    int8_t isTheGoodKey = strcmp(key, trim(cpy)) == 0;
    free(cpy);
    return isTheGoodKey;
}

char* findStringValueInConfigFile(char* key) {
    FILE* config = getConfigFile();
    if( config == NULL) {
        return NULL;
    }
    while( !feof(config) ) {
        char line[255];
        fgets(line, 253, config);
        line[254] = '\0';
        if( isTheGoodKey(key, line) ) {
            return getValueInConfigLine(line);
        }
    }

    return NULL;
}

int findIntValueInConfigFile(char* key) {
    char* stringValue = findStringValueInConfigFile(key);
    if(stringValue == NULL) {
        return INT_MIN;
    }
    char* endPtr;
    long value = strtol(stringValue, &endPtr, 10);
    if( endPtr == stringValue) { // doesn't found a long value
        return INT_MIN + 1;
    }

    free(stringValue);
    return (int)value;
}