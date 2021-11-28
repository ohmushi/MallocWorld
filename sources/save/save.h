//
// Filename: save.h
//
// Made by Théo Omnès on 21 oct. 2021.
//
// Description:
//
#ifndef MALLOCWORLD_SAVE_H
#define MALLOCWORLD_SAVE_H

#include <stdbool.h>
#include "../config/config.h"
#include "../player/player.h"
#include "../chest/chest.h"
#include "../item/tool/tool.h"
#include "../item/weapon/weapon.h"
#include "../item/heal/heal.h"
#include "../item/craft_resource/craft_resource.h"

char* getSaveFilePath();
FILE* openSaveFile(const char* mode);
void seekToLine(FILE* file, const char* line);
FILE* openSaveFileAndSearchNextLine(const char* mode, const char* line);
FILE* openSaveFileAndSearch(const char* mode, const char* line);
char getPreviousCharInFile(FILE* file);
void addLineInFile(FILE* file, char* lineToAdd, char* endOfLine);
char* getFileAsString(FILE* file);
long getFileLength(FILE* file);
Player* getPlayerFromRestoreFile();
void setPlayerLevelFromRestoreLine(Player* player, char* restoreLineOfLevel);
void setPlayerExperienceFromRestoreLine(Player* player, char* restoreLineOfExperience);
void setPlayerHealthPointsFromRestoreLine(Player* player, char* restoreLineOfHealthPoints);
Bag* getBagFromRestoreString(const char* restore);
void setPlayerInventoryFromRestoreFile(Player* player);
void setPlayerChestFromRestoreFile(Player* player);
char* getLastSavedGameAsString();
Map* getMapFromRestoreFile();
Zone* getZoneFromRestoreFile(int zoneId);
int getNumberOfRowsInZoneInRestoreFile(int zoneId);
int getNumberOfColumnsInZoneInRestoreFile(int zoneId);
char* getZoneSectionLineById(int zoneId);
void fillZoneWithRestoreFile(Zone* zone);
IntArray* zoneLineToArray(char* zoneLine);
FILE* getRestoreFileSingleton();
void setRestoreFileSingleton(FILE* file);
Item newCompleteItemById(ItemId id);

#endif //MALLOCWORLD_SAVE_H