//
// Filename: save.h
//
// Made by Théo Omnès on 21 oct. 2021.
//
// Description:
//
#ifndef MALLOCWORLD_SAVE_H
#define MALLOCWORLD_SAVE_H

#endif //MALLOCWORLD_SAVE_H

#ifndef MALLOCWORLD_CONFIG_H
#include "../config/config.h"
#endif

char* getSaveFilePath();
FILE* openSaveFile(const char* mode);
void seekToLine(FILE* file, const char* line);
FILE* openSaveFileAndSeek(const char* mode, const char* line);