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
    char* unixRelativePath = findStringValueInConfigFile("save_file_unix_path");
    char* relativePath = adaptFilePathForCurrentOS(unixRelativePath);
    char* absolutePath = malloc(sizeof(char) * PATH_MAX);
    sprintf(absolutePath, "%s%s%s", projectDirectory, PATH_SEPARATOR, relativePath);
    free(projectDirectory);
    free(unixRelativePath);
    free(relativePath);
    return absolutePath;
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
 * @return The the previous player of the file current position
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

Player* getPlayerFromRestoreFile() {
    char* playerSectionDelimiter = findStringValueInConfigFile("player_section_save_file");
    FILE* restore = openSaveFileAndSearchNextLine("r", playerSectionDelimiter);
    if (NULL == restore) {
        return NULL;
    }
    Player* player = newPlayer(0, 0, 0,
                               newLocation(0,0,0),
                               newBag(5,20)
                               );
    char line[100] = "";
    setPlayerLevelFromRestoreLine(player, fgets(line, 100, restore));
    setPlayerExperienceFromRestoreLine(player, fgets(line, 100, restore));
    setPlayerHealthPointsFromRestoreLine(player, fgets(line, 100, restore));
    setPlayerInventoryFromRestoreFile(player);
    return player;
}

void setPlayerLevelFromRestoreLine(Player* player, char* restoreLineOfLevel) {
    char line[100] = "";
    strcpy(line, restoreLineOfLevel);
    char* playerLevelFormat = findStringValueInConfigFile("player_level_format");
    sscanf(line, playerLevelFormat, &player->level);
    free(playerLevelFormat);
}

void setPlayerExperienceFromRestoreLine(Player* player, char* restoreLineOfExperience) {
    char line[100] = "";
    strcpy(line, restoreLineOfExperience);
    char* playerExperienceFormat = findStringValueInConfigFile("player_experience_format");
    sscanf(line, playerExperienceFormat, &player->experience);
    free(playerExperienceFormat);
}

void setPlayerHealthPointsFromRestoreLine(Player* player, char* restoreLineOfHealthPoints) {
    char line[100] = "";
    strcpy(line, restoreLineOfHealthPoints);
    char* playerHealthPointsFormat = findStringValueInConfigFile("player_experience_format");
    sscanf(line, playerHealthPointsFormat, &player->healthPoints, &player->maxHealthPoints);
    free(playerHealthPointsFormat);
}

Bag* getBagFromRestoreString(const char* restore) {
    return newBag(10, 20);
}

void setPlayerInventoryFromRestoreFile(Player* player) {
    char* inventorySectionRestoreFile = findStringValueInConfigFile("inventory_section_save_file");
    int numberOfSlots = findIntValueInConfigFile("bag_size");
    int slotsCapacity = findIntValueInConfigFile("bag_slot_capacity");
    char* formatInventorySlot = findStringValueInConfigFile("inventory_slot_format");
    FILE* inventory = openSaveFileAndSearchNextLine("r", inventorySectionRestoreFile);
    Bag* bag = newBag(numberOfSlots,slotsCapacity);
    char lineSlot[100] = "";
    for(int i = 0; i < numberOfSlots; i += 1) {
        fgets(lineSlot, 100, inventory);
        ItemId itemId = Empty;
        int durability = 0;
        sscanf(lineSlot, formatInventorySlot, &bag->slots[i]->quantity, &itemId, &durability);
        Item item = findItemById(itemId);
        item.durability = durability;
        bag->slots[i]->item = item;
    }
    player->bag = bag;
    free(inventorySectionRestoreFile);
    free(formatInventorySlot);
    fclose(inventory);
}

/**
 * @return The save file as a string;
 */
char* getLastSavedGameAsString() {
    FILE* saveFile = openSaveFile("r");
    return getFileAsString(saveFile);
}

/**
 * Read the file and get a string of it.
 * https://stackoverflow.com/a/174552
 * @param file to read.
 * @return The string extract from the file.
 */
char* getFileAsString(FILE* file) {
    if (NULL == file) {
        return NULL;
    }
    char* buffer = NULL;
    long length = getFileLength(file);
    fseek (file, 0, SEEK_SET);
    buffer = malloc (length);
    if (buffer) {
        fread (buffer, 1, length, file);
    }
    fclose (file);
    char* copy = malloc(sizeof(char) * strlen(buffer) + 1);
    strncpy(copy, buffer, length);
    return copy;
}

/**
 * @return the length of a file in bytes.
 */
long getFileLength(FILE* file) {
    fseek (file, 0, SEEK_END);
    long length = ftell (file);
    fseek (file, 0, SEEK_SET);
    return length;
}

Map* getMapFromRestoreString(char* restore) {
    Zone** zones = malloc(sizeof(Zone*) * 3);
    for (int i = 0; i < 3; i += 1) {
        zones[i] = newZone(i, 10, 10, Ground, findZoneMinLevel(i+1));
    }
    return newMap(
            3,
            zones
            );
}