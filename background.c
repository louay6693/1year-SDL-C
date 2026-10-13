#include "background.h"


void initBack (background *b)
{
//background
b->imgback=IMG_Load("lvl3.jpg");
b->posback.x=0;
b->posback.y=0;
//camera
b->camera.x=0;
b->camera.y=0;
b->camera.w=800; 
b->camera.h=675;
//musique


}

void initBackMasque (background *b)
{
//background

b->masque=IMG_Load("lvl3_masque.jpg");
if(b->masque==NULL){printf("xxxxxxxx");}
b->posback.x=0;
b->posback.y=0;
//camera
b->camera.x=0;
b->camera.y=0;
b->camera.w=800; 
b->camera.h=675;



}

void initBack2 (background *b)
{
//background2
b->imgback=IMG_Load("lvl3.jpg");
b->masque=IMG_Load("lvl3_masque.jpg");
b->posback2.x=400;
b->posback2.y=0;
//camera2
b->camera2.x=0;
b->camera2.y=0;
b->camera2.w=400; 
b->camera2.h=675;
//musique
b->son=Mix_LoadMUS("musique.mp3"); //Chargement de la musique

}

void initialisation_back(background *b)
{
	initBack(b);
	initBack2(b);
}



void afficheBack (background b, SDL_Surface *ecran)
{
/* On blitte par-dessus l'écran */
Mix_PlayMusic(b.son, -1);
SDL_BlitSurface(b.imgback,&b.camera,ecran,&b.posback);
}

void afficheBack2 (background b, SDL_Surface *ecran)
{
/* On blitte par-dessus l'écran */
Mix_PlayMusic(b.son, -1); //Jouer infiniment la musique
SDL_BlitSurface(b.imgback,&b.camera2,ecran,&b.posback2);
}
void afficher_back(background b, SDL_Surface *ecran)
{
	afficheBack(b,ecran);
	afficheBack2(b,ecran);
	
}


