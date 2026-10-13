/**  
* @file ennemi.h  
* @brief Testing Program.  
* @author C Team  
* @version 0.1  
* @date 04/05/2023
*  
* all the structs and the functions that we need  *  
*/
#ifndef ENNEMI_H_INCLUDED
#define ENNEMI_H_INCLUDED
#include<SDL/SDL.h>
/**
* @struct ennemi
* @brief struct for ennemi
*/
typedef enum STATE STATE;
enum STATE {waiting,following,attacking};
/**
*@struct Ennemi
*@brief struct for the ennemy
*/
struct Ennemi
{
int direction,num,at,aff,mort;
STATE etat_ennemi;
SDL_Surface *warning;
SDL_Rect pos;
SDL_Surface *e[10];
SDL_Surface *attaque[10];
};
/**
*@struct ennemi
*@brief rename the struct for the ennemy
*/
typedef struct Ennemi ennemi;

void init_ennemi(ennemi *enn);

void etat_ennemi(ennemi *enn,SDL_Rect poshero);

void afficher_ennemi(SDL_Surface *ecran,ennemi *enn);

void deplacement_ennemi(ennemi *enn,SDL_Rect poshero);

void animer_ennemi(SDL_Surface *ecran,ennemi *enn,SDL_Rect poshero);

void free_ennemi(ennemi *enn);



#endif
