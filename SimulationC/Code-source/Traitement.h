#ifndef TRAITEMENT_H
#define TRAITEMENT_H
#include "Init.h"
#include "Simulation.h"

typedef struct{
    int x;
    int y;
} CenterB;

CenterB* InitCenterB(void);

void FindCenterB(CenterB* c,Beauce* b, World* w);

int DistAniCent(CenterB* c, Animal* a, World* w);

Animal* PrevMaxDist(List_Animal* l, CenterB* c, World* w);

void ListSort(CenterB* c, List_Animal* l, List_Animal* sortedL, World* w);

List_Animal** CreateListFam(List_Animal* l, int nbFam);

void FreeAnimals(List_Animal* l);

void FulfillFam(List_Animal* source, List_Animal** tabFam);

#endif
