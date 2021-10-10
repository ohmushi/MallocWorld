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
    printf("\nNew Character");
    int pass = 0;
    int total = 3;

    Character* c = newCharacter(0, 1, 100);

    pass += assertEqualsInt(0, c->experience);
    pass += assertEqualsInt(1, c->level);
    pass += assertEqualsInt(1000, c->healthPoints);
    if(pass == total){
        printf(": OK (%d/%d)\n", pass, total);
    }
    else{
        printf("\nFAIL (%d/%d)\n", pass, total );
    }
}
