//
// Created by Théo Omnès on 29/10/2021.
//

#include "craft_resource.h"

const CraftResource RESOURCES[NUMBER_OF_RESOURCES] = {
        {FirTree, 20},
        {Stone, 20},
        {Grass, 20},
        {BeechTree, 20},
        {Iron, 20},
        {Lavender, 20},
        {OakTree, 20},
        {Diamond, 20},
        {Hemp, 20},
};

Item newResource(ItemId id) {
    return newStructItem(id, "", true, 0, NULL, CraftResourceType);
}
