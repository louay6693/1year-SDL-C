#ifndef _XO_H_
#define _XO_H_
#include <SDL/SDL_image.h>
#include <SDL/SDL.h>

typedef struct
{
SDL_Surface *table;
SDL_Surface *bg;
SDL_Surface *t[2];
int i[3][3];
SDL_Rect r[3][3];
int turn;
int choixx;
int choixy;
}xo;
void quitgame(int *q,xo c);
int main();
void init(xo *c);
void showme(xo c,SDL_Surface *screen);
void change(xo *c);
int winner_is(xo c);
void ia2(xo *c);
#endif
