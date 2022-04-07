#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char* CreateName(int k) {
    char* nameF = malloc(12 * sizeof(char));
    if (nameF == NULL) exit(0);
    strcat(nameF, "monde");
    char tmp[4];
    if (k < 10) sprintf(tmp, "0%d", k);
    else if (k < 100) sprintf(tmp, "%d", k);
    else exit(0);
    strcat(nameF, tmp);
    strcat(nameF, ".txt");
    return nameF;
}

int main(int argc, char *argv[]) {
  int nbphine,wh,ww,bx,by,bh,bw,food,rep,nbAni;
  int ax,ay,adir,aeng,chr[8];
  int i,j,k;
  if (argc != 2) return 0;
  if (sscanf(argv[1],"%d",&nbphine) != 1) return 0;
  srand(time(NULL));
  for (i=0;i<nbphine;i++){
    char* name=CreateName(i+1);
    FILE * f=fopen(name,"w");
    if (f==NULL) continue;
    printf("Hauteur Monde ?\n");
    scanf("%d",&wh);
    printf("Largeur Monde ?\n");
    scanf("%d",&ww);
    printf("Abscisse Beauce ?\n");
    scanf("%d",&bx);
    printf("Ordonnee Beauce ?\n");
    scanf("%d",&by);
    printf("Hauteur Beauce ?\n");
    scanf("%d",&bh);
    printf("Largeur Beauce ?\n");
    scanf("%d",&bw);
    printf("Energie nourriture ?\n");
    scanf("%d",&food);
    printf("Seuil reproduction ?\n");
    scanf("%d",&rep);
    fprintf(f,"\nMonde %d %d \nBeauce %d %d %d %d \nEnergie Nourriture %d \nSeuil Reproduction %d \n\n\n",wh,ww,bx,by,bh,bw,food,rep);
    printf("Nombre animaux ? \n");
    scanf("%d",&nbAni);
    for(j=0;j<nbAni;j++){
      ax=rand() % ww;
      ay=rand() % wh;
      adir = rand() % 8;
      aeng = rand() % (ww+wh) + 1 ;
      fprintf(f, "(%d %d) %d %d | ",ax,ay,adir,aeng);
      for (k=0;k<8;k++){
        chr[k] = rand() % (100) + 1;
        fprintf(f, "%d ",chr[k]);
      }
      fprintf(f, "| \n");
    }
    fclose(f);
  }

  return 0;
}
