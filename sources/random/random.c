//
// Created by Théo Omnès on 03/11/2021.
//

#include "random.h"


/**
 * @return an int in the given range [lower,upper]
 */
int randomIntInRange(int lowerBound, int upperBound) {
    return rand() % (upperBound - lowerBound + 1) + lowerBound;
}