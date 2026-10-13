#include "Image.h"
#include "settings.h"
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include "perso.h"
#include "enigmea.h"
//#include "serie.h"
#include "enigme.c"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include <time.h>
#include"xo.h"
#include "ennemi.h"
#include"collisionbb.h"
#include "background.h"
#include"sousmenu.h"
//-------------------------------------------
typedef struct{
SDL_Rect pos;
SDL_Surface *is[50],*masque;//imagesbg si il ya une animation
int anim;//numéro image bg
SDL_Rect camera;
}bg;

typedef struct {
    char name[20];
    int score;
} Score;

void init_bg(bg *bg);
void afficher_bg(bg bg,SDL_Surface *screen);
void anim_bg(bg *bg);
void scrolling(bg *bg,int d,int pas);
void bg_in_borders(bg *bg,SDL_Surface *screen);
void animation_bg(bg* bg);
void animation_start(SDL_Surface *screen);
void musique(int stage);

void save_score(Score score);
void show_top_scores(SDL_Surface *screen);

void init_bg(bg *bg)
{
char ch[50];
for(int i=0;i<7;i++)//boucle pour charger les images background
{
sprintf(ch,"images bg/LOL%d.png",i);
bg->is[i] = IMG_Load(ch);
}
bg->pos.x=0;
bg->pos.y=0;
bg->pos.w=bg->is[1]->w;
bg->pos.h=600;
bg->camera.x=0;
bg->camera.y=0;
bg->camera.w=bg->is[1]->w;
bg->camera.h=bg->is[1]->h;
bg->anim=0;
bg->masque=IMG_Load("mask.png");
}

void scrolling(bg *bg,int d,int pas)
{//on scrolle verticalement ou horizontalement
if(d==1) bg->camera.x+=pas;
if(d==2) bg->camera.y+=pas;
}

void bg_in_borders(bg *bg,SDL_Surface *screen) // garder l'image sur l'ecran 
{//ki bsh tokhrej taswira mel ajneb tarja3 
if(bg->camera.x<0) bg->camera.x=0;
if(bg->camera.y<0) bg->camera.y=0;
if(bg->camera.x>bg->camera.w-screen->w) bg->camera.x=bg->camera.w-screen->w;
if(bg->camera.y>bg->camera.h-screen->h) bg->camera.y=bg->camera.h-screen->h;
}

void afficher_bg(bg bg,SDL_Surface *screen)
{
SDL_BlitSurface(bg.is[bg.anim],&bg.camera,screen,NULL);
//image,shnowa bsh taffichi menha,3la shnowa bsh tafficheha,win bsh tafficheha
}

void animation_bg(bg* bg)
{
bg->anim++;
if(bg->anim==7){bg->anim=0;}
}

void animation_start(SDL_Surface *screen)
{//animation début
//principe enou taswiret lbackground loula tji mel yssar lel ymin 9bal ma tebda jeu
SDL_Surface *image;
image= IMG_Load("images bg/LOL0.png");
SDL_Rect pos;pos.x=screen->w+1000;pos.y=0;
SDL_Delay(500);//pause 0.5 secondes
while(pos.x>10)
{
SDL_BlitSurface(image,NULL,screen,&pos);
pos.x-=10;
SDL_Flip(screen);//actualiser
}
}

void musique(int stage)
{
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);//initialisation audio
	Mix_Music *musique; //Création du pointeur de type Mix_Music
    char nom_musique[40];
	sprintf(nom_musique,"musiques/%d.mp3",stage); 
	musique = Mix_LoadMUS(nom_musique); //Chargement de la musique
    Mix_PlayMusic(musique, -1);//-1:boucle infinie
	Mix_VolumeMusic(128);
}

void save_score(Score score) {
    FILE *fp;
    fp = fopen("score.txt", "a");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }
    fprintf(fp, "%s %d\n", score.name, score.score);
    fclose(fp);
}

void show_top_scores(SDL_Surface *screen) {
    TTF_Font *font;
    SDL_Color textColor = {255, 255, 255}; // White color
    SDL_Surface *textSurface;
    SDL_Rect textPos;
    char scoreStr[30];
    Score scores[100] = {0};
    int i, j;
    FILE *fp;

    // Load the font
    font = TTF_OpenFont("font.ttf", 28);
    if (font == NULL) {
        printf("Error opening font\n");
        return;
    }

    // Read the scores from the file
    fp = fopen("score.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }
    for (i = 0; i < 100; i++) {
        if (fscanf(fp, "%s %d", scores[i].name, &scores[i].score) == EOF) {
            break;
        }
    }
    fclose(fp);
    // Sort the scores in descending order
    for (i = 0; i < 99; i++) {
        for (j = i+1; j < 100; j++) {
            if (scores[j].score > scores[i].score) {
                Score temp = scores[i];
                scores[i] = scores[j];
                scores[j] = temp;
            }
        }
    }

    // Display the top 3 scores on screen
    for (i = 0; i < 3; i++) {
        sprintf(scoreStr, "%d. %s: %d", i+1, scores[i].name, scores[i].score);
        textSurface = TTF_RenderText_Solid(font, scoreStr, textColor);
        textPos.x = (screen->w - textSurface->w) / 2;
        textPos.y = 50 + i * 50;
        SDL_BlitSurface(textSurface, NULL, screen, &textPos);
        SDL_FreeSurface(textSurface);
    }
SDL_Flip(screen);SDL_Delay(1500);
    TTF_CloseFont(font);
}


void deplacement(SDL_Rect position_hero,SDL_Rect camera, SDL_Rect * position_mini_joueur) {
    // Calculate the ratio between the main map and mini map dimensions
    float ratio_x = 3000.0 / 300.0;
    float ratio_y = 600.0 / 150.0;

    // Update the position of the mini player based on the main player's position
    (*position_mini_joueur).x = (camera.x / ratio_x)+490;
    (*position_mini_joueur).y = position_hero.y / ratio_y;
}



////////////////////////////                          collision p b
Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        return *(Uint32 *)p;
        break;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}


int collisionpb(SDL_Rect poshero,bg bg)
{
Uint32 noir = SDL_MapRGB(bg.masque->format,0,0,0);
if(getpixel(bg.masque,bg.camera.x+poshero.x,poshero.y+124) == noir)
{
return 1;
}
else
return 0;
}

//////////////////////////////////////
Uint32 getpixel1(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        return *(Uint32 *)p;
        break;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}


int collisionlvl3(SDL_Rect poshero,background b)
{
Uint32 noire = SDL_MapRGB(b.masque->format,0,0,0);
if(getpixel1(b.masque,b.camera.x+poshero.x,poshero.y+124) == noire)
{
return 1;
}
else
return 0;
}

