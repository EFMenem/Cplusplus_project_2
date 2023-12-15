#include "../include/Juego.hpp"

using namespace std;

Juego::Juego() {
    costo_total = 0;
    nivel = 1;
    arma_equipada = nullptr;
    inventario_armas = nullptr;
    arbol_placas = nullptr;
    posicion_actual = 0;
    nivel_logrado = false;
    nivel_perdido = false;
    juego_ganado = false;
}

void Juego::limpiar_terminal() {
    system("clear"); // Para sistemas tipo Unix/Linux/macOS
}

char Juego::menu_inicio() {
    char respuesta;
    std::cout << "¿Deseas jugar Silent Hill 2? (S/N): ";
    std::cin >> respuesta;
    while(toupper(respuesta) != 'S' && toupper(respuesta) != 'N') {
        std::cout << "Por favor, ingresa 'S' o 'N'.\n";
        std::cin >> respuesta;
    }
    return respuesta;
}


void Juego::generar_nivel(size_t altura) {
    laberinto = Laberinto(); //inicializo el laberinto
    laberinto.generar_layouts(altura); // genero los layout dependiendo la altura
    srand( static_cast<unsigned > (time(nullptr)));
    for(int i = 0; i < 2; i++){
        size_t random = static_cast<size_t>(rand() % 2);
        if(random){
            laberinto.agregar_pyramidhead();
        }
    }
}

bool Juego::puede_mover(size_t casillero_origen, size_t casillero_destino, Arma* armas) {
    bool puede_mover = false;
    if (laberinto.es_casillero_valido(casillero_destino)&& !laberinto.es_pyramidhead_pose(casillero_destino)){//verifica si el destino es un casillero valido.
        obtener_camino_minimo(casillero_origen, casillero_destino);//calcula el camino minimo con su peso.
        if (camino_minimo.second == 10) { //aca se verifica si el peso del camino es igual a 10.
            puede_mover = true;
        }
    } else if(casillero_destino == 8 || casillero_destino == 72){
        puede_mover = true;

    } else if(laberinto.es_pyramidhead_pose(casillero_destino) && arma_equipada){
        puede_mover = true;
    }
    return puede_mover;
}

bool Juego::pisar_pyramidhead(size_t posicion) {
    return laberinto.es_pyramidhead_pose(posicion);
}
void Juego::imprimir_layout(size_t posicion) {
    laberinto.imprimir_laberinto(posicion);
    vector<size_t> pyramid = laberinto.get_pyramidhead_poses();
    for (size_t i = 0 ; i < pyramid.size(); i++) {
        cout << "Hay un pyramid head en pose : " << pyramid[i] << endl;
    }
}

bool Juego::hay_pyramidhead() {
    return !laberinto.get_pyramidhead_poses().empty();
}

void Juego::eliminar_pyramidhead(size_t posicion) {
    laberinto.eliminar_pyramidhead(posicion);
}

bool Juego::es_vecino_pyramid_head(size_t posicion) {
    bool vecino = false;
    size_t i = 0;
    size_t linea1 = posicion / (size_t )9;
    size_t columna1 = posicion % (size_t) 9;
    vector<size_t> pyramidhead_pose = laberinto.get_pyramidhead_poses();
    while (i < pyramidhead_pose.size() && !vecino) {
        size_t linea2 = pyramidhead_pose[i] / 9;
        size_t columna2 = pyramidhead_pose[i] % 9;
        bool vecino_horizontal = (linea1 == linea2) && (abs((int) columna1 - (int) columna2) == 1);
        bool vecino_vertical = (columna1 == columna2) && (abs((int) linea1 - (int) linea2) == 1);
        vecino = vecino_horizontal || vecino_vertical;
        i++;
    }
    return vecino;
}

void Juego::obtener_camino_minimo(size_t origen, size_t destino) {
    // devuelve una tupla con el vector camino y el peso del camino
    camino_minimo = laberinto.camino_minimo_dijkstra(origen, destino);
}

