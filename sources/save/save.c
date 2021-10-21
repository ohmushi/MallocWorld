//
// Filename: save.c
//
// Made by Théo Omnès on 21 oct. 2021.
//
// Description:
//

#include "save.h"


/**
 * Get the absolute path of the save file
 * the path inside the project is by default resources/save.txt
 * can be changed in the config file with the key "save_file"
 * @return String of the absolute path of the save file
 */
char* getSaveFilePath() {
    char* projectDirectory = getProjectDirectory();
    char* saveFileRelativePath = findStringValueInConfigFile("save_file");
    char saveFileRelativePathOs[255];
    strcpy(saveFileRelativePathOs, saveFileRelativePath); // path separator change
    char* pathSaveFile = malloc(sizeof(char) * PATH_MAX);
    sprintf(pathSaveFile, "%s%s%s", projectDirectory, PATH_SEPARATOR, saveFileRelativePathOs);
    free(projectDirectory);
    free(saveFileRelativePath);
    return pathSaveFile;
}

/**
 * open the save file
 * @param mode The mode of opening the file (r, w, a, +)
 */
FILE* openSaveFile(const char* mode) {
    char* path = getSaveFilePath();
    FILE* file = fopen(path, mode);
    if(file == NULL) {
        return NULL;
    }
    free(path);
    return file;
}

void seekToLine(FILE* file, const char* line) {
    char currentLine[255] = "\0";
    while(!feof(file)) {
        fgets(currentLine, 254, file );
        currentLine[strlen(currentLine)-1] = '\0';
        if(strcmp(currentLine, line) == 0) {
            return;
        }
    }
}

FILE* openSaveFileAndSeek(const char* mode, const char* line) {
    FILE* saveFile = openSaveFile(mode);
    if(saveFile == NULL) {
        return NULL;
    }
    seekToLine(saveFile, line);
    return saveFile;
}