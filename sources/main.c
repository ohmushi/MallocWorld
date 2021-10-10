//
// Filename: main.c
//
// Made by Théo Omnès on 09 oct. 2021.
//
// Description:
//

#include <stdio.h>
#include "main.h"

int main(int argc, char* argv[]) {
    FILE* config = getConfigFile();
    if(config != NULL) {
        printf("ok");
    }
    else {
        printf("ko");
    }

    return 0;
}
