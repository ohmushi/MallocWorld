//
// Created by kontc on 15/11/2021.
//

#include "resources_reappearance.h"

/**
 * Push a resource in the To Respawn linked list.
 */
void addResourceToRespawnList(CellValue resource, ToRespawn** head, Location location) {
    ToRespawn* node = malloc(sizeof (ToRespawn));
    node->cell = resource;
    node->location = location;
    node->remainingTurns = findResourcesRespawnTime();
    node->next = *head;
    *head = node;
}

/**
 * @return The number of turns between the moment a resource is collected and its supposed respawn.
 */
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

/**
 * Remove 1 from the remaining turns before respawn to each resource of the To Respawn linked list.
 * @param head The head of the linked list.
 */
void updateToRespawnList(ToRespawn* head) {
    while(head != NULL) {
        head->remainingTurns -= 1;
        head = head->next;
    }
}

/**
 * If the head of the To Respawn linked list has to be removed, remove it,
 * then call removeToRespawnNodes for rest of the linked list
 */
void removeRespawnedCellsFromToRespawnList(ToRespawn** head, Location playerLocation){
    bool headMustBeRemoved = toRespawnNodeMustBeRemoved(*head, playerLocation);
    if (headMustBeRemoved) {
        ToRespawn* tmp = *head;
        *head = tmp->next;
        free(tmp);
    }
    removeToRespawnNodes(head, playerLocation);
}

/**
 * @return True if the remaining turns before respawn of the node of the To Respawn list <= 0
 * and of the location of the resource is different from the player location
 */
bool toRespawnNodeMustBeRemoved(ToRespawn* node, Location playerLocation) {
    if(node == NULL) {
        return false;
    }
    bool playerIsNotAtRespawnLocation = !locationsAreEquals(node->location, playerLocation);
    return  playerIsNotAtRespawnLocation
            && node->remainingTurns <= 0;
}

/**
 * Browse all elements in the To Respawn list, and if an element has to be removed, remove it.
 */
void removeToRespawnNodes(ToRespawn** head, Location playerLocation) {
    ToRespawn* node = *head;
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