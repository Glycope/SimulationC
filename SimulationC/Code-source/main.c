#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Init.h"
#include "ReadPhine.h"
#include "Simulation.h"
#include "Traitement.h"
#include "Image.h"

int main(int argc, char* argv[]) {
    int n = 0;
    int c = 0;
    char* input;
    char* output;
    int a;

    if(argc < 5 || argc > 6) {
        usage(argv[0]);
        return 0;
    }

    if(sscanf(argv[1], "%d", &a) != 1 || (a != 1 && a != 0)) {
        printf("Incorrect value for a (%s)\n", argv[1]);
        usage(argv[0]);
        return 0;
    }

    if(sscanf(argv[2], "%d", &n) != 1 || (n < 0)) {
        printf("Incorrect value for n (%s)\n", argv[2]);
        usage(argv[0]);
        return 0;
    }

    input = argv[3];
    output = argv[4];

    if((argc > 5 && sscanf(argv[5], "%d", &c) != 1) || c < 0 || c >= 10000) {
        printf("Incorrect value for c (%s)\n", argv[3]);
        usage(argv[0]);
        return 0;
    }

    if (a) {
        srand(time(NULL));
    }

    FILE* f = fopen(input,"r");
    if (f == NULL) {
        printf("The opening of the file has failed\n");
        return 0;
    }

    World* w = InitWorld();
    Beauce* b = InitBeauce();
    List_Animal* l = InitList();
    int nbFam = ReadPhine(f, w, b, l);
    fclose(f);

    int** cell = InitCell(w);
    int b_e = BeauceExists(b);
    int sim, stop;

    if (c > 0) n--;
    for(sim = 1; sim <= n; sim++) { /* La simulation commence */
        RandomFood(cell, w, b, b_e);
        stop = AfterMoveAnimals(l, w, cell);
        if (sim % 100000 == 0) printf("%d iteration completed\n",sim);
        if (stop) break;
    }
    Pixel*** tabPix;
    List_Animal** tabFam = CreateListFam(l, nbFam);
    GenerateColors(tabFam, nbFam);
    int i;
    for (sim = 1; sim <= c; sim ++) {
        RandomFood(cell, w, b, b_e);
        stop = AfterMoveAnimals(l, w, cell);
        for (i = 0; i < nbFam; i++) {
            FreeAnimals(tabFam[i]);
        }
        FulfillFam(l, tabFam);
        tabPix = InitTabPix(w);
        char* nameF = calloc(15, sizeof(char));
        if (nameF == NULL) ErrorAlloc();
        CreateName(sim, nameF);
        f = fopen(nameF, "w");
        if (f == NULL){
          printf("The opening of the file has failed\n");
          return 0;
        }
        free(nameF);
        CreateImage(f, w, b, cell, tabFam, nbFam, tabPix, b_e);
        fclose(f);
        if ((sim + n) % 100000 == 0) printf("%d iteration completed\n", sim + n);
        if (stop) break;
    }
    List_Animal* sortedL = InitList();
    f = fopen(output, "w");
    if (f == NULL){
      printf("The opening of the file has failed\n");
      return 0;
    }
    if (b_e) {
        CenterB* center = InitCenterB();
        FindCenterB(center, b, w);
        ListSort(center, l, sortedL, w);
        PrintPhine(f, sortedL, tabFam, nbFam, w, b);
        FreeAnimals(sortedL);
        free(sortedL);
        free(center);
    }
    else {
        PrintPhine(f, l, tabFam, nbFam, w, b);
        FreeAnimals(l);
        free(l);
    }
    fclose(f);
    for (i = 0; i < nbFam; i++) {
        FreeAnimals(tabFam[i]);
        free(tabFam[i]);
    }
    free(tabFam);
    FreeCells(cell, w);
    free(b);
    free(w);
    return 0;
}
