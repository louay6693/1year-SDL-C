prog:Image.o main.o settings.o perso.o enigmea.o xo.o ennemi.o collisionbb.o background.o sousmenu.o
	gcc Image.o main.o settings.o perso.o enigmea.o xo.o ennemi.o collisionbb.o background.o sousmenu.o -o prog -lSDL -lSDL_ttf -lSDL_image -lSDL_mixer -lSDL_gfx -g
	gcc -c enigmea.c -I/usr/include/SDL -g
main.o:main.c 
	gcc -c main.c -g
Image.o:Image.c 
	gcc -c Image.c -g
settings.o:settings.c
	gcc -c settings.c -g
perso.o:perso.c
	gcc -c perso.c -g
enigmea.o:enigmea.c
	gcc -c enigmea.c -g
xo.o:xo.c
	gcc -c xo.c -g
ennemi.o:ennemi.c
	gcc -c ennemi.c -g
collisionbb.o:collisionbb.c
	gcc -c collisionbb.c -g
background.o:background.c
	gcc -c background.c -lSDL -lSDL_image  -lSDL_mixer  -g

sousmenu.o:sousmenu.c
	gcc -c sousmenu.c -g
