
#ifndef ENIGME_H_INCLUDED
#define ENIGME_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <string.h>
#include <time.h>
#include <SDL/SDL_ttf.h>

typedef struct enigme
{
char titre[30];
char reponse[30];
}enigme;


void init_enigmes(int tabl[]);
int generer_enigme(int tabl[]);
int saisir(SDL_Surface *ecran,int numEnigme);








#endif // ENIGME_H_INCLUDED

