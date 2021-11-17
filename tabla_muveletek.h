#ifndef TABLA_MUVELETEK_H_INCLUDED
#define TABLA_MUVELETEK_H_INCLUDED

#include "debugmalloc.h"
#include "strukturak.h"

double randfrom(double min, double max);
int el_v_hal(double esely);
int szomszed_szam(Matrix n, int oszlop, int sor);
int** lefoglal(Matrix n);
void felszabadit(Matrix n);
void randfeltolt(Matrix n, double esely);
void uresfeltolt(Matrix n, double esely);
void kiir(Matrix n);
void ujgen(Matrix n, Matrix m);
void szomszed_tabla(Matrix n, Matrix m);
int** novel(Matrix a, int z, int h);
void mentes(Matrix a);
Matrix beolvasas(void);


#endif // MATRIX_MUVELETEK_H_INCLUDED
