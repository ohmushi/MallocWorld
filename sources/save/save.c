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
    if(NULL == file) {
        return NULL;
    }
    free(path);
    return file;
}

/**
 * Put the file cursor on the next line matching the searched line.
 * Browse a file line by line until the current line
 * matches the searched line.
 * The line given and the line in file must be exactly the same
 * If the line is not found, the cursor is at the end of the file
 * @param file The file to search in
 * @param line The line wanted
 */
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

/**
 * Open the Save file the the wanted mode
 * then set the file cursor at the very next line matching the searched string
 * or at the end of file if not found
 * @return The Save file at the next line of the searched one
 */
FILE* openSaveFileAndSearchNextLine(const char* mode, const char* line) {
    FILE* saveFile = openSaveFile(mode);
    if(NULL == saveFile) {
        return NULL;
    }
    seekToLine(saveFile, line);
    return saveFile;
}

/**
 * Open the Save file with the wanted mode then put the cursor at the beginning of
 * the searched line or at the end of file if not found
 * @return The Save file at the beginning of the searched line
 */
FILE* openSaveFileAndSearch(const char* mode, const char* line) {
    FILE* saveFile = openSaveFileAndSearchNextLine(mode, line);
    if(NULL == saveFile) {
        return NULL;
    }
    int offset = (int)(strlen(line)+1) * -1;
    fseek(saveFile, offset, SEEK_CUR);
    return saveFile;
}

/**
 * @return The the previous character of the file current position
 */
char getPreviousCharInFile(FILE* file) {
    fseek(file, (long)sizeof(char) * -1, SEEK_CUR);
    return (char)fgetc(file);
}

/**
 * Add a line in a file.
 * @param file
 * @param lineToAdd
 * @param endOfLine The end of the line, it can be a line feed, or any custom string
 */
void addLineInFile(FILE* file, char* lineToAdd, char* endOfLine) {
    if(getPreviousCharInFile(file) != '\n') {
        fputc('\n',file);
    }
    fputs(strcat(lineToAdd, endOfLine),file);
}