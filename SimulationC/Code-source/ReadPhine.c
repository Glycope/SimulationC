#include <stdio.h>
#include <stdlib.h>
#include "ReadPhine.h"

int ReadPhine(FILE* f, World* w, Beauce* b, List_Animal* l) {
    int test = fscanf(f,"\nMonde %d %d \nBeauce %d %d %d %d \nEnergie Nourriture %d \nSeuil Reproduction %d \n\n\n",&(w->h),&(w->w),&(b->x),&(b->y),&(b->h),&(b->w),&(w->food),&(w->repro));
    if (test != 8 || (w->h < 1 || w->w < 1) || (b->x < 0 || b->y < 0 || b->h < 0 || b->w < 0) || w->food < 1 || w->repro < 2) { /* Verifie que les 8 premieres variables sont bien extraites */
        printf("Incorrect format\n");
        exit(0);
    }
    b->w = min(b->w, w->w);
    b->h = min(b->h, w->h);
    b->x = b->x % w->w;
    b->y = b->y % w->h;

    int nbFam = 0;
    int ch = fgetc(f); // Recuperer le caractere "(" pour voir s'il y'a un animal

    do
    {
        Animal* a = InitAnimal();
        test = fscanf(f,"%d %d) %d %d | ",&(a->x),&(a->y),&(a->dir),&(a->enrg));
        if (test != 4 || (a->dir < 0 || a->dir > 7) || (a->x < 0 || a->y < 0) || a->enrg < 1) { /* Verifie que les 4 premieres variables sont bien extraites pour chaque animal */
            printf("Incorrect format\n");
            exit(0);
        }
        int i;
        for (i = 0; i < N; i++ ) {
            test = fscanf(f,"%d ",&(a->chr[i])); /* Verifie que les genes sont bien extraits */
            if (test != 1 || a->chr[i] < 1) {
                printf("Incorrect format\n");
                exit(0);
            }
        }
        fscanf(f,"| \n");
        a->fam = nbFam;
        nbFam++;
        AddAnimal(l, a);
        ch = fgetc(f);
    }
        while (test != EOF && ch == '(');

    return nbFam;
}

void PrintPhine(FILE* f, List_Animal* l, List_Animal** tabFam, int nbFam, World* w, Beauce* b) {
    int i, j;
    fprintf(f, "\nMonde %d %d \nBeauce %d %d %d %d \nEnergie Nourriture %d \nSeuil Reproduction %d \n\n\n", w->h, w->w, b->x, b->y, b->h, b->w, w->food, w->repro);
    Animal* a = l->head;
    while (a != NULL) {
        fprintf(f, "(%d %d) %d %d | ", a->x, a->y, a->dir, a->enrg);
        for (i = 0; i < N; i++) {
            fprintf(f, "%d ", a->chr[i]);
        }
        fprintf(f, "| \n");
        a = a->next;
    }
    fprintf(f, "\n\n");
    for (i = 0; i < nbFam; i++) {
        a = tabFam[i]->head;
        fprintf(f, "Famille numero %d :\n", i);
        while (a != NULL) {
            fprintf(f, "(%d %d) %d %d | ", a->x, a->y, a->dir, a->enrg);
            for (j = 0; j < N; j++) {
                fprintf(f, "%d ", a->chr[j]);
            }
            fprintf(f, "| \n");
            a = a->next;
        }
        fprintf(f, "\n");
    }
}
