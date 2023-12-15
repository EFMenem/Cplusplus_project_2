#include "../include/Dijkstra.hpp"

Dijkstra::Dijkstra() {
    vertices_visitados = nullptr;
    distancia = nullptr;
    recorrido = nullptr;
}

void Dijkstra::inicializar_arreglos(size_t origen) {
    delete[] vertices_visitados;
    delete[] distancia;
    delete[] recorrido;
    
    vertices_visitados = new bool[cantidad_vertices];
    distancia = new int[cantidad_vertices];
    recorrido = new size_t[cantidad_vertices];

    for (size_t i = 0; i < cantidad_vertices; i++) {
        vertices_visitados[i] = false;
        recorrido[i] = origen;
        distancia[i] = matriz_adyacencia.elemento(origen, i);
    }
    vertices_visitados[origen] = true;
}

size_t Dijkstra::vertice_minima_distancia() {
    int distancia_minima = INFINITO;
    size_t vertice_minimo;
    for (size_t i = 0; i < cantidad_vertices; i++) {
        if (!vertices_visitados[i] && distancia[i] <= distancia_minima) {
            distancia_minima = distancia[i];
            vertice_minimo = i;
        }
    }
    return vertice_minimo;
}

void Dijkstra::actualizar_distancia(size_t vertice) {
    for (size_t i = 0; i < cantidad_vertices; i++) {
        if (!vertices_visitados[i] && distancia[vertice] != INFINITO &&
            distancia[i] > matriz_adyacencia.elemento(vertice, i) + distancia[vertice]) {
            distancia[i] = matriz_adyacencia.elemento(vertice, i) + distancia[vertice];
            recorrido[i] = vertice;
        }
    }
}

std::vector<size_t> Dijkstra::obtener_camino(size_t origen, size_t destino) {
    std::vector<size_t> camino;

    // TODO: Escribir el código necesario, haciendo uso de los métodos existentes.
   if(distancia[destino] == INFINITO){
        return camino;
    }else{
        do{
            camino.insert(camino.begin(),destino);
            destino = recorrido[destino];
        }while(origen != destino);
        camino.insert(camino.begin(),origen);
    }
    return camino;
}

std::vector<size_t>
Dijkstra::calcular_camino_minimo(Matriz adyacencia, size_t vertices, size_t origen, size_t destino,
                                 bool hay_cambios) {
    matriz_adyacencia = adyacencia;
    cantidad_vertices = vertices;
    inicializar_arreglos(origen);

    // TODO: Escribir el código necesario, haciendo uso de los métodos existentes.
    bool destino_arribado = origen == destino;
    while(!destino_arribado){
        size_t minimo_vertice = vertice_minima_distancia();
        destino_arribado = minimo_vertice == destino;
        if(!destino_arribado){
            vertices_visitados[minimo_vertice] = true;
            actualizar_distancia(minimo_vertice);
        }
    }

    return obtener_camino(origen, destino);
}

Dijkstra::~Dijkstra() {
    delete[] vertices_visitados;
    delete[] distancia;
    delete[] recorrido;
}