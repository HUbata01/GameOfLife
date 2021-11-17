#include "grafika.h"
#include <math.h>
/* ablak megnyitasa */
void sdl_init(char const *felirat, int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_Window *window = SDL_CreateWindow("SDL peldaprogram", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szeles, magas, 0);
    if (window == NULL) {
        SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(1);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(1);
    }
    SDL_RenderClear(renderer);

    *pwindow = window;
    *prenderer = renderer;
}
/* idozito letrehozasa */
Uint32 idozit(Uint32 ms, void *param) {
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;
}

/* gombok feliratozasa */
void gomb_felirat(Gombfelirat g, SDL_Rect hova, char *szoveg, int szoveg_x, int szoveg_y, Panel p){
    SDL_Color fekete = { 0, 0, 0};
    g.felirat = TTF_RenderUTF8_Blended(g.font, szoveg, fekete);
    g.felirat_t = SDL_CreateTextureFromSurface(p.renderer, g.felirat);
    hova.x = szoveg_x - g.felirat->w/2;
    hova.y = szoveg_y - g.felirat->h/2;
    hova.w = g.felirat->w;
    hova.h = g.felirat->h;
    SDL_RenderCopy(p.renderer, g.felirat_t, NULL, &hova);
    SDL_FreeSurface(g.felirat);
    SDL_DestroyTexture(g.felirat_t);
}


void start_rajzolas(Matrix m, Panel p){
    TTF_Init();
    Gombfelirat g;
    SDL_Rect hova = { 0, 0, 0, 0 };
    g.font = TTF_OpenFont("LiberationSerif-Regular.ttf", 34);
    if (!g.font) {
      SDL_Log("Nem sikerult megnyitni a fontot! %s\n", TTF_GetError());
      SDL_Quit();
    }


    //start
    boxRGBA(p.renderer, 1055, 170, 1190, 270, 0, 0, 0, 255);
    boxRGBA(p.renderer, 1057, 172, 1188, 268, 192, 192, 192, 255);
    gomb_felirat(g, hova, "Start", 2245/2, 220, p);

    TTF_CloseFont(g.font);
    SDL_RenderPresent(p.renderer);
}

void stop_rajzolas(Matrix m, Panel p){
    TTF_Init();
    Gombfelirat g;
    SDL_Rect hova = { 0, 0, 0, 0 };
    g.font = TTF_OpenFont("LiberationSerif-Regular.ttf", 34);
    if (!g.font) {
      SDL_Log("Nem sikerult megnyitni a fontot! %s\n", TTF_GetError());
      SDL_Quit();
    }


    //start
    boxRGBA(p.renderer, 1055, 170, 1190, 270, 0, 0, 0, 255);
    boxRGBA(p.renderer, 1057, 172, 1188, 268, 192, 192, 192, 255);
    gomb_felirat(g, hova, "Stop", 2245/2, 220, p);


    TTF_CloseFont(g.font);
    SDL_RenderPresent(p.renderer);
}



