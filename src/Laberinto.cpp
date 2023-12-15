#include "../include/Laberinto.hpp"

using namespace std;


Laberinto::Laberinto() {
    grafo = Grafo(81);
    vertice_inicial = 72;
    vertice_final = 8;
}

void Laberinto::conectar_fila(Grafo& grafos, size_t fila, size_t inicio, size_t fin) {
    for (size_t i = inicio; i < fin; i++) {
        grafos.cambiar_arista((fila * 9) + i, (fila * 9) + i + 1, PESO_ARISTA);
        grafos.cambiar_arista((fila * 9) + i + 1, (fila * 9) + i, PESO_ARISTA);
    }
}

void Laberinto::conectar_columna(Grafo& grafos, size_t columna, size_t inicio, size_t fin) {
    for (size_t i = inicio; i < fin; i++) {
        grafos.cambiar_arista(i * 9 + columna, (i + 1) * 9 + columna, PESO_ARISTA);
        grafos.cambiar_arista((i + 1) * 9 + columna, i * 9 + columna, PESO_ARISTA);
    }
}

void Laberinto::layout_1() {
    conectar_columna(grafo,0,0,8);
    conectar_columna(grafo,1,7,8);
    conectar_columna(grafo,2,0,8);
    conectar_columna(grafo,4,0,8);
    conectar_columna(grafo,6,0,8);
    conectar_columna(grafo,8,0,8);
    conectar_fila(grafo,1,2,4);
    conectar_fila(grafo,2,6,8);
    conectar_fila(grafo,3,0,2);
    conectar_fila(grafo,4,4,6);
    conectar_fila(grafo,5,2,4);
    conectar_fila(grafo,7,0,2);
    conectar_fila(grafo,8,0,2);
    conectar_fila(grafo,8,4,8);

    casilleros_validos = {0,2,4,6,9,11,12,13,15,17,18,20,22,24,25,26, 27,28,29,31,33,35,36,38,40,41,42,44,45,47,48,
                          49,51,53,54,56,58,60,62,63,64,65,67,69,71,73,74,76,77,78,79,80};

}

void Laberinto::layout_2() {

    conectar_fila(grafo,0,0,8);
    conectar_fila(grafo,2,0,6);
    conectar_fila(grafo,3,6,8);
    conectar_fila(grafo,4,0,6);
    conectar_fila(grafo,6,0,4);
    conectar_fila(grafo,6,6,8);
    conectar_fila(grafo,8,0,2);
    conectar_fila(grafo,8,4,8);
    conectar_columna(grafo,0,0,2);
    conectar_columna(grafo,0,4,8);
    conectar_columna(grafo,2,2,4);
    conectar_columna(grafo,2,6,8);
    conectar_columna(grafo,4,4,8);
    conectar_columna(grafo,6,0,8);
    conectar_columna(grafo,8,0,6);

    casilleros_validos = {0,1,2,3,4,5,6,7,9,15,17,18,19,20,21,22,23,24,26,29,33,34,35,36,37,38,39,40,41,42,44,45,49,51,
                          53,54,55,56,57,58,60,61,62,63,65,67,69,73,74,76,77,78,79,80};
}

void Laberinto::asignar_casillero(std::vector<std::vector<std::string> >& matriz) {
    for (size_t casillero : casilleros_validos) {
        size_t fila = casillero / FILAS;
        size_t columna = casillero % COLUMNAS;//HACER METODO
        matriz[fila][columna] = " ";
    }
}

void Laberinto::asignar_pyramid(std::vector<std::vector<std::string> >& matriz) {
    for (size_t posicion : pyramidhead_poses) {
        size_t fila_pyramid = posicion / FILAS;
        size_t columna_pyramid = posicion % COLUMNAS;
        matriz[fila_pyramid][columna_pyramid] = "☻";

    }
}

void Laberinto::asignar_jugador(size_t posicion,std::vector<std::vector<std::string> > &matriz) {
    size_t fila = posicion / FILAS;
    size_t columna = posicion % COLUMNAS;//aca tmb
    matriz[fila][columna] = "☺";
}

void Laberinto::imprimir_matriz(std::vector<std::vector<std::string> > &matriz) {
    std::cout << " ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒\n";
    for (size_t i = 0; i < FILAS; ++i) {
        std::cout << " ▒ ";
        for (size_t j = 0; j < COLUMNAS; ++j) {
            std::cout << matriz[i][j] << " ";
        }//usar clase matriz
        std::cout << "▒ \n";
    }
    std::cout << " ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒\n";
    std::cout << "----------------------------------------\n";
}

void Laberinto::imprimir_laberinto(size_t posicion) {
    std::vector<std::vector<string> > matriz(FILAS, std::vector<string>(FILAS, "▒"));
    asignar_casillero(matriz);
    asignar_pyramid(matriz);
    matriz[0][8] = "L";
    matriz[8][0] = "S";
    asignar_jugador(posicion,matriz);
    imprimir_matriz(matriz);
}

void Laberinto::generar_layouts(size_t altura) {
    pyramidhead_poses.clear();
    casilleros_validos.clear();
    if(altura % 2 == 0) {
        layout_1();
    } else {
        layout_2();
    }
}

