//
// Created by Théo Omnès on 14/11/2021.
//

#ifndef MALLOCWORLD_PERLIN_NOISE_H
#define MALLOCWORLD_PERLIN_NOISE_H

float perlin(float x, float y, float freq, int octave);
float noise2d(float x, float y);
float smooth_inter(float x, float y, float s);
float lin_inter(float x, float y, float s);
int noise2(int x, int y);
void setSeed(int seed);
int getSeed();
void setSeedFromString(char* seed);

#endif //MALLOCWORLD_PERLIN_NOISE_H
