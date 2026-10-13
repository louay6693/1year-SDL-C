#include <SDL/SDL.h>
#include "Image.h"
#include <SDL/SDL_image.h>

void initbackground(Image *backg)
{
backg->img=IMG_Load("999.png");
if(backg->img == NULL){
printf("unable to load bitmap: %s \n",SDL_GetError());
return ;}
backg->pos1.x=0;
backg->pos1.y=0;
backg->pos2.x=0;
backg->pos2.y=0;
backg->pos2.w=(SCREEN_W);
backg->pos2.h=(SCREEN_H);
}
void liberer(Image A)
{
SDL_FreeSurface(A.img);
}
void afficher (Image p,SDL_Surface *screen)
{
SDL_BlitSurface(p.img,&p.pos2,screen,&p.pos1);

}
