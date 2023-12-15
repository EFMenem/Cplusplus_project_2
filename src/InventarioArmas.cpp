#include "../include/InventarioArmas.hpp"

InventarioArmas::InventarioArmas() {
    es_maxima = true;
}

void InventarioArmas::agregar_arma(Arma* nueva_arma) {
    heap_armas.alta(nueva_arma);
}

void InventarioArmas::invertir_prioridades() {
     if(es_maxima) {//si es igual a true paso de maxima a minima
         while (!heap_armas.vacio()) {
          heap_armas_invertida.alta(heap_armas.baja());
         }
         es_maxima = false;
     } else { // si es false paso de minima a maxima.
         while (!heap_armas_invertida.vacio()) {
             heap_armas.alta(heap_armas_invertida.baja());
         }
         es_maxima = true;
     }
}

Arma* InventarioArmas::consultar() {
    if (es_maxima && !heap_armas.vacio() ) {
        return heap_armas.primero();
    } else if (!es_maxima && !heap_armas_invertida.vacio()) {
        return heap_armas_invertida.primero();
    } else {
        std::cout << "El inventario esta vacio " << std::endl;
        return nullptr;
    }
}

Arma* InventarioArmas::eliminar() {
    if (es_maxima && !heap_armas.vacio()) {
        return heap_armas.baja();
    } else if(!es_maxima && !heap_armas_invertida.vacio()) {
        return heap_armas_invertida.baja();
    } else {
        return nullptr;
    }
}

bool InventarioArmas::es_heap_maximo() {
    return es_maxima;
}

bool InventarioArmas::vacio() {
    return (heap_armas.vacio()) && (heap_armas_invertida.vacio());
}
