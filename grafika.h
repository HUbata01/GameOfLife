#ifndef GRAFIKA_H_INCLUDED
#define GRAFIKA_H_INCLUDED

#include "strukturak.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>

void sdl_init(char const *felirat, int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer);
Uint32 idozit(Uint32 ms, void *param);
void gomb_felirat(Gombfelirat g, SDL_Rect hova, char *szoveg, int szoveg_x, int szoveg_y, Panel p);
void start_rajzolas(Matrix m, Panel p);
void stop_rajzolas(Matrix m, Panel p);
void menu_rajzolas(Matrix m, Panel p);
void kirajzol(Matrix m, Panel p);

#endif // GRAFIKA_H_INCLUDED
