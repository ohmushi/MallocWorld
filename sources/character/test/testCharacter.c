//
// Created by Théo Omnès on 09 oct. 2021.
//

#include "testCharacter.h"
#include "../character.h"

void testNewCharacter();


void testCharacter(){
    testNewCharacter();
}

void testNewCharacter(){
    //setUp()
    printf("\nNew Character");
    int pass = 0;
    int total = 3;
    Location* characterLocation = newLocation(0,0,1);
    Character* c = newCharacter(0, 1, 100, characterLocation, newBag(10, 20));

    pass += assertEqualsInt(0, c->experience);
    pass += assertEqualsInt(1, c->level);
    pass += assertEqualsInt(1000, c->healthPoints);
    printResultTest(pass, total);

    //after ->free character
}
