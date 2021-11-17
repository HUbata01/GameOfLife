#!/bin/sh
gcc main.c allapotok.c tabla_muveletek.c grafika.c -o main `sdl2-config --cflags --libs` -lSDL2_gfx -lSDL2_ttf -lSDL2_image -lSDL2_mixer -lm -Werror -Wall -pedantic && ./main
