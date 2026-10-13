#include <stdio.h>
#include <stdlib.h>
#include "enigme.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <string.h>
#include <time.h>
#include <SDL/SDL_ttf.h>
#include <string.h>

void init_enigmes(int tabl[])
{
    for(int i=0;i<3;i++) {
    tabl[i]=0;
     }
}

int generer_enigme(int tabl[])
{
int j;
srand(time(NULL));
	do
	{
       	   j=rand()%6;
	}
	while (tabl[j]==1);
tabl[j]=1;
return j;
}

int saisir(SDL_Surface *ecran,int numEnigme)
{
SDL_Surface *fonds[9];
	fonds[0] = IMG_Load("enigmes/background1.png");
	fonds[1] = IMG_Load("enigmes/background2.png");
	fonds[2] = IMG_Load("enigmes/background3.png");
	fonds[3] = IMG_Load("enigmes/background4.png");
	fonds[4] = IMG_Load("enigmes/background5.png");
	fonds[5] = IMG_Load("enigmes/background6.png");
	fonds[6] = IMG_Load("enigmes/background7.png");
        fonds[7] = IMG_Load("enigmes/background8.png");
	fonds[8] = IMG_Load("enigmes/background9.png");
int currentBG = 0;

	printf("Indice de l'enigme : %d\n",numEnigme);
	TTF_Init();
	SDL_Surface *fond = NULL;
	SDL_Surface *titre = NULL;
	SDL_Surface *texte=NULL;
	SDL_Event event;

	SDL_Rect positionBG;
	positionBG.x = 0;
	positionBG.y = 0;

	SDL_Rect position;
	position.x = 286;
	position.y = 380;

	SDL_Rect positionTitre;
	positionTitre.x = 125;
	positionTitre.y = 219;
	TTF_Font *police = NULL;
	police = TTF_OpenFont("enigmes/font.ttf",24);

int continuer = 1;
char mot[256]={0};
	SDL_Color couleur={255,255,255};
int z=0;
char line[256];
enigme enigme;
char titreTXT[256];
char reponseTXT[256];

	FILE* titres = fopen("enigmes/enigmes.txt", "r");
int number = 0;
	while (fgets(line, sizeof(line), titres)) {
	if(number == numEnigme) {
	strcpy(titreTXT,line);
	break;
	}
	number++;
    	}
    	number = 0;
    	
	FILE* reponses = fopen("enigmes/reponses.txt", "r");
    while (fgets(line, sizeof(line), reponses)) {
        if(number == numEnigme) {
	strcpy(reponseTXT,line);
	break;
	}
	number++;
    	}

    printf("Titre de l'enigme : %s",titreTXT);
    printf("Reponse de l'enigme : %s",reponseTXT);
fond=IMG_Load("enigmes/background.png");
titre = TTF_RenderText_Blended(police,titreTXT,couleur);
SDL_BlitSurface(fonds[currentBG],NULL,ecran,&positionBG);
SDL_BlitSurface(titre, NULL, ecran, &positionTitre);
SDL_Flip(ecran);

	
while (continuer)
	{
		SDL_PollEvent(&event);
		switch(event.type)
		{
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_RETURN:
						continuer=0;
					break;
					case SDLK_BACKSPACE:
						if(z>0) {
							z--;
							mot[z]='\0';
						}
					break;
				case SDLK_SPACE:
    					mot[z] = ' ';
    					z++;
    					break;
				case SDLK_a:
						mot[z]='a';
						z++;
					break;
				case SDLK_b:
						mot[z]='b';
						z++;
					break;
				case SDLK_c:
						mot[z]='c';
						z++;
					break;
				case SDLK_d:
						mot[z]='d';
						z++;
					break;
				case SDLK_e:
						mot[z]='e';
						z++;
					break;
				case SDLK_f:
						mot[z]='f';
						z++;
					break;
				case SDLK_g:
						mot[z]='g';
						z++;
					break;
				case SDLK_h:
						mot[z]='h';
						z++;
					break;
				case SDLK_i:
						mot[z]='i';
						z++;
					break;
				case SDLK_j:
						mot[z]='j';
						z++;
					break;
				case SDLK_k:
						mot[z]='k';
						z++;
					break;
				case SDLK_l:
						mot[z]='l';
						z++;
					break;
				case SDLK_m:
						mot[z]='m';
						z++;
					break;
				case SDLK_n:
						mot[z]='n';
						z++;
					break;
				case SDLK_o:
						mot[z]='o';
						z++;
					break;
				case SDLK_p:
						mot[z]='p';
						z++;
					break;
				case SDLK_q:
						mot[z]='q';
						z++;
					break;
				case SDLK_r:
						mot[z]='r';
						z++;
					break;
				case SDLK_s:
						mot[z]='s';
						z++;
					break;
				case SDLK_t:
						mot[z]='t';
						z++;
					break;
				case SDLK_u:
						mot[z]='u';
						z++;
					break;
				case SDLK_v:
						mot[z]='v';
						z++;
					break;
				case SDLK_x:
						mot[z]='x';
						z++;
					break;
				case SDLK_y:
						mot[z]='y';
						z++;
					break;
				case SDLK_w:
						mot[z]='w';
						z++;
					break;
				case SDLK_z:
						mot[z]='z';
						z++;
					break;
				case SDLK_KP0:
						mot[z]='0';
						z++;
					break;
				case SDLK_KP1:
						mot[z]='1';
						z++;
					break;
				case SDLK_KP2:
						mot[z]='2';
						z++;
					break;
				case SDLK_KP3:
						mot[z]='3';
						z++;
					break;
				case SDLK_KP4:
						mot[z]='4';
						z++;
					break;
				case SDLK_KP5:
						mot[z]='5';
						z++;
					break;
				case SDLK_KP6:
						mot[z]='6';
						z++;
					break;
				case SDLK_KP7:
						mot[z]='7';
						z++;
					break;
				case SDLK_KP8:
						mot[z]='8';
						z++;
					break;
				case SDLK_KP9:
						mot[z]='9';
						z++;
					break;
				}
			break;
		}
texte = TTF_RenderText_Blended(police,mot,couleur);
SDL_BlitSurface(fonds[currentBG],NULL,ecran,&positionBG);
SDL_BlitSurface(titre, NULL, ecran, &positionTitre);
SDL_BlitSurface(texte, NULL, ecran, &position);
SDL_Flip(ecran);
currentBG++;
if(currentBG==9)
{
currentBG = 0;
}
SDL_Delay(50);
}
printf("Reponse joueur : %s\n",mot);
if(z>0) {
mot[z] = '\0';
reponseTXT[z] = '\0';
}
return strcmp(reponseTXT,mot);
}

