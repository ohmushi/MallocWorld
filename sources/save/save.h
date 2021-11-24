//
// Filename: save.h
//
// Made by Théo Omnès on 21 oct. 2021.
//
// Description:
//
#ifndef MALLOCWORLD_SAVE_H
#define MALLOCWORLD_SAVE_H

#include "../config/config.h"
#include <stdbool.h>
#include "../player/player.h"

char* getSaveFilePath();
FILE* openSaveFile(const char* mode);
void seekToLine(FILE* file, const char* line);
FILE* openSaveFileAndSearchNextLine(const char* mode, const char* line);
FILE* openSaveFileAndSearch(const char* mode, const char* line);
char getPreviousCharInFile(FILE* file);
void addLineInFile(FILE* file, char* lineToAdd, char* endOfLine);

#endif //MALLOCWORLD_SAVE_H