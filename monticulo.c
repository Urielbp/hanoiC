//
// Created by Uriel Pinheiro on 2018-12-05.
//

#include "monticulo.h"
#include <stdlib.h>
#include <stdbool.h>

void monticuloFiltradoAscendente(monticulo *m, int i){
    while(m->elemento[i/2].clave > m->elemento[i].clave){
        i = i/2;
    }
}

void monticuloFiltradoDescendente(monticulo *m, int i){
    int finFiltrado = 0;
    int hijo;
    while(2*i <=m->tamanio && (!finFiltrado)){
        hijo = 2*i;
        if(hijo != m->tamanio){
            if(m->elemento[hijo+1].clave < m->elemento[hijo].clave)
                hijo++;
        }
        if(m->elemento[m->tamanio].clave > m->elemento[hijo].clave){
            i = hijo;
        }
        else
            finFiltrado = 1;
    }
}

void monticuloIniciar(monticulo *m){
    m->tamanio = 0;
}

bool monticuloEstaVacio(monticulo *m) {
    if(m->tamanio == 0) {
        return true;
    }
    else {
        return false;
    }
}

bool monticuloInsertar(monticuloElemento x, monticulo *m) {
    int i;
    monticuloElemento aux;

    if (m->tamanio == MAXIMOCERRADOSABIERTOS)
        return false;
    m->tamanio++;
    i = m->tamanio;
    m->elemento[i] = x;
    while(m->elemento[i/2].clave > m->elemento[i].clave) {
        aux = m->elemento[i];
        m->elemento[i] = m->elemento[i/2];
        m->elemento[i/2] = aux;
        i = i/2;
    }
    m->elemento[i].clave = x.clave;
    m->elemento[i].valor = x.valor;
    return true;
}

bool monticuloEliminar(monticuloElemento *minimo, monticulo *m){
    int finFiltrado = 0;
    int hijo;
    int i;
    monticuloElemento ultimo;
    ultimo.clave = m->elemento[m->tamanio].clave;
    ultimo.valor = m->elemento[m->tamanio].valor;

    if(monticuloEstaVacio(m) == true)
        return false;
    minimo->clave = m->elemento[1].clave;
    minimo->valor = m->elemento[1].valor;
    m->tamanio--;
    i = 1;

    while(2*i <=m->tamanio && (!finFiltrado)){
        hijo = 2*i;
        if(hijo != m->tamanio){
            if(m->elemento[hijo+1].clave < m->elemento[hijo].clave)
                hijo++;
        }
        if(m->elemento[m->tamanio].clave > m->elemento[hijo].clave){
            m->elemento[i].clave = m->elemento[hijo].clave;
            m->elemento[i].valor = m->elemento[hijo].valor;
            i = hijo;
        }
        else
            finFiltrado = 1;
    }

    m->elemento[i].clave = ultimo.clave;
    m->elemento[i].valor = ultimo.valor;

    return true;
}

void monticuloDecrementarClave(monticuloElemento elemento, monticuloClaveTipo nuevoValor, monticulo *m) {
    int i, tam;
    monticuloElemento aux[MAXIMOCERRADOSABIERTOS];
    monticuloElemento elementoAux;

    tam = m->tamanio;
    for(i = 0; i < tam; i++) {
        monticuloEliminar(&elementoAux, m);
        if(elementoAux.valor == elemento.valor) {
            elementoAux.clave = nuevoValor;
        }
        aux[i] = elementoAux;
    }

    for(i = 0; i < tam; i++) {
        elementoAux = aux[i];
        monticuloInsertar(elementoAux, m);
    }
}

void monticuloIncrementarClave(int posicion, monticuloClaveTipo incremento, monticulo *m){
    m->elemento[posicion].clave += incremento;
    monticuloFiltradoDescendente(m, posicion);
}



