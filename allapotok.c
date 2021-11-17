#include "allapotok.h"


enum Allapot programgerinc(Matrix* a, Matrix* b, Panel p, double esely, enum Allapot allapot, int szamlalo, bool megy, int* valami){
    switch(allapot){
        /*Random*/
        case random1:{
            randfeltolt(*a, esely);
            kirajzol(*a, p);
            allapot = ures;
            break;
        }
        /*onestep*/
        case onestep:{
            szomszed_tabla(*a, *b);
            ujgen(*a, *b);
            kirajzol(*a, p);
            allapot = ures;
            break;
        }
        /*clear*/
        case clear:{
            uresfeltolt(*a, esely);
            kirajzol(*a, p);
            allapot = ures;
            break;
        }
        case start:{
            if(megy){
                if(szamlalo == 5){
                    szomszed_tabla(*a, *b);
                    ujgen(*a, *b);
                    kirajzol(*a, p);
                }
            }
            else
                allapot = ures;
            break;
        }
        //jelenleg az open a pálya csökkentéséért felelős, később javítom
        case minus_one:{

            a->sor -= 1;
            a->oszlop -= 1;
            b->sor -= 1;
            b->oszlop -= 1;

            Matrix uj_a;
            uj_a.tabla = novel(*a, -1, -1);
            felszabadit(*a);
            a->tabla = uj_a.tabla;

            Matrix uj_b;
            uj_b.tabla = lefoglal(*b);
            felszabadit(*b);
            b->tabla = uj_b.tabla;

            kirajzol(*a, p);
            allapot = ures;

            break;
        }
        //jelenleg save a pálya nagyításáért felelős, később javítom
        case plus_one:{
            a->sor += 1;
            a->oszlop += 1;
            b->sor += 1;
            b->oszlop += 1;

            Matrix uj_a;
            uj_a.tabla = novel(*a, 1, 1);
            felszabadit(*a);
            a->tabla = uj_a.tabla;

            Matrix uj_b;
            uj_b.tabla = lefoglal(*b);
            felszabadit(*b);
            b->tabla = uj_b.tabla;

            kirajzol(*a, p);
            allapot = ures;

            break;
        }

        case save:{
            mentes(*a);
            allapot = ures;
            break;
        }

        case open:{
            felszabadit(*a);
            felszabadit(*b);
            *a = beolvasas();
            b->sor = a->sor;
            b->oszlop = a->oszlop;
            b->tabla = lefoglal(*b);
            kirajzol(*a, p);
            allapot = ures;
            break;
        }

        default:
            break;
    }
    return allapot;
}
