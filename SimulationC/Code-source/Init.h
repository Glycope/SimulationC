#ifndef INIT_H
#define INIT_H
#define N 8 /* Definition du nombre de chromosomes ici en cas de changement de code */

typedef struct list_Animal List_Animal;

typedef struct {
    int w;
    int h;
    int repro;
    int food;
} World;

typedef struct {
    int x;
    int y;
    int w;
    int h;
} Beauce;

typedef struct animal {
    int x;
    int y;
    int enrg;
    int dir;
    int chr[N];
    int fam;
    struct animal* next;
} Animal;

struct list_Animal {
    Animal* head;
    int len;
    int color[3];
};

List_Animal* InitList(void); //Intialise une liste chainee vide d'animaux
Animal* InitAnimal(void);
World* InitWorld(void); //Intialise un monde vide
Beauce* InitBeauce(void); //Intialise une beauce vide
int** InitCell(World* w); //Initialise toutes les cellules a 0 nourriture
void usage(char *prog);
void AddAnimal(List_Animal* l, Animal* a); //Ajoute un animal en tete de liste (pour une meilleure complexite)
Animal* SuppAnimal(List_Animal* l, Animal* aPrev, Animal* a);
int max(int a, int b);
int min(int a, int b);
void CopyAnimal(Animal* source, Animal* destination);
void FreeCells(int** cell,World*w);
void ErrorAlloc(void);
#endif
