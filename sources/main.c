//
// Filename: main.c
//
// Made by Théo Omnès on 09 oct. 2021.
//
// Description:
//

#include "main.h"

int main(int argc, char* argv[]) {
    srand((unsigned int) time(NULL));
    callTests(true);
    mallocworld();
    return 0;
}



void callTests(bool lunchWithTests) {
    if(!lunchWithTests){
        return;
    }
    testBag();
    testPlayer();
    testChest();
    testCollectResources();
    testCraft();
    testItem();
    testMovement();
    testNpc();
    testTurnBased();
    testMonster();
    testResourcesReappearance();
}