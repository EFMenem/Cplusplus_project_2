#include "../include/Floyd.hpp"

Floyd::Floyd() {}

void Floyd::inicializar_matrices() {
    matriz_caminos = Matriz(cantidad_vertices);
    for (size_t i = 0; i < cantidad_vertices; i++) {
        for (size_t j = 0; j < cantidad_vertices; j++) {
            matriz_caminos.elemento(i, j) = (int) j;
        }
    }

    matriz_costos = matriz_adyacencia;
}

std::vector<size_t> Floyd::obtener_camino(size_t origen, size_t destino) {
    std::vector<size_t> camino;
    camino.push_back(origen);
    size_t vertice = origen;
    while(vertice != destino) {
        vertice = (size_t) matriz_caminos.elemento(vertice,destino);
        camino.push_back(vertice);
    }
    return camino;
}

std::vector<size_t>
Floyd::calcular_camino_minimo(Matriz adyacencia, size_t vertices, size_t origen, size_t destino, bool hay_cambios) {
    if (hay_cambios) {
        matriz_adyacencia = adyacencia;
        cantidad_vertices = vertices;
        inicializar_matrices();

        for (size_t k = 0; k < cantidad_vertices; k++) {
            for (size_t fila = 0; fila < cantidad_vertices; fila++){
                for(size_t columna = 0; columna < cantidad_vertices; columna++) {
                    if(matriz_costos.elemento(fila,columna) > (matriz_costos.elemento(fila,k) + matriz_costos.elemento(k,columna))) {
                        matriz_costos.elemento(fila,columna) = matriz_costos.elemento(fila,k) + matriz_costos.elemento(k,columna);
                        matriz_caminos.elemento(fila,columna) = matriz_caminos.elemento(fila,k);
                    }
                }
            }
        }
    }

    return obtener_camino(origen, destino);
}

Floyd::~Floyd() {}