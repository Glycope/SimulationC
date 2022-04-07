#ifndef SIMULATION_H
#define SIMULATION_H
#include "Init.h"

int SumTab(int tab[], int lenTab);

int BeauceExists(Beauce* b);

void RandomFood(int** cell, World* w, Beauce* b, int b_e);

void RandomDirection(Animal* a);

void MoveAnimal(Animal* a, World* w, int** cell);

int AfterMoveAnimals(List_Animal* l, World* w, int** cell);

void Mutation(Animal* a);

#endif
