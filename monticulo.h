//
// Created by Uriel Pinheiro on 2018-12-05.
//

#ifndef HANOIC_MONTICULO_H
#define HANOIC_MONTICULO_H

#include <stdbool.h>
#include "estado.h"
#include "aEstrella.h"

typedef int monticuloClaveTipo;
typedef estado *monticuloValorTipo;

typedef struct {
    monticuloClaveTipo clave;
    monticuloValorTipo valor;
} monticuloElemento;

typedef struct {
    monticuloElemento elemento[MAXIMOCERRADOSABIERTOS];
    int tamanio;
} monticulo;

void monticuloFiltradoAscendente(monticulo *m, int i);
void monticuloFiltradoDescendente(monticulo *m, int i);
void monticuloIniciar(monticulo *m);
bool monticuloEstaVacio(monticulo *m);
bool monticuloInsertar(monticuloElemento x, monticulo *m);
bool monticuloEliminar(monticuloElemento *minimo, monticulo *m);
void monticuloDecrementarClave(monticuloElemento elemento, monticuloClaveTipo nuevoValor, monticulo *m);
void monticuloIncrementarClave(int posicion, monticuloClaveTipo incremento, monticulo *m);


#endif //HANOIC_MONTICULO_H
