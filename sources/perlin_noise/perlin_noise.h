//
// Created by Théo Omnès on 14/11/2021.
//

#ifndef MALLOCWORLD_PERLIN_NOISE_H
#define MALLOCWORLD_PERLIN_NOISE_H

double perlin(double x, double y, double freq, int octave);
double noise2d(double x, double y);
double smooth_inter(double x, double y, double s);
double lin_inter(double x, double y, double s);
int noise2(int x, int y);
void setSeed(int seed);
int getSeed();
void setSeedFromString(char* seed);

#endif //MALLOCWORLD_PERLIN_NOISE_H
