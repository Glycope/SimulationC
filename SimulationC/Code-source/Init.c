#include <stdio.h>
#include <stdlib.h>
#include "Init.h"

void usage(char *prog) {
    printf("How to execute the simulation : %s a n monde.phine sortie.phine [c]\n\n\ta : 0 (without randomness) or 1 (with randomness)\n\tn : number of iterations\n\tc : [option] numbre of generated images after the n iterations (must be under 10000)\n", prog);
}
Animal* InitAnimal(void){
    Animal * a = malloc(sizeof(Animal));
    if (a == NULL) ErrorAlloc();
    return a;
}
List_Animal* InitList(void) {
    List_Animal* l = malloc(sizeof(List_Animal));
    if (l == NULL) ErrorAlloc();
    l->len = 0;
    l->head = NULL;
    return l;
}

World* InitWorld(void) {
    World* w = malloc(sizeof(World));
    if (w == NULL) ErrorAlloc();
    return w;
}

Beauce* InitBeauce(void) {
    Beauce* b = malloc(sizeof(Beauce));
    if (b == NULL) ErrorAlloc();
    return b;
}

int** InitCell(World* w) {
    int i;
    int** cell = calloc(w->h, sizeof(int*));
    if (cell == NULL) ErrorAlloc();
    for (i = 0; i < w->h; i++) {
        cell[i] = calloc(w->w, sizeof(int));
        if (cell[i]==NULL) ErrorAlloc();
    }
    return cell;
}

void AddAnimal(List_Animal* l, Animal* a) {
    a->next = l->head;
    l->head = a;
    l->len++;
}

Animal* SuppAnimal(List_Animal* l, Animal* aPrev, Animal* a) {
    Animal* aSupp = a;
    if (a == l->head) l->head = l->head->next;
    else aPrev->next = a->next;
    l->len--;
    return aSupp;
}

int max(int a, int b) {
    if (a > b) return a;
    return b;
}

int min(int a, int b) {
    if (a > b) return b;
    return a;
}

void CopyAnimal(Animal* source, Animal* destination) {
    int i;
    destination->x = source->x;
    destination->y = source->y;
    destination->enrg = source->enrg;
    destination->dir = source->dir;
    for (i = 0; i < N; i++ ) {
        destination->chr[i] = source->chr[i];
    }
    destination->fam = source->fam;
}

void FreeCells(int** cell,World*w){
  int i;
  for (i=0;i<w->h;i++){
      free(cell[i]);
    }
  free(cell);
}

void ErrorAlloc(void){
  printf("Memory allocation has failled");
  exit(0);
}
