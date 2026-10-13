#include "perso.h"
#include <stdio.h>
#define ACCELERATION 0.1
#define LIM_LEFT 50
#define LIM_RIGHT 150

void init_perso(perso *p)
{
int i; char ch[50];
    (*p).health = 0;
    (*p).score = 50;
    (*p).vie = 100;
    (*p).d = 1;
    (*p).jump = 0;
    (*p).pos.x = 50;
    (*p).pos.y = 450;
    (*p).pos_rel.x=-50;
    (*p).pos_rel.y=0;
    (*p).sprite.x=0;
    (*p).sprite.y=0;
    (*p).state = idle;
    (*p).sprite_num = 0;
    (*p).images[0][0] = IMG_Load("idleright.png");
    (*p).images[1][0] = IMG_Load("walkright.png");
    (*p).images[2][0] = IMG_Load("jumpright.png");
    (*p).images[0][1] = IMG_Load("idleleft.png");
    (*p).images[1][1] = IMG_Load("walkleft.png");
    (*p).images[2][1] = IMG_Load("jumpleft.png"); 
    (*p).pos.w = 100;
    (*p).pos.h = (*p).images[1][0]->h;
    (*p).isl[0] = 3;
    (*p).isl[1] = 5;
    (*p).isl[2] = 3;
for(i=0;i<5;i++)
	{
            (*p).v.vi[i]=NULL;
	    sprintf(ch,"vie%d.png",i+1);
	    (*p).v.vi[i]=IMG_Load(ch);
	}
 (*p).v.num=0;//ce compteur va augmenter lorsque le personnage sera blessé (v->num)++ pour afficher l'image de la vie quand elle diminue
   (*p).v.pos.x=0;
  (*p).v.pos.y=0;
	    (*p).attack = IMG_Load("attack.png"); 
    (*p).attacking=0;
	if((*p).attack==NULL){printf("erreur attack \n");}
}
void init_perso_s1(perso *p)
{
int i; char ch[50];
    (*p).health = 0;
    (*p).score = 50;
    (*p).vie = 100;
    (*p).d = 1;
    (*p).jump = 0;
    (*p).pos.x = 450;
    (*p).pos.y = 450;
    (*p).pos_rel.x=-50;
    (*p).pos_rel.y=0;
    (*p).sprite.x=0;
    (*p).sprite.y=0;
    (*p).state = idle;
    (*p).sprite_num = 0;
    (*p).images[0][0] = IMG_Load("idleright_1.png");
    (*p).images[1][0] = IMG_Load("walkright_1.png");
    (*p).images[2][0] = IMG_Load("jumpright_1.png");
    (*p).images[0][1] = IMG_Load("idleleft_1.png");
    (*p).images[1][1] = IMG_Load("walkleft_1.png");
    (*p).images[2][1] = IMG_Load("jumpleft_1.png"); 
    (*p).pos.w = 100;
    (*p).pos.h = (*p).images[1][0]->h;
    (*p).isl[0] = 3;
    (*p).isl[1] = 5;
    (*p).isl[2] = 3;
for(i=0;i<5;i++)
	{
            (*p).v.vi[i]=NULL;
	    sprintf(ch,"vie%d.png",i+1);
	    (*p).v.vi[i]=IMG_Load(ch);
	}
 (*p).v.num=0;//ce compteur va augmenter lorsque le personnage sera blessé (v->num)++ pour afficher l'image de la vie quand elle diminue
   (*p).v.pos.x=10;
  (*p).v.pos.y=0;
	    (*p).attack = IMG_Load("attack.png"); 
    (*p).attacking=0;
	if((*p).attack==NULL){printf("erreur attack \n");}
}