/* menu letrehozasa */
void menu_rajzolas(Matrix m, Panel p){

    boxRGBA(p.renderer, 0, 0, 1200, 900, 255, 255, 255, 255);
    boxRGBA(p.renderer, 5, 5, 1195, 895, 200, 0, 20, 255);
    boxRGBA(p.renderer, 905, 5, 1195, 895, 0, 0, 0, 255);
    boxRGBA(p.renderer, 907, 7, 1193, 893, 150, 0, 20, 255);


    TTF_Init();
    Gombfelirat g;
    SDL_Rect hova = { 0, 0, 0, 0 };
    g.font = TTF_OpenFont("LiberationSerif-Regular.ttf", 34);
    if (!g.font) {
      SDL_Log("Nem sikerult megnyitni a fontot! %s\n", TTF_GetError());
      SDL_Quit();
    }

    //random
    boxRGBA(p.renderer, 910, 60, 1045, 160, 0, 0, 0, 255);
    boxRGBA(p.renderer, 912, 62, 1043, 158, 192, 192, 192, 255);
    gomb_felirat(g, hova, "Random", 1955/2, 110, p);

    // clear
    boxRGBA(p.renderer, 1055, 60, 1190, 160, 0, 0, 0, 255);
    boxRGBA(p.renderer, 1057, 62, 1188, 158, 192, 192, 192, 255);
    gomb_felirat(g, hova, "Clear", 2245/2, 110, p);

    //step
    boxRGBA(p.renderer, 910, 170, 1045, 270, 0, 0, 0, 255);
    boxRGBA(p.renderer, 912, 172, 1043, 268, 192, 192, 192, 255);
    gomb_felirat(g, hova, "One step", 1955/2, 220, p);

    //start
    boxRGBA(p.renderer, 1055, 170, 1190, 270, 0, 0, 0, 255);
    boxRGBA(p.renderer, 1057, 172, 1188, 268, 192, 192, 192, 255);
    gomb_felirat(g, hova, "Start", 2245/2, 220, p);

    // toggle speed
    boxRGBA(p.renderer, 910, 280, 1190, 380, 0, 0, 0, 255);
    boxRGBA(p.renderer, 912, 282, 1188, 378, 192, 192, 192, 255);
    gomb_felirat(g, hova, "Speed", 1050, 310, p);

    boxRGBA(p.renderer, 915, 340, 950, 375, 0, 0, 0, 255);
    boxRGBA(p.renderer, 917, 342, 948, 373, 150, 150, 150, 255);
    gomb_felirat(g, hova, "-", 1865/2, 715/2, p);

    boxRGBA(p.renderer, 1150, 340, 1185, 375, 0, 0, 0, 255);
    boxRGBA(p.renderer, 1152, 342, 1183, 373, 150, 150, 150, 255);
    gomb_felirat(g, hova, "+", 2335/2, 715/2, p);

    thickLineRGBA(p.renderer, 950, (340+375)/2 , 1150, (340+375)/2, 10, 0, 0, 0, 255);

    //X Y
    boxRGBA(p.renderer, 910, 390, 1190, 490, 0, 0, 0, 255);
    boxRGBA(p.renderer, 912, 392, 1188, 488, 192, 192, 192, 255);


    /*
        //+ - gombok
    for (int y = 0; y < 2; y++){
      for (int x = 0; x < 4; x++){
        boxRGBA(p.renderer, 1010 + x * (10 + 35), 400 + y * (10 + 35), 1045 + x * (10 + 35), 435 + y * (10 + 35), 0, 0, 0, 255);
        boxRGBA(p.renderer, 1012 + x * (10 + 35), 402 + y * (10 + 35), 1043 + x * (10 + 35), 433 + y * (10 + 35), 150, 150, 150, 255);
      }
    }
    char cimke[][5] = { "-5", "-", "+", "+5" };
    for (int y = 0; y < 2; y++){
      for (int x = 0; x < 4; x++){
        gomb_felirat(g, hova, cimke[x], 2055/2 + x * (10 + 35), 835/2+ y * (10 + 35), p);
      }
    }
    */

    for (int x = 0; x < 4; x++){
        boxRGBA(p.renderer, 1010 + x * (10 + 35), 400+45/2, 1045 + x * (10 + 35), 400+45/2+35, 0, 0, 0, 255);
        boxRGBA(p.renderer, 1012 + x * (10 + 35), 402+45/2, 1043 + x * (10 + 35), 398+45/2+35, 150, 150, 150, 255);
    }
    char cimke[][5] = { "-5", "-", "+", "+5" };
    for (int x = 0; x < 4; x++){
      gomb_felirat(g, hova, cimke[x], 2055/2 + x * (10 + 35), (400+435+45)/2, p);
    }

        //X Y axis gombok
    boxRGBA(p.renderer, 920, 400, 995, 480, 0, 0, 0, 255);
    boxRGBA(p.renderer, 922, 402, 993, 478, 150, 150, 150, 255);

    TTF_CloseFont(g.font);


    g.font = TTF_OpenFont("LiberationSerif-Regular.ttf", 24);
    if (!g.font) {
      SDL_Log("Nem sikerult megnyitni a fontot! %s\n", TTF_GetError());
      SDL_Quit();
    }
    gomb_felirat(g, hova, "X-axis:", 960, 835/2, p);
    gomb_felirat(g, hova, "Y-axis:", 960, 835/2 + 45, p);

    TTF_CloseFont(g.font);



    g.font = TTF_OpenFont("LiberationSerif-Regular.ttf", 34);
    if (!g.font) {
      SDL_Log("Nem sikerult megnyitni a fontot! %s\n", TTF_GetError());
      SDL_Quit();
    }

    //Open
    boxRGBA(p.renderer, 910, 500, 1045, 600, 0, 0, 0, 255);
    boxRGBA(p.renderer, 912, 502, 1043, 598, 192, 192, 192, 255);
    gomb_felirat(g, hova, "Save", 1955/2, 550, p);

    //Save
    boxRGBA(p.renderer, 1055, 500, 1190, 600, 0, 0, 0, 255);
    boxRGBA(p.renderer, 1057, 502, 1188, 598, 192, 192, 192, 255);
    gomb_felirat(g, hova, "Open", 2245/2, 550, p);

    TTF_CloseFont(g.font);
    SDL_RenderPresent(p.renderer);
}
void rajzol(double x1, double y1, double x2, double y2){

}

void kirajzol(Matrix m, Panel p){


    boxRGBA(p.renderer, 5, 5, 895, 895, 200, 0, 20, 255);
    //boxRGBA(p.renderer, 905, 5, 1195, 895, 0, 0, 0, 255);
    //boxRGBA(p.renderer, 907, 7, 1193, 893, 150, 0, 20, 255);

    double cellahossz, x1, x2, y1, y2;
    if (m.sor < m. oszlop){
        cellahossz = (p.x2 - p.x1) / m.oszlop;
        x1 = p.x1;
        x2 = x1 + cellahossz;
        y1 = p.y1 + (m.oszlop - m.sor) / 2 * cellahossz;
        y2 = y1 + cellahossz;
    } else{
        cellahossz = (p.y2 - p.y1) / m.sor;
        y1 = p.x1;
        y2 = y1 + cellahossz;
        x1 = p.x1 + (m.sor - m.oszlop) / 2 * cellahossz;
        x2 = x1 + cellahossz;
    }
    boxRGBA(p.renderer, x1-1 , y1-1 , x1+m.oszlop*cellahossz+1 , y1+m.sor*cellahossz+1 , 0,0,0,255);
    for (int y = 0; y < m.sor; y++){
        for (int x = 0; x < m.oszlop; x++){
          if (m.tabla[x][y] == 0)
            boxRGBA(p.renderer, round(x1+x*cellahossz+1) , round(y1+y*cellahossz+1) , round(x2+x*cellahossz-1) , round(y2+y*cellahossz-1) , 255,255,255,255);
          else
            boxRGBA(p.renderer, round(x1+x*cellahossz+1) , round(y1+y*cellahossz+1) , round(x2+x*cellahossz-1) , round(y2+y*cellahossz-1) , 0,0,0,255);
        }
    }

    SDL_RenderPresent(p.renderer);
}
