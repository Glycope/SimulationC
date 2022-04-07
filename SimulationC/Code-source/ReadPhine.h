#ifndef READPHINE_H
#define READPHINE_H
#include "Init.h"

int ReadPhine(FILE* f, World* w, Beauce* b, List_Animal* l);
//Recupere les donnees du fichier phine

void PrintPhine(FILE* f, List_Animal* l, List_Animal** tabFam, int nbFam, World* w, Beauce* b);

#endif
