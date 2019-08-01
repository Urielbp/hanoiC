//
// Created by Uriel Pinheiro on 2018-12-05.
//

#include "aEstrella.h"
#include "monticulo.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool aEstrella() {
    int longitudSolucion = -1;
    bool incluidoEnCerrados = false, incluidoEnAbiertos = false;
    estado *ei, *ef, *estadosSalida;
    estado **m;
    int *numeroNodosExpansion;
    int i, j,numeroCerrados = 0, abiertosPosicion, cerradosPosicion;
    monticulo abiertos;
    estado **cerrados;
    monticuloElemento montAux, montAux2;
    estado *estadoAux;

    cerrados = (estado **) calloc(MAXIMOCERRADOSABIERTOS, sizeof(estado *));
    ei = (estado *) calloc(1, sizeof(estado));
    ef = (estado *) calloc(1, sizeof(estado));
    numeroNodosExpansion = (int *) malloc(1 * sizeof(int));

    if(cerrados == NULL ||ei == NULL || ef == NULL || numeroNodosExpansion == NULL) {
        fprintf(stderr,"Error en la reserva de memoria\n");
        return false;
    }

    estadoAux = (estado *) malloc(1 * sizeof(estado));
    if(estadoAux == NULL) {
        return  false;
    }

    //Estado inicial y estado final
    for (i = 0; i < N; i++) {
        ei->c1[i] = i + 1;
        ef->c3[i] = i + 1;
    }

    ei->h = h2(ei);                     //TODO: Cambiar heurísitica
    ei->g = 0;
    ei->f = ei->g + ei->h;
    ei->nSucesores = 0;
    montAux.clave = ei->f;
    montAux.valor = ei;

    monticuloIniciar(&abiertos);
    monticuloInsertar(montAux, &abiertos);

    while(1){
        //Si la lista de abiertos está vacía, devuelve fallo
        if(monticuloEstaVacio(&abiertos) == true) {
            return false;
        }
        //Si hubo algún error al eliminar el nodo actual, devolvemos fallo
        if(monticuloEliminar(&montAux, &abiertos) == false) {
            return false;
        }
        estadoAux = montAux.valor;
        //Si el nodo actual es el nodo final, tenemos la solución
        if(compararEstados(estadoAux,ef) == true) {
            printf("Solución hallada.\n");

            estadosSalida = (estado *) malloc((estadoAux->g + 1) * sizeof(estado));
            if (estadosSalida == NULL) {
                return false;
            }
            estadosSalida[0] = *estadoAux;
            longitudSolucion = 0;
            estadoAux = estadosSalida;
            while(estadoAux != NULL){
                longitudSolucion += 1;
                estadosSalida[longitudSolucion] = *estadoAux;
                estadoAux = estadoAux->padre;
            }

            printf("Solución con %d movimientos.", longitudSolucion - 1);
//            for (i = longitudSolucion ; i > 0; i--) {
//                printf("\n");
//                imprimirEstado(&estadosSalida[i]);
//            }
//            TODO: Para imprimir la solución

            free(ei);
            free(ef);
            free(cerrados);

            return true;
        }

        //Expandimos el nodo actual
        cerrados[numeroCerrados] = estadoAux;

        numeroCerrados += 1;
        m = devolverEstadosValidos(estadoAux, numeroNodosExpansion);


        for (i = 0; i < *numeroNodosExpansion; i++) {
            //Comprobamos si el nodo sucesor no es ascendiente de n
            if(comprobarAncestralidad(m[i], estadoAux) == false) {
                abiertosPosicion = 0;
                cerradosPosicion = 0;
                //Añadimos el nodo de M como sucesor de n
                m[i]->nSucesores = 0;
                if(anadirSucesor(m[i], estadoAux) == false) {
                    return false;
                }
                incluidoEnAbiertos = false;
                incluidoEnCerrados = false;
                m[i]->g = estadoAux->g + 1;
                m[i]->h = h2(m[i]);                     //TODO: Cambiar heurísitica
                m[i]->f = m[i]->g + m[i]->h;

                //Buscamos por el elemento en abiertos
                for (j = 0; j < abiertos.tamanio; j++) {
                    //Recorremos la lista de abiertos
                    if (compararEstados(abiertos.elemento[j + 1].valor, m[i])) {
                        //Si el sucesor ya está en la lista de abiertos
                        incluidoEnAbiertos = true;
                        abiertosPosicion = j + 1;
                        break;
                    }
                }
                //Buscamos por el elemento en cerrados
                for (j = 0; j < numeroCerrados; j++) {
                    if (compararEstados(cerrados[j], m[i])) {
                        incluidoEnCerrados = true;
                        cerradosPosicion = j;
                        break;
                    }
                }

                if(incluidoEnAbiertos == true) {
                    if(m[i]->f > ((abiertos.elemento[abiertosPosicion].valor->f) )) {
                        monticuloDecrementarClave(abiertos.elemento[abiertosPosicion], m[i]->f, &abiertos);
                        m[i]->padre = estadoAux;
                    }
                }
                else if (incluidoEnCerrados == true) {
                    if(m[i]->f > ((cerrados[cerradosPosicion]->f) )) {
                        cerrados[cerradosPosicion]->f = m[i]->f;
                        m[i]->padre = estadoAux;
                    }

                    if((m[i]->f) < (cerrados[cerradosPosicion]->f)) {
                        //El camino por el nodo actual es mejor
                        m[i]->sucesores = (estado **) malloc((cerrados[cerradosPosicion]->nSucesores) * sizeof(estado *));
                        m[i]->nSucesores = cerrados[cerradosPosicion]->nSucesores;
                        for (j = 0; j < cerrados[cerradosPosicion]->nSucesores; j++) {
                            //m[i]->sucesores[j]->padre = cerrados[cerradosPosicion]->padre;
                            cerrados[cerradosPosicion]->sucesores[j]->padre = m[i];
                        }
                    }
                }
                else {
                    //Ni en abiertos ni cerrados
                    m[i]->padre = estadoAux;
                    montAux2.valor = m[i];
                    montAux2.clave = m[i]->f;
                    monticuloInsertar(montAux2, &abiertos);
                }
            }
        }
    }
}