//-------------------------------------
int main (int argc,char** argv)
{
int one_time_xo=0;
int LEVEL=1;
/*
    char buffer[100];                   // un buffer
    int i;
    uint8_t val1='1';
    uint8_t val2='2';
uint8_t val3='3';
uint8_t val4='4';
    // ouverture du port à 9600 bauds
    int fd = serialport_init("/dev/ttyACM0", 9600);
    if (fd==-1) return -1;
*/

SDL_Surface *mask=IMG_Load("images bg/mask.png");





int isInsideBox(int x, int y, SDL_Rect pos) {
    if((x > pos.x ) && (x < pos.x+pos.w ) && (y < pos.y+pos.h) && (y > pos.y )) {
        return 1;
    }
    return 0;
}

//declaration

    int menuON = 1;
    int mouseX, mouseY;
    int displayAlert = 0;
    int playHovered = 0;
    int hoverSound = 0;
    int settingsHovered = 0;
    int creditsHovered = 0;
    int exitHovered = 0;
	int fullHovered = 0 ;
	int windowHovered = 0 ;
		int plusHovered = 0 ;
	int minusHovered = 0 ;
	
    SDL_Surface *menuBG , *play, *settings, *credits, *exit, *alert,*menuSBG,*menuPBG,*t[13],*logo,*full,*window,*plus,*minus,*v[6];
    SDL_Surface *playHover, *settingsHover, *creditsHover, *exitHover,*fullHover,*windowHover,*plusHover,*minusHover;
    SDL_Rect posBG, posPlay, posSettings, posCredits, posExit, posAlert,posLogo,posFull,posWindow,posPlus,posMinus,posVolume;
    SDL_Event event;
    SDL_Surface *screen;
	SDL_Surface *ecran;
	Mix_Chunk *loading;

enigmea enig;
enigme e;
int tabl[] = {0,0,0,0,0,0};


//initialisation
    SDL_Init(SDL_INIT_EVERYTHING);
    // Initialisation TTF
    if (TTF_Init() < 0) {
        fprintf(stderr, "Unable to init TTF");
        return 1;
    }
//texte
 // Chargement de la police de caractères
    TTF_Font *font = TTF_OpenFont("angelina.TTF", 50);
 // Vérification du chargement de la police de caractères
    if (!font) {
        printf("Erreur de chargement de la police de caractères : %s\n", TTF_GetError());
        return 1;
    }
// Création du texte
    SDL_Color color = { 255, 255, 255 };  // Couleur du texte en blanc
    SDL_Surface *text = TTF_RenderText_Solid(font, "Click Or Diy", color);
 // Vérification de la création du texte
    if (!text) {
        printf("Erreur de création du texte : %s\n", TTF_GetError());
        return 1;
    }
// Positionnement du texte dans la fenêtre
    SDL_Rect text_position;
    text_position.x = 600;
    text_position.y = 540;



//son

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) {
        printf("%s",Mix_GetError());
    }
    Mix_Music *musicBG;
    musicBG = Mix_LoadMUS("./menu/backgroundMusic.mp3");
    Mix_PlayMusic(musicBG, -1);

    Mix_AllocateChannels(10);
    Mix_Chunk *mouseEffect = Mix_LoadWAV("./menu/hoverSound.wav");
    Mix_VolumeChunk(mouseEffect, 100);
    Mix_Chunk *elec = Mix_LoadWAV("Electric.wav");
    Mix_VolumeChunk(elec, 100);
 Mix_Chunk *laser = Mix_LoadWAV("laser.wav");
    Mix_VolumeChunk(laser, 100);
Mix_Chunk *damage = Mix_LoadWAV("damage.wav");
    Mix_VolumeChunk(damage, 100);
    Mix_VolumeMusic(MIX_MAX_VOLUME);


 int volume = MIX_MAX_VOLUME / 2;

// creation d une fenetre 

    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        fprintf( stderr, "Unable to init SDL" );
        return 1;
    }

    screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32,SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_SRCALPHA);
	ecran=screen;
    if ( !screen )
    {
        fprintf(stderr, "Unable to set /n");
        return 1;
    }

    SDL_WM_SetCaption("ESPRIT Under Control", NULL);
    SDL_WM_SetIcon(IMG_Load("./media/game_logo.png"), NULL);


//affichage
    menuBG = IMG_Load("./menu animee/menu4.png");
    posBG.x =0;
    posBG.y =0;

    logo=IMG_Load("./media/logo.png");
	posLogo.x=420;
	posLogo.y=200;


    play = IMG_Load("./menu/play.png");
    playHover = IMG_Load("./menu/playHover.png");
    posPlay.x =300;
    posPlay.y = 211;
    posPlay.h = 45;
    posPlay.w = 218;

    settings = IMG_Load("./menu/settings.png");
    settingsHover = IMG_Load("./menu/settingsHover.png");
    posSettings.x = 300;
    posSettings.y = 264;

    credits = IMG_Load("./menu/credits.png");
    creditsHover = IMG_Load("./menu/creditsHover.png");
    posCredits.x = 300;
    posCredits.y = 323 ;

    exit = IMG_Load("./menu/exit.png");
    exitHover = IMG_Load("./menu/exitHover.png");
    posExit.x = 300;
    posExit.y = 376;


	
	t[1] = IMG_Load("./mnu99/11.png");
	t[2] = IMG_Load("./mnu99/10.png");
	t[3] = IMG_Load("./mnu99/9.png");
	t[4] = IMG_Load("./mnu99/8.png");
	t[5] = IMG_Load("./mnu99/7.png");
	t[6] = IMG_Load("./mnu99/6.png");
	t[7] = IMG_Load("./mnu99/5.png");
	t[8] = IMG_Load("./mnu99/4.png");
	t[9] = IMG_Load("./mnu99/3.png");
	t[10] = IMG_Load("./mnu99/2.png");
	t[11] = IMG_Load("./mnu99/1.png");
	t[12] = IMG_Load("./mnu99/0.png");



SDL_Surface *fonds[9];
	fonds[0] = IMG_Load("enigmes/a1.png");
	fonds[1] = IMG_Load("enigmes/a2.png");
	fonds[2] = IMG_Load("enigmes/a3.png");
	fonds[3] = IMG_Load("enigmes/a4.png");
	fonds[4] = IMG_Load("enigmes/a5.png");
	fonds[5] = IMG_Load("enigmes/a6.png");
	fonds[6] = IMG_Load("enigmes/a7.png");
        fonds[7] = IMG_Load("enigmes/a8.png");
	fonds[8] = IMG_Load("enigmes/a9.png");
int currentBG = 0;

	
	TTF_Init();
	SDL_Surface *fond = NULL;
	SDL_Surface *titre = NULL;
	SDL_Surface *texte=NULL;
	

	SDL_Rect positionBGnom;
	positionBGnom.x = 0;
	positionBGnom.y = 0;

	SDL_Rect position;
	position.x = 286;
	position.y = 380;

	SDL_Rect positionTitre;
	positionTitre.x = 125;
	positionTitre.y = 219;
	TTF_Font *police = NULL;
	police = TTF_OpenFont("enigmes/font.ttf",24);

int poop = 1;
char mot[256]={0};
	SDL_Color couleur={0,0,0};