void init_perso_s2(perso *p)
{
int i; char ch[50];
    (*p).health = 0;
    (*p).score = 50;
    (*p).vie = 100;
    (*p).d = 1;
    (*p).jump = 0;
    (*p).pos.x = 450;
    (*p).pos.y = 450;
    (*p).pos_rel.x=-50;
    (*p).pos_rel.y=0;
    (*p).sprite.x=0;
    (*p).sprite.y=0;
    (*p).state = idle;
    (*p).sprite_num = 0;
    (*p).images[0][0] = IMG_Load("idleright_2.png");
    (*p).images[1][0] = IMG_Load("walkright_2.png");
    (*p).images[2][0] = IMG_Load("jumpright_2.png");
    (*p).images[0][1] = IMG_Load("idleleft_2.png");
    (*p).images[1][1] = IMG_Load("walkleft_2.png");
    (*p).images[2][1] = IMG_Load("jumpleft_2.png"); 
    (*p).pos.w = 100;
    (*p).pos.h = (*p).images[1][0]->h;
    (*p).isl[0] = 3;
    (*p).isl[1] = 5;
    (*p).isl[2] = 3;
for(i=0;i<5;i++)
	{
            (*p).v.vi[i]=NULL;
	    sprintf(ch,"vie%d.png",i+1);
	    (*p).v.vi[i]=IMG_Load(ch);
	}
 (*p).v.num=0;//ce compteur va augmenter lorsque le personnage sera blessé (v->num)++ pour afficher l'image de la vie quand elle diminue
   (*p).v.pos.x=0;
  (*p).v.pos.y=0;
	    (*p).attack = IMG_Load("attack.png"); 
    (*p).attacking=0;
	if((*p).attack==NULL){printf("erreur attack \n");}
}



void init_perso_controls(perso *p)
{
	   (*p).keys.attack=SDLK_SPACE;

   (*p).keys.left=SDLK_LEFT;
   (*p).keys.right=SDLK_RIGHT;
   (*p).keys.jump=SDLK_UP;
}

void init_perso_controls_p2(perso *p)
{
(*p).keys.attack=SDLK_e;
   (*p).keys.left=SDLK_q;
   (*p).keys.right=SDLK_d;
   (*p).keys.jump=SDLK_z;
}

void afficher_perso(perso p,SDL_Surface *screen)
{
   if(p.attacking==0)
        SDL_BlitSurface(p.images[p.state][p.d-1],&p.sprite,screen,&p.pos);
   else
   {
        SDL_Rect pos; 
        pos.w=p.attack->w/19;
        pos.x=pos.w*p.attacking;
        pos.y=0;
        pos.h = p.attack->h;
        SDL_BlitSurface(p.attack,&pos,screen,&p.pos);
   }
}

void afficher_score_vie(perso p,SDL_Surface *screen,int n)
{
  /* if(p.pos.x+p.pos.w>0) 
   {
       TTF_Font *font=TTF_OpenFont("fonts/score.ttf", 25);
       SDL_Color color={255*n,255,255};
       SDL_Surface *text,*s;
       SDL_Rect pos=p.pos;pos.y-=10;
       s = SDL_CreateRGBSurface(0,p.pos.w*p.vie/100,10, 32,0,0,0, 10);
       SDL_FillRect(s, NULL, SDL_MapRGB(s->format, 100 +155*n, 0, 0));
       char ch[15];
       sprintf(ch,"%d",p.score);
       text=TTF_RenderText_Solid(font,ch,color);
       SDL_BlitSurface(s,NULL,screen,&pos);pos.y-=25;
       SDL_BlitSurface(text,NULL,screen,&pos);
       TTF_CloseFont(font);
       font=NULL;
       SDL_FreeSurface(text);
       text=NULL;
       SDL_FreeSurface(s);
       s=NULL;
   }*/
	SDL_BlitSurface(p.v.vi[p.v.num],NULL,screen,&p.v.pos);
}

