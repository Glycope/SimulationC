#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Simulation.h"

int SumTab(int tab[], int lenTab) { // Somme des elements d'un tableau d'entiers
    int sum = 0;
    int i;
    for (i = 0; i < lenTab; i++) {
        sum += tab[i];
    }
    return sum;
}

int BeauceExists(Beauce* b) { // Renvoie 1 si la beauce existe
    if (b->h == 0 || b->w == 0) {
        return 0;
    }
    return 1;
}

void RandomFood(int** cell, World* w, Beauce* b, int b_e) {
    int i = rand() % (w->h);
    int j = rand() % (w->w);
    cell[i][j]++;
    if (b_e) {
        i = ((rand() % (b->h)) + b->y) % w->h;
          // Choisir un nombre entre b->y et b->y + b->h, le mod %w->h permet de tronquer pour une beauce depassant les limites du monde (qui est un tore)
        j = ((rand() % (b->w)) + b->x) % w->w;
        cell[i][j]++;
    }
}

void RandomDirection(Animal* a) {
    int sum = SumTab(a->chr, N);
    int rnd = rand() % sum;
    int gk = 0;
    while (rnd >=0) { // Somme cumulee decroissante des valeurs de genes
      rnd -= a->chr[gk];
      gk++;
    }
    a->dir = (a->dir + gk - 1) % 8; // Calcul de la nouvelle direction
}

void MoveAnimal(Animal* a, World* w, int** cell) {
    RandomDirection(a);
    switch(a->dir) { // Deplacement selon la direction definie par l'appel de la fonction precedente
        case 0:
            (a->y)++;
            break;
        case 1:
            (a->y)++;
            (a->x)++;
            break;
        case 2:
            (a->x)++;
            break;
        case 3:
            (a->x)++;
            (a->y)--;
            break;
        case 4:
            (a->y)--;
            break;
        case 5:
            (a->x)--;
            (a->y)--;
            break;
        case 6:
            (a->x)--;
            break;
        default:
            (a->x)--;
            (a->y)++;
            break;
    }
    // Passage a l'autre bout du monde en cas de depassement
    if (a->x < 0) a->x = w->w - 1;
    if (a->y < 0) a->y = w->h - 1;
    if (a->x >= w->w) a->x = 0;
    if (a->y >= w->h) a->y = 0;
    (a->enrg)--; // Perte d'energie due au deplacement
    if (cell[a->y][a->x] > 0) { // Gain d'energie en cas de prescense de nourriture
        (a->enrg) += w->food;
        (cell[a->y][a->x])--;
    }
}

int AfterMoveAnimals(List_Animal* l, World* w, int** cell) {
    Animal* a = l->head;
    Animal* aSupp = NULL;
    Animal* aPrev = NULL;
    while (a != NULL) {
        if (l->len <= 0) return 1; // Permet l'arret de la simulation dans le main.c car tous les nimaux sont morts
        MoveAnimal(a, w, cell);
        if (a->enrg <= 0) { // Aminal mort
            aSupp = SuppAnimal(l, aPrev, a);
            if (aPrev == NULL) a = l->head;
            else a = aPrev->next;
            free(aSupp);
            aSupp = NULL;
        }
        else {
            if (a->enrg >= w->repro) { // Reproduction de l'animal
                a->enrg = a->enrg / 2;
                Animal* aNew = InitAnimal();
                CopyAnimal(a, aNew);
                AddAnimal(l, aNew);
                Mutation(aNew);
            }
            aPrev = a;
            a = a->next;
        }
    }
    return 0;
}

void Mutation(Animal* a) { // Mutation d'un gene aleatoire du nouveau nee
    int gn = rand() % N;
    int mut = rand() % 3 - 1;
    a->chr[gn] = a->chr[gn] + mut;
    if (a->chr[gn] <= 1) a->chr[gn] = 1;
}