int z=0;
char line[256];
enigme enigme;
char titreTXT[256];
char reponseTXT[256];
SDL_Rect positionBGE;

		
//player
   perso p1;
   init_perso(&p1);
   init_perso_controls(&p1);

//enigme


 int condition_aff_enigme=0;
int a=0;
int contine=1;
enig.affiche=0;
init_enigme(&enig,"fichier.txt");
int time_1=0;
int www=0;
int animation=0;



	bg bg,bg2;
init_bg(&bg);

  SDL_Rect button_rect = { 10, 10, 0, 0 };
    SDL_Color textColor = {255, 255, 255};
    SDL_Surface* button_surface = TTF_RenderText_Solid(TTF_OpenFont("font.ttf", 32),"Show Scores",textColor);
    SDL_Surface *fondVrai;
    SDL_Surface *fondFaux;
    fondVrai = IMG_Load("enigmes/backgroundVrai.png");
    fondFaux = IMG_Load("enigmes/backgroundFaux.png");
init_enigmes(tabl);
SDL_Surface *sss,*ttt,*ss,*tt;
SDL_Rect ppp,pp;
ppp.x=400;
ppp.y=350;
pp.x=600;
pp.y=350;
sss=IMG_Load("./enigme/loo.png");
ttt=IMG_Load("./enigme/looo.png");

ss=IMG_Load("./enigme/loo.png");
tt=IMG_Load("./enigme/looo.png");

///////////////////////



SDL_Surface *choose_ur_player1,*choose_ur_player2,*choose_ur_player6,*choose_ur_player7,*choose_ur_player8,*choose_ur_player9;
choose_ur_player1=IMG_Load("./x1.png");
choose_ur_player2=IMG_Load("./x2.png");

choose_ur_player6=IMG_Load("./x6.png");
choose_ur_player7=IMG_Load("./x7.png");
choose_ur_player8=IMG_Load("./x8.png");
choose_ur_player9=IMG_Load("./x9.png");
int cond_choose_player=0;

int scoree=100;
int prs2=0;
int time_11=0;
int plz=0;
SDL_Rect player1,player2;
player1.x=200;
player1.y=280;
player1.w=200;
player1.h=200;

player2.x=430;
player2.y=280;
player2.w=200;
player2.h=200;

int show=1;
int anim_prs2=0;
int moom=0;
xo tic;
init(&tic);
       	 int x=0; 


int animation_mini=0;
SDL_Surface *minii[9];
minii[0]=IMG_Load("mini.png");
minii[1]=IMG_Load("mini1.png");
minii[2]=IMG_Load("mini2.png");
minii[3]=IMG_Load("mini3.png");
minii[4]=IMG_Load("mini4.png");
minii[5]=IMG_Load("mini5.png");
minii[6]=IMG_Load("mini6.png");
SDL_Rect posMini;
posMini.x=500;
posMini.y=0;

SDL_Surface *miniPlayer=IMG_Load("minijoueur.png");
SDL_Rect posMiniPlayer;
posMiniPlayer.x=470;
posMiniPlayer.y=110;
/*
int a_m_2=0;
SDL_Surface *minilvl_2[6];
minilvl_2[0]=IMG_Load("minilvl2_1.jpg");
minilvl_2[1]=IMG_Load("minilvl2_1.jpg");
minilvl_2[2]=IMG_Load("minilvl2_1.jpg");
minilvl_2[3]=IMG_Load("minilvl2_1.jpg");
minilvl_2[4]=IMG_Load("minilvl2_5.jpg");
minilvl_2[5]=IMG_Load("minilvl2_5.jpg");
*/


int mpmp=0;












SDL_Surface *next_level=IMG_Load("next_level.png");
SDL_Surface *looser=IMG_Load("gameover.png");
SDL_Rect nl;
nl.x=0;
nl.y=0;

int reglage=0;

ennemi enn;
   init_ennemi(&enn);
   enn.etat_ennemi=waiting; 

SDL_Surface *green=IMG_Load("grn.png");

bg2.is[0]=IMG_Load("1.jpg");
bg2.is[1]=IMG_Load("2.jpg");
bg2.is[2]=IMG_Load("3.jpg");
bg2.is[3]=IMG_Load("4.jpg");
bg2.is[4]=IMG_Load("5.jpg");
bg2.is[5]=IMG_Load("6.jpg");
bg2.is[6]=IMG_Load("7.jpg");
bg2.is[7]=IMG_Load("8.jpg");
bg2.is[8]=IMG_Load("9.jpg");
bg2.is[9]=IMG_Load("10.jpg");

bg2.pos.x=0;
bg2.pos.y=0;
bg2.camera.x=0;
bg2.camera.y=0;
bg2.camera.w=bg2.is[0]->w-200;
bg2.camera.h=bg2.is[0]->h;
bg2.anim=9;

 SDL_Surface *iimage;
iimage= IMG_Load("1.jpg");
int khsert=0;
int time_111=0;
int h_a_e=0;
int e_met=0;
SDL_Surface *ani_die=IMG_Load("hihihi.png");


    background b;
initialisation_back(&b);
int xxx=0;

int ch[50];




 


























			
int ppllrr=0;
int ani=0;
int c_a_i=0;
int dam=0;


vie v2;

SDL_Surface *msk=NULL;









   perso p2;
   init_perso(&p2);
   p2.pos.x=400;
   init_perso_controls_p2(&p2);

ennemi enn1,enn2;
init_ennemi(&enn1);
   enn1.etat_ennemi=waiting;
init_ennemi(&enn2);
   enn2.etat_ennemi=waiting; 

SDL_Surface *cadre=IMG_Load("cadre.png");
SDL_Rect posC;
posC.x=0;
posC.y=0;

SDL_Surface *endgame=IMG_Load("endgame.png");
SDL_Rect pE;
pE.x=pE.y=0;
int certain_x_coordinate=0;
Score score;
int savy=0;
vie v1;


SDL_Surface *savo1=IMG_Load("SAVE1.png");
SDL_Surface *savo2=IMG_Load("SAVE2.png");
SDL_Surface *savo3=IMG_Load("SAVE3.png");
SDL_Rect psavo;
psavo.x=psavo.y=0;
int old_new=0;
SDL_Rect new_game,old_game;
old_game.x=500;
old_game.y=404;
old_game.w=200;
old_game.h=100;

new_game.x=170;
new_game.y=404;
new_game.w=200;
new_game.h=100;

SDL_Surface *p=IMG_Load("p.png");
SDL_Rect ppos;
ppos.x=355;
ppos.y=33;
ppos.w=70;
ppos.h=70;
SDL_Surface *pause_y=IMG_Load("yn.png");
SDL_Surface *pause_n=IMG_Load("saveno.png");
SDL_Rect paus;
paus.x=-50;
paus.y=50;
int poz=0;
SDL_Rect py,pn;
py.x=315;
py.y=305;
py.w=50;
py.h=50;

pn.x=340;
pn.y=305;
pn.w=50;
pn.h=50;
int nono=0;




