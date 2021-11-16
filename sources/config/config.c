//
// Filename: config.c
//
// Made by Théo Omnès on 10 oct. 2021.
//
// Description:
//
#include "config.h"

const IntConfig INT_CONFIG[NUMBER_OF_INT_CONFIG] = {
        {"number_of_zones", 3},

        {"zone_1_minimum_level", 0},
        {"zone_2_minimum_level", 0},
        {"zone_3_minimum_level", 7},

        {"player_start_level", 1},
        {"player_start_HP", 100},
        {"player_start_XP", 0},

        {"bag_size", 10},
        {"bag_slot_capacity", 20},
        {"resource_frequency", 20}
        {"resources_spawn_time", 10},
};

const IntArrayConfig INT_ARRAY_CONFIG[NUMBER_OF_INT_ARRAY_CONFIG] = {
        {"zone_1_size", {20,30}, 2},
        {"zone_2_size", {30,50}, 2},
        {"zone_3_size", {50,70}, 2},

        {"player_start_equipment", {1,2,3,4}, 4},

        {"zone_1_resources", {3, 4, 5}, 3},
        {"zone_2_resources", {6, 7, 8}, 3},
        {"zone_3_resources", {9, 10, 11}, 3},
};

const StringConfig STRING_CONFIG[NUMBER_OF_STRING_CONFIG] = {
        {"format_slot_chest", "{%d}@{%d}"}
};

/*
 * Check if a char is a white space,
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
        default:
            return 0;
    }
}

/*
 * trim
 * https://stackoverflow.com/a/2531068
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

/*
 * get the absolute path of the project directory root
 * using getcwd() in unistd.h
 */
char* getProjectDirectory() {
    char* cwd = malloc(sizeof(char) * PATH_MAX);
    if( getcwd(cwd, PATH_MAX) != NULL) {
        char* cursor = strstr(cwd, MALLOCWORLD_PROJECT_NAME);
        if(NULL == cursor) {
            return NULL;
        }
        int8_t sizeProjectName = strlen(MALLOCWORLD_PROJECT_NAME);
        *(cursor + sizeProjectName) = '\0';
    }
    return cwd;
}

/*
 * get the absolute path of the config file
 * by default in /...../mallocworld/resources/config.yaml
 */
char* getConfigFilePath() {
    char* projectDirectory = getProjectDirectory();
    char* pathConfigFile = malloc(sizeof(char) * (strlen(projectDirectory) + strlen(MALLOCWORLD_PATH_CONFIG_FILE)) );
    sprintf(pathConfigFile, "%s%s%s", projectDirectory, PATH_SEPARATOR , MALLOCWORLD_PATH_CONFIG_FILE);
    free(projectDirectory);
    //pathConfigFile[strlen(pathConfigFile)] = '\0';
    return pathConfigFile;
}

/*
 * Get the config file in READ Mode
 */
FILE* openConfigFile() {
    char* configFilePath = getConfigFilePath();
    FILE* file = fopen(configFilePath, "r");
    //free(configFilePath);

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
    if(NULL == endOfKey) {
        return 0;
    }
    *endOfKey = '\0';
    int8_t isTheGoodKey = strcmp(key, trim(cpy)) == 0;
    //free(cpy);
    return isTheGoodKey;
}

/*
 * find in all the config file the STRING value corresponding to a unique key
 * the config is file like:
 * {key1}: {value1}
 * {key2}: {value2}
 * {key3}: {value3}
 */
char* findStringValueInConfigFile(char* key) {
    for(int i = 0; i < NUMBER_OF_STRING_CONFIG; i += 1) {
        if(strcmp(STRING_CONFIG[i].key, key) == 0) {
            char* value = malloc(sizeof(char) * strlen(STRING_CONFIG[i].value));
            strcpy(value, STRING_CONFIG[i].value);
            return value;
        }
    }
    return NULL;
}

/*
 * find in all the config file the INT value corresponding to a unique key (cf. char* findStringValueInConfigFile(char* key) )
 * return the int value
 * OR
 * INT_MIN if the value is not found
 * OR
 * INT_MIN + 1 if the value is not a integer
 */
int findIntValueInConfigFile(char* key) {
    for(int i = 0; i < NUMBER_OF_INT_CONFIG; i += 1) {
        if(strcmp(INT_CONFIG[i].key, key) == 0) {
            return INT_CONFIG[i].value;
        }
    }
    return INT_MIN;
}

/**
 * find in the config file the values of an array key: [a,b,c,...]
 * @param key in the config file
 * @return
 */
IntArray* findIntArrayInConfigFile(char* key) {
    IntArrayConfig arrayConfig = {"", {0}, 0};
    for(int i = 0; i < NUMBER_OF_INT_ARRAY_CONFIG; i += 1) {
        if(strcmp(INT_ARRAY_CONFIG[i].key, key) == 0) {
            arrayConfig = INT_ARRAY_CONFIG[i];
            break;
        }
    }

    IntArray* array = malloc(sizeof(struct IntArray));
    array->size = arrayConfig.arraySize;
    array->array = malloc(sizeof(int) * array->size);
    for(int i = 0; i < arrayConfig.arraySize; i += 1) {
        array->array[i] = arrayConfig.array[i];
    }
    return array;
}

void freeIntArrayConfig(IntArrayConfig* array) {
    free(array);
}

/**
 * free the struct IntArray and its int* array
 * @param array to free
 */
void freeIntArray(IntArray* array) {
    if(array != NULL) {
        if(array->array != NULL) {
            free(array->array);
        }
        free(array);
    }
}

/**
 * Transform a string "[a, b,c ,d,...]" to a struct IntArray
 * spaces do not matter
 * @param string
 * @return
 */
IntArray* stringToArray(char* string) {
    IntArray* array = malloc(sizeof(IntArray));
    array->size = 0;
    array->array = NULL;
    int stringLength = (int)strlen(string);
    if(string[0] != '[' || string[stringLength - 1] != ']'){ // check if string is like "[ ... ]"
        return NULL;
    }

    array->size = countCharInString(string, ',') + 1;
    array->array = malloc(sizeof(int) * array->size);

    const char * separators = ",\0";
    char* cpy = malloc(sizeof(char) * stringLength);
    strcpy(cpy, string+1); // +1 to remove the '['
    cpy[stringLength-2] = '\0'; // to remove the ']'

    char* strToken = strtok ( cpy, separators );
    for(int i = 0; strToken != NULL; i += 1 ) {
        array->array[i] = atoi(strToken);
        strToken = strtok ( NULL, separators );
    }
    //free(cpy);
    return array;
}

/**
 * Count the number of times a char is present in a string
 */
int8_t countCharInString(char* string, char searched) {
    int8_t count = 0;
    for(int i = 0; i < strlen(string); i += 1) {
        if(string[i] == searched) {
            count += 1;
        }
    }
    return count;
}