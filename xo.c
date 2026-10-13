#include"xo.h"

void quitgame(int *q,xo c)
{
Uint8 *keystate = SDL_GetKeyState(NULL);
if ( keystate[SDLK_ESCAPE] ) (*q)=1;
int count=0;
for (int i=0;i<3;i++)
for (int j=0;j<3;j++)
if(c.i[i][j]!=-1) 
count++;
if (count==9) (*q)=1;
}
////////////////



void init(xo *c)
{
c->table = IMG_Load("xo.png");
c->t[0] = IMG_Load("x.png");
c->t[1] = IMG_Load("o.png");
c->bg = IMG_Load("white.jpeg");
if(c->t[1]==NULL) 
printf("aa\n");
for (int i=0;i<3;i++)for (int j=0;j<3;j++)
{c->i[i][j]=-1;
c->r[i][j].x=217*i+40;
c->r[i][j].y=217*j+40;
c->turn=rand()%2;
c->choixx=0;
c->choixy=0;
}
}
////////////////////////////////////
void showme(xo c,SDL_Surface *screen)
{
SDL_Flip(screen);
SDL_BlitSurface(c.bg,NULL,screen,NULL);
SDL_BlitSurface(c.table,NULL,screen,NULL);
for (int i=0;i<3;i++)
for (int j=0;j<3;j++)
{if(c.i[i][j]!=-1)SDL_BlitSurface(c.t[c.i[i][j]],NULL,screen,&c.r[i][j]);
if((c.choixx==i)&&(c.choixy==j))SDL_BlitSurface(c.t[c.turn],NULL,screen,&c.r[i][j]);
}}
///////////////////////////
void turn_played(xo *c)
{c->turn++;
if(c->turn==2)
c->turn=0;
}
/////////////////////////////
void change(xo *c)
{
SDL_Delay(100);
Uint8 *keystate = SDL_GetKeyState(NULL);
if ( keystate[SDLK_RIGHT] ) if(c->choixx<2)c->choixx++;
if ( keystate[SDLK_LEFT] ) if(c->choixx>0)c->choixx--;
if ( keystate[SDLK_DOWN] ) if(c->choixy<2)c->choixy++;
if ( keystate[SDLK_UP] ) if(c->choixy>0)c->choixy--;
if ( keystate[SDLK_RETURN] ) if(c->i[c->choixx][c->choixy]==-1){c->i[c->choixx][c->choixy]=c->turn;turn_played(&(*c));}
}
/////////////////////////////
int winner_is(xo c)
{
for(int i=0;i<2;i++)
{for(int j=0;j<3;j++)
{
if((c.i[j][0]==i)&&(c.i[j][1]==i)&&(c.i[j][2]==i)) return i;
if((c.i[0][j]==i)&&(c.i[1][j]==i)&&(c.i[2][j]==i)) return i;
}
if((c.i[0][0]==i)&&(c.i[1][1]==i)&&(c.i[2][2]==i)) return i;
if((c.i[0][2]==i)&&(c.i[1][1]==i)&&(c.i[2][0]==i)) return i;
}
return -1;
}
//////////////////////////////
void ia2(xo *c)
{int count=0;
if(c->turn==1){
SDL_Delay(500);
for(int i=0;i<2;i++)
{for(int j=0;j<3;j++)
{count=0;
for(int k=0;k<3;k++)if(c->i[j][k]==i) count++;
if(count==2)for(int k=0;k<3;k++) if(c->i[j][k]==-1){c->i[j][k]=1;turn_played(&(*c));return;}
count=0;
for(int k=0;k<3;k++)if(c->i[k][j]==i) count++;
if(count==2)for(int k=0;k<3;k++) if(c->i[k][j]==-1){c->i[k][j]=1;turn_played(&(*c));return;}
count=0;
}
for(int k=0;k<3;k++)if(c->i[k][k]==i)count++;
if(count==2)for(int k=0;k<3;k++) if(c->i[k][k]==-1){c->i[k][k]=1;turn_played(&(*c));return;}
count=0;
if(c->i[0][2]==i) count++;
if(c->i[1][1]==i) count++;
if(c->i[2][0]==i) count++;
if(count==2)
{if(c->i[0][2]==-1){c->i[0][2]=1;turn_played(&(*c));return;}
if(c->i[2][0]==-1){c->i[2][0]=1;turn_played(&(*c));return;}
if(c->i[1][1]==-1){c->i[1][1]=1;turn_played(&(*c));return;}}

}
for(int i=0;i<3;i++)for(int j=0;j<3;j++)if(c->i[i][j]==-1){c->i[i][j]=1;turn_played(&(*c));return;}
}}
//////////////////////////////////
/*int main()
{
int q=0;
SDL_Surface *screen;
xo tic;
init(&tic);
screen =SDL_SetVideoMode(600,600,32,SDL_SWSURFACE);
while(q==0){
SDL_PumpEvents();
quitgame(&q,tic);
if(tic.turn==0)change(&tic);
ia2(&tic);
if(winner_is(tic)!=-1){showme(tic,screen);SDL_Flip(screen);SDL_Delay(1000);return winner_is(tic);}
showme(tic,screen);
}SDL_Delay(1000);
if(winner_is(tic)==-1){q=1;}
//return -1;
}
*/






