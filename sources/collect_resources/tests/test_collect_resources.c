//
// Created by Théo Omnès on 27/10/2021.
//

#include "test_collect_resources.h"

Map* MAP;
Character* PLAYER;

void testCollectResources() {
    printf("\n=== Test Collect Resources ===\n");
    //Rock
    testCollectRockZoneOne();
    testCollectRockZoneTwo();
    testCollectRockZoneThree();
    testCollectRockZoneTwoWithWoodPickaxe();

    //Wood
    testCollectWoodZoneOne();
    testCollectWoodZoneTwo();
    testCollectWoodZoneThree();
    testCollectWoodZoneThreeWithStoneAxe();

    //Plant
    testCollectPlantZoneOne();
    testCollectPlantZoneTwo();
    testCollectPlantZoneThree();
    testCollectPlantZoneOneWithIronBillhook();

    testCollectGround();
}
/*
 * 0   0   0
 * 0   1   0
 * 0   0   0
 */
void setUpCollectResources() {
    Zone** zones = malloc(sizeof(Zone*));
    zones[0] = newZone(1, 3, 3, Ground, 0);
    MAP = newMap(1, zones);
    PLAYER = newCharacter(100, 1,  10, newLocation(1,1,1), newBag(5, 10));
}

void afterCollectResources() {
    freeMap(MAP);
    freeCharacter(PLAYER);
}


// ROCK

/*
 * .   .   .
 * .   P   rockZ1
 * .   .   .
 */
void testCollectRockZoneOne() {
    printf("Test Collect RockZoneOne");
    setUpCollectResources();
    Item woodPickaxe = newTool(WoodPickaxe, "Pioche en bois");
    PLAYER->bag->slots[0]->item = woodPickaxe;
    setZoneValueAtPosition(MAP->zones[0], 2, 1, RockZoneOne);
    int p = 0;

    collectResource(PLAYER, MAP, Right);

    p += assertEqualsInt(Stone, PLAYER->bag->slots[1]->item.id);
    p += assertBetweenInt(1, 4, PLAYER->bag->slots[1]->quantity);
    p += assertEqualsInt(9, PLAYER->bag->slots[0]->item.durability); // woodPickaxe
    p += assertEqualsInt(Ground, getZoneValueAtPosition(*(MAP->zones[0]), 2, 1));

    printResultTest(p, 4);
    afterCollectResources();
}

void testCollectRockZoneTwo() {
    printf("Test Collect RockZoneTwo");
    setUpCollectResources();
    Item stonePickaxe = newTool(StonePickaxe, "Pioche en pierre");
    PLAYER->bag->slots[0]->item = stonePickaxe;
    setZoneValueAtPosition(MAP->zones[0], 2, 1, RockZoneTwo);
    int p = 0;

    collectResource(PLAYER, MAP, Right);

    p += assertEqualsInt(Iron, PLAYER->bag->slots[1]->item.id);
    p += assertBetweenInt(1, 4, PLAYER->bag->slots[1]->quantity);
    p += assertEqualsInt(8, PLAYER->bag->slots[0]->item.durability); // stonePickaxe
    p += assertEqualsInt(Ground, getZoneValueAtPosition(*(MAP->zones[0]), 2, 1));

    printResultTest(p, 4);
    afterCollectResources();
}

void testCollectRockZoneThree() {
    printf("Test Collect RockZoneThree");
    setUpCollectResources();
    Item ironPickaxe = newTool(IronPickaxe, "Pioche en fer");
    PLAYER->bag->slots[0]->item = ironPickaxe;
    setZoneValueAtPosition(MAP->zones[0], 2, 1, RockZoneThree);
    int p = 0;

    collectResource(PLAYER, MAP, Right);

    p += assertEqualsInt(Diamond, PLAYER->bag->slots[1]->item.id);
    p += assertBetweenInt(1, 4, PLAYER->bag->slots[1]->quantity);
    p += assertEqualsInt(6, PLAYER->bag->slots[0]->item.durability); // ironPickaxe
    p += assertEqualsInt(Ground, getZoneValueAtPosition(*(MAP->zones[0]), 2, 1));

    printResultTest(p, 4);
    afterCollectResources();
}

/**
 * Player should fail to collect a RockZoneTwo with a WoodPickaxe
 */
