//
// Filename: config.h
//
// Made by Théo Omnès on 10 oct. 2021.
//
// Description:
//

#ifndef MALLOCWORLD_CONFIG_H
#define MALLOCWORLD_CONFIG_H

#endif //MALLOCWORLD_CONFIG_H

#define MALLOCWORLD_PROJECT_NAME  "mallocworld"
#define MALLOCWORLD_PATH_CONFIG_FILE "resources/config.yaml"


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

char* getProjectDirectory();
char* getConfigFilePath();
FILE* getConfigFile();
char* findStringValueInConfigFile(char* key);