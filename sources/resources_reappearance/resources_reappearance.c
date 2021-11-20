//
// Created by kontc on 15/11/2021.
//

#include "resources_reappearance.h"

void addResourceToRespawnList(CellValue resource, Respawns** head, Location location) {
    Respawns* node = malloc(sizeof (Respawns));
    node->cell = resource;
    node->location = location;
    node->remainingTurns = findResourcesRespawnTime();
    node->next = *head;
    *head = node;
}

int findResourcesRespawnTime() {
    return findIntValueInConfigFile("resources_spawn_time");
}

void printRespawnList(Respawns* list) {
    while(list != NULL) {
        printf("\nResource %d (%d,%d) in zone %d respawns in %d turns",
               list->cell, list->location.x, list->location.y, list->location.zoneId, list->remainingTurns);
        list = list->next;
    }
}

///*****************Osiris
int updateRespawnList(Respawns** head){
    while(head != NULL) {
        head->findResourcesRespawnTime()-1;
        head = head->next;
    }
}