void testCollectRockZoneTwoWithWoodPickaxe() {
    printf("Test Collect RockZoneTwo with WoodPickaxe");
    setUpCollectResources();
    Item woodPickaxe = newTool(WoodPickaxe, "Pioche en bois");
    PLAYER->bag->slots[0]->item = woodPickaxe;
    setZoneValueAtPosition(MAP->zones[0], 2, 1, RockZoneTwo);
    int p = 0;

    collectResource(PLAYER, MAP, Right);

    p += assertEqualsInt(Empty, PLAYER->bag->slots[1]->item.id);
    p += assertEqualsInt(0, PLAYER->bag->slots[1]->quantity);
    p += assertEqualsInt(10, PLAYER->bag->slots[0]->item.durability);
    p += assertEqualsInt(RockZoneTwo, getZoneValueAtPosition(*(MAP->zones[0]), 2, 1));

    printResultTest(p, 4);
    afterCollectResources();
}

// WOOD
void testCollectWoodZoneOne() {
    printf("Test Collect WoodZoneOne");
    setUpCollectResources();
    Item woodAxe = newTool(WoodAxe, "Hache en bois");
    PLAYER->bag->slots[0]->item = woodAxe;
    setZoneValueAtPosition(MAP->zones[0], 2, 1, WoodZoneOne);
    int p = 0;

    collectResource(PLAYER, MAP, Right);

    p += assertEqualsInt(FirTree, PLAYER->bag->slots[1]->item.id);
    p += assertBetweenInt(1, 4, PLAYER->bag->slots[1]->quantity);
    p += assertEqualsInt(9, PLAYER->bag->slots[0]->item.durability); // woodAxe
    p += assertEqualsInt(Ground, getZoneValueAtPosition(*(MAP->zones[0]), 2, 1));

    printResultTest(p, 4);
    afterCollectResources();
}


void testCollectWoodZoneTwo() {
    printf("Test Collect WoodZoneTwo");
    setUpCollectResources();
    Item stoneAxe = newTool(StoneAxe, "Hache en pierre");
    PLAYER->bag->slots[0]->item = stoneAxe;
    setZoneValueAtPosition(MAP->zones[0], 2, 1, WoodZoneTwo);
    int p = 0;

    collectResource(PLAYER, MAP, Right);

    p += assertEqualsInt(BeechTree, PLAYER->bag->slots[1]->item.id);
    p += assertBetweenInt(1, 4, PLAYER->bag->slots[1]->quantity);
    p += assertEqualsInt(8, PLAYER->bag->slots[0]->item.durability); // stoneAxe
    p += assertEqualsInt(Ground, getZoneValueAtPosition(*(MAP->zones[0]), 2, 1));

    printResultTest(p, 4);
    afterCollectResources();
}

void testCollectWoodZoneThree() {
    printf("Test Collect WoodZoneThree");
    setUpCollectResources();
    Item ironAxe = newTool(IronAxe, "Hache en fer");
    PLAYER->bag->slots[0]->item = ironAxe;
    setZoneValueAtPosition(MAP->zones[0], 2, 1, WoodZoneThree);
    int p = 0;

    collectResource(PLAYER, MAP, Right);

    p += assertEqualsInt(OakTree, PLAYER->bag->slots[1]->item.id);
    p += assertBetweenInt(1, 4, PLAYER->bag->slots[1]->quantity);
    p += assertEqualsInt(6, PLAYER->bag->slots[0]->item.durability); // ironAxe
    p += assertEqualsInt(Ground, getZoneValueAtPosition(*(MAP->zones[0]), 2, 1));

    printResultTest(p, 4);
    afterCollectResources();
}

void testCollectWoodZoneThreeWithStoneAxe() {
    printf("Test Collect WoodZoneThree With StoneAxe");
    setUpCollectResources();
    Item stoneAxe = newTool(StoneAxe, "Hache en pierre");
    PLAYER->bag->slots[0]->item = stoneAxe;
    setZoneValueAtPosition(MAP->zones[0], 2, 1, WoodZoneThree);
    int p = 0;

    collectResource(PLAYER, MAP, Right);

    p += assertEqualsInt(Empty, PLAYER->bag->slots[1]->item.id);
    p += assertEqualsInt(0, PLAYER->bag->slots[1]->quantity);
    p += assertEqualsInt(10, PLAYER->bag->slots[0]->item.durability);
    p += assertEqualsInt(WoodZoneThree, getZoneValueAtPosition(*(MAP->zones[0]), 2, 1));

    printResultTest(p, 4);
    afterCollectResources();
}


