#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Traitement.h"

CenterB* InitCenterB(void) {
    CenterB* c = malloc(sizeof(CenterB));
    if (c == NULL) ErrorAlloc();
    return c;
}

void FindCenterB(CenterB* c, Beauce* b, World* w) { // Recherche centre beauce
    c->x = ((b->x + b->w - 1) % w->w) / 2;
    c->y = ((b->y + b->h - 1) % w->h) / 2;
}

int DistAniCent(CenterB* c, Animal* a, World* w) {
    int x = abs(a->x - c->x), y = abs(a->y - c->y);
    if (x > w->w / 2) x = w->w - x;
    if (y > w->h / 2) y = w->h - y;
    return max(x,y);
}

Animal* PrevMaxDist(List_Animal* l, CenterB* c, World* w) { // Renvoie le precedent du max
    Animal* aPrev = l->head;
    Animal* a = aPrev->next;
    int m0, m1;
    Animal* aMax = aPrev;
    Animal* aPrevMax = NULL;
    while (a != NULL) {
        m0 = DistAniCent(c, aMax, w);
        m1 = DistAniCent(c, a, w);
        if (m1 > m0) {
            aPrevMax = aPrev;
            aMax = a;
        }
        aPrev = a;
        a = a->next;
    }
    return aPrevMax;
}

void ListSort(CenterB* c, List_Animal* l, List_Animal* sortedL, World* w) {
    Animal* aPrev;
    Animal* aMax;
    while (l->len > 0){
        aPrev = PrevMaxDist(l, c, w);
        if (aPrev == NULL) aMax = l->head;
        else aMax = aPrev->next;
        Animal* aNew = InitAnimal();
        CopyAnimal(aMax, aNew);
        AddAnimal(sortedL, aNew);
        Animal* aSupp = SuppAnimal(l, aPrev, aMax);
        free(aSupp);
    }
    free(l);
}

List_Animal** CreateListFam(List_Animal* l, int nbFam) { // Creer un tableau de liste pour les familles
    List_Animal** tabFam = calloc(nbFam, sizeof(List_Animal*));
    if (tabFam == NULL) ErrorAlloc();
    int i;
    for (i = nbFam - 1; i >= 0; i--) {
        tabFam[i] = InitList();
    }
    FulfillFam(l,tabFam);
    return tabFam;
}

void FreeAnimals(List_Animal* l){ 
  Animal* a= l->head;
  while (a!=NULL){
    Animal * aSupp=SuppAnimal(l,NULL,a);
    free(aSupp);
    a=l->head;
  }
}
void FulfillFam(List_Animal* source, List_Animal** tabFam){ // Remplie la liste de chaque famille
  Animal* a = source->head;
  while (a != NULL) {
      Animal* aNew = InitAnimal();
      CopyAnimal(a, aNew);
      AddAnimal(tabFam[a->fam], aNew);
      a = a->next;
  }
}
