#ifndef INVENTARIOARMAS_H
#define INVENTARIOARMAS_H

#include "Heap.hpp"
#include "Arma.hpp"

#include<iostream>

class InventarioArmas {
private:
    Heap<Arma *, Arma::mayor> heap_armas ;
    Heap<Arma *, Arma::menor> heap_armas_invertida;
    bool es_maxima;

public:
    // Constructor
    InventarioArmas();

    //PRE:--
    //POST: invierte las prioridades del inventario. Pasa de un heap de maxima a uno de minima y viceversa
    void invertir_prioridades();

    //PRE:--
    //POST: agrega la nueva arma tanto al heap de maxima como el de minima.
    void agregar_arma(Arma *nueva_arma);

    //PRE: ningun heap puede estar vacio
    //POST: devuelve el primer elemento del heap de maxima o minima.
    Arma *consultar();

    //PRE: --
    //POST: elimina el primer elemento del heap de maxima o minima y lo devuelve.
    Arma *eliminar();

    //PRE:--
    //POST: devuelve el valor de es_maxima
    bool es_heap_maximo();

    //PRE:
    //POST:devuelve verdadero si el inventario esta vacio
    bool vacio();

};
#endif