void Juego::obtener_camino_minimo_con_pyramidhead(size_t origen, size_t destino) {
    //devuelve una tupla con el vector camino sin pasar por pyramidhead y el peso del camino.
    camino_minimo = laberinto.camino_minimo_dijkstra_pyramidhead(origen, destino);
}

void Juego::calcular_camino_minimo_con_pyramidhead(size_t origen, size_t destino) {
    camino_minimo = laberinto.camino_minimo_dijkstra_pyramidhead(origen, destino);
    //aca se modifica camino minimo con pyramid_head
}

void Juego::calcular_camino_minimo_sin_pyramidhead(size_t origen, size_t destino) {
    //aca se modifica camino minimo sin pyramid_head
    camino_minimo = laberinto.camino_minimo_dijkstra(origen, destino);
}


void Juego::reiniciar_nivel() {
    nivel_logrado = false;
    nivel_perdido = false;
    camino_minimo.first.clear();
    camino_minimo.second = 0;
}

void Juego::definir_camino_minimo_con_o_sin_arma() {
    if(arma_equipada){
        std::cout << "----------------------------------------\n";
        cout << "Camino minimo con arma equipada: " ;
        obtener_camino_minimo(posicion_actual, DESTINO);
    } else {
        std::cout << "----------------------------------------\n";
        cout << "Camino minimo sin arma equipada: ";
        if(hay_pyramidhead()) {
            obtener_camino_minimo_con_pyramidhead(posicion_actual, DESTINO);
        } else {
            obtener_camino_minimo(posicion_actual,DESTINO);
        }
    }
}

void Juego::menu_jugador() {
    std::cout << "----------------------------------------\n";
    std::cout<< "Acciones:\n -Izquierda (A)\n -Derecha (D)\n -Arriba (W)\n -Abajo (S)\n "
                "-Ir hasta el fin (F) \n -Equipar/Desequipar (E)\n -Invertir prioridad (I)\n";
    std::cout << "----------------------------------------\n";
    std::cout << "Opcion : ";
}

void Juego::contar_movimientos(size_t nueva_posicion) {
    if(nueva_posicion == posicion_actual) {
        costo_total += 0;
    } else {
        if (puede_mover(posicion_actual, nueva_posicion, arma_equipada)) {
            posicion_actual = nueva_posicion;
            if (arma_equipada) {
                if (pisar_pyramidhead(nueva_posicion)) {
                    destruir_arma();
                    eliminar_pyramidhead(nueva_posicion);
                }
                costo_total += (int) PESO_ARISTA;
            } else {
                if (es_vecino_pyramid_head(nueva_posicion)) {
                    costo_total += (int) (PESO_ARISTA * MULTIPLICADOR_PYRAMID);
                } else {
                    costo_total += (int) PESO_ARISTA;
                }//ver de usar el grafo para calcular el costo de los movimientos.
            }
        }
    }
}

void Juego::mover_jugador() {
    char movimiento;

    imprimir_layout(posicion_actual);
    std::cout << "El costo por ahora es : " << costo_total << std::endl;
    menu_jugador();
    cin >> movimiento;
    hay_pyramid_camino_minimo();
    size_t nueva_posicion = posicion_actual;
    switch (toupper(movimiento)) {
        case 'A':
            nueva_posicion -= 1;
            limpiar_terminal();
            cout << "\n";
            break;
        case 'D':
            nueva_posicion += 1; //usar grafo para esto tmb
            limpiar_terminal();
            cout << "\n";
            break;
        case 'W':
            nueva_posicion -= 9;
            limpiar_terminal();
            cout << "\n";
            break;
        case 'S':
            nueva_posicion += 9;
            limpiar_terminal();
            cout << "\n";
            break;
        case 'E':
            limpiar_terminal();
            if (!arma_equipada) {
                if (!inventario_armas->vacio()) {
                    arma_equipada = inventario_armas->eliminar();
                    cout << "Se equipo el arma" << endl;
                } else {
                    std::cout << "No hay armas en el inventario\n";
                }
            }else {
                inventario_armas->agregar_arma(arma_equipada);
                arma_equipada = nullptr;
                std::cout << "El arma se guardo en el inventario\n";
            }
            break;
        case 'I':
            limpiar_terminal();
            inventario_armas->invertir_prioridades(); //modularizar todos los casos. hacer metodo para cada opcion
            std::cout << "Se invirtio la prioridad \n";
            break;
        case 'F':
            limpiar_terminal();
            if (camino_minimo.second < INFINITO && camino_minimo.second != 0) {

                if(hay_pyramid_camino_minimo()) {
                    destruir_arma();
                }
                posicion_actual = DESTINO;
                costo_total += camino_minimo.second;
                cout << "costo total despues de mover al final : "<< costo_total << endl;
            }
            break;
        default:
            limpiar_terminal();
            std::cout << "Por favor, ingresa una opción válida'.\n";
            break;
    }
    if(posicion_actual != DESTINO){
        contar_movimientos(nueva_posicion);
    }
}