SDL_Surface *h1,*h2,*h3;
h1=IMG_Load("image 1.png");
h2=IMG_Load("image 2.png");
h3=IMG_Load("image 3.png");
SDL_Rect hhh;
hhh.x=hhh.y=0;
    while(menuON == 1) {

/*			
	    for ( ; ; ){
        //  lecture d'une ligne
        serialport_read_until(fd, buffer, '\r', 99, 10000);

        // suppression de la fin de ligne
        for (i=0 ; buffer[i]!='\r' && i<100 ; i++);
        buffer[i] = 0;
         if(strstr(buffer,"right"))
         {
        // écriture du résultat
        printf("right \n");
        serialport_writebyte(fd,val1);
         }
         if(strstr(buffer,"left"))
         {
        // écriture du résultat
        printf("left \n");
        serialport_writebyte(fd,val2);
         }
// suppression de la fin de ligne
        for (i=0 ; buffer[i]!='\r' && i<100 ; i++);
        buffer[i] = 0;
         if(strstr(buffer,"up"))
         {
        // écriture du résultat
        printf("up \n");
        serialport_writebyte(fd,val3);
// suppression de la fin de ligne
        for (i=0 ; buffer[i]!='\r' && i<100 ; i++);
        buffer[i] = 0;
         if(strstr(buffer,"down"))
         {
        // écriture du résultat
        printf("down \n");
        serialport_writebyte(fd,val4);
    }
*/




if(khsert==1){;SDL_BlitSurface(looser,NULL,ecran,&nl); SDL_Flip(ecran);SDL_Delay(1000); LEVEL=1;khsert=0;time_111=0;p1.pos.x=50;bg.camera.x=0;bg2.camera.x=0;}

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
                        //Pause & resume background music avec le bouton "P"
                        case SDLK_p:
                            if(Mix_PausedMusic() == 1) {
                                Mix_ResumeMusic();
                            }
                            else {
                                Mix_PauseMusic();
                            }
                        break;
                    }
                break;
                case SDL_MOUSEBUTTONUP:
                    SDL_GetMouseState(&mouseX, &mouseY);
                    if(isInsideBox(mouseX,mouseY,posPlay)==1){
///////////////////////////////////////////				block play

int iw=0;
while(old_new==0)
{
SDL_BlitSurface(savo1,NULL,ecran,&psavo);
if(iw==2){SDL_BlitSurface(savo2,NULL,ecran,&psavo);}
if(iw==3){SDL_BlitSurface(savo3,NULL,ecran,&psavo);}
SDL_Flip(ecran);
while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    old_new =1;
                break;

                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        //Pause & resume background music avec le bouton "P"
                       
                    }
                break;
                case SDL_MOUSEBUTTONUP:
                    SDL_GetMouseState(&mouseX, &mouseY);
                    if(isInsideBox(mouseX,mouseY,new_game)==1) {old_new=1;}
		   if(isInsideBox(mouseX,mouseY,old_game)==1) {LEVEL=3; old_new=1;

FILE *f=fopen("save_me","r");
if(f==NULL){printf("erreur");}
	if(f!=NULL){



    
    fscanf(f,"%d",&LEVEL);LEVEL=3;}

   





}
			break;
			 case SDL_MOUSEMOTION:
                    SDL_GetMouseState(&mouseX, &mouseY);
		
		   if(isInsideBox(mouseX,mouseY,old_game)==1) {Mix_PlayChannel(-1, mouseEffect, 0);}
		if(isInsideBox(mouseX,mouseY,new_game)==1) {Mix_PlayChannel(-1, mouseEffect, 0);}
			if( isInsideBox(mouseX,mouseY,old_game)==0  && isInsideBox(mouseX,mouseY,new_game)==1 ) {iw=2;}
if( isInsideBox(mouseX,mouseY,old_game)==1  && isInsideBox(mouseX,mouseY,new_game)==0 ) {iw=3;}
if( isInsideBox(mouseX,mouseY,old_game)==0  && isInsideBox(mouseX,mouseY,new_game)==0 ) {iw=0;}

			break;
	     }break;
	  }
      
}
			



    

    

  
 



