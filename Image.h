#ifndef Image_H
#define Image_H
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#define SCREEN_W 800
#define SCREEN_H 600
typedef struct 
{
SDL_Rect pos1;
SDL_Rect pos2;
SDL_Surface *img;
}Image;


void initbackground(Image *backg);
void liberer(Image A);
void afficher(Image p,SDL_Surface *screen);

#endif
