//
// Filename: config.c
//
// Made by Théo Omnès on 10 oct. 2021.
//
// Description:
//
#include "config.h"

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

char* findStringValueInConfigFile(char* key) {
    FILE* config = getConfigFile();
    if( config == NULL) {
        return NULL;
    }
    while( !feof(config) ) {
        char line[255];
        fgets(line, 253, config);
        line[254] = '\0';

    }

    return "__";
}