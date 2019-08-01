//
// Created by Uriel Pinheiro on 04/12/2018.
//
#include "estado.h"
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool compararEstados(estado *e1, estado *e2) {
    int i;
    for (i = 0; i < N; i++){
        if(e1->c1[i] != e2->c1[i] || e1->c2[i] != e2->c2[i]  || e1->c3[i] != e2->c3[i]){
            return false;
        }
    }
    return true;
}

void imprimirEstado(estado *e){
    int i;
    for (i = 0; i < N; i++) {
        printf("[%d] [%d] [%d]\n",e->c1[i],e->c2[i],e->c3[i]);
    }
}

int h1(estado *e){
    int r = N;
    int i;

    if(e == NULL){
        return -1;
    }

    for (i = (N - 1); i >= 0; i--) {
        if(e->c3[i] == r) {
            r--;
        }
        else {
            break;
        }
    }

    return (int) pow(2, (double) r) - 1;
}

int h2(estado *e){
    int r = N;
    int i;

    if(e == NULL){
        return -1;
    }

    for (i = (N - 1); i >= 0; i--) {
        if(e->c3[i] == r) {
            r--;
        }
        else {
            break;
        }
    }

    return (int) pow(2, (double) r - 1);
}

bool estadoSeguro(estado *e) {
    int fichaCima;
    int segundaFicha;
    int i;
    bool estadoC1 = true, estadoC2 = true, estadoC3 = true;

    for (i = (N - 1); i >= 0; i--) {
        if (e->c1[i] == 0) {
            //si la columna está vacía, es un estado seguro
            if(i == (N - 1)) {
                //return  true;
                estadoC1 = true;
                break;
            }
            //si no, comprobamos si hay solo una ficha en la columna
            if(i == (N - 2)) {
                //return true;
                estadoC1 = true;
                break;
            }
            else {
                //i + 1 es el índice de la ficha de la cima de la pila
                //i + 2 es el índice de la segunda ficha
                fichaCima = e->c1[i + 1];
                segundaFicha = e->c1[i + 2];

                if (fichaCima > segundaFicha) {
                    return false;
//                    estadoC1 = false;
//                    break;
                }
            }
        }
    }

    for (i = (N - 1); i >= 0; i--) {
        if (e->c2[i] == 0) {
            if(i == (N - 1)) {
                //return  true;
                estadoC2 = true;
                break;
            }
            if(i == (N - 2)) {
                //return true;
                estadoC2 = true;
                break;
            }
            else {
                fichaCima = e->c2[i + 1];
                segundaFicha = e->c2[i + 2];

                if (fichaCima > segundaFicha) {
                    return false;
//                    estadoC2 = false;
//                    break;
                }
            }
        }
    }

    for (i = (N - 1); i >= 0; i--) {
        if (e->c3[i] == 0) {
            if(i == (N - 1)) {
                //return  true;
                estadoC3 = true;
                break;
            }
            if(i == (N - 2)) {
                //return true;
                estadoC3 = true;
                break;
            }
            else {
                fichaCima = e->c3[i + 1];
                segundaFicha = e->c3[i + 2];

                if (fichaCima > segundaFicha) {
                    return false;
//                    estadoC3 = false;
//                    break;
                }
            }
        }
    }
    //Si no se ha encontrado un estado inseguro
    return (estadoC1 && estadoC2 && estadoC3);
}

