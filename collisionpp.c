/**
* @file collisionpp.c
* @brief functions of the collision perfect pixel
* @author Hakim Bedhief
* @version final
* @date June 6, 2020
*/
#include "perso.h"
//-------------------------------------------
typedef struct{
SDL_Rect pos;
SDL_Surface *is[50];//imagesbg si il ya une animation
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




/*!
* @brief to Return the pixel color that represents the surface
* @param surface (masque) to be accessed
* @param x coordinate to access a pixel.
* @param y coordinate to access a pixel.
* @return the pixel color
*/
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




/**
*@brief if it hits the black pixels it will stop from moving or less health
*@param poshero is the position of the hero
*@param bg the surface (masque) to be accessed
*@param camera position of the camera
*@return 1 if there's a collision else 0
*/
int collisionp(SDL_Rect poshero,background bg,SDL_Rect camera)
{
Uint32 noir = SDL_MapRGB(bg.masque->format,0,0,0);
if(getpixel(bg.masque,camera.x+poshero.x,poshero.y+124) == noir)
{
return 1;
}
else
return 0;
}

