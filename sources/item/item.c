//
// Filename: bag.c
//
// Made by Théo Omnès on 24 oct. 2021.
//
// Description:
//

#include "item.h"

/**
 * The list of all the items in game
 */
const Item ITEMS[NUMBER_OF_ITEMS] = {
        {WoodSword, "Épée en bois", 10, 10, WeaponType, false, NULL},
        {WoodPickaxe, "Pioche en bois", 10, 10, ToolType, false, NULL},
        {WoodBillhook, "Serpe en bois", 10, 10, ToolType, false, NULL},
        {WoodAxe, "Hache en bois", 10, 10, ToolType, false, NULL},
        {FirTree, "Sapin", 0, 0, CraftResourceType, true, NULL},
        {Stone, "Pierre", 0, 0, CraftResourceType, true, NULL},
        {Grass, "Herbe", 0, 0, CraftResourceType, true, NULL},
        {StoneSword, "Épée en pierre", 10, 10, WeaponType, false, NULL},
        {StoneSpear, "Lance en pierre", 8, 8, WeaponType, false, NULL},
        {StoneHammer, "Marteau en pierre", 5, 5, WeaponType, false, NULL},
        {StoneChestplate, "Plastron en pierre", 0, 0, ArmorType, false, NULL},
        {StonePickaxe, "Pioche en pierre", 10, 10, ToolType, false, NULL},
        {StoneBillhook, "Serpe en pierre", 10, 10, ToolType, false, NULL},
        {StoneAxe, "Hache en pierre", 10, 10, ToolType, false, NULL},
        {HealingPotionOne, "Potion de vie 1", 0, 0, HealType, false, NULL},
        {BeechTree, "Hêtre", 0, 0, CraftResourceType, true, NULL},
        {Iron, "Fer", 0, 0, CraftResourceType, true, NULL},
        {Lavender, "Lavande", 0, 0, CraftResourceType, true, NULL},
        {IronSword, "Épée en fer", 10, 10, WeaponType, false, NULL},
        {IronSpear, "Lance en fer", 8, 8, WeaponType, false, NULL},
        {IronHammer, "Marteau en fer", 5, 5, WeaponType, false, NULL},
        {IronChestplate, "Plastron en fer", 0, 0, ArmorType, false, NULL},
        {IronPickaxe, "Pioche en fer", 10, 10, ToolType, false, NULL},
        {IronBillhook, "Serpe en fer", 10, 10, ToolType, false, NULL},
        {IronAxe, "Hache en fer", 10, 10, ToolType, false, NULL},
        {HealingPotionTwo, "Potion de vie 2", 0, 0, HealType, false, NULL},
        {OakTree, "Chene", 0, 0, CraftResourceType, true, NULL},
        {Diamond, "Diamant", 0, 0, CraftResourceType, true, NULL},
        {Hemp, "Chanvre", 0, 0, CraftResourceType, true, NULL},
        {DiamondSword, "Épée en diamant", 10, 10, WeaponType, false, NULL},
        {DiamondSpear, "Lance en diamant", 8, 8, WeaponType, false, NULL},
        {DiamondHammer, "Marteau en diamant", 5, 5, WeaponType, false, NULL},
        {DiamondChestplate, "Plastron en diamant", 0, 0, ArmorType, false, NULL},
        {HealingPotionThree, "Potion de vie 3", 0, 0, HealType, false, NULL},
};

/**
 * allocate a struct Item
 * @return
 */
Item* newItem(ItemId id, char* name, bool isStackable, int16_t durability, void* object, ItemType type) {
    Item* item = malloc(sizeof(Item));
    *item = newStructItem(id, name, isStackable, durability, object, type);
    return item;
}

/**
 * Create a struct Item with the parameters
 * @return the Item created
 */
Item newStructItem(ItemId id, char* name, bool isStackable, int16_t durability, void* object, ItemType type) {
    Item item;
    item.name = malloc(sizeof(char) * strlen(name));
    strcpy(item.name, name);
    item.id = id;
    item.isStackable = isStackable;
    item.object = object;
    item.durability = durability;
    item.maxDurability = durability;
    item.type = type;
    return item;
}

/**
 * Display on stdout the item like {id} - name
 */
void printItem(Item item) {
    printf("\n{%d} - %s", item.id, item.name);
}

/**
 * free the item
 * @param item
 */
void freeItem(Item* item) {
    if(NULL == item) {
        return;
    }
    if(item->object != NULL) {
        free(item->object);
    }
    free(item);
}

/**
 * @return a struct Item with id Empty
 */
Item newEmptyItem() {
    return newStructItem(Empty, "Empty", false, 0, NULL, ToolType);
}

/**
 * Fetch the list of items in game ang get the one with the searched ItemId
 * @param itemId searched
 * @return the found Item or an empty Item
 */
Item findItemById(ItemId itemId) {
    for(int i = 0; i < NUMBER_OF_ITEMS; i += 1) {
        if(ITEMS[i].id == itemId) {
            return ITEMS[i];
        }
    }
    return newEmptyItem(); //not found
}

ItemList newItemList(int maxSize) {
    ItemList list;
    list.maxSize = maxSize;
    list.size = malloc(sizeof(int));
    *(list.size) = 0;
    list.list = maxSize > 0 ? malloc(sizeof(Item) * maxSize) : NULL;
    return list;
}

void freeItemList(ItemList itemList) {
    free(itemList.list);
}

void appendItemInItemList(Item item, ItemList list) {
    if(*(list.size) >= list.maxSize) {
        return;
    }
    int size = *(list.size);
    list.list[size] = item;
    *(list.size) += 1;
}

int getItemListSize(ItemList list) {
    return *(list.size);
}

bool isEmptyItem(Item item) {
    return item.id == Empty;
}

bool itemsAreEquals(Item first, Item second) {
    bool id = first.id == second.id;
    bool type = first.type == second.type;
    bool durability = first.durability == second.durability;
    bool maxDurability = first.maxDurability == second.maxDurability;
    return id && type && durability && maxDurability;
}