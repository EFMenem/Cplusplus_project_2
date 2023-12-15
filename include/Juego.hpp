#ifndef JUEGO_HPP
#define JUEGO_HPP
#include "Laberinto.hpp"
#include "Arma.hpp"
#include "InventarioArmas.hpp"
#include "ABB.hpp"
#include "Placa.hpp"
#include <random>
#include <cstdlib>
#include "Grafo.hpp"

const size_t DESTINO = 8;
class Juego {
private:
    Laberinto laberinto;
    int costo_total;
    //Nivel* nivel_actual;
    int nivel;
    bool nivel_logrado;
    bool nivel_perdido;
    bool juego_ganado;
    Arma* arma_equipada;
    size_t posicion_actual;
    InventarioArmas* inventario_armas;//no hace falta ser puntero, porque siempre es uno
    ABB<Placa,Placa::menor,Placa::igual>* arbol_placas;//lo mismo que para inventario arma
    std::pair<std::vector<size_t>, int> camino_minimo;

    //PRE:
    //POST: Limpia la terminal (No terminal de IDE's)
    static void limpiar_terminal();

    //PRE:--
    //POST: Imprime por pantalla las preguntas iniciales antes de comenzar a jugar
    char menu_inicio();

    //PRE:--
    //POST: Agrega o no un arma al inventario armas dependiendo lo que elija el usuario.
    void condiciones_inciales();

    //PRE:--
    //POST: Llama a los metodos para que el juego comience.
    void jugar_juego();

    //PRE:
    //POST: Verifica si hay un pyramidhead en el camino minimo
    bool hay_pyramid_camino_minimo();

    //PRE:--
    //POST: Verifica si el camino minimo es posible o no. Si es posible imprime por pantalla el costo, si no lo
    // es da por perdido el nivel
    void verificar_camino_minimo();

    //PRE:--
    //POST: Imprime por pantalla el camino minimo desde la posicion inicial.
    void imprimir_camino_minimo();

    //PRE:--
    //POST: Define un camino minimo dependiendo si tiene equipada un arma o no.
    void definir_camino_minimo_con_o_sin_arma();

    //PRE: --
    //POST: Mueve al jugador
    void mover_jugador();

    //PRE:--
    //POST: Muestra el menu de comandos para moverse en el nivel
    void menu_jugador();

    //PRE:--
    //POST: Suma al costo total, cada movimiento del jugador.
    void contar_movimientos(size_t nueva_posicion);

    // PRE:--
    // POST: genera el nivel correspondiente dependiendo de si la altura es par o impar.
    void generar_nivel(size_t altura);

    //PRE:--
    //POST: verifica si se puede mover al casillero siguiente.
    bool puede_mover(size_t casillero_origen, size_t casillero_destino,Arma* arma_equipada);

    //PRE:--
    //POST: devuelve verdadero si la posicion coincide con la posicion de un pyramid head.
    bool pisar_pyramidhead(size_t posicion);

    //PRE:--
    //POST: devuelve verdadero si la posicion es adyacente a un pyramid head.
    bool es_vecino_pyramid_head(size_t posicion);

    //PRE: --
    //POST: imprime por pantalla el layout y se actualiza con el movmiento del jugador
    void imprimir_layout(size_t posicion);

    //PRE:--
    //POST: elimina el pyramidhead que este en la posicion pasada por parametro.
    void eliminar_pyramidhead(size_t posicion);

    //PRE:--
    //POST:devuelve verdadero si hay pyramid head en el laberinto.
    bool hay_pyramidhead();

    // PRE:--
    // POST: genera un nivel de test donde los pyramidhead bloquean el pasaje.
    void generar_nivel_bloqueado(size_t altura,size_t posicion_jugador);

    // PRE: Recibe el origen y el destino.
    // POST:  modifica el atributo camino minimo entre el origen y el destino.
    void obtener_camino_minimo(size_t origen, size_t destino);

    // PRE: Recibe el origen y el destino.
    // POST: Devuelve el camino minimo entre el origen y el destino si hay pyramidhead.
    void obtener_camino_minimo_con_pyramidhead(size_t origen, size_t destino);

    // PRE:--
    // POST: calcula el camino minimo con pyramidhead y actualiza el atributo camino_minimo.
    void calcular_camino_minimo_con_pyramidhead(size_t origen, size_t destino);

    // PRE:--
    // POST: calcula el camino minimo sin pyramidhead y actualiza el atributo camino_minimo.
    void  calcular_camino_minimo_sin_pyramidhead(size_t origen, size_t destino);

    // PRE: -
    // Pre: Inicia la interacción con el usuario
    void menu_nivel(); //privado

    // PRE: -
    // POST: Reinicializa los atributos relacionados al nivel para empezar un nuevo nivel.
    void reiniciar_nivel();//privado

    //PRE:--
    //POST: Genera una placa aleatoria.
    Placa generar_placa_aleatoria();//privado

    //PRE:--
    //POST: 20% de probabilidad de que el usuario consiga un arma
    void probar_suerte_arma(InventarioArmas &Inventario);//privado

    //PRE:--
    //POST: Agrega un arma al inventario de armas.
    void agregar_arma_aleatoria(InventarioArmas& inventario);//privado

    // PRE: -
    // POST: Destruye el arma equipada
    void destruir_arma();//privado



public:
    Juego();

    //PRE:
    //POST: inicia el juego.
    void iniciar_juego();

    // Destructor.
    ~Juego();
};

#endif
