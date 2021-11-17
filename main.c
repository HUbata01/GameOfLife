#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "debugmalloc.h"
#include "allapotok.h"
#include <SDL2/SDL_ttf.h>
#include "strukturak.h"
#include "tabla_muveletek.h"
#include "grafika.h"
#include <string.h>



enum Allapot hol_kattint(SDL_Event event, enum Allapot allapot, bool megy){
    //Random
    if (event.button.x >= 910 && event.button.x <= 1045 && event.button.y >= 60 && event.button.y <= 160){
        allapot = random1;
    }
    //Clear
    else if (event.button.x >= 1055 && event.button.x <= 1190 && event.button.y >= 60 && event.button.y <= 160){
        allapot = clear;
    }
    //One step
    else if (event.button.x >= 910 && event.button.x <= 1045 && event.button.y >= 170 && event.button.y <= 270){
        allapot = onestep;
    }
    //Start
    else if (event.button.x >= 1055 && event.button.x <= 1190 && event.button.y >= 170 && event.button.y <= 270){
        if (!megy)
            allapot = start;
        else
            allapot = stop;
    }
    //Speed
    else if (event.button.x >= 780 && event.button.x <= 980 && event.button.y >= 395 && event.button.y <= 455){
        allapot = speed;
    }
    //Decrase
    else if (event.button.x >= 915 && event.button.x <= 950 && event.button.y >= 340 && event.button.y <= 375){
        allapot = decrase;
    }
    //Incrase
    else if (event.button.x >= 1150 && event.button.x <= 1185 && event.button.y >= 340 && event.button.y <= 375){
        allapot = incrase;
    }
    //Minus One
    else if (event.button.x >= 1055 && event.button.x <= 1090 && event.button.y >= 400+45/2 && event.button.y <= 435+45/2){
        allapot = minus_one;
    }
    //Plus One
    else if (event.button.x >= 1100 && event.button.x <= 1145 && event.button.y >= 400+45/2 && event.button.y <= 435+45/2){
        allapot = plus_one;
    }
    //Save
    else if (event.button.x >= 910 && event.button.x <= 1045 && event.button.y >= 500 && event.button.y <= 600){
        allapot = save;
    }
    //Open
    else if (event.button.x >= 1055 && event.button.x <= 1190 && event.button.y >= 500 && event.button.y <= 600){
        allapot = open;
    }
    return allapot;
}

int main(int argc, char *argv[]){

    Panel p;
    p.x1 = 20; p.y1 = 20;
    p.x2 = 880; p.y2 = 880;


    srand (time ( NULL));
    Matrix a;
    Matrix b;
    int valami = 0;
    double esely = 0.35;
    a.sor = 5;
    a.oszlop = 10;
    b.sor = 5;
    b.oszlop = 10;

    a.tabla = lefoglal(a);
    b.tabla = lefoglal(b);

    randfeltolt(a, esely);
    szomszed_tabla(a, b);
    ujgen(a, b);



    SDL_Window *window;
    
    sdl_init("SDL peldaprogram", 1200, 900, &window, &p.renderer);
    menu_rajzolas(a, p);
    kirajzol(a, p);

    SDL_TimerID id = SDL_AddTimer(20, idozit, NULL);

    enum Allapot allapot = ures;

    int szamlalo = 0;
    bool quit = false;
    bool megy = false;
    while (!quit) {
        SDL_Event event;
        SDL_WaitEvent(&event);
        switch (event.type) {
            /* eger kattintas */
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                    allapot = hol_kattint(event, allapot, megy);
                if (allapot != start){
                    start_rajzolas(a, p);
                    megy = false;
                }
                else{
                    stop_rajzolas(a, p);
                    megy = true;
                }
                break;
            case SDL_USEREVENT:
                if (allapot != ures)
                    allapot = programgerinc(&a, &b, p, esely, allapot, szamlalo, megy, &valami);
                szamlalo++;
                if (szamlalo == 6)
                    szamlalo = 0;
                break;
            case SDL_QUIT:
                quit = true;
                break;
            default:
                break;
        }

    }
    SDL_RemoveTimer(id);

    SDL_Quit();


    felszabadit(a);
    felszabadit(b);
    return 0;
}
