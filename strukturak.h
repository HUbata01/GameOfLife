#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

enum Allapot {
    ures,
    random1,
    clear,
    start,
    stop,
    speed,
    decrase,
    incrase,
    minus_one,
    plus_one,
    onestep,
    open,
    save
};

typedef struct Matrix{
    int** tabla;
    int oszlop;
    int sor;
}Matrix;

typedef struct Panel{
    double x1;
    double y1;
    double x2;
    double y2;
    SDL_Renderer *renderer;
}Panel;

typedef struct Gombfelirat{
        SDL_Surface *felirat;
        SDL_Texture *felirat_t;
        TTF_Font *font;
}Gombfelirat;

#endif // STRUCTS_H_INCLUDED
