//
// Created by Théo Omnès on 09 oct. 2021.
//

#include "test_player.h"

Player* PLAYER;


void testPlayer(){
    printf("\n== Test Player ==\n");

    testNewCharacter();
    testPlayerLevelUp();
    testPlayerGainExperiencePoints();
    testGetIndexInRange();
}

void setUpCharacter(char* testName) {
    printf("%s", testName);
    PLAYER = newPlayer(0, 1, 100, newLocation(1, 1, 1), newBag(5, 10));
}

void afterCharacter() {
    freePlayer(PLAYER);
}

void testNewCharacter(){
    setUpCharacter("Test New Player");
    int pass = 0;
    int total = 3;
    Location* characterLocation = newLocation(0,0,1);
    Player * c = newPlayer(0, 1, 100, characterLocation, newBag(10, 20));

    pass += assertEqualsInt(0, c->experience);
    pass += assertEqualsInt(1, c->level);
    pass += assertEqualsInt(100, c->healthPoints);

    printResultTest(pass, total);
    afterCharacter();
}

void testPlayerLevelUp() {
    setUpCharacter("Test Player Level Up");
    PLAYER->level = 1;
    PLAYER->healthPoints = 100;
    int p = 0;

    p += assertEqualsInt(2, playerLevelUp(PLAYER));
    p += assertEqualsInt(110, PLAYER->healthPoints);
    p += assertEqualsInt(3, playerLevelUp(PLAYER));
    p += assertEqualsInt(4, playerLevelUp(PLAYER));
    p += assertEqualsInt(5, playerLevelUp(PLAYER));
    p += assertEqualsInt(200, PLAYER->healthPoints);
    p += assertEqualsInt(6, playerLevelUp(PLAYER));
    p += assertEqualsInt(250, PLAYER->healthPoints);
    p += assertEqualsInt(7, playerLevelUp(PLAYER));
    p += assertEqualsInt(8, playerLevelUp(PLAYER));
    p += assertEqualsInt(350, PLAYER->healthPoints);
    p += assertEqualsInt(9, playerLevelUp(PLAYER));
    p += assertEqualsInt(10, playerLevelUp(PLAYER));
    p += assertEqualsInt(500, PLAYER->healthPoints);

    printResultTest(p, 14);
    afterCharacter();
}

void testPlayerGainExperiencePoints() {
    setUpCharacter("Test Player Gain Experience Points");
    PLAYER->level = 1;
    int p = 0;

    p += assertEqualsInt(15, playerGainExperiencePoints(PLAYER, 15));
    p += assertEqualsInt(15, playerGainExperiencePoints(PLAYER, 15));
    p += assertEqualsInt(2, PLAYER->level);
    p += assertEqualsInt(10, PLAYER->experience);

    printResultTest(p , 4);
    afterCharacter();
}

void testGetIndexInRange() {
    setUpCharacter("Test Get Index In Range");
    int p = 0;

    p += assertEqualsInt(1, getIndexInRange(1, 5));
    p += assertEqualsInt(0, getIndexInRange(5, 5));
    p += assertEqualsInt(1, getIndexInRange(7, 3));
    p += assertEqualsInt(2, getIndexInRange(-7, 3));
    p += assertEqualsInt(0, getIndexInRange(-6, 3));

    printResultTest(p , 5);
    afterCharacter();
}