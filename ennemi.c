/**

* @file ennemi.c
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include "ennemi.h"
#include"perso.h"
#include"collisionbb.h"
void init_ennemi(ennemi *enn)
{
   int i;
   enn->direction=1;
   enn->aff=0;
   enn->num=0;
   enn->at=0;
   enn->mort=0;
   enn->etat_ennemi=waiting;
   char image[40];
   enn->pos.x=550;
   enn->pos.y=450;
   enn->warning=NULL;
   for(i=0;i<10;i++)
	{
	    enn->e[i]=NULL;
	}
   for(i=0;i<10;i++)
	{
	    sprintf(image,"ennemi%d.png",i+1);
	    enn->e[i]=IMG_Load(image);
	}
   for(i=0;i<10;i++)
	{
	    enn->attaque[i]=NULL;
	}
   for(i=0;i<10;i++)
	{
	    sprintf(image,"at%d.png",i+1);
	    enn->attaque[i]=IMG_Load(image);
	}
   enn->warning=IMG_Load("warning.png");
}
/**
*@brief to get the state of the ennemy: waiting/following/attacking
*@param *enn : ennemy
*@param poshero : hero position
*@return nothing
*/
void etat_ennemi(ennemi *enn,SDL_Rect poshero)
{
   if((enn->pos.x>poshero.x)&&(enn->pos.x-poshero.x>500)) enn->etat_ennemi=waiting;
else
   if((enn->pos.x<poshero.x)&&(poshero.x-enn->pos.x>500)) enn->etat_ennemi=waiting; 
else
   if(collision(poshero,enn)==1) enn->etat_ennemi=attacking;
else enn->etat_ennemi=following;
}

/**
*@brief to move the ennemy
*@param *enn : ennemy
*@param poshero : hero position
*@return nothing
*/
void deplacement_ennemi(ennemi *enn,SDL_Rect poshero)
{
   switch(enn->etat_ennemi)
   {

   case waiting:
   if((enn->pos.x)<=900) enn->direction=0;
   if((enn->pos.x)>=1200) enn->direction=1;
   if(enn->direction==1) enn->pos.x-=1;
   if(enn->direction==0) enn->pos.x+=1;
   break;

   case following:
   if((enn->pos.x)<=poshero.x) enn->direction=0;
   if((enn->pos.x)>poshero.x) enn->direction=1;
   if(enn->direction==1) enn->pos.x-=2;
   if(enn->direction==0) enn->pos.x+=2;
   break;

   }
}
/**
*@brief to blit the image of the ennemy
*@param *ecran : the screen 
*@param *enn : ennemy
*@return nothing
*/
void afficher_ennemi(SDL_Surface *ecran,ennemi *enn)
{
   SDL_Rect pos;
   pos.x=enn->pos.x+40;
   pos.y=enn->pos.y-70;
   switch (enn->etat_ennemi)
   {
      case waiting:
      if(enn->direction==1)
      {
         if((enn->num==5)||(enn->num==10)) (enn->num)=0; 
         SDL_BlitSurface(enn->e[enn->num],NULL,ecran,&enn->pos);
         (enn->num)++;
      }
      if(enn->direction==0)
      {
         if((enn->num==5)||(enn->num==10)) (enn->num)=5; 
         SDL_BlitSurface(enn->e[enn->num],NULL,ecran,&enn->pos);
         (enn->num)++;
      }
      
      break;


      case following:

      if(enn->direction==1)
      {
         if((enn->num==5)||(enn->num==10)) (enn->num)=0; 
         SDL_BlitSurface(enn->e[enn->num],NULL,ecran,&enn->pos);SDL_BlitSurface(enn->warning,NULL,ecran,&pos);
         (enn->num)++;
      }
      if(enn->direction==0)
      {
         if((enn->num==5)||(enn->num==10)) (enn->num)=5; 
         SDL_BlitSurface(enn->e[enn->num],NULL,ecran,&enn->pos);SDL_BlitSurface(enn->warning,NULL,ecran,&pos);
         (enn->num)++;
      }
      
      break;

      case attacking:

            if(enn->direction==1)
            {
               if((enn->at==5)||(enn->at==10)) (enn->at)=0; 
               SDL_BlitSurface(enn->attaque[enn->at],NULL,ecran,&enn->pos);SDL_BlitSurface(enn->warning,NULL,ecran,&pos);
               (enn->at)++;
            }
            if(enn->direction==0)
            {
    	       if((enn->at==5)||(enn->at==10)) (enn->at)=5; 
     	       SDL_BlitSurface(enn->attaque[enn->at],NULL,ecran,&enn->pos);SDL_BlitSurface(enn->warning,NULL,ecran,&pos);
    	       (enn->at)++;
            }
            break;
   }

   
}
/**
*@brief to animate the ennemy: get state+mouvement+blit
*@param *ecran : the screen
*@param *enn : ennemy
*@param poshero : hero position
*@return nothing
*/
void animer_ennemi(SDL_Surface *ecran,ennemi *enn,SDL_Rect poshero)
{

   if(enn->mort==0) 
   {
   enn->aff=1;
   etat_ennemi(enn,poshero); 
   afficher_ennemi(ecran,enn);
   deplacement_ennemi(enn,poshero);
   }

}
/**
*@brief to free the ennemy
*@param *enn : ennemy
*@return nothing
*/
void free_ennemi(ennemi *enn)
{
   int i;
   for(i=0;i<10;i++)
   {
      SDL_FreeSurface(enn->e[i]);
   }
   for(i=0;i<10;i++)
   {
      SDL_FreeSurface(enn->attaque[i]);
   }
   SDL_FreeSurface(enn->warning);
}
