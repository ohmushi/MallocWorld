//
// Created by Théo Omnès on 21/10/2021.
//

#include "npc.h"


/**
 * display the menu of a NPC actions.
 * Get the player choice and call the functions.
 * 3 choices : fix items, craft items or access to the chest (store or take)
 */
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

/**
 * Display the options of the NPC menu:
 * 4 choices: Fix items, craft items, access to chest or leave.
 * @param message
 */
void displayNpcMenu(char* message) {
    int nbOptions = 4;
    char* options[4];
    options[Fix] = "Réparer tes armes et tes outils";
    options[Craft] = "Crafter des objets";
    options[Chest] = "Accéder au coffre";
    options[Nothing] = "Partir";
    displayMenu("NPC", message, nbOptions, options);
}

/**
 *  Get the NPC menu choice by stdin and return
 *  a enum NpcMenuChoice
 * @return
 */
NpcMenuChoice getNpcMenuChoice() {
    int choice = getc(stdin) - '0';
    switch (choice) {
        case Fix: return Fix;
        case Craft: return Craft;
        case Chest: return Chest;
        case Nothing: return Nothing;
        default: return Nothing;
    }
}

/**
 * First remove from the bag the items to store, then add in chest the quantity removed.
 * check if the quantity added in chest is the same removed from the bag, if not: roll back.
 * @return the quantity stored in chest
 */
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

/**
 * First remove from the chest the items to take, then add in bag the quantity removed.
 * check if the quantity removed from chest is the same added in the bag, if not: roll back.
 * @return the quantity took from chest
 */
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


void fixWeaponsAndToolsInBag(Bag* bag) {
    BagSlot* slot = NULL;
    for(int i = 0; i < bag->capacity; i += 1) {
        Item item = bag->slots[i]->item;
        if(item.type == ToolType || item.type == WeaponType) {
            slot->item.durability = slot->item.maxDurability;
        }
    }
}