//---------------------------

	
while (poop)
	{
		SDL_PollEvent(&event);
		switch(event.type)
		{
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_RETURN:
						poop=0;
					break;
					case SDLK_BACKSPACE:
						if(z>0) {z--;mot[z]='\0';}
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
SDL_BlitSurface(fonds[currentBG],NULL,ecran,&positionBGnom);

SDL_BlitSurface(texte, NULL, ecran, &position);
SDL_Flip(ecran);
currentBG++;
if(currentBG==9){currentBG = 0;}
SDL_Delay(40);
}

SDL_Flip(ecran);
SDL_BlitSurface(h1,NULL,ecran,&hhh);
SDL_Flip(ecran);
SDL_Delay(5000);
//------------------------------

animation_start(screen);

musique(1);
  reglage=1;
	button_rect.w = button_surface->w;
    button_rect.h = button_surface->h;
// riri

SDL_EnableKeyRepeat(60,60);


    positionBGE.x = 0;
    positionBGE.y = 0;

// animation enigme
//////////////////////////////////////////////////////////////////////////////////////////////
/*
while (savy==0){

printf("1 save 2 load \n");
scanf("%d",&savy);
if(savy==1){
save(enn,p1,p2,v1,v2,bg.camera,0,0,0,0,0,&LEVEL);}
if(savy==2){
LEVEL=3;
load(&enn,&p1,&p2,&v1,&v2,&bg.camera,0,0,0,0,0,&LEVEL);
}

}
*/
//////////////////////////////////////////////////////////////


///////////////////////// start lvl1
if(LEVEL==1){
while(LEVEL==1) 
{







certain_x_coordinate=p1.pos.x;

if (p1.pos.x >= certain_x_coordinate) {
    score.score++;
}

if(collisionpb(p1.pos,bg)==1){      Mix_PlayChannel(-1, elec, 0);SDL_Delay(500);p1.pos.x=p1.pos.x-50;bg.camera.x=bg.camera.x-100;p1.v.num++;}
if(p1.v.num>=5){SDL_Delay(400);p1.v.num=0;khsert=1;LEVEL=0;}





www++;

if(p1.pos.x >=  400) {
p1.pos.x=400;
}


//---------------------


  if( (bg.camera.x>2150) )
{ 


p1.pos.x=0;
bg.camera.x=0;
moom=0;
for (int iii=0;iii<3;iii++)for (int jjj=0;jjj<3;jjj++)
{tic.i[iii][jjj]=-1;
tic.r[iii][jjj].x=217*iii+40;
tic.r[iii][jjj].y=217*jjj+40;
tic.turn=rand()%2;
tic.choixx=0;
tic.choixy=0;
}
while(moom==0 )
{
quitgame(&moom, tic);
SDL_PumpEvents();
if (tic.turn == 0) change(&tic);
        ia2(&tic);
        if (winner_is(tic) != -1) 
        {
            showme(tic, screen);
            SDL_Flip(screen);
            SDL_Delay(1000);
            moom = 1;  // Set q to 1 to break out of the loop
        }
        else {showme(tic, screen);}

}

LEVEL=2;

}

//-------------------



	
		 if(condition_aff_enigme ==1){ plz=1;  }
	if(a==1){afficher_resultat(ecran,enig,&scoree);SDL_Delay(1000); enig.affiche=0;plz=0; condition_aff_enigme=0; init_enigme(&enig,"fichier.txt");a=0;}
	//SDL_BlitSurface(menuPBG, NULL, ecran, &posBG);
	SDL_PumpEvents();
     animation_bg(&bg);
bg_in_borders(&bg,screen);
afficher_bg(bg,screen);

if(reglage==1){
SDL_BlitSurface(minii[animation_mini],NULL,screen,&posMini);
animation_mini++;
if(animation_mini>=6){animation_mini=0;}
SDL_BlitSurface(miniPlayer,NULL,ecran,&posMiniPlayer);
deplacement(p1.pos,bg.camera,&posMiniPlayer);}
//SDL_BlitSurface(mask,NULL,screen,&bg.pos);
SDL_BlitSurface(button_surface, NULL, screen, &button_rect);


		if(p1.pos.x >= 380 && p1.pos.x <= 420   && time_1==0  &&  1==0 ){ condition_aff_enigme=1;time_1=1;p1.pos.x=200;}

	if(plz==1){afficher_enigme(enig,screen,&animation) ; p1.pos.x=100;}
//prsooo hero
     if(show==1){ afficher_perso(p1,screen);
      afficher_score_vie(p1,screen,0);
      animer_perso(&p1);
      deplacer_perso(&p1);
      player_in_bounds(&p1,screen);
      jump_perso(&p1);
	
}

//affichage second person
      
/////////
if(show==1 && prs2==1){

afficher_perso(p2,screen);
afficher_score_vie(p2,screen,1);
animer_perso(&p2);
deplacer_perso(&p2);
player_in_bounds(&p2,screen);
jump_perso(&p2);


}  


        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    menuON = 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.x >= button_rect.x && event.button.x < button_rect.x + button_rect.w &&
                    event.button.y >= button_rect.y && event.button.y < button_rect.y + button_rect.h) {
                    show_top_scores(screen);
                }break;
		 case SDL_MOUSEBUTTONUP:
		SDL_GetMouseState(&mouseX, &mouseY);
		if(isInsideBox(mouseX,mouseY,ppos)==1)
{
//////////
	FILE *f=fopen("save_me","r");
poz=1;
while(poz==1)
{
while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
		case SDL_KEYDOWN:
		
		switch(event.key.keysym.sym)
                    {
		case SDLK_y:
		if(f==NULL){printf("erreur");}
		if(f!=NULL){
		fprintf(f,"%d",LEVEL);poz=0;} 
		break;
		case SDLK_n:
			poz=0;
		break;}
	    }break;

	}
SDL_BlitSurface(pause_y,NULL,ecran,&paus);

SDL_Flip(ecran);






}






////////////
}
			break;
                case SDL_KEYDOWN:
		if ( condition_aff_enigme == 1 ) {scan_reponse(&enig,event);  }
				if(enig.affiche == 1  ){a=1;};
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
			 case SDLK_m:
				
		prs2=1;
					break;

                case SDLK_LEFT:
                    scrolling(&bg,1,-20);
                    break;
                case SDLK_RIGHT:
                    scrolling(&bg,1,20);
                    break;
                case SDLK_q:
                   if(prs2==1) scrolling(&bg,1,-20);
                    break;
                case SDLK_d:
                    if (prs2==1) scrolling(&bg,1,20);
                    break;
		
                    }
                break;
            }
        }
        
     
if(poz==0){SDL_BlitSurface(p,NULL,ecran,&ppos);}



	   SDL_Flip(ecran);

	SDL_Delay(50);

strcpy(score.name,mot);

save_score(score);


    }
