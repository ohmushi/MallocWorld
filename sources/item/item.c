//
// Filename: bag.c
//
// Made by Théo Omnès on 24 oct. 2021.
//
// Description:
//

#include "item.h"

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

Item* newItem(ItemId id, char* name, bool isStackable, int16_t durability, void* object, ItemType type) {
    Item* item = malloc(sizeof(Item));
    *item = newStructItem(id, name, isStackable, durability, object, type);
    return item;
}

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


void printItem(Item item) {
    printf("{%d} - %s", item.id, item.name);
}

void freeItem(Item* item) {
    if(NULL == item) {
        return;
    }
    // TODO free object
    free(item);
}

Item newEmptyItem() {
    return newStructItem(Empty, "Empty", false, 0, NULL, ToolType);
}