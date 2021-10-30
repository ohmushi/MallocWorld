//
// Created by Théo Omnès on 29/10/2021.
//

#include "craft_resource.h"

Item newResource(ItemId id) {
    return newStructItem(id, "", true, 0, NULL, CraftResourceType);
}
