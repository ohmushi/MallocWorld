//
// Created by Théo Omnès on 21/10/2021.
//

#include "npc.h"


void talkToNPC(Character* player) {
    displayNpcMenu("Que souhaites tu faire ?");
    NpcMenuChoice choice = getNpcMenuChoice();
    switch (choice) {
        case Fix: printf("fix !");//TODO fix
            break;
        case Craft: printf("craft !");//TODO craft
            break;
        case Chest: printf("chest !");//TODO chest
            break;
        case Nothing: return;
    }
}

void displayNpcMenu(char* message) {
    int nbOptions = 4;
    char* options[4];
    options[Fix] = "Réparer tes armes et tes outils";
    options[Craft] = "Crafter des objets";
    options[Chest] = "Accéder au coffre";
    options[Nothing] = "Partir";
    displayMenu("NPC", message, nbOptions, options);
}

NpcMenuChoice getNpcMenuChoice() {
    char choice;
    scanf("%hhd", &choice);
    switch (choice) {
        case Fix: return Fix;
        case Craft: return Craft;
        case Chest: return Chest;
        case Nothing: return Nothing;
        default: return Nothing;
    }
}

bool storeItemsInChest(Bag* bag, ItemId itemId, int16_t quantityToStore) {
    int quantityRemovedFromBag = removeItemsFromBag(bag, itemId, quantityToStore);
    if(addItemsInChest(itemId, quantityRemovedFromBag)) {
        return true;
    } else {
        //addItemInBag(bag, itemId, quantityRemovedFromBag);
        return false;
    }
}

bool unstoreItemsFromChest(Bag* bag, ItemId itemId, int16_t quantityToRecover) {
    int removedFromChest = removeItemsFromChess(itemId, quantityToRecover);
    int addedInBag = 0; //addItemInBag(bag, );
    if(addedInBag == removedFromChest) {
        return true;
    } else {
        addItemsInChest(itemId, removedFromChest);
        return false;
    }
}