#ifndef ENIGMEA_H_INCLUDED
#define ENIGMEA_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

typedef struct
{
   
    SDL_Surface *image[7],*imagewin,*imagelose;
    SDL_Surface *q,*r1,*r2,*r3;
    SDL_Rect pos,pos_r1,pos_r2,pos_r3,pos_q;
	
	int alea;
	int bonne_reponse;
	int votre_reponse;
	int affiche;
 
}enigmea;

void init_enigme(enigmea *enig,char *nom_fichier);
void  afficher_enigme(enigmea  enig, SDL_Surface *screen,int* animation);    
void scan_reponse(enigmea *enig,SDL_Event event);
void afficher_resultat(SDL_Surface *ecran,enigmea enig,int *score);
void free_enigme(enigmea *enig);



#endif // ENIGME_H_INCLUDED

