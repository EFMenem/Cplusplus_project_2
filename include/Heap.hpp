#ifndef ALGO2_TP3_PT2_HEAP_H
#define ALGO2_TP3_PT2_HEAP_H

#include <vector>
#include <cstdlib>
#include <exception>

class Heap_exception : public std::exception {
};

template<typename T, bool comp(T, T)>
class Heap {
private:
    std::vector<T> datos;

    // Pre: Ambos índices deben ser menor que la cantidad de datos.
    // Post: Intercambia de lugar los datos de los indices indicados.
    void swap(size_t index_1, size_t index_2);

    // Pre: Ambos índices deben ser menor que la cantidad de datos.
    // Post: Realiza un "upheap" sobre los índices indicados.
    // (El dato "sube" en el heap.)
    void upheap(size_t& index_insertado, size_t index_padre);

    // Post: El índice debe ser menor que la cantidad de datos.
    // Post: Realiza un "downheap" sobre el índice indicado.
    // (El dato "baja" en el heap, intercambiándose con el menor/mayor dato.)
    void downheap(size_t& index_movido);

    //PRE: --
    //POST: devuelve verdadero si el dato en el indice del hijo izquierdo es mayor que el del hijo derecho.
    bool hijo_mayor(size_t hijo_izquierdo,size_t hijo_derecho);
public:
    // Constructor.
    Heap();

    // Pre: -
    // Post: Agrega el dato al Heap.
    void alta(T dato);

    // Pre: El heap no puede estar vacío.
    // Post: Elimina y devuelve el primer dato.
    T baja();

    // Pre: El heap no puede estar vacío.
    // Post: Devuelve el primer dato.
    T primero();

    // Pre: -
    // Post: Devuelve true si el heap está vacío.
    bool vacio();

    // Pre: -
    // Post: Devuelve la cantidad de datos en el heap.
    size_t tamanio();

    // El constructor de copia está deshabilitado.
    Heap(const Heap& heap) = delete;

    // El operador = (asignación) está deshabilitado.
    void operator=(const Heap& heap) = delete;

    // Destructor.
    ~Heap();
};

template<typename T,bool comp(T,T)>
Heap<T,comp>::Heap() {}

template<typename T, bool comp(T, T)>
void Heap<T,comp>::swap(size_t index_1, size_t index_2) {
    if(index_1 >= tamanio() || index_2 >= tamanio()) {
        return;
    }
    T auxiliar = datos[index_1];
    datos[index_1] = datos[index_2];
    datos[index_2] = auxiliar;
}

template<typename T,bool comp(T,T)>
void Heap<T,comp>::upheap(size_t &index_insertado, size_t index_padre) {

    // Mientras no sea la raíz y se cumpla la condición de comparación:
    while ( index_insertado > 0 && comp(datos[index_insertado], datos[index_padre]) ) {
        // Intercambia los datos entre el índice del padre y el insertado.
        swap(index_padre,index_insertado);
        // Actualiza los índices para continuar con la verificación hacia arriba.
        index_insertado = index_padre;
        index_padre = (index_insertado - 1) / 2;
    }
}

template<typename T,bool comp(T,T)>
bool Heap<T,comp>::hijo_mayor(size_t hijo_izquierdo, size_t hijo_derecho) {
    // Compara los datos en los índices de los hijos y retorna el resultado de la comparación.
    return comp(datos[hijo_izquierdo], datos[hijo_derecho]);
}

template<typename T,bool comp(T,T)>
void Heap<T,comp>::downheap(size_t &index_movido) {
    size_t index_hijo_izq = 2 * index_movido + 1;
    size_t index_hijo_der = 2 * index_movido + 2;
    size_t index_menor_mayor = index_movido;

    if (index_hijo_izq < datos.size() && comp(datos[index_hijo_izq], datos[index_menor_mayor])) {
        index_menor_mayor = index_hijo_izq;
    }

    if (index_hijo_der < datos.size() && comp(datos[index_hijo_der], datos[index_menor_mayor])) {
        index_menor_mayor = index_hijo_der;
    }

    if (index_menor_mayor != index_movido) {
        swap(index_movido, index_menor_mayor);
        index_movido = index_menor_mayor;
        downheap(index_movido);
    }
}


template<typename T,bool comp(T,T)>
void Heap<T,comp>::alta(T dato) {
    datos.push_back(dato);
    if (tamanio() != 1) {
        size_t ultimo = tamanio()-1;
        size_t padre = (ultimo - 1) / 2;
        upheap(ultimo,padre);
    }
}

template<typename T,bool comp(T,T)>
T Heap<T,comp>::baja() {
    if (vacio()) {
        throw Heap_exception();
    }

    T borrado = datos[0];
    datos[0] = datos.back();
    datos.pop_back();

    size_t primero = 0;
    downheap(primero);

    return borrado;
}

template<typename T,bool comp(T,T)>
T Heap<T,comp>::primero() {
    if(vacio()) {
        throw Heap_exception();
    }
    return datos[0];
}
template<typename T, bool comp(T,T)>
bool Heap<T,comp>::vacio() {
    return datos.empty();
}

template<typename T,bool comp(T,T)>
size_t Heap<T,comp>::tamanio() {
    return datos.size();
}

template<typename T,bool comp(T,T)>
Heap<T,comp>::~Heap() {

}


#endif