/////////////////end boucle  lvl 1
//////////////////////////////////////////////////////////////
}
///////////////////start lvl2
if(LEVEL==2){

cond_choose_player=0;
p1.pos.x=0;
bg2.camera.x=0;


SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    int x7x7 = -next_level->w; // position initiale de l'image en dehors de l'écran
    SDL_Rect destRect;
	int u=0;
    // boucle de jeu pour animer la translation de l'image
    while ( (u!=150)) {
	u++;
        // effacer l'écran
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

        // mise à jour de la position de l'image
        x7x7 += 10; // ajustez cette valeur pour contrôler la vitesse de translation
       
        destRect.x = x7x7;
        destRect.y = (ecran->h - enig.imagewin->h) / 2;

        // affichage de l'image en fonction de la réponse de l'utilisateur
        
            SDL_BlitSurface(next_level, NULL, ecran, &destRect);
        

        // mise à jour de l'affichage
        SDL_Flip(ecran);

        // pause pour limiter le taux de rafraîchissement
        SDL_Delay(10);
	
    }

SDL_Flip(ecran);
SDL_BlitSurface(h2,NULL,ecran,&hhh);
SDL_Flip(ecran);
SDL_Delay(5000);
musique(3);

SDL_Rect pos;pos.x=screen->w+1000;pos.y=0;
SDL_Delay(500);//pause 0.5 secondes
while(pos.x>10)
{

SDL_BlitSurface(iimage,NULL,screen,&pos);
pos.x-=10;
SDL_Flip(screen);//actualiser
}
bg2.anim=0;
while( LEVEL==2) 
{
//


		if(e_met==1&  bg2.camera.x>5200  && time_1==0 ){ condition_aff_enigme=1;time_1=1;p1.pos.x=200;}
 if(condition_aff_enigme ==1){ plz=1;  }

	if(a==1){afficher_resultat(ecran,enig,&scoree);SDL_Delay(100); enig.affiche=0;plz=0; condition_aff_enigme=0; init_enigme(&enig,"fichier.txt");a=0;p1.v.num=0;






/*
while(cond_choose_player == 0)
{
anim_prs2++;
show=0;
if(anim_prs2>0){SDL_BlitSurface(choose_ur_player1,NULL,ecran,NULL);}
if(anim_prs2>10){SDL_BlitSurface(choose_ur_player2,NULL,ecran,NULL);}
if(anim_prs2>20){SDL_BlitSurface(choose_ur_player6,NULL,ecran,NULL);}
if(anim_prs2>30){SDL_BlitSurface(choose_ur_player7,NULL,ecran,NULL);}
if(anim_prs2>40){SDL_BlitSurface(choose_ur_player8,NULL,ecran,NULL);}
if(anim_prs2>50){SDL_BlitSurface(choose_ur_player9,NULL,ecran,NULL);}

if(anim_prs2>60){anim_prs2=0;}
  while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
		case SDL_QUIT:
                    cond_choose_player = 0;
                break;		

		case SDL_MOUSEBUTTONUP:
                    SDL_GetMouseState(&mouseX, &mouseY);
                    if(isInsideBox(mouseX,mouseY,player1)==1){ppllrr=5;cond_choose_player=1;}	
			                                                
	    
		    if(isInsideBox(mouseX,mouseY,player2)==1){ppllrr=6;cond_choose_player=1;}	
     
            }
 break;   

        }
SDL_Flip(ecran);
}

*/





LEVEL=3;

}













//

//////// condition enigme riri
	if(  collision(p1.pos,&enn)==1 && (time_11==0) && c_a_i==1 )
{

if(saisir(screen,generer_enigme(tabl))==0){//reponse vrai 

        SDL_BlitSurface(fondVrai,NULL,screen,&positionBGE);
 SDL_Flip(ecran);
	SDL_Delay(1200);
        printf("Vrai !\n");

    } else {

        SDL_BlitSurface(fondFaux,NULL,screen,&positionBGE);
 SDL_Flip(ecran);
SDL_Delay(1200);

        printf("Faux !\n");
}

time_11=1;
p1.v.num=0;

}
/////////////








if(p1.v.num==5){}
afficher_score_vie( p1,screen,7);
if(collision(p1.pos,&enn)==1){dam++;}
if(p1.v.num>=5){SDL_Delay(400);p1.v.num=0;khsert=1;LEVEL=0;c_a_i=0;}
	if(dam>30 && c_a_i==1){p1.v.num++;dam=0;}
if(p1.v.num>=5){SDL_Delay(400);p1.v.num=0;khsert=1;LEVEL=0;c_a_i=0;}
	
SDL_Delay(50);
ani++;
if(p1.pos.x >=  550) {p1.pos.x=550;}
if( (bg2.camera.x>2400) && time_111==0){c_a_i=1;time_111=1;}
//////bg
//SDL_BlitSurface(bg2.is[0],&bg2.camera,screen,NULL);
animation_bg(&bg2);

afficher_bg(bg2,screen);
/*SDL_BlitSurface(minilvl_2[a_m_2],NULL,screen,&posMini);
animation_mini++;
if(a_m_2>=5){a_m_2=0;}
SDL_BlitSurface(miniPlayer,NULL,ecran,&posMiniPlayer);
deplacement(p1.pos,bg2.camera,&posMiniPlayer);*/
bg_in_borders(&bg2,ecran);
if(bg2.camera.x>bg2.camera.w-screen->w-200){ bg2.camera.x=bg2.camera.w-screen->w-200;}

////////prs

afficher_perso(p1,screen);
      afficher_score_vie(p1,screen,0);
      animer_perso(&p1);
      deplacer_perso(&p1);
      player_in_bounds(&p1,screen);
      jump_perso(&p1);
SDL_BlitSurface(p1.v.vi[p1.v.num],NULL,screen,&p1.v.pos);

/// ennemi 
 
while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
		case SDL_QUIT:
                    LEVEL = 0;
                break;
		case SDL_MOUSEBUTTONDOWN:
                if (event.button.x >= button_rect.x && event.button.x < button_rect.x + button_rect.w &&
                    event.button.y >= button_rect.y && event.button.y < button_rect.y + button_rect.h) {
                    show_top_scores(screen);
                }
		case SDL_KEYDOWN:
		if ( condition_aff_enigme == 1 ) {scan_reponse(&enig,event);  }
				if(enig.affiche == 1  ){a=1;};
		switch(event.key.keysym.sym)
                    {
		case SDLK_d:
                    LEVEL=3;
                break;
		case SDLK_LEFT:
                    scrolling(&bg2,1,-20);
                    break;
                case SDLK_RIGHT:
                    scrolling(&bg2,1,20);
                    break;
		case SDLK_SPACE:
			 Mix_PlayChannel(-1, laser, 0);
		break;
		   }
	     }
	}	
//bg2.camera.x+=20;

 if(c_a_i==1){animer_ennemi(screen,&enn,p1.pos);   } 
if( ( p1.attacking>0)  && enn.pos.x-p1.pos.x<=100 && c_a_i==1 ){h_a_e++;}
if(h_a_e>30){c_a_i=0;h_a_e=0;e_met=1;


SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
int x7x7 = ecran->w; // position initiale de l'image en dehors de l'écran
SDL_Rect destRect;
int u = 0;

// boucle de jeu pour animer la translation de l'image
while (u != 150) {
    u++;
    
    // effacer l'écran
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

    // mise à jour de la position de l'image
    x7x7 -= 10; // ajustez cette valeur pour contrôler la vitesse de translation
    
    destRect.x = x7x7;
    destRect.y = (ecran->h - ani_die->h) / 2;

    // affichage de l'image en fonction de la réponse de l'utilisateur
    SDL_BlitSurface(ani_die, NULL, ecran, &destRect);

    // mise à jour de l'affichage
    SDL_Flip(ecran);

    // pause pour limiter le taux de rafraîchissement
    SDL_Delay(50);
}

















}
if(plz==1){afficher_enigme(enig,screen,&animation) ; p1.pos.x=100;}
SDL_BlitSurface(button_surface, NULL, screen, &button_rect);
SDL_Flip(ecran);
Score score;
strcpy(score.name,mot);
score.score = p1.score;
save_score(score);






}



}
//////////////////////end lvl2

//////////////start lvl3
if(LEVEL==3){




SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    int x7x7 = -next_level->w; // position initiale de l'image en dehors de l'écran
    SDL_Rect destRect;
	int u=0;
    // boucle de jeu pour animer la translation de l'image
    while ( (u!=150)) {
	u++;
        // effacer l'écran
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

        // mise à jour de la position de l'image
        x7x7 += 10; // ajustez cette valeur pour contrôler la vitesse de translation
       
        destRect.x = x7x7;
        destRect.y = (ecran->h - enig.imagewin->h) / 2;

        // affichage de l'image en fonction de la réponse de l'utilisateur
        
            SDL_BlitSurface(next_level, NULL, ecran, &destRect);
        

        // mise à jour de l'affichage
        SDL_Flip(ecran);

        // pause pour limiter le taux de rafraîchissement
        SDL_Delay(10);
	
    }

musique(2);
SDL_Flip(ecran);
SDL_BlitSurface(h3,NULL,ecran,&hhh);
SDL_Flip(ecran);
SDL_Delay(5000);
int anim_prs2=0;
int cond_choose_player=0;


while(cond_choose_player == 0)
{
anim_prs2++;
show=0;
if(anim_prs2>0){SDL_BlitSurface(choose_ur_player1,NULL,ecran,NULL);}
if(anim_prs2>10){SDL_BlitSurface(choose_ur_player2,NULL,ecran,NULL);}
if(anim_prs2>20){SDL_BlitSurface(choose_ur_player6,NULL,ecran,NULL);}
if(anim_prs2>30){SDL_BlitSurface(choose_ur_player7,NULL,ecran,NULL);}
if(anim_prs2>40){SDL_BlitSurface(choose_ur_player8,NULL,ecran,NULL);}
if(anim_prs2>50){SDL_BlitSurface(choose_ur_player9,NULL,ecran,NULL);}
SDL_Flip(ecran);
if(anim_prs2>60){anim_prs2=0;}
  while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
case SDL_QUIT:
                    menuON = 0;
                break;		

case SDL_MOUSEBUTTONUP:
                    SDL_GetMouseState(&mouseX, &mouseY);
                    if(isInsideBox(mouseX,mouseY,player1)==1){ //************************************
			p2.images[0][0] = IMG_Load("idleright_1.png");
    			p2.images[1][0] = IMG_Load("walkright_1.png");
    			p2.images[2][0] = IMG_Load("jumpright_1.png");
    			p2.images[0][1] = IMG_Load("idleleft_1.png");
    			p2.images[1][1] = IMG_Load("walkleft_1.png");
    			p2.images[2][1] = IMG_Load("jumpleft_1.png"); 
			p2.attack = IMG_Load("attackY.png"); 
			cond_choose_player=1;
			show=1;}
	    
		if(isInsideBox(mouseX,mouseY,player2)==1){
			p2.images[0][0] = IMG_Load("idleright_2.png");
    			p2.images[1][0] = IMG_Load("walkright_2.png");
    			p2.images[2][0] = IMG_Load("jumpright_2.png");
    			p2.images[0][1] = IMG_Load("idleleft_2.png");
    			p2.images[1][1] = IMG_Load("walkleft_2.png");
    			p2.images[2][1] = IMG_Load("jumpleft_2.png"); 
			p2.attack = IMG_Load("attackP.png"); 

cond_choose_player=1;show=1;}	
     
        }
 break;   

}
}
//////
/////////////








