#include "settings.h"
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
void settingsBLOCK(SDL_Surface *ecran , int *volume)
{
int isInsideBox(int x, int y, SDL_Rect pos) {
    if((x > pos.x ) && (x < pos.x+pos.w ) && (y < pos.y+pos.h) && (y > pos.y )) {
        return 1;
    }
    return 0;
}
//declaration

    int menuON = 1;
    int mouseX, mouseY;
    
	int fullHovered = 0 ;
	int windowHovered = 0 ;
		int plusHovered = 0 ;
	int minusHovered = 0 ;
    int displayAlert = 0;
   int hoverSound = 0;
	
    SDL_Surface *menuSBG, *alert,*full,*window,*plus,*minus,*v[6],*screen;
    SDL_Surface *fullHover,*windowHover,*plusHover,*minusHover;
    SDL_Rect posFull,posWindow,posPlus,posMinus,posVolume, posAlert;
    SDL_Event event;

	Mix_Chunk *loading;
//initialisation





    SDL_WM_SetCaption("ESPRIT Under Control", NULL);
    SDL_WM_SetIcon(IMG_Load("./media/game_logo.png"), NULL);

  SDL_Init(SDL_INIT_EVERYTHING);

    ecran = SDL_SetVideoMode(800, 600, 32,SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_RESIZABLE);
    SDL_Surface *menuBG = NULL;
    SDL_Rect posBG;



    full = IMG_Load("./menu/full.png");
    fullHover=IMG_Load("./menu/windowHover.png");
    posFull.x=167;
    posFull.y=408;

    window = IMG_Load("./menu/window.png");
    windowHover=IMG_Load("./menu/fullHover.png");
    posWindow.x=465;
    posWindow.y=408;

	plus=IMG_Load("./menu/plus.png");
	plusHover=IMG_Load("./menu/plusHover.png");
	posPlus.x=220;
	posPlus.y=206;

	minus=IMG_Load("./menu/minus.png");
	minusHover=IMG_Load("./menu/minusHover.png");
	posMinus.x=530;
	posMinus.y=220;
	
    alert = IMG_Load("./menu/alert.png");
    posAlert.x = 608;
    posAlert.y = 141;


	v[1] = IMG_Load("./mnu99/v0.png");
	v[2] = IMG_Load("./mnu99/v25.png");
	v[3] = IMG_Load("./mnu99/v50.png");
	v[4] = IMG_Load("./mnu99/v75.png");
	v[5] = IMG_Load("./mnu99/v100.png");
	posVolume.x=275 ;
	posVolume.y=160;
	




    menuSBG = IMG_Load("./menu/settings_background.png");
    posBG.x = 0;
    posBG.y = 0;


    Mix_Chunk *mouseEffect = Mix_LoadWAV("./menu/hoverSound.wav");    //hover son
    Mix_VolumeChunk(mouseEffect, 100);
    Mix_VolumeMusic(MIX_MAX_VOLUME);
   
 while(menuON == 1) {
displayAlert ++;
        if(displayAlert==100) {displayAlert = 0;}
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    menuON = 0;

                break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        //Pause & resume background music avec le bouton "t"
                        case SDLK_t:
				if(Mix_PausedMusic() == 1) {
                                Mix_ResumeMusic();
                            }
                            else {
                                Mix_PauseMusic();
                            }
				break;
                        // Diminuer le volume avec le bouton p
			 case SDLK_p:
                           (*volume)+=32;
                            if ((*volume) > 128) {
				 (*volume) = MIX_MAX_VOLUME;
                               
                            }Mix_VolumeMusic((*volume));

                            break;

                        // Diminuer le volume avec le bouton m
                        case SDLK_m:
                            (*volume)-=32;
                            if ((*volume) < 0) {
                                (*volume) = 0;
                            }Mix_VolumeMusic((*volume));
     
                            break;
			
	






                    }
                break;
	case SDL_MOUSEMOTION:
                    SDL_GetMouseState(&mouseX, &mouseY);
                    if(isInsideBox(mouseX,mouseY,posFull)==1) {
                        //On joue le son du Hover qu'au début (C-a-d : Si on garde la souris sur le bouton, on ne joue pas le son encore une fois)
                        if(fullHovered == 0) {
                            hoverSound = 1;
                        }
                        fullHovered = 1;
                    } else {
                        fullHovered = 0;
                    }
                    if(isInsideBox(mouseX,mouseY,posWindow)==1) {
                        if(windowHovered == 0) {
                            hoverSound = 1;
                        }
                        windowHovered = 1;
                    } else {
                        windowHovered = 0;
                    }
if(isInsideBox(mouseX,mouseY,posPlus)==1) {
                        if(plusHovered == 0) {
                            hoverSound = 1;
                        }
                        plusHovered = 1;
                    } else {
                        plusHovered = 0;
                    }
if(isInsideBox(mouseX,mouseY,posMinus)==1) {
                        if(minusHovered == 0) {
                            hoverSound = 1;
                        }
                       minusHovered = 1;
                    } else {
                        minusHovered = 0;
                    }
		break;
		
		case SDL_MOUSEBUTTONUP:
                    SDL_GetMouseState(&mouseX, &mouseY);
                    if(isInsideBox(mouseX,mouseY,posFull)==1){
				screen=SDL_SetVideoMode(SCREEN_W,SCREEN_H,32,SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
			ecran=screen;

		
}
		if(isInsideBox(mouseX,mouseY,posWindow)==1){screen=SDL_SetVideoMode(SCREEN_W,SCREEN_H,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
	ecran=screen;}
if(isInsideBox(mouseX,mouseY,posPlus)==1){
(*volume)+=32;
                            if ((*volume) > 128) {
				(* volume) = MIX_MAX_VOLUME;
                               
                            }Mix_VolumeMusic((*volume));}
if(isInsideBox(mouseX,mouseY,posMinus)==1) {                            (*volume)-=32;
                            if  ( (*volume) < 0) {
                               (* volume )= 0;
                            }Mix_VolumeMusic((*volume));}


	
break;
	
	case SDL_KEYUP:
	if(event.key.keysym.sym==SDLK_f)
	screen=SDL_SetVideoMode(SCREEN_W,SCREEN_H,32,SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
	ecran=screen;
	if(event.key.keysym.sym==SDLK_n)
	screen=SDL_SetVideoMode(SCREEN_W,SCREEN_H,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
	ecran=screen;
	break;
            }
        }

        SDL_BlitSurface(menuSBG, NULL, ecran, &posBG);
if(fullHovered == 1) {
            SDL_BlitSurface(fullHover, NULL, ecran, &posFull);
        } else {
            SDL_BlitSurface(full, NULL, ecran, &posFull);
        }
        if(windowHovered == 1) {
            SDL_BlitSurface(windowHover, NULL, ecran, &posWindow);
        } else {
            SDL_BlitSurface(window, NULL, ecran, &posWindow);
        }
if(plusHovered == 1) {
            SDL_BlitSurface(plusHover, NULL, ecran, &posPlus);
        } else {
            SDL_BlitSurface(plus, NULL, ecran, &posPlus);
        }
if(minusHovered == 1) {
            SDL_BlitSurface(minusHover, NULL, ecran, &posMinus);
        } else {
            SDL_BlitSurface(minus, NULL, ecran, &posMinus);
        }

        if(hoverSound==1) {
            Mix_PlayChannel(-1, mouseEffect, 0);
            hoverSound = 0;
        }
	if((*volume) == 0){SDL_BlitSurface(v[1], NULL, ecran, &posVolume);}
	if((*volume) == 32){SDL_BlitSurface(v[2], NULL, ecran, &posVolume);}
	if((*volume) == 64){SDL_BlitSurface(v[3], NULL, ecran, &posVolume);}
	if((*volume) == 96){SDL_BlitSurface(v[4], NULL, ecran, &posVolume);}
	if((*volume) == 128){SDL_BlitSurface(v[5], NULL, ecran, &posVolume);}
 	if(displayAlert<50) {
            SDL_BlitSurface(alert, NULL, ecran, &posAlert);
        }
	
        SDL_Flip(ecran);
    }



}