void Juego::imprimir_camino_minimo() {
    for (size_t i = 1; i < camino_minimo.first.size(); ++i) { //es 1 porque el primer casillero es donde arrancamos.
        std::cout << camino_minimo.first[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "----------------------------------------\n";
}

void Juego::verificar_camino_minimo() {
    if (camino_minimo.second > INFINITO || camino_minimo.second == 0) {
        std::cout << "----------------------------------------\n";
        std::cout << "Situacion imposible\n" << std::endl;
        std::cout << "----------------------------------------\n";
        nivel_perdido = true;
    } else {
        std::cout << "----------------------------------------\n";
        std::cout << "Costo del camino : " << camino_minimo.second << std::endl;
        std::cout << "----------------------------------------\n";
    }
}

void Juego::menu_nivel() {
    posicion_actual = 72; //lo tiene que manejar laberinto.
    size_t altura = arbol_placas->altura();
    generar_nivel(altura);
    while(!nivel_perdido && !nivel_logrado && !juego_ganado) {

        cout << "Nivel: " << nivel << endl;
        definir_camino_minimo_con_o_sin_arma();
        imprimir_camino_minimo();
        verificar_camino_minimo();
        if(!nivel_perdido){
            mover_jugador();
            if (posicion_actual == DESTINO) {
                nivel_logrado = true;
            }
        }
    }
}

Placa Juego::generar_placa_aleatoria() {
    srand(static_cast<unsigned int>(time(nullptr)));
    int id = 100 + rand() % (666 - 100 + 1); // Generar un ID aleatorio entre 100 y 666
    cout << "ID de placa generada: " << id << endl;
    Placa placa_generada("Nombre", "Leyenda", id);
    return placa_generada; //conceptualmente tener las placas en heap.
}

bool Juego::hay_pyramid_camino_minimo() {
    bool hay_pyramid = false;
    size_t i = 0;
    while (i < camino_minimo.first.size() && !hay_pyramid) {
        if(pisar_pyramidhead(camino_minimo.first[i])) {
            std::cout << "Hay pyramid head en camino mimino en  " << camino_minimo.first[i] << std::endl;
            hay_pyramid = true;
        }
        i++;
    }
    return hay_pyramid;
}

void Juego::probar_suerte_arma(InventarioArmas &Inventario) {
    std::string nombre_armas[] = {"Pistola", "Escopeta", "Rifle", "Lanzagranadas", "Arco",
                                  "Espada", "Ballesta", "Lanza", "Cuchillo", "Hacha"}; //el arreglo puede ser una constante
    int index_arma_aleatoria = rand() % 10; // Elegir un índice entre 0 y 9
    int chance = rand() % 100; // Generar un número entre 0 y 99
    if (chance <= 20) { // Probabilidad del 20%
        size_t potencia_aleatoria = (size_t) (10 + rand() % (100 - 10 + 1)); // Potencia entre 10 y 100
        Arma* arma_aleatoria = new Arma(nombre_armas[index_arma_aleatoria], potencia_aleatoria);
        inventario_armas->agregar_arma(arma_aleatoria);
        std::cout << "¡Conseguiste un arma aleatoria: " << nombre_armas[index_arma_aleatoria]
                  << " con potencia " << potencia_aleatoria << "!\n";
        delete arma_aleatoria;
    } else {
        std::cout << "No has tenido suerte esta vez. No has obtenido un arma.\n";
    }
}

void Juego::destruir_arma() {
    if (arma_equipada) {
        arma_equipada = nullptr;
        std::cout << "Se destruyó el arma\n";
    } else {
        std::cout << "No hay ningun arma equipada.\n";
    }
}

void Juego::agregar_arma_aleatoria(InventarioArmas &Inventario) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(10, 100); // Rango de potencia entre 10 y 100
    std::uniform_int_distribution<> dis_index(0, 9); // Rango de índices de armas
    size_t potencia_aleatoria = (size_t) dis(gen); // Potencia aleatoria entre 10 y 100
    std::string nombre_armas[] = {"Pistola", "Escopeta", "Rifle", "Lanzagranadas", "Arco",
                                  "Espada", "Ballesta", "Lanza", "Cuchillo", "Hacha"};
    int index_arma_aleatoria = dis_index(gen); // Índice aleatorio entre 0 y 9
    // Crear el arma aleatoria con la potencia generada y el nombre correspondiente
    Arma* arma_aleatoria = new Arma(nombre_armas[index_arma_aleatoria], potencia_aleatoria);
    inventario_armas->agregar_arma(arma_aleatoria);
    std::cout << "Arma aleatoria agregada al inventario: " << nombre_armas[index_arma_aleatoria]
              << " con potencia " << potencia_aleatoria << "\n";
    delete arma_aleatoria;
}


void Juego::condiciones_inciales() {
    char dificultad;
    std::cout << "\n¿Que dificultad desea?\n\nFacil (F) -> comienza con un arma en el inventario\nSupervivencia (S)"
                 " -> comienza sin ningun arma en el inventario.\nOpcion : ";
    cin >>dificultad;
    limpiar_terminal();
    while (toupper(dificultad) != 'S' && toupper(dificultad) != 'F') {
        std::cout << "Por favor ingrese un valor valido F/S" << endl;
        cin >> dificultad;
    }
    if(toupper(dificultad) == 'F') {
        agregar_arma_aleatoria(*inventario_armas);
    }
}

void Juego::jugar_juego() {
    reiniciar_nivel();
    menu_nivel(); // Inicia la interacción con el usuario
    if(nivel_logrado){
        std::cout << "----------------------------------------" << endl;
        cout << "NIVEL LOGRADO !!!" << endl;
        std::cout << "----------------------------------------" << endl;
        cout << "COSTO TOTAL : " << costo_total << endl;
        std::cout << "----------------------------------------" << endl;
        nivel++;
        probar_suerte_arma(*inventario_armas);
        Placa placa_obtenida = generar_placa_aleatoria();
        arbol_placas->alta(placa_obtenida);
    }else{
        cout << "Nivel perdido! Intenta otra vez." << endl;
    }
}


void Juego::iniciar_juego() {
    bool salir = false;
    arbol_placas = new ABB<Placa,Placa::menor,Placa::igual>();
    inventario_armas  = new InventarioArmas();
    char respuesta = menu_inicio();
    if (toupper(respuesta) == 'S') {
        condiciones_inciales();
        int i = 0;
        while(!nivel_perdido && i < 5 && !salir){
            jugar_juego();
            char opcion_salir;
            std::cout << "¿Deseas salir? (S) para salir o ingrese cualquier otra cosa para seguir: ";
            std::cin >> opcion_salir;
            if (toupper(opcion_salir) == 'S') {
                salir = true;
            }
            limpiar_terminal();
            i++;

        }
        if (i == 5) {
            std::cout << "\n" << std::endl;
            std::cout << "═════════════════════════════════════\n";
            std::cout << "HAS GANADO EL JUEGO!!!" << endl;
            std::cout << "═════════════════════════════════════\n";
        }
    }
}

Juego::~Juego() {
    if(arbol_placas) {
        delete arbol_placas;
    }
    if(inventario_armas) {
        delete inventario_armas;
    }
}



