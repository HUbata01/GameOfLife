#include <stdio.h>
#include "tabla_muveletek.h"



/* generate a random floating point number from min to max */
double randfrom(double min, double max){
  double range = (max - min);
  double div = RAND_MAX / range;
  return min + (rand() / div);
}

int el_v_hal(double esely){
  if (randfrom(0.0, 1.0) < esely){
    return 1;
  }
  return 0;
}

int szomszed_szam(Matrix n, int oszlop, int sor){
  int hany = 0;
  for (int y = 0; y <= 2; y++){
    for (int x = 0; x <= 2; x++){
      if ((x != 1 ) || (y != 1))
      if ((oszlop + y -1 >= 0) && (oszlop + y -1 < n.oszlop) && (sor + x -1 >= 0) && (sor + x -1 < n.sor)){
        hany+=n.tabla[oszlop + y -1][sor + x -1];
      }
    }
  }
  return hany;
}

int** lefoglal(Matrix n){
  n.tabla = (int**) calloc(sizeof(int*) * n.oszlop, sizeof(int*));
  n.tabla[0] = (int*) calloc(sizeof(int) * n.oszlop * n.sor, sizeof(int));
  for(int x = 1; x < n.oszlop; ++x)
    n.tabla[x] = n.tabla[0] + x * n.sor;
  return n.tabla;
}

void felszabadit(Matrix n){
  free(n.tabla[0]);
  free(n.tabla);
}

void randfeltolt(Matrix n, double esely){
  for (int y = 0; y < n.sor; y++){
    for (int x = 0; x < n.oszlop; x++){
      n.tabla[x][y] = el_v_hal(esely);
    }
  }
}

void uresfeltolt(Matrix n, double esely){
  for (int y = 0; y < n.sor; y++){
    for (int x = 0; x < n.oszlop; x++){
      n.tabla[x][y] = 0;
    }
  }
}

void kiir(Matrix n){
  for (int y = 0; y < n.sor; y++){
    for (int x = 0; x < n.oszlop; x++){
      printf("%d ", n.tabla[x][y]);
    }
    printf("\n");
  }
  printf("\n\n");
}


void ujgen(Matrix n, Matrix m){
  for (int y = 0; y < n.sor; y++){
    for (int x = 0; x < n.oszlop; x++){
      switch(m.tabla[x][y]){
        case 3: n.tabla[x][y] = 1; break;
        case 2: break;
        default: n.tabla[x][y] = 0; break;
      }
    }
  }
}

void szomszed_tabla(Matrix n, Matrix m){
  for (int y = 0; y < n.sor; y++){
    for (int x = 0; x < n.oszlop; x++){
      m.tabla[x][y] = szomszed_szam(n, x, y);
    }
  }
}



int** novel(Matrix a, int z, int h){


    Matrix uj;
    uj.sor = a.sor;
    uj.oszlop = a.oszlop;
    uj.tabla = lefoglal(uj);

    if(z > 0 && h > 0){
        for(int y = 0; y < a.sor-z; y++){
            for(int x = 0; x < a.oszlop-h; x++){
                uj.tabla[x][y] = a.tabla[x][y];
            }
        }
    }
    else if(z < 0 && h > 0){
        for(int y = 0; y < a.sor; y++){
            for(int x = 0; x < a.oszlop-h; x++){
                uj.tabla[x][y] = a.tabla[x][y];
            }
        }
    }
    else if(z > 0 && h < 0){
        for(int y = 0; y < a.sor-z; y++){
            for(int x = 0; x < a.oszlop; x++){
                uj.tabla[x][y] = a.tabla[x][y];
            }
        }
    }
    else{
        for(int y = 0; y < a.sor; y++){
            for(int x = 0; x < a.oszlop; x++){
                uj.tabla[x][y] = a.tabla[x][y];
            }
        }
    }
    return uj.tabla;
}

void mentes(Matrix a){
    FILE *fp;
    fp = fopen("mentes.txt", "wt");
    if (fp == NULL) {
        perror("Fajl megnyitasa sikertelen");
        SDL_Quit();
    }
    for(int y = 0; y < a.sor; y++){
        for(int x = 0; x < a.oszlop; x++){
            if(a.tabla[x][y] == 0){
                fprintf(fp, "O");
            }
            else{
                fprintf(fp, "1");
            }
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

Matrix beolvasas(void){
    FILE *fp;
    fp = fopen("mentes.txt", "rt");
    if (fp == NULL) {
        perror("Fajl megnyitasa sikertelen");
        SDL_Quit();
    }
    int oszlop = 0;
    char mozgo1;
    fscanf(fp, "%c", &mozgo1);
    while(mozgo1 != '\n'){
        oszlop++;
        fscanf(fp, "%c", &mozgo1);
    }
    fseek(fp, 0, SEEK_SET);

    int sor = 0;
    int ch = 0;
    while((ch = fgetc(fp)) != EOF){
        if (ch == '\n'){
            sor++;
        }
    }


    fseek(fp, 0, SEEK_SET);
    Matrix uj;
    //javítani
    uj.oszlop = oszlop;
    uj.sor = sor;
    uj.tabla = lefoglal(uj);
    char temp;
    for(int y = 0; y < uj.sor; y++){
        for(int x = 0;  x <  uj.oszlop; x++){
            fscanf(fp, "%c", &temp);
            if(temp == '1')
                uj.tabla[x][y] = 1;
            else
                uj.tabla[x][y] = 0;
        }
       fseek(fp, 1, SEEK_CUR);
    }


    fclose(fp);
    return uj;
}