bool izqd_a_medio(estado *ei, estado *ef) {
    int i, ficha = -1, indiceFicha = -1;

    if(ei == NULL) {
        return false;
    }
    //Si la columna de origen está vacía
    if (ei->c1[N - 1] == 0) {
        return false;
    }
    //Si la columna de destino está llena
    if(ei->c2[0] != 0) {
        return false;
    }

//    ef = malloc(1 * sizeof(estado));
//    if (ef == NULL){
//        return false;
//    }

    //Copiamos el contenido de ei a ef.
    *ef = *ei;

    //Recorremos la columna de origen para hallar la ficha de la cima
    for (i = 0; i < N; i++) {
        if (ef->c1[i] != 0) {
            ficha = ef->c1[i];
            indiceFicha = i;
            break;
        }
    }

    if (ficha == -1 || indiceFicha == -1){
        return false;
    }

    //Borramos la ficha de la columna de origen
    ef->c1[indiceFicha] = 0;

    //Copiamos la ficha a la columna de destino
    for (i = (N - 1); i >= 0; i--) {
        if (ef->c2[i] == 0) {
            ef->c2[i] = ficha;
            break;
        }
    }

    return (estadoSeguro(ef));
}
bool medio_a_izqd(estado *ei, estado *ef) {
    int i, ficha = -1, indiceFicha = -1;

    if(ei == NULL) {
        return false;
    }
    if (ei->c2[N - 1] == 0) {
        return false;
    }
    if(ei->c1[0] != 0) {
        return false;
    }

//    ef = malloc(1 * sizeof(estado));
//    if (ef == NULL){
//        return false;
//    }
    *ef = *ei;

    for (i = 0; i < N; i++) {
        if (ef->c2[i] != 0) {
            ficha = ef->c2[i];
            indiceFicha = i;
            break;
        }
    }

    if (ficha == -1 || indiceFicha == -1){
        return false;
    }

    ef->c2[indiceFicha] = 0;

    for (i = (N - 1); i >= 0; i--) {
        if (ef->c1[i] == 0) {
            ef->c1[i] = ficha;
            break;
        }
    }

    return (estadoSeguro(ef));
}
bool izqd_a_dcha(estado *ei, estado *ef) {
    int i, ficha = -1, indiceFicha = -1;

    if(ei == NULL) {
        return false;
    }
    if (ei->c1[N - 1] == 0) {
        return false;
    }
    if(ei->c3[0] != 0) {
        return false;
    }

//    ef = malloc(1 * sizeof(estado));
//    if (ef == NULL){
//        return false;
//    }

    *ef = *ei;

    for (i = 0; i < N; i++) {
        if (ef->c1[i] != 0) {
            ficha = ef->c1[i];
            indiceFicha = i;
            break;
        }
    }

    if (ficha == -1 || indiceFicha == -1){
        return false;
    }

    ef->c1[indiceFicha] = 0;

    for (i = (N - 1); i >= 0; i--) {
        if (ef->c3[i] == 0) {
            ef->c3[i] = ficha;
            break;
        }
    }

    return (estadoSeguro(ef));
}
bool dcha_a_izqd(estado *ei, estado *ef) {
    int i, ficha = -1, indiceFicha = -1;

    if(ei == NULL) {
        return false;
    }
    if (ei->c3[N - 1] == 0) {
        return false;
    }
    if(ei->c1[0] != 0) {
        return false;
    }

//    ef = malloc(1 * sizeof(estado));
//    if (ef == NULL){
//        return false;
//    }

    *ef = *ei;

    for (i = 0; i < N; i++) {
        if (ef->c3[i] != 0) {
            ficha = ef->c3[i];
            indiceFicha = i;
            break;
        }
    }

    if (ficha == -1 || indiceFicha == -1){
        return false;
    }

    ef->c3[indiceFicha] = 0;

    for (i = (N - 1); i >= 0; i--) {
        if (ef->c1[i] == 0) {
            ef->c1[i] = ficha;
            break;
        }
    }

    return (estadoSeguro(ef));
}
bool dcha_a_medio(estado *ei, estado *ef) {
    int i, ficha = -1, indiceFicha = -1;

    if(ei == NULL) {
        return false;
    }
    if (ei->c3[N - 1] == 0) {
        return false;
    }
    if(ei->c2[0] != 0) {
        return false;
    }

//    ef = malloc(1 * sizeof(estado));
//    if (ef == NULL){
//        return false;
//    }

    *ef = *ei;

    for (i = 0; i < N; i++) {
        if (ef->c3[i] != 0) {
            ficha = ef->c3[i];
            indiceFicha = i;
            break;
        }
    }

    if (ficha == -1 || indiceFicha == -1){
        return false;
    }

    ef->c3[indiceFicha] = 0;

    for (i = (N - 1); i >= 0; i--) {
        if (ef->c2[i] == 0) {
            ef->c2[i] = ficha;
            break;
        }
    }

    return (estadoSeguro(ef));
}
bool medio_a_dcha(estado *ei, estado *ef) {
    int i, ficha = -1, indiceFicha = -1;

    if(ei == NULL) {
        return false;
    }
    if (ei->c2[N - 1] == 0) {
        return false;
    }
    if(ei->c3[0] != 0) {
        return false;
    }

//    ef = malloc(1 * sizeof(estado));
//    if (ef == NULL){
//        return false;
//    }

    *ef = *ei;

    for (i = 0; i < N; i++) {
        if (ef->c2[i] != 0) {
            ficha = ef->c2[i];
            indiceFicha = i;
            break;
        }
    }

    if (ficha == -1 || indiceFicha == -1){
        return false;
    }

    ef->c2[indiceFicha] = 0;

    for (i = (N - 1); i >= 0; i--) {
        if (ef->c3[i] == 0) {
            ef->c3[i] = ficha;
            break;
        }
    }

    return (estadoSeguro(ef));
}
estado ** devolverEstadosValidos(estado *ei, int *n) {
    estado *e1,*e2,*e3,*e4,*e5,*e6;
    estado **salida;
    *n = 0;

    e1 = (estado*) malloc(1 * sizeof(estado));
    e2 = (estado*) malloc(1 * sizeof(estado));
    e3 = (estado*) malloc(1 * sizeof(estado));
    e4 = (estado*) malloc(1 * sizeof(estado));
    e5 = (estado*) malloc(1 * sizeof(estado));
    e6 = (estado*) malloc(1 * sizeof(estado));
    salida = (estado **) malloc(6 * sizeof(estado *));

    if(salida == NULL|| e1 == NULL || e2 == NULL || e3 == NULL || e4 == NULL || e5 == NULL || e6 == NULL) {
        return  NULL;
    }

    if(izqd_a_medio(ei,e1) == true) {
        salida[*n] = e1;
        *n += 1;
    }
    else {
        free(e1);
    }

    if(medio_a_izqd(ei,e2) == true) {
        salida[*n] = e2;
        *n += 1;
    }
    else {
        free(e2);
    }

    if(izqd_a_dcha(ei,e3) == true) {
        salida[*n] = e3;
        *n += 1;
    }
    else {
        free(e3);
    }

    if(dcha_a_izqd(ei,e4) == true) {
        salida[*n] = e4;
        *n += 1;
    }
    else {
        free(e4);
    }

    if(dcha_a_medio(ei,e5) == true) {
        salida[*n] = e5;
        *n += 1;
    }
    else {
        free(e5);
    }

    if(medio_a_dcha(ei,e6) == true) {
        salida[*n] = e6;
        *n += 1;
    }
    else {
        free(e6);
    }

    salida = (estado **) realloc(salida, (*n * sizeof(estado *)));
    return salida;
}
bool comprobarAncestralidad(estado *e1, estado *e2) {
    if(e2->padre == NULL){
        return false;
    }

    if(compararEstados(e2->padre, e1) == true) {
        return true;
    }
    return (comprobarAncestralidad(e1, e2->padre));
}
bool anadirSucesor(estado *e1, estado *e2) {
    estado **aux;

    if(e2->nSucesores == 0) {
        e2->sucesores = (estado **) malloc(1 * sizeof(estado *));
        if(e2->sucesores == NULL){
            return false;
        }
        e2->sucesores[0] = e1;
        e2->nSucesores = 1;
        return true;
    }
    else {
        aux = (estado **) malloc(e2->nSucesores * sizeof(estado *));
        if(aux == NULL) {
            return false;
        }
        //*aux = *e2->sucesores;
        memcpy(aux, e2->sucesores, e2->nSucesores * sizeof(estado *));
        e2->sucesores = (estado **) realloc(e2->sucesores, (e2->nSucesores + 1) * sizeof(estado *));
        if (e2->sucesores == NULL) {
            return false;
        }

        memcpy(e2->sucesores, aux, e2->nSucesores * sizeof(estado *));
//        for (i = 0; i < e2->nSucesores; i++) {
//            e2->sucesores[i] = aux[i];
//        }
        e2->sucesores[e2->nSucesores] = e1;
        e2->nSucesores += 1;
        free(aux);
        return true;
    }
}