p1.v.pos.x=30;

   p2.v.pos.x=400;
  p2.v.pos.y=0;
c_a_i=1;
 enn.pos.x=350;
 enn2.pos.x=750;

int dam2=0;
int c_a_i2=1;
int khsert2,khsert1=0;
khsert2=0;
int e_met2=0;
int h_a_e2=0;
int marra=0;int marra2=0;
int martin=0; int martin2=0;
int yzy=0;
char image[50];
int i=0;
int end=0;
while(LEVEL==3){

xxx++;




//////// condition enigme riri
	if(  b.camera2.x>2500 && b.camera.x>2500  && yzy==0)
{

if(saisir(screen,generer_enigme(tabl))==0){//reponse vrai 

        SDL_BlitSurface(fondVrai,NULL,screen,&positionBGE);
 SDL_Flip(ecran);
	SDL_Delay(1200);
        printf("Vrai !\n");

    } else {

        SDL_BlitSurface(fondFaux,NULL,screen,&positionBGE);
 SDL_Flip(ecran);
SDL_Delay(1200);

        printf("Faux !\n");
}

time_11=1;
p1.v.num=0;
p2.v.num=0;
yzy=1;

}
/////////////



















if(b.camera2.x<=400){b.camera2.x=400;}
if(b.camera.x<=0){b.camera.x=0;}
if(p1.pos.x>=200){p1.pos.x=200;}
if(p2.pos.x<=400){p2.pos.x=400;}
 



if(b.camera.x>1000 && marra==0){c_a_i=1;marra=1;}
if(b.camera2.x>1000 && marra2==0){c_a_i2=1;marra2=1;}

if(b.camera.x>2000 && martin==0){c_a_i=1;martin=1;}
if(b.camera2.x>2000 && martin2==0){c_a_i2=1;martin2=1;}

if(b.camera.x>3000 && martin==1 && b.camera2.x>3000 && martin2==1 && end==0) {c_a_i=1;c_a_i2=1;
for(i=0;i<10;i++)
	{
	    sprintf(image,"./special/ennemi%d.png",i+1);
	    enn.e[i]=IMG_Load(image);enn2.e[i]=IMG_Load(image);
	}
 for(i=0;i<10;i++)
	{
	    sprintf(image,"./special/at%d.png",i+1);
	    enn.attaque[i]=IMG_Load(image);enn2.attaque[i]=IMG_Load(image);
	}

end=1;
SDL_Delay(1000);
enn.pos.x=400;
enn2.pos.x=800;
p1.pos.x=0;
p2.pos.x=400;

}

if(c_a_i==1 && collision(p1.pos,&enn)==1){dam++;}

if(p1.v.num>=5){p1.v.num=4;khsert1=1;}
	if(dam>30 && c_a_i==1){p1.v.num++;dam=0;Mix_PlayChannel(-1, damage, 0);}
if(p1.v.num>=5){p1.v.num=4;khsert1=1;p1.pos.x=50;}


if(khsert1==1 && khsert2==1){khsert=1;}



if(khsert1==1){c_a_i=0;p1.pos.x=50;}
/////
if(c_a_i2==1 && collision(p2.pos,&enn2)==1){dam2++;}

if(p2.v.num>=5){p2.v.num=4;khsert2=1;}
	if(dam2>30 && c_a_i2==1){p2.v.num++;dam2=0;Mix_PlayChannel(-1, damage, 0);}
if(p2.v.num>=5){p2.v.num=4;khsert2=1;p2.pos.x=50;}




if(khsert2==1){c_a_i2=0;p2.pos.x=430;}

if(b.camera.x>=5900 && b.camera2.x>=5900){ 
SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    int x7x7 = ecran->w;

    // Rectangle de destination pour l'affichage de l'image
    SDL_Rect destRect;
    destRect.y = (ecran->h - endgame->h) / 2;

    // Boucle de jeu pour animer la translation de l'image
    int u = 0;
    while (u != 220) {
        u++;

        // Effacer l'écran
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

        // Mise à jour de la position de l'image
        x7x7 -= 10; // Ajustez cette valeur pour contrôler la vitesse de translation

        destRect.x = x7x7;

        // Affichage de l'image
        SDL_BlitSurface(endgame, NULL, ecran, &destRect);

        // Mise à jour de l'affichage
        SDL_Flip(ecran);

        // Pause pour limiter le taux de rafraîchissement
        SDL_Delay(50);
	if(u>=219){SDL_Delay(4000);}

    }
LEVEL=0;

}





        while (SDL_PollEvent(&event)){
        switch(event.type)
        {
            case SDL_QUIT:
                LEVEL = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {    
	           case SDLK_LEFT:
                  if( khsert1==0 &&c_a_i==0 && b.camera.x<=6000 ){  b.camera.x+=-20;} 
                    break;
                case SDLK_RIGHT:
			if( khsert1==0 &&c_a_i == 0 && b.camera.x<=6000 ){b.camera.x+=20;}
                    break;     
	           case SDLK_q:
                  if(khsert2==0 && c_a_i==0 && b.camera2.x<=6000){  b.camera2.x+=-20;} 
                    break;
                case SDLK_d:
			if( khsert2==0 && c_a_i == 0  && b.camera2.x<=6000){b.camera2.x+=20;}
                    break; 
					case SDLK_SPACE:
			 Mix_PlayChannel(-1, laser, 0);
		break;
								case SDLK_e:
			 Mix_PlayChannel(-1, laser, 0);
		break;
 		
                }
                break;
       }
}
afficher_back(b,ecran);
 afficher_perso(p1,screen);
      afficher_score_vie(p1,screen,0);
      animer_perso(&p1);
      deplacer_perso(&p1);
      player_in_bounds(&p1,screen);
      jump_perso(&p1);
 afficher_perso(p2,screen);
        
      afficher_score_vie(p2,screen,0);
      animer_perso(&p2);
      deplacer_perso(&p2);
      player_in_bounds(&p2,screen);
      jump_perso2(&p2);

   
 


if(c_a_i==1  ){animer_ennemi(screen,&enn,p1.pos);   } 


 
if( ( p1.attacking>0)  && enn.pos.x-p1.pos.x<=100 && c_a_i==1 ){h_a_e++;}
if(h_a_e>30){c_a_i=0;h_a_e=0;e_met=1;}

////
if(c_a_i2==1  ){animer_ennemi(screen,&enn2,p2.pos);   } 


 
if( ( p2.attacking>0)  && enn2.pos.x-p2.pos.x<=100 && c_a_i2==1 ){h_a_e2++;}
if(h_a_e2>30){c_a_i2=0;h_a_e2=0;e_met2=1;}













SDL_BlitSurface(cadre,NULL,ecran,&posC);
SDL_Flip(ecran);
SDL_Delay(50);
}






















}
//////////////////end lvl3
                     }
                     if(isInsideBox(mouseX,mouseY,posSettings)==1){
	 settingsBLOCK(ecran,&volume);

                     }
                     if(isInsideBox(mouseX,mouseY,posExit)==1){
                        return 0;
                     }
			if(isInsideBox(mouseX,mouseY,posCredits)==1){

////////////////////////////////////////////////////////////////////  BLOCK CREDITS 
    SDL_Init(SDL_INIT_EVERYTHING);
    ecran = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_RESIZABLE);
    SDL_Surface *menuBG = NULL;
    SDL_Rect posBG;
    SDL_Event event;
    int menuON = 1;

    menuPBG = IMG_Load("credit.png");
    posBG.x = 0;
    posBG.y = 0;

    while(menuON == 1) {
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
                    }
                break;
            }
        }
        SDL_BlitSurface(menuPBG, NULL, ecran, &posBG);
        SDL_Flip(ecran);
    }

