#ifndef _PERSO_H_
#define _PERSO_H_
#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "controls.h"

enum state{idle,walk,jump};
int posinit_x;
int posinit_y;
typedef struct
{
int num;
SDL_Surface *vi[5];
SDL_Rect pos;
}vie;
typedef struct{
  int health;
  int score;
  int vie;
  int speed;
  int jump;
  keymapping keys;
  SDL_Rect pos;
  SDL_Rect pos_rel;
  SDL_Rect sprite;
  enum state state;
  int d;//direction
  SDL_Surface* images[3][2];
  int isl[3]; //image sprite length
  int sprite_num;
   vie v;
  SDL_Surface* attack;
  int attacking;
}perso;



void init_perso(perso *p);
void init_perso_controls(perso *p);
void afficher_perso(perso p,SDL_Surface *screen);
void afficher_score_vie(perso p,SDL_Surface *screen,int n);
void animer_perso(perso *p);
void deplacer_perso(perso *p);
void player_in_bounds(perso *p,SDL_Surface *screen);
void jump_perso(perso *p);
void saut_perso(perso *p);
void on_ground(perso *p,int bg,SDL_Surface *masque);
void init_perso_controls_p2(perso *p);

void init_perso_s1(perso *p);
void init_perso_s2(perso *p);
void jump_perso2(perso *p);

#endif
