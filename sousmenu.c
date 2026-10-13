

#include<SDL/SDL.h>
#include<stdio.h>
#include<stdlib.h>
#include<SDL/SDL_image.h>
#include<SDL/SDL_ttf.h>
#include"sousmenu.h"


void save(ennemi enn,perso p,perso p2,vie v,vie v2,SDL_Rect camera,int choix,int en1,int enigme1,int enigme2,int temps_joueur,int *LEVEL)
{
saves save;
FILE *f=NULL;
f=fopen("save.bin","wb");
if(f!=NULL)
{
save.LEVEL=(*LEVEL);
save.enn=enn;
save.camera=camera;
save.choix=choix;
save.p1=p;save.v=v;
save.p2=p2;
save.v2=v2;
save.en1=en1;
save.enigme1=enigme1;
save.enigme2=enigme2;
save.temps=temps_joueur;
fwrite(&save,sizeof(saves),1,f);
fclose(f);
}

}

void load(ennemi *enn,perso *p,perso *p2,vie *v,vie *v2,SDL_Rect *camera,int *choix,int *en1,int *enigme1,int *enigme2,int *temps_joueur, int* LEVEL)
{
saves save;
SDL_Color couleur={0,255,0};
char ch[20]; 
FILE *f=NULL;
f=fopen("save.bin","rb");
if(f!=NULL)
{
fread(&save,sizeof(saves),1,f);
(*LEVEL)=save.LEVEL;
enn->pos.x=save.enn.pos.x;
enn->mort=save.enn.mort;
enn->aff=save.enn.aff;
(*choix)=save.choix;
p->pos.x=save.p1.pos.x;
p->pos.y=save.p1.pos.y;   
sprintf(ch,"Score: %d",save.p1.score);

v->num=save.v.num;
p2->pos.x=save.p2.pos.x;
p2->pos.y=save.p2.pos.y;   
sprintf(ch,"Score: %d",save.p2.score);

v2->num=save.v2.num;
camera->x=save.camera.x;
camera->y=save.camera.y;
(*en1)=save.en1;
(*enigme1)=save.enigme1;
(*enigme2)=save.enigme2;
(*temps_joueur)=save.temps;

fclose(f);
}
}

int sousmenu(SDL_Surface *ecran)
{
int continuer=1,b=1;
SDL_Surface *oui=NULL,*non=NULL;

SDL_Event event;
oui=IMG_Load("../rahma/saveyes.png");
non=IMG_Load("../rahma/saveno.png");

while(continuer)
{
SDL_Delay(100);
if(b==1)
{SDL_BlitSurface(oui,NULL,ecran,NULL);SDL_BlitSurface(oui,NULL,ecran,NULL);}
else
{SDL_BlitSurface(non,NULL,ecran,NULL);SDL_BlitSurface(non,NULL,ecran,NULL);}
SDL_Flip(ecran);
SDL_WaitEvent(&event);
switch(event.type)
    {

       case SDL_KEYDOWN:
                             switch(event.key.keysym.sym)
                             {
				 case SDLK_RETURN:  continuer=0;
						    break;
                                 case SDLK_RIGHT: b++;if(b==3) b=1;
						  break;

				 case SDLK_LEFT:  b--;if(b==0) b=2;
						  break;           
     
                             }

    }


}
SDL_FreeSurface(oui);
SDL_FreeSurface(non);

return b;
}
