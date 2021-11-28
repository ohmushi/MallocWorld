//
// Created by Théo Omnès on 29/10/2021.
//

#ifndef MALLOCWORLD_CRAFT_RESOURCE_H
#define MALLOCWORLD_CRAFT_RESOURCE_H

#include <stdlib.h>
#include "../item.h"
#include <stdint.h>

#define NUMBER_OF_RESOURCES 9

typedef struct CraftResource {
    ItemId id;
    const char* name;
    int8_t maxStackHeight;
} CraftResource;


Item newResource(ItemId id);
CraftResource findCraftResourceByItemId(ItemId id);
Item getCraftResourceItemById(ItemId id);

#endif //MALLOCWORLD_CRAFT_RESOURCE_H
