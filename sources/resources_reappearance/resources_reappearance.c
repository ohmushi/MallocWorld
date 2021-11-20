//
// Created by kontc on 15/11/2021.
//

#include "resources_reappearance.h"

void addResourceToRespawnList(CellValue resource, toRespawn** head, Location location) {
    toRespawn* node = malloc(sizeof (toRespawn));
    node->cell = resource;
    node->location = location;
    node->remainingTurns = findResourcesRespawnTime();
    node->next = *head;
    *head = node;
}

int findResourcesRespawnTime() {
    return findIntValueInConfigFile("resources_spawn_time");
}

void printRespawnList(toRespawn* list) {
    printf("\nRespawn List:\n");
    while(list != NULL) {
        printf("\nResource %d (%d,%d) in zone %d respawns in %d turns",
               list->cell, list->location.x, list->location.y, list->location.zoneId, list->remainingTurns);
        list = list->next;
    }
}

///*****************Osiris
void updateRespawnList(toRespawn* head){
    while(head != NULL) {
        head->remainingTurns -= 1;
        head = head->next;
    }
}