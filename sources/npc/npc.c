//
// Created by Théo Omnès on 21/10/2021.
//

#include "npc.h"


/**
 * display the menu of a NPC actions.
 * Get the player choice and call the functions.
 * 3 choices : fix items, craft items or access to the chest (store or take)
 */
void talkToNPC(Player* player) {
    NpcMenuChoice choice;
    do {
        displayNpcMenu("Que souhaites tu faire ?");
        choice = getNpcMenuChoice();
        switch (choice) {
            case Fix: fixWeaponsAndToolsInBag(player->bag);
                break;
            case Craft: onSelectCraft(player);
                break;
            case ChestAccess: printf("chest !");//TODO chest
                break;
            case Leave: return;
            default: return;
        }
    } while (choice != Leave);
}

void onSelectCraft(Player* player) {
    printf("\nEntrez l'ID de l'item à crafter: ");
    ItemId id;
    fflush(stdin);
    scanf("%d", &id);
    CraftRecipe recipe = findCraftRecipeByItemIdToCraft(id);
    if(recipe.itemId == Empty) {
        displayItemCanNotBeCrafted();
        return;
    }
    if(!isBagContainsCraftIngredients(player->bag, recipe)) {
        displayBagDoNotContainsIngredients(recipe);
        return;
    }
    bool craftSucceeded = craft(id, player);
    if(craftSucceeded) {
        displayCraftSucceeded(id);
    } else {
        displayCraftFailed(id);
    }
    fflush(stdin);
    getchar();
}

void displayItemCanNotBeCrafted() {
    printf("\nL'item recherché ne peut pas être crafté");
    fflush(stdin);
    getchar();
}

void displayBagDoNotContainsIngredients(CraftRecipe recipe) {
    Item item = findItemById(recipe.itemId);
    char* msg = malloc(sizeof(char) * FILE_LINE_LENGTH);
    sprintf(msg, "\nTu ne possède pas les ressources pour crafter l'item [%s]", item.name);
    printMessageType(msg, Error);
    printf("\nVoici les ressources nécessaires pour le crafter:");
    printRecipe(recipe);
    fflush(stdin);
    getchar();
}

void displayCraftSucceeded(ItemId crafted) {
    Item item = findItemById(crafted);
    char* msg = malloc(sizeof(char) * FILE_LINE_LENGTH);
    sprintf(msg, "\nL'item %s a bien été crafté", item.name);
    printMessageType(msg, Success);
    fflush(stdin);
    getchar();
    free(msg);
}

void displayCraftFailed(ItemId crafted) {
    Item item = findItemById(crafted);
    char* msg = malloc(sizeof(char) * FILE_LINE_LENGTH);
    sprintf(msg, "\nLe craft de l'item %s a échoué", item.name);
    printMessageType(msg, Error);
    fflush(stdin);
    getchar();
    free(msg);
}

bool isNpcMenuChoice(NpcMenuChoice choice) {
    return Fix <= choice && choice <= Leave;
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
    options[ChestAccess] = "Accéder au coffre";
    options[Leave] = "Partir";
    displayMenu("NPC", message, nbOptions, options);
}

/**
 *  Get the NPC menu choice by stdin and return
 *  a enum NpcMenuChoice
 * @return
 */
NpcMenuChoice getNpcMenuChoice() {
    NpcMenuChoice choice = -1;
    while(!isNpcMenuChoice(choice)) {
        fflush(stdin);
        choice = getchar() - '0';
    }
    return choice;
}

/**
 * First remove from the bag the items to store, then add in chest the quantity removed.
 * check if the quantity added in chest is the same removed from the bag, if not: roll back.
 * @return the quantity stored in chest
 */
int playerStoreItemsInChest(Player* player, Item item, int16_t quantityToStore) {
    int quantityRemovedFromBag = removeItemsFromBag(player->bag, item.id, quantityToStore);
    int quantityAddedInChest = addItemsInChest(item.id, quantityRemovedFromBag, &player->chest);
    if(quantityAddedInChest == quantityRemovedFromBag) {
        return quantityAddedInChest;
    } else {
        // remove what was added in chest, and add what was removed from bag
        removeItemsFromChest(item.id, quantityAddedInChest, &player->chest);
        addItemsInBag(player->bag, item, quantityRemovedFromBag);
        return 0;
    }
}

/**
 * First remove from the chest the items to take, then add in bag the quantity removed.
 * check if the quantity removed from chest is the same added in the bag, if not: roll back.
 * @return the quantity took from chest
 */
int playerTakeItemsFromChest(Player* player, Item item, int16_t quantityToRecover) {
    int removedFromChest = removeItemsFromChest(item.id, quantityToRecover, &player->chest);
    int addedInBag = addItemsInBag(player->bag, item, removedFromChest);
    if(addedInBag == removedFromChest) {
        return addedInBag;
    } else {
        // add what was removed from chest and remove what was added in bag
        addItemsInChest(item.id, removedFromChest, &player->chest);
        removeItemsFromBag(player->bag, item.id, addedInBag);
        return false;
    }
}

/**
 * Loop on each slot of the bag, if the item in it is a tool or a weapon:
 * set the durability at the max durability
 */
void fixWeaponsAndToolsInBag(Bag* bag) {
    printf("\nOK\n");
    if(NULL == bag) {
        return;
    }
    BagSlot* slot = NULL;
    for(int i = 0; i < bag->capacity; i += 1) {
        Item item = bag->slots[i]->item;
        slot = bag->slots[i];
        if(item.type == ToolType || item.type == WeaponType) {
            slot->item.durability = slot->item.maxDurability;
        }
    }
}