void animer_perso(perso *p)
{
    int nb_images = (*p).isl[(*p).state];
    float d=nb_images;d=1/(d*2);
    int image_width = (*p).images[(*p).state][(*p).d-1]->w/(nb_images+1);
    (*p).sprite.h = (*p).images[(*p).state][(*p).d-1]->h;
    (*p).sprite_num++;if((*p).sprite_num>nb_images) (*p).sprite_num=0;
    (*p).sprite.x=image_width*(*p).sprite_num;(*p).sprite.x=(*p).sprite.x*(1+d);
    (*p).sprite.w=image_width*(1-d);
	if((*p).attacking>0)(*p).attacking++;
    if((*p).attacking==18)
    (*p).attacking=0;
   

}

void deplacer_perso(perso *p)
{
   Uint8 *keystate = SDL_GetKeyState(NULL);
	 if ( keystate[(*p).keys.attack] )
       (*p).attacking=1;
   if ( keystate[(*p).keys.right] ) 
   {
          if((*p).d==1) 
          { 
             if((*p).speed<20) 
                 (*p).speed+=1+(*p).speed*ACCELERATION;
          }
          else (*p).speed=2;(*p).d=1;(*p).state=walk;
   }
   else if ( keystate[(*p).keys.left] ) 
   {  
      if((*p).d==2) 
      {
        if((*p).speed<20) (*p).speed+=1+(*p).speed*ACCELERATION;
      }
      else (*p).speed=2;(*p).d=2;(*p).state=walk;}

   else {(*p).state=idle;(*p).speed=0;}
   if((*p).d==1)(*p).pos.x+=(*p).speed;
   else (*p).pos.x-=(*p).speed;
   (*p).pos.y-=20*(*p).jump;
   if((*p).d==1)
   (*p).pos.x+=2*(*p).jump*(*p).jump;
   else
   (*p).pos.x-=2*(*p).jump*(*p).jump;
}

void jump_perso(perso *p)
{
  Uint8 *keystate = SDL_GetKeyState(NULL);       
    if(   keystate[SDLK_UP]     ) if((*p).jump ==0) (*p).jump = 1;
    if((*p).jump>0)
    {
       (*p).state=jump;
       if ((*p).jump <4) 
          (*p).jump ++;
       else (*p).jump=-1; 
    } 
    if((*p).jump<0)
    {
       (*p).state=jump;
       if ((*p).jump >-4) 
          (*p).jump --;
       else (*p).jump=0;
    }
}
void jump_perso2(perso *p)
{
  Uint8 *keystate = SDL_GetKeyState(NULL);       
    if(    keystate[SDLK_z]    ) if((*p).jump ==0) (*p).jump = 1;
    if((*p).jump>0)
    {
       (*p).state=jump;
       if ((*p).jump <4) 
          (*p).jump ++;
       else (*p).jump=-1; 
    } 
    if((*p).jump<0)
    {
       (*p).state=jump;
       if ((*p).jump >-4) 
          (*p).jump --;
       else (*p).jump=0;
    }
}
void saut_perso(perso *p)
{
   Uint8 *keystate = SDL_GetKeyState(NULL);
   if ( keystate[SDLK_UP] ) (*p).jump=1;
  if((*p).jump==1)
  {

          (*p).pos_rel.x+=2;
          
          (*p).pos.x=posinit_x;
          (*p).pos.y=posinit_y;

          (*p).pos_rel.y=(-0.04*((*p).pos_rel.x * (*p).pos_rel.x)+100);

          (*p).pos.x = (*p).pos.x + (*p).pos_rel.x+50;
          (*p).pos.y = (*p).pos.y - (*p).pos_rel.y;

          if((*p).pos_rel.x>=50)
          {
              (*p).pos_rel.x =- 50;
              (*p).jump=0;
          }
  
  SDL_Delay(10);
  }

}

void player_in_bounds(perso *p,SDL_Surface *screen)
{
   if((*p).state!=0)
   {
      if ((*p).pos.x<LIM_LEFT) 
         (*p).pos.x=LIM_LEFT;
   if((*p).pos.x>(*screen).w-LIM_RIGHT) (*p).pos.x=(*screen).w-LIM_RIGHT;}
}






