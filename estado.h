//
// Created by Uriel Pinheiro on 04/12/2018.
//

#ifndef HANOIC_ESTADO_H
#define HANOIC_ESTADO_H

#include <stdbool.h>

#define N 8

typedef struct estado {
    int c1[N];
    int c2[N];
    int c3[N];
    int f;
    int g;
    int h;
    struct estado *padre;
    struct estado **sucesores;
    int nSucesores;
} estado;

bool compararEstados(estado *e1, estado *e2);
void imprimirEstado(estado *e);
int h1(estado*);
int h2(estado*);
bool estadoSeguro(estado *e);
estado ** devolverEstadosValidos(estado *ei, int *n);
bool izqd_a_medio(estado *ei, estado *ef);
bool medio_a_izqd(estado *ei, estado *ef);
bool izqd_a_dcha(estado *ei, estado *ef);
bool dcha_a_izqd(estado *ei, estado *ef);
bool dcha_a_medio(estado *ei, estado *ef);
bool medio_a_dcha(estado *ei, estado *ef);
bool comprobarAncestralidad(estado *e1, estado *e2);
bool anadirSucesor(estado *e1, estado *e2);


//void inicializaEstado(estado *);

#endif //HANOIC_ESTADO_H