// PLANT
void testCollectPlantZoneOne() {
    printf("Test Collect PlantZoneOne");
    setUpCollectResources();
    Item woodBillhook = newTool(WoodBillhook, "Serpe en bois");
    PLAYER->bag->slots[0]->item = woodBillhook;
    setZoneValueAtPosition(MAP->zones[0], 2, 1, PlantZoneOne);
    int p = 0;

    collectResource(PLAYER, MAP, Right);

    p += assertEqualsInt(Grass, PLAYER->bag->slots[1]->item.id);
    p += assertBetweenInt(1, 4, PLAYER->bag->slots[1]->quantity);
    p += assertEqualsInt(9, PLAYER->bag->slots[0]->item.durability); // WoodBillhook
    p += assertEqualsInt(Ground, getZoneValueAtPosition(*(MAP->zones[0]), 2, 1));

    printResultTest(p, 4);
    afterCollectResources();
}

void testCollectPlantZoneTwo() {
    printf("Test Collect PlantZoneTwo");
    setUpCollectResources();
    Item stoneBillhook = newTool(StoneBillhook, "Serpe en pierre");
    PLAYER->bag->slots[0]->item = stoneBillhook;
    setZoneValueAtPosition(MAP->zones[0], 2, 1, PlantZoneTwo);
    int p = 0;

    collectResource(PLAYER, MAP, Right);

    p += assertEqualsInt(Lavender, PLAYER->bag->slots[1]->item.id);
    p += assertBetweenInt(1, 4, PLAYER->bag->slots[1]->quantity);
    p += assertEqualsInt(8, PLAYER->bag->slots[0]->item.durability);
    p += assertEqualsInt(Ground, getZoneValueAtPosition(*(MAP->zones[0]), 2, 1));

    printResultTest(p, 4);
    afterCollectResources();
}

void testCollectPlantZoneThree() {
    printf("Test Collect PlantZoneThree");
    setUpCollectResources();
    Item ironBillhook = newTool(IronBillhook, "Serpe en fer");
    PLAYER->bag->slots[0]->item = ironBillhook;
    setZoneValueAtPosition(MAP->zones[0], 2, 1, PlantZoneThree);
    int p = 0;

    collectResource(PLAYER, MAP, Right);

    p += assertEqualsInt( Hemp, PLAYER->bag->slots[1]->item.id);
    p += assertBetweenInt(1, 4, PLAYER->bag->slots[1]->quantity);
    p += assertEqualsInt(6, PLAYER->bag->slots[0]->item.durability);
    p += assertEqualsInt(Ground, getZoneValueAtPosition(*(MAP->zones[0]), 2, 1));

    printResultTest(p, 4);
    afterCollectResources();
}

void testCollectPlantZoneOneWithIronBillhook() {
    printf("Test Collect PlantZoneOne With IronBillhook");
    setUpCollectResources();
    Item ironBillhook = newTool(WoodBillhook, "Serpe en fer");
    PLAYER->bag->slots[0]->item = ironBillhook;
    setZoneValueAtPosition(MAP->zones[0], 2, 1, PlantZoneOne);
    int p = 0;

    collectResource(PLAYER, MAP, Right);

    p += assertEqualsInt(Grass, PLAYER->bag->slots[1]->item.id);
    p += assertBetweenInt(1, 4, PLAYER->bag->slots[1]->quantity);
    p += assertEqualsInt(9, PLAYER->bag->slots[0]->item.durability); // WoodBillhook
    p += assertEqualsInt(Ground, getZoneValueAtPosition(*(MAP->zones[0]), 2, 1));

    printResultTest(p, 4);
    afterCollectResources();
}

/*
 * 0   0   0
 * 0   1   0
 * 0   0   0
 */
void testCollectGround() {
    printf("Test Collect Ground");
    setUpCollectResources();
    Item ironBillhook = newTool(WoodBillhook, "Serpe en fer");
    PLAYER->bag->slots[0]->item = ironBillhook;
    int p = 0;

    collectResource(PLAYER, MAP, Right);

    p += assertEqualsInt(Ground, PLAYER->bag->slots[1]->item.id);
    p += assertEqualsInt(0, PLAYER->bag->slots[1]->quantity);
    p += assertEqualsInt(10, PLAYER->bag->slots[0]->item.durability); // WoodBillhook
    p += assertEqualsInt(Ground, getZoneValueAtPosition(*(MAP->zones[0]), 2, 1));

    printResultTest(p, 4);
    afterCollectResources();
}
