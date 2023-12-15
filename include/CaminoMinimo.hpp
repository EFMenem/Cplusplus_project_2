#ifndef GRAFOS_CAMINOMINIMO_H
#define GRAFOS_CAMINOMINIMO_H

#include <cstddef>
#include <vector>
#include "Matriz.hpp"

const int INFINITO = 66666;

class CaminoMinimo {
protected:
    Matriz matriz_adyacencia;
    size_t cantidad_vertices;
public:
    // Pre: Origen y destino deben ser vértices válidos. La cantidad de vértices debe corresponder con la matriz.
    // Post: Devuelve el camino mínimo desde el vértice origen al destino.
    virtual std::vector<size_t>

    // Pre: Recibe una matriz de adyacencia, la cantidad de vertices, el origen y el destino.
    // Post: Devuelve el camino minimo desde el origen al destino.
    calcular_camino_minimo(Matriz adyacencia, size_t vertices, size_t origen, size_t destino, bool hay_cambios) = 0;

    virtual ~CaminoMinimo() {};
};

#endif