////////////////////////////////////////////////////////////////////
}
			
                break;
                case SDL_MOUSEMOTION:
                    SDL_GetMouseState(&mouseX, &mouseY);
                    if(isInsideBox(mouseX,mouseY,posPlay)==1) {
                        //On joue le son du Hover qu'au début (C-a-d : Si on garde la souris sur le bouton, on ne joue pas le son encore une fois)
                        if(playHovered == 0) {
                            hoverSound = 1;
                        }
                        playHovered = 1;
                    } else {
                        playHovered = 0;
                    }
                    if(isInsideBox(mouseX,mouseY,posSettings)==1) {
                        if(settingsHovered == 0) {
                            hoverSound = 1;
                        }
                        settingsHovered = 1;
                    } else {
                        settingsHovered = 0;
                    }
                    if(isInsideBox(mouseX,mouseY,posCredits)==1) {
                        if(creditsHovered == 0) {
                            hoverSound = 1;
                        }
                        creditsHovered = 1;
                    } else {
                        creditsHovered = 0;
                    }
                    if(isInsideBox(mouseX,mouseY,posExit)==1) {
                        if(exitHovered == 0) {
                            hoverSound = 1;
                        }
                        exitHovered = 1;
                    } else {
                        exitHovered = 0;
                    }
                break;
            }
            
        }

        //Son
        if(hoverSound==1) {
            Mix_PlayChannel(-1, mouseEffect, 0);
            hoverSound = 0;
        }
        //Affichage

	if(x<10 ){SDL_BlitSurface(t[1], NULL, ecran, &posBG);}
	if(x>20 ){SDL_BlitSurface(t[2], NULL, ecran, &posBG);}
	if(x>30 ){SDL_BlitSurface(t[3], NULL, ecran, &posBG);}
	if(x>40 ){SDL_BlitSurface(t[4], NULL, ecran, &posBG);}
	if(x>50){SDL_BlitSurface(t[5], NULL, ecran, &posBG);}
	if(x>60){SDL_BlitSurface(t[6], NULL, ecran, &posBG);} 
	if(x>70){SDL_BlitSurface(t[7], NULL, ecran, &posBG);} 
	if(x>80){SDL_BlitSurface(t[8], NULL, ecran, &posBG);} 
	if(x>90){SDL_BlitSurface(t[9], NULL, ecran, &posBG);}
	if(x>100){SDL_BlitSurface(t[10], NULL, ecran, &posBG);}  
	if(x>110){SDL_BlitSurface(t[11], NULL, ecran, &posBG);} 
	if(x>120){SDL_BlitSurface(t[12], NULL, ecran, &posBG);} 
	if(x > 120 && x % 10== 0){SDL_BlitSurface(t[10], NULL, ecran, &posBG);}
	if(x > 120 && x % 10!= 0){SDL_BlitSurface(t[12], NULL, ecran, &posBG);}  
	

 

		
	//SDL_BlitSurface(menuBG, NULL, ecran, &posBG);
	SDL_BlitSurface(logo, NULL, ecran, &posLogo);
 


        if(playHovered == 1) {
            SDL_BlitSurface(playHover, NULL, ecran, &posPlay);
        } else {
            SDL_BlitSurface(play, NULL, ecran, &posPlay);
        }
        if(settingsHovered == 1) {
            SDL_BlitSurface(settingsHover, NULL, ecran, &posSettings);
        } else {
            SDL_BlitSurface(settings, NULL, ecran, &posSettings);
        }
        if(creditsHovered == 1) {
            SDL_BlitSurface(creditsHover, NULL, ecran, &posCredits);
        } else {
            SDL_BlitSurface(credits, NULL, ecran, &posCredits);
        }
        if(exitHovered == 1) {
            SDL_BlitSurface(exitHover, NULL, ecran, &posExit);
        } else {
            SDL_BlitSurface(exit, NULL, ecran, &posExit);
        }
	  SDL_BlitSurface(text, NULL, screen, &text_position);

        SDL_Flip(ecran);

 x++;
    
}
//liberer
    Mix_FreeMusic(musicBG);
    SDL_FreeSurface(menuBG);
    SDL_FreeSurface(play);
    SDL_FreeSurface(settings);
    SDL_FreeSurface(credits);
    SDL_FreeSurface(exit);
    SDL_FreeSurface(playHover);
    SDL_FreeSurface(settingsHover);
    SDL_FreeSurface(creditsHover);
    SDL_FreeSurface(exitHover);
    Mix_CloseAudio();
    SDL_FreeSurface(text);
    TTF_CloseFont(font);
    TTF_Quit();
	free_enigme(&enig);
SDL_FreeSurface(button_surface);
    // fermeture du port
 /*   serialport_flush(fd);
    serialport_close(fd);*/
return 0;
}








