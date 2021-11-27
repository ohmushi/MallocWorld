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
    char currentLine[FILE_LINE_LENGTH] = "\0";
    while(!feof(file)) {
        fgets(currentLine, FILE_LINE_LENGTH, file );
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
    Player* player = newPlayer(0, 0, 0, newLocation(0,0,0), NULL);
    char line[FILE_LINE_LENGTH] = "";
    setPlayerLevelFromRestoreLine(player, fgets(line, FILE_LINE_LENGTH, restore));
    setPlayerExperienceFromRestoreLine(player, fgets(line, FILE_LINE_LENGTH, restore));
    setPlayerHealthPointsFromRestoreLine(player, fgets(line, FILE_LINE_LENGTH, restore));
    setPlayerInventoryFromRestoreFile(player);
    setPlayerChestFromRestoreFile(player);
    return player;
}

void setPlayerLevelFromRestoreLine(Player* player, char* restoreLineOfLevel) {
    char line[FILE_LINE_LENGTH] = "";
    strncpy(line, restoreLineOfLevel, FILE_LINE_LENGTH);
    char* playerLevelFormat = findStringValueInConfigFile("player_level_format");
    sscanf(line, playerLevelFormat, &player->level);
    free(playerLevelFormat);
}

void setPlayerExperienceFromRestoreLine(Player* player, char* restoreLineOfExperience) {
    char line[FILE_LINE_LENGTH] = "";
    strncpy(line, restoreLineOfExperience, FILE_LINE_LENGTH);
    char* playerExperienceFormat = findStringValueInConfigFile("player_experience_format");
    sscanf(line, playerExperienceFormat, &player->experience);
    free(playerExperienceFormat);
}

void setPlayerHealthPointsFromRestoreLine(Player* player, char* restoreLineOfHealthPoints) {
    char line[FILE_LINE_LENGTH] = "";
    strncpy(line, restoreLineOfHealthPoints, FILE_LINE_LENGTH);
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
    char lineSlot[FILE_LINE_LENGTH] = "";
    for(int i = 0; i < numberOfSlots; i += 1) {
        fgets(lineSlot, FILE_LINE_LENGTH, inventory);
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

void setPlayerChestFromRestoreFile(Player* player) {
    char* storageSectionRestoreFile = findStringValueInConfigFile("storage_section_save_file");
    char* formatSlotChest = findStringValueInConfigFile("format_slot_chest");
    FILE* storage = openSaveFileAndSearchNextLine("r", storageSectionRestoreFile);
    char slotLine[FILE_LINE_LENGTH] = "";
    while (fgets(slotLine, FILE_LINE_LENGTH, storage), !feof(storage)) {
        ChestSlot slot = newChestSlot(0, Empty);
        sscanf(slotLine, formatSlotChest, &slot.quantity, &slot.id);
        pushSlotInChest(slot, &player->chest);
    }
    free(storageSectionRestoreFile);
    free(formatSlotChest);
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

Map* getMapFromRestoreFile() {
    int numberOfZones = (int)findNumberOfZones();
    Zone** zoneList = malloc(sizeof(Zone*) * numberOfZones);
    Map* map = newMap(numberOfZones,zoneList);
    for (int i = 0; i < numberOfZones; i += 1) {
        int zoneId = i+1;
        map->zones[i] = getZoneFromRestoreFile(zoneId);
    }
    return map;
}

Zone* getZoneFromRestoreFile(int zoneId) {
    Zone* zone = newZone(zoneId,
                         getNumberOfRowsInZoneInRestoreFile(zoneId),
                         getNumberOfColumnsInZoneInRestoreFile(zoneId),
                         Ground,
                         findZoneMinLevel(zoneId));
    fillZoneWithRestoreFile(zone);
    return zone;
}

int getNumberOfRowsInZoneInRestoreFile(int zoneId) {
    char* zoneSectionLine = getZoneSectionLineById(zoneId);
    FILE* zoneSection = openSaveFileAndSearchNextLine("r", zoneSectionLine);
    int count = 0;
    char line[FILE_LINE_LENGTH] = "";
    bool lineIsInZone = true;
    while (lineIsInZone) {
        fgets(line, FILE_LINE_LENGTH, zoneSection);
        lineIsInZone = !feof(zoneSection) && strncmp(line, "--", 2) != 0 && strncmp(line, "===", 3) != 0;
        count += lineIsInZone ? 1 : 0;
    }
    free(zoneSectionLine);
    fclose(zoneSection);
    return count;
}

int getNumberOfColumnsInZoneInRestoreFile(int zoneId) {
    char* zoneSectionLine = getZoneSectionLineById(zoneId);
    FILE* zoneSection = openSaveFileAndSearchNextLine("r", zoneSectionLine);
    char line[FILE_LINE_LENGTH] = "";
    fgets(line, FILE_LINE_LENGTH, zoneSection);
    int numberOfColumns = countCharInString(line, ' ') + 1;
    free(zoneSectionLine);
    fclose(zoneSection);
    return numberOfColumns;
}

char* getZoneSectionLineById(int zoneId) {
    char* formatZoneSectionLine = getFormatOfZoneSectionLine();
    char* zoneSectionLine = malloc(sizeof(char) * FILE_LINE_LENGTH);
    sprintf(zoneSectionLine, formatZoneSectionLine, zoneId);
    free(formatZoneSectionLine);
    return zoneSectionLine;
}

void fillZoneWithRestoreFile(Zone* zone) {
    char* zoneSectionLine = getZoneSectionLineById(zone->id);
    FILE* zoneSection = openSaveFileAndSearchNextLine("r", zoneSectionLine);
    char line[FILE_LINE_LENGTH] = "";
    for (int y = 0; y < zone->numberRows; y += 1) {
        fgets(line, FILE_LINE_LENGTH, zoneSection);
        IntArray* row = zoneLineToArray(line);
        for (int x = 0; x < zone->numberColumns; x += 1) {
            setZoneValueAtPosition(zone, x, y, row->array[x]);
        }
        freeIntArray(row);
    }
    free(zoneSectionLine);
    fclose(zoneSection);
}

IntArray* zoneLineToArray(char* zoneLine) {
    IntArray* array = malloc(sizeof(IntArray));
    array->size = countCharInString(zoneLine, ' ') + 1;
    array->array = malloc(sizeof(int) * array->size);
    char lineCopy[FILE_LINE_LENGTH] = "";
    strcpy(lineCopy, zoneLine);
    const char * separators = " \0";
    char* strToken = strtok ( lineCopy, separators );
    for(int i = 0; strToken != NULL; i += 1 ) {
        array->array[i] = atoi(strToken);
        strToken = strtok (NULL, separators);
    }
    return array;
}