#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include "enigmea.h"
#include <SDL/SDL_image.h>
#include <time.h>
#include <SDL/SDL_rotozoom.h>

//*************************************
void init_enigme(enigmea *enig,char *nom_fichier)              
{
	
    
  
    enig->pos.x=220;
    enig->pos.y=150;
    enig->alea=0;

    enig->imagewin=IMG_Load("./enigme/gagner.png");
    enig->imagelose=IMG_Load("./enigme/perdu.png");
	
    enig->image[0]=IMG_Load("./enigme/1.png");
    enig->image[1]=IMG_Load("./enigme/2.png");
    enig->image[2]=IMG_Load("./enigme/3.png");
    enig->image[3]=IMG_Load("./enigme/4.png");
    enig->image[4]=IMG_Load("./enigme/5.png");
    enig->image[5]=IMG_Load("./enigme/6.png");




    int ancienne = enig->alea;
    char q[30];
	char r1[30],r2[30],r3[30];
    
    do
    {
        enig->alea = 1 + random() % 4;  // 5 to 4
    } while (enig->alea == ancienne);


	FILE *f=fopen(nom_fichier,"r");
	if(f!=NULL){
int nb_ligne=1;
while (nb_ligne <= enig->alea   )            
{ 

    
    fscanf(f,"%s %s %s %s %d \n",q,r1,r2,r3,&enig->bonne_reponse);
    enig->q=IMG_Load(q);
    enig->r1=IMG_Load(r1);
    enig->r2=IMG_Load(r2);
    enig->r3=IMG_Load(r3);
	nb_ligne++;
}
		   }fclose(f);
enig->pos_q.x=280;
enig->pos_q.y=280;

enig->pos_r1.x=350;
enig->pos_r1.y=360;
enig->pos_r2.x=350;
enig->pos_r2.y=410;
enig->pos_r3.x=350;
enig->pos_r3.y=460;

}
//*****************************
void  afficher_enigme(enigmea  enig, SDL_Surface *screen,int *animation)        
{

	if(*animation>0 ){ SDL_BlitSurface(enig.image[0], NULL, screen, &(enig.pos));}
	if(*animation>10 ){ SDL_BlitSurface(enig.image[1], NULL, screen, &(enig.pos));}
	if(*animation>20 ){ SDL_BlitSurface(enig.image[2], NULL, screen, &(enig.pos));}
	if(*animation>30){ SDL_BlitSurface(enig.image[3], NULL, screen, &(enig.pos));}
	if(*animation>40){ SDL_BlitSurface(enig.image[4], NULL, screen, &(enig.pos));}
	if(*animation>50 ){SDL_BlitSurface(enig.image[5], NULL, screen, &(enig.pos));}
if((*animation)>60){(*animation)=0;}
 SDL_BlitSurface(enig.q, NULL, screen, &(enig.pos_q));
 SDL_BlitSurface(enig.r1, NULL, screen, &(enig.pos_r1));
 SDL_BlitSurface(enig.r2, NULL, screen, &(enig.pos_r2));
 SDL_BlitSurface(enig.r3, NULL, screen, &(enig.pos_r3));
 	
   SDL_Flip(screen);

(*animation)++;
}


//**************************************
void scan_reponse(enigmea *enig, SDL_Event event)
{
  while(enig->affiche !=1){
        switch (event.key.keysym.sym) {
            case SDLK_a:
                enig->votre_reponse = 1;
                enig->affiche = 1;
                break;
            case SDLK_z:
                enig->votre_reponse = 2;
                enig->affiche = 1;
                break;
            case SDLK_e:
                enig->votre_reponse = 3;
                enig->affiche = 1;
                break;
            default:
                enig->affiche = 0;
                
        }break;
}
   
}
/////////////////////////////////////////////////////////
void afficher_resultat(SDL_Surface *ecran,enigmea enig,int *score)
{
    double angle = 0.0;
    double zoom = 1.0;
    SDL_Surface* rotatedImagewin = NULL;
    SDL_Surface* rotatedImagelost = NULL;
    SDL_Rect destRect;

    // boucle de jeu pour animer la rotation et le zoom de l'image
    while (angle < 360.0 && zoom < 2.0) {
        // effacer l'écran
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

        // rotation et zoom de l'image
        angle += 7.0;
        zoom += 0.02;
        if (angle >= 360.0) {
            angle -= 360.0;
        }
        if (zoom >= 2.0) {
            zoom = 2.0;
        }
        rotatedImagewin = rotozoomSurface(enig.imagewin, angle, zoom, 1);
        rotatedImagelost = rotozoomSurface(enig.imagelose, angle, zoom, 1);

        // position de l'image centrée sur l'écran
        destRect.x = (ecran->w - rotatedImagewin->w) / 2;
        destRect.y = (ecran->h - rotatedImagewin->h) / 2;

        // affichage de l'image en fonction de la réponse de l'utilisateur
        if (enig.bonne_reponse == enig.votre_reponse) {
            SDL_BlitSurface(rotatedImagewin, NULL, ecran, &destRect);
	*score+=10;
        } else {
            SDL_BlitSurface(rotatedImagelost, NULL, ecran, &destRect);
	*score-=10;
        }

        // mise à jour de l'affichage
        SDL_Flip(ecran);

        // pause pour limiter le taux de rafraîchissement
        SDL_Delay(10);
    }


}

void free_enigme(enigmea *enig)
{
    int i=0;
for(i=0;i<5;i++){SDL_FreeSurface(enig->image[i]);}
}



































