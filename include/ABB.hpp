#ifndef ABB_H
#define ABB_H

#include <exception>
#include "NodoABB.hpp"

class ABB_exception : public std::exception {
};

template<typename T, bool menor(T, T), bool igual(T, T)>
class ABB {
private:
    NodoABB<T, menor, igual>* raiz;
    std::size_t cantidad_datos;
public:
    // Constructor.
    ABB();

    // Pre: El dato a ingresar no puede estar en el árbol.
    // Post: Agrega el dato al árbol. Si no hay datos, crea una nueva raiz.
    void alta(T dato);

    // Pre: -
    // Post: Elimina el dato del árbol. Si no existe, no hace nada.
    // NOTA: Si la raiz cambia (sin importar el caso), se debe reasignar correctamente.
    void baja(T dato);

    // Pre: -
    // Post: Devuelve true si el dato está en el árbol. Si no hay datos, devuelve false.
    bool consulta(T dato);

    // Pre: -
    // Post: Devuelve el recorrido inorder.
    std::vector<T> inorder();

    // Pre: -
    // Post: Devuelve el recorrido preorder.
    std::vector<T> preorder();

    // Pre: -
    // Post: Devuelve el recorrido postorder.
    std::vector<T> postorder();

    // Pre: -
    // Post: Devuelve el recorrido en ancho.
    std::vector<T> ancho();

    // Pre: -
    // Post: Ejecuta el método/función en cada uno de los nodos.
    void ejecutar(void metodo(T));

    // Pre: -
    // Post: Devuelve la cantidad de datos en el árbol.
    std::size_t tamanio();

    // Pre: -
    // Post: Devuelve true si el árbol está vacio.
    bool vacio();

    // Pre: -
    // Post: Devuelve la altura del árbol.
    std::size_t altura();

    // El constructor de copia está deshabilitado.
    ABB(const ABB& abb) = delete;

    // El operador = (asignación) está deshabilitado.
    void operator=(const ABB& abb) = delete;

    // Destructor.
    ~ABB();
};

template<typename T, bool menor(T, T), bool igual(T, T)>
ABB<T,menor,igual>::ABB() {
    raiz = nullptr;
    cantidad_datos = 0;
}

template<typename T, bool menor(T,T), bool igual(T,T)>
void ABB<T,menor,igual>::alta(T dato) {
    if (vacio()) {
        raiz = new NodoABB<T,menor,igual>(dato);
    } else {
        if(!raiz->consulta(dato)) {
            raiz->alta(dato);
        } else {
            throw ABB_exception();
        }
    }
    cantidad_datos++;
}

template<typename T,bool menor(T,T), bool igual(T,T)>
void ABB<T,menor,igual>::baja(T dato) {
    if (consulta(dato)) {
        raiz->baja(dato);
        cantidad_datos--;
    }
}

template<typename T,bool menor(T,T),bool igual(T,T)>
bool ABB<T,menor,igual>::consulta(T dato_consultar) {
    if (!vacio()) {
        return raiz->consulta(dato_consultar);
    }
    return false;
}

template <typename T, bool menor(T,T), bool igual(T,T)>
std::vector<T> ABB<T, menor, igual>::inorder() {
    std::vector<T> vector;
    if (!vacio()) {
        raiz->inorder(vector);
    }
    return vector;
}

template <typename T, bool menor(T,T) , bool igual(T,T)>
std::vector<T> ABB<T,menor,igual>::preorder() {
    std::vector<T> vector;
    if (!vacio()) {
        raiz->preorder(vector);
    }
    return vector;
}

template<typename T, bool menor(T,T) , bool igual(T,T)>
std::vector<T> ABB<T,menor,igual>::postorder() {
    std::vector<T> vector;
    if(!vacio()) {
        raiz->postorder(vector);
    }
    return vector;
}

template <typename T, bool menor(T,T), bool igual(T,T)>
std::vector<T> ABB<T,menor,igual>::ancho() {
    std::vector<T> vector;
    if (!vacio()) {
        std::queue<NodoABB<T, menor, igual> *> cola;
        raiz->ancho(cola, vector);
    }
    return vector;
}

template<typename T, bool menor(T, T), bool igual(T, T)>
void ABB<T, menor, igual>::ejecutar(void metodo(T)) {
    if (!vacio()) {
        raiz->ejecutar(metodo);
    }
}

template<typename T,bool menor(T,T), bool igual(T,T)>
bool ABB<T,menor,igual>::vacio() {
    return cantidad_datos == 0;
}

template<typename T,bool menor(T,T), bool igual(T,T)>
size_t ABB<T,menor,igual>::altura() {
    size_t altura = 0;
    if (!vacio()) {
        altura = raiz->altura();
    }
    return altura;
}

template <typename T,bool menor(T,T),bool igual(T,T)>
size_t ABB<T,menor,igual>::tamanio() {
    return cantidad_datos;
}

template<typename T, bool menor(T, T), bool igual(T, T)>
ABB<T, menor, igual>::~ABB() {
    if (!vacio()) {
        delete raiz;
    }
}

#endif
