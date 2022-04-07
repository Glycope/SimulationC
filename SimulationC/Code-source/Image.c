#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Image.h"

void CreateImage(FILE* f, World* w, Beauce* b, int** cell, List_Animal** tabFam, int nbFam, Pixel*** tabPix, int b_e) {
    ColorPixels(tabFam, nbFam, tabPix);
    fprintf(f, "P3 \n%d %d \n255 \n", w->w, w->h);
    int i, j, k;
    for (i = 0; i < w->h; i++) {
        for (j = 0; j < w->w; j++) {
            if (tabPix[i][j]->enrg > 0) {
                for (k = 0; k < 3; k++) {
                    fprintf(f, "%d ", tabPix[i][j]->color[k]);
                }
                fprintf(f, "\n");
            }
            else if (cell[i][j] > 0)
                fprintf(f, "127 127 127 \n");
            else if ((b_e) && (((b->y + b->h < w->h) && (i >= b->y && i <= (b->y + b->h - 1)))
                    ||
                    ((b->y + b->h >= w->h) && (i >= b->y || i <= (b->y + b->h - 1) % w->h)))
                    &&
                    (((b->x + b->w < w->w) && (j >= b->x && j <= (b->x + b->w - 1)))
                    ||
                    ((b->x + b->w >= w->w) && (j >= b->x || j <= (b->x + b->w - 1) % w->w))))
                fprintf(f, "255 255 255 \n");
            else
                fprintf(f, "0 0 0 \n");
        }
    }
    freePixels(tabPix, w);
}

void CreateName(int k, char* nameF) {
    strcat(nameF, "sortie");
    char tmp[5];
    if (k < 10) sprintf(tmp, "000%d", k);
    else if (k < 100) sprintf(tmp, "00%d", k);
    else if (k < 1000) sprintf(tmp, "0%d", k);
    else sprintf(tmp, "%d", k);
    strcat(nameF, tmp);
    strcat(nameF, ".ppm");
}

Pixel* InitPixel(void) {
    Pixel* pix = malloc(sizeof(Pixel));
    if (pix == NULL) ErrorAlloc();
    pix->enrg = 0;
    return pix;
}

Pixel*** InitTabPix(World* w) {
    int i, j;
    Pixel*** tabPix = calloc(w->h, sizeof(Pixel**));
    if (tabPix == NULL) ErrorAlloc();
    for (i = 0; i < w->h; i++) {
        tabPix[i] = calloc(w->w, sizeof(Pixel*));
        if (tabPix[i]==NULL) ErrorAlloc();
    }
    for (i = 0; i < w->h; i++) {
        for (j = 0; j < w->w; j++) {
            tabPix[i][j] = InitPixel();
        }
    }
    return tabPix;
}

void GenerateColors(List_Animal** tabFam, int nbFam) {
    int i;
    for (i = 0; i < nbFam; i++) {
        int fixedcolor1 = rand() % 3;
        tabFam[i]->color[fixedcolor1] = 255;
        int fixedcolor2 = rand() % 2;
        if (fixedcolor1 == 0) fixedcolor2 += 1;
        else if (fixedcolor1 == 1) fixedcolor2 *= 2;
        tabFam[i]->color[fixedcolor2] = 0;
        tabFam[i]->color[3 - (fixedcolor1 + fixedcolor2)] = rand() % 256;
    }
}

void ColorPixels(List_Animal** tabFam, int nbFam, Pixel*** tabPix) {
    int i, j;
    for (i = 0; i < nbFam; i++) {
        Animal* a = tabFam[i]->head;
        while (a != NULL) {
            if (a->enrg > tabPix[a->y][a->x]->enrg) {
                tabPix[a->y][a->x]->enrg = a->enrg;
                for (j = 0; j < 3; j++) {
                    tabPix[a->y][a->x]->color[j] = tabFam[i]->color[j];
                }
            }
            a = a->next;
        }
    }
}

void freePixels(Pixel*** tabPix, World* w) {
    int i, j;
    for (i = 0; i < w->h; i++) {
        for (j = 0; j < w->w; j++) {
            free(tabPix[i][j]);
        }
        free(tabPix[i]);
    }
    free(tabPix);
}
