
#include"perso.h"
#include"ennemi.h"
#include"collisionbb.h"


int collision(SDL_Rect poshero,ennemi *enn)
{
   if(enn->direction==1)
    {
      if(((enn->pos.x)<(poshero.x+75))&&(enn->pos.x>poshero.x)&&(poshero.y+100>=enn->pos.y))
         return 1;
      else
         return 0;
    }
   if(enn->direction==0)
    {
      if(((enn->pos.x)+50>poshero.x)&&(enn->pos.x<poshero.x)&&(poshero.y+100>=enn->pos.y))
         return 1;
      else
         return 0;
    }
}