pair<std::vector<size_t>, int> Laberinto::camino_minimo_dijkstra(size_t origen, size_t destino) {
    grafo.usar_dijkstra();
    pair<std::vector<size_t>, int> res = grafo.obtener_camino_minimo(origen, destino);
    return res;
}

std::pair<std::vector<size_t>, int> Laberinto::camino_minimo_floyd(size_t origen, size_t destino) {
    grafo.usar_floyd();
    pair<std::vector<size_t>, int> res = grafo.obtener_camino_minimo(origen, destino);
    return res;
}

std::pair<std::vector<size_t>, int> Laberinto::camino_minimo_dijkstra_pyramidhead(size_t origen, size_t destino) {
    grafo_con_pyramidhead.usar_dijkstra();
    pair<std::vector<size_t>, int> res = grafo_con_pyramidhead.obtener_camino_minimo(origen, destino);
    return res;
}

std::pair<std::vector<size_t>, int> Laberinto::camino_minimo_floyd_pyramidhead(size_t origen, size_t destino) {
    grafo_con_pyramidhead.usar_floyd();
    pair<std::vector<size_t>, int> res = grafo_con_pyramidhead.obtener_camino_minimo(origen, destino);
    return res;
}

bool Laberinto::es_casillero_valido(size_t casillero) {
    bool valido = false;
    size_t i = 0;
    while(!valido && i < casilleros_validos.size()) {
        if(casilleros_validos[i] == casillero) {
            valido = true;
        }//crear un metodo para pasar por parametro lo que queremos buscar en el vector TDA
        i++;
    }
    return valido;
}

bool Laberinto::es_pyramidhead_pose(size_t pyramidhead_pose) {
    bool ocupado = false;
    size_t i = 0;
    while(!ocupado && i < pyramidhead_poses.size()) {
        if(pyramidhead_poses[i] == pyramidhead_pose) {
            ocupado = true;
        }
        i++;
    }
    return ocupado;
}

bool Laberinto::es_vecino(size_t posicion_1, size_t posicion_2) {
    bool vecino = false;
    if(posicion_1 < 81 && posicion_1 >= 0 && posicion_2 >= 0 && posicion_2 < 81){
        size_t fila_1 = posicion_1 / 9;
        size_t columna_1 = posicion_1 % 9;

        size_t fila_2 = posicion_2 / 9;
        size_t columna_2 = posicion_2 % 9;

        bool vecino_horizontal = (fila_1 == fila_2) && (abs((int) columna_1 - (int) columna_2) == 1);
        bool vecino_vertical = (columna_1 == columna_2) && (abs((int) fila_1 - (int) fila_2) == 1);
        vecino = vecino_horizontal || vecino_vertical;
    }
    return vecino;
}

void Laberinto::cambiar_peso_pyramidhead(size_t pyramidhead_pose) {
    size_t vecinos[4] = {pyramidhead_pose-1, pyramidhead_pose+1, pyramidhead_pose-9, pyramidhead_pose+9};
    for(int i=0; i<4; i++){//usar atributo o constantes
        if(es_vecino(pyramidhead_pose, vecinos[i]) && (es_casillero_valido(vecinos[i]) || vecinos[i]==8 || vecinos[i]==72)){
            grafo_con_pyramidhead.cambiar_arista(vecinos[i],pyramidhead_pose,INFINITO);
            size_t vecinos_vecinos[4] = {vecinos[i]-1, vecinos[i]+1, vecinos[i]-9, vecinos[i]+9};
            for(int j=0; j<4; j++){
                if(es_vecino(vecinos[i], vecinos_vecinos[j]) && es_casillero_valido(vecinos[j]) && vecinos_vecinos[j]!=pyramidhead_pose){
                    grafo_con_pyramidhead.cambiar_arista(vecinos_vecinos[j],vecinos[i],PESO_ARISTA * MULTIPLICADOR_PYRAMID);
                }
            }
        }
    }
}

void Laberinto::agregar_pyramidhead() {
    int N = 81;
    bool agregado = false;
    grafo_con_pyramidhead = grafo;//Pensarlo como set
    while (!agregado) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        size_t random = static_cast<size_t> (std::rand() % N);

        if (es_casillero_valido(random) && !es_pyramidhead_pose(random)) {
            cambiar_peso_pyramidhead(random);
            pyramidhead_poses.push_back(random);
            agregado = true;
        }
    }
}

void Laberinto::eliminar_pyramidhead(size_t posicion) {
    pyramidhead_poses.erase(std::remove(pyramidhead_poses.begin(), pyramidhead_poses.end(), posicion));
    //reiniciar grafo con un pyramid o los que queden
}

void Laberinto::test_pyramidhead_bloqueadores() {
    grafo_con_pyramidhead = grafo;
    cambiar_peso_pyramidhead(54);
    pyramidhead_poses.push_back(54);
    cambiar_peso_pyramidhead(58);
    pyramidhead_poses.push_back(58);
    return;
}

std::vector<size_t> Laberinto::get_pyramidhead_poses() {
    return pyramidhead_poses;
}

std::vector<size_t> Laberinto::get_casilleros_validos() {
    return casilleros_validos;
}
