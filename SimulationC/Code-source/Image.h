#ifndef IMAGE_H
#define IMAGE_H
#include "Init.h"

typedef struct {
    int color[3];
    int enrg;
} Pixel;

void CreateImage(FILE* f, World* w, Beauce* b, int** cell, List_Animal** tabFam, int nbFam, Pixel*** tabPix,int b_e);

void CreateName(int k, char* nameF);

Pixel* InitPixel(void);

Pixel*** InitTabPix(World* w);

void GenerateColors(List_Animal** tabFam, int nbFam);

void ColorPixels(List_Animal** tabFam, int nbFam, Pixel*** tabPix);

void freePixels(Pixel*** tabPix,World* w);

#endif
