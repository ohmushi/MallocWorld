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
    char choice = atoi(getc(stdin));
    switch (choice) {
        case Fix: return Fix;
        case Craft: return Craft;
        case Chest: return Chest;
        case Nothing: return Nothing;
        default: return Nothing;
    }
}

int storeItemsInChest(Bag* bag, Item item, int16_t quantityToStore) {
    int quantityRemovedFromBag = removeItemsFromBag(bag, item.id, quantityToStore);
    int quantityAddedInChest = addItemsInChest(item.id, quantityRemovedFromBag);
    if(quantityAddedInChest == quantityRemovedFromBag) {
        return quantityAddedInChest;
    } else {
        // remove what was added in chest, and add what was removed from bag
        removeItemsFromChest(item.id, quantityAddedInChest);
        addItemsInBag(bag, item, quantityRemovedFromBag);
        return 0;
    }
}

int takeItemsFromChest(Bag* bag, Item item, int16_t quantityToRecover) {
    int removedFromChest = removeItemsFromChest(item.id, quantityToRecover);
    int addedInBag = addItemsInBag(bag, item, removedFromChest);
    if(addedInBag == removedFromChest) {
        return addedInBag;
    } else {
        // add what was removed from chest and remove what was added in bag
        addItemsInChest(item.id, removedFromChest);
        removeItemsFromBag(bag, item.id, addedInBag);
        return false;
    }
}