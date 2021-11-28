//
// Created by Théo Omnès on 29/10/2021.
//

#include "craft_resource.h"

const CraftResource RESOURCES[NUMBER_OF_RESOURCES] = {
        {FirTree, "Sapin", 20},
        {Stone,"Pierre", 20},
        {Grass,"Herbe", 20},
        {BeechTree,"Hetre", 20},
        {Iron,"Fer", 20},
        {Lavender,"Lavande", 20},
        {OakTree,"Chene", 20},
        {Diamond,"Diamand", 20},
        {Hemp,"Chanvre", 20},
};

Item newResource(ItemId id) {
    return newStructItem(id, "", true, 0, NULL, CraftResourceType);
}

CraftResource findCraftResourceByItemId(ItemId id) {
    for(int i = 0; i < NUMBER_OF_RESOURCES; i += 1) {
        if(RESOURCES[i].id == id) {
            return RESOURCES[i];
        }
    }
    //not found
    CraftResource empty = {Empty, "Empty", 0};
    return empty;
}

Item getCraftResourceItemById(ItemId id) {
    CraftResource resource = findCraftResourceByItemId(id);
    return findItemById(resource.id);
}