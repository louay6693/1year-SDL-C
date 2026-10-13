#ifndef SOUSMENU_H_
#define SOUSMENU_H_
#include<SDL/SDL.h>
#include "perso.h"

#include "ennemi.h"

typedef struct saves
{
perso p1;
perso p2;
SDL_Rect camera;
ennemi enn;
vie v;
vie v2;
int choix,en1,enigme1,enigme2,temps;
int LEVEL;
}saves;
void save(ennemi enn,perso p,perso p2,vie v,vie v2,SDL_Rect camera,int choix,int en1,int enigme1,int enigme2,int temps_joueur,int *LEVEL);
void load(ennemi *enn,perso *p,perso *p2,vie *v,vie *v2,SDL_Rect *camera,int *choix,int *en1,int *enigme1,int *enigme2,int *temps_joueur,int* LEVEL);
int sousmenu(SDL_Surface *ecran);
#endif 

