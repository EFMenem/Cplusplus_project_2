
#ifndef LABERINTO_HPP
#define LABERINTO_HPP

#include <iostream>
#include <string>
#include <cstddef>
#include <vector>
#include <algorithm>

#include "Grafo.hpp"
#include <iomanip>

const size_t PESO_ARISTA = 10;
const size_t MULTIPLICADOR_PYRAMID = 5;
const size_t FILAS = 9;
const size_t COLUMNAS = 9;

class Laberinto {
private:
    Grafo grafo;
    Grafo grafo_con_pyramidhead;
    std::vector<size_t> casilleros_validos;
    std::vector<size_t> pyramidhead_poses;
    size_t vertice_inicial;
    size_t vertice_final;

    //PRE: fila, inicio y fin tienen que ser mayor o igual que cero y menor que 9.
    //POST: conecta las nodos del grafo por fila.
    void conectar_fila(Grafo& grafo, size_t fila, size_t inicio, size_t fin);

    //PRE: fila, inicio y fin tienen que ser mayor o igual que cero y menor que 9.
    //POST: conecta los nodos del grafo por columna.
    void conectar_columna(Grafo& grafo, size_t columna, size_t inicio, size_t fin);

    //PRE:--
    //POST: asigna a la matriz los casilleros validos para moverse
    void asignar_casillero(std::vector<std::vector<std::string> >& matriz);

    //PRE:--
    //POST: asigna a la matriz los piramid head
    void asignar_pyramid(std::vector<std::vector<std::string> >& matriz);

    //PRE:--
    //POST: asigna a la matriz la posicion actual del jugador
    void asignar_jugador(size_t posicion,std::vector<std::vector<std::string> > &matriz);

    //PRE:--
    //POST: imprime la matriz por pantalla
    void imprimir_matriz(std::vector<std::vector<std::string> >& matriz);

    //PRE:--
    //POST: genera el layout 1 para la interfaz del juego
    void layout_1();

    //PRE:--
    //POST: genera el layout 2 para la interfaz del juego
    void layout_2();

    //PRE:
    //POST: devuelve true si se puede mover del origen hasta el destino
    bool son_vecinos(size_t casillero_1, size_t casillero_2);

public:
    //constructor.
    Laberinto();

    //PRE:--
    //POST: dependiendo si la altura es par o impar genera el layout correspondiente para el nivel.
    void generar_layouts(size_t altura);

    //PRE:--
    //POST: calcular camino minimo con dijkstra sin tener en cuenta los pyramid head.
    std::pair<std::vector<size_t>, int> camino_minimo_dijkstra(size_t origen, size_t destino);

    //PRE:--
    //POST: calcular camino minimo con floyd sin tener en cuenta los pyramid head.
    std::pair<std::vector<size_t>, int> camino_minimo_floyd(size_t origen, size_t destino);

    //PRE:--
    //POST: calcular camino minimo con dijkstra teniendo en cuenta los pyramid head (sin arma).
    std::pair<std::vector<size_t>, int> camino_minimo_dijkstra_pyramidhead(size_t origen, size_t destino);

    //PRE:--
    //POST: calcular camino minimo con floyd teniendo en cuenta los pyramid head (sin arma).
    std::pair<std::vector<size_t>, int> camino_minimo_floyd_pyramidhead(size_t origen, size_t destino);

    //PRE:
    //POST: dentro de la probabilidad de que aparezcan los pyramidhead, los asigna algun vertice del grafo.
    void agregar_pyramidhead();

    //PRE:--
    //POST:eliminar un pyramidhead si pasan con un arma equipada por encima
    void eliminar_pyramidhead(size_t posicion);
    //ESTO SOLO ES PARA TESTEAR.
    //PRE:
    //POST: Agregar 2 pyramid en posicion 25 y 26 para bloquear el paseo en el layout 1.
    void test_pyramidhead_bloqueadores();

    //PRE:--
    //POST: devuelve verdadero si el casillero no esta ocupado por un pyramid, o es el casillero inicial/final o una pared.
    bool es_casillero_valido(size_t casillero);

    //PRE:--
    //POST:devuelve verdadero si la posicion no esta ocupada por un pyramidhead
    bool es_pyramidhead_pose(size_t pyramidhead_pose);

    //PRE:--
    //POST:devuelve true si la posicion1 es un vecino de posicion2
    bool es_vecino(size_t posicion1, size_t posicion2);

    //PRE:--
    //POST:cambia el peso de las aristas con los vertices de pyramidhead
    void cambiar_peso_pyramidhead(size_t pyramidhead_pose);

    //PRE:--
    //POST: devuelve el vector de las poses de pyramid head.
    std::vector<size_t> get_pyramidhead_poses();

    //PRE:
    //POST: devuelve el vector de los casilleors validos.
    std::vector<size_t> get_casilleros_validos();

    //PRE:--
    //POST: imprime por pantalla el laberinto.
    void imprimir_laberinto(size_t posicion);

    // Destructor.
    ~Laberinto() {};
};

#endif