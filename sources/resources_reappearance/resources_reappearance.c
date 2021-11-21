//
// Created by kontc on 15/11/2021.
//

#include "resources_reappearance.h"

void addResourceToRespawnList(CellValue resource, ToRespawn** head, Location location) {
    ToRespawn* node = malloc(sizeof (ToRespawn));
    node->cell = resource;
    node->location = location;
    node->remainingTurns = findResourcesRespawnTime();
    node->next = *head;
    *head = node;
}

int findResourcesRespawnTime() {
    return findIntValueInConfigFile("resources_spawn_time");
}

void printRespawnList(ToRespawn* list) {
    printf("\nRespawn List:\n");
    while(list != NULL) {
        printf("\nResource %d (%d,%d) in zone %d respawns in %d turns",
               list->cell, list->location.x, list->location.y, list->location.zoneId, list->remainingTurns);
        list = list->next;
    }
}

void updateToRespawnList(ToRespawn* head) {
    while(head != NULL) {
        head->remainingTurns -= 1;
        head = head->next;
    }
}

void removeRespawnedCellsFromToRespawnList(ToRespawn** head, Location playerLocation){
    bool headMustBeRemoved = toRespawnNodeMustBeRemoved(*head, playerLocation);
    if (headMustBeRemoved) {
        ToRespawn* tmp = *head;
        *head = tmp->next;
        free(tmp);
    }
    removeToRespawnNodes(head, playerLocation);
}

bool toRespawnNodeMustBeRemoved(ToRespawn* node, Location playerLocation) {
    if(node == NULL) {
        return false;
    }
    bool playerIsNotAtRespawnLocation = !locationsAreEquals(node->location, playerLocation);
    return  playerIsNotAtRespawnLocation
            && node->remainingTurns <= 0;
}

void removeToRespawnNodes(ToRespawn** toRemove, Location playerLocation) {
    ToRespawn* node = *toRemove;
    ToRespawn* prev = node;
    while (node != NULL) {
        prev = node;
        node = node->next;
        if (toRespawnNodeMustBeRemoved(node, playerLocation)) {
            prev->next = node->next;
            free(node);
            prev = prev->next;
            node = prev;
        }
    }
}