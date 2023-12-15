#ifndef NODOABB_H
#define NODOABB_H

#include <iostream>
#include <vector>
#include <queue>

template<typename T, bool menor(T, T), bool igual(T, T)>
class NodoABB {

private:
    T dato{};
    NodoABB<T, menor, igual>* padre;
    NodoABB<T, menor, igual>* hijo_izquierdo;
    NodoABB<T, menor, igual>* hijo_derecho;

    //PRE:--
    //POST: elimina un nodo que no tiene hijos y devuelve un puntero a nullptr
    NodoABB<T,menor,igual> * baja_hoja();

    //PRE:--
    //POST: elimina un nodo con un solo hijo y devuelve un puntero a la raiz del subarbol
    NodoABB<T,menor,igual> * baja_un_hijo();

    //PRE:--
    //POST: intercambia el dato del nodo con dos hijos con los datos del sucesor, elimina el sucesor y devuelve la nueva raiz.
    NodoABB<T,menor,igual> * baja_dos_hijos();

    //PRE:--
    //POST: si existe, devuelve un puntero al sucesor.
    NodoABB<T,menor, igual> * sucesor();

    //PRE:--
    //POST: setea los punteros del nodo que se quiere eliminar a null
    void reiniciar_nodo();

public:
    // Constructor.
    NodoABB(T dato);

    // Pre: -
    // Post: Agrega el dato al árbol.
    // NOTA: Ya se debería haber revisado si el dato está o no.
    void alta(T dato_insertar);

    // Pre: -
    // Post: Elimina el dato del árbol y devuelve la nueva raiz, de haberla.
    // NOTA: Ya se debería haber revisado si el dato está o no.
    NodoABB<T, menor, igual>* baja(T dato_bajar);

    // Pre: -
    // Post: Devuelve true si el dato está en el subárbol.
    bool consulta(T dato_consultar);

    // Pre: -
    // Post: Carga los datos, respetando el recorrido inorder.
    void inorder(std::vector<T>& datos);

    // Pre: -
    // Post: Carga los datos, respetando el recorrido preorder.
    void preorder(std::vector<T>& datos);

    // Pre: -
    // Post: Carga los datos, respetando el recorrido postorder.
    void postorder(std::vector<T>& datos);

    // Pre: -
    // Post: Carga los datos, respetando el recorrido en ancho.
    void ancho(std::queue<NodoABB<T, menor, igual>*>& nodos, std::vector<T>& datos);

    // Pre: -
    // Post: Ejecuta el método/función en el subárbol.
    void ejecutar(void metodo(T));

    // Pre: -
    // Post: Ejecuta el método/función en el subárbol.
    std::size_t altura();

    // Destructor.
    ~NodoABB();
};

template <typename T, bool menor(T, T), bool igual(T, T)>
NodoABB<T, menor, igual>::NodoABB(T dato) {
    this->dato = dato;
    padre = nullptr;
    hijo_izquierdo = nullptr;
    hijo_derecho = nullptr;
}

template <typename T, bool menor(T, T), bool igual(T, T)>
void NodoABB<T, menor, igual>::alta(T dato_insertar) {
    if (menor(dato_insertar, this->dato)) {
        if (!hijo_izquierdo) {
            hijo_izquierdo = new NodoABB(dato_insertar);
            hijo_izquierdo->padre = this;
        } else {
            hijo_izquierdo->alta(dato_insertar);
        }
    } else {
        if (!hijo_derecho) {
            hijo_derecho = new NodoABB(dato_insertar);
            hijo_derecho->padre = this;
        } else {
            hijo_derecho->alta(dato_insertar);
        }
    }
}

template <typename T, bool menor(T, T), bool igual(T, T)>
bool NodoABB<T, menor, igual>::consulta(T dato_consultar) {
    if(igual(dato, dato_consultar)) {
        return true;
    } else if(menor(dato_consultar, dato) && hijo_izquierdo ) {
        return this->hijo_izquierdo->consulta(dato_consultar);
    } else if(menor(dato, dato_consultar) && hijo_derecho ){
        return this->hijo_derecho->consulta(dato_consultar);
    }
    return false;
}

template <typename T, bool menor(T,T), bool igual(T,T)>
void NodoABB<T, menor, igual>::inorder(std::vector<T> &datos) {
    if (hijo_izquierdo) {
        hijo_izquierdo->inorder(datos);
    }
    datos.push_back(dato);

    if (hijo_derecho) {
        hijo_derecho->inorder(datos);
    }
}

template <typename T, bool menor(T,T) , bool igual(T,T)>
void NodoABB<T,menor,igual>::preorder(std::vector<T> &datos) {
    datos.push_back(dato);
    if(hijo_izquierdo) {
        hijo_izquierdo->preorder(datos);
    }

    if (hijo_derecho) {
        hijo_derecho->preorder(datos);
    }
}

template <typename T, bool menor(T,T), bool igual(T,T)>
void NodoABB<T,menor,igual>::postorder(std::vector<T> &datos) {
    if(hijo_izquierdo) {
        hijo_izquierdo->postorder(datos);
    }

    if (hijo_derecho) {
        hijo_derecho->postorder(datos);
    }
    datos.push_back(dato);
}

template <typename T, bool menor(T,T), bool igual(T,T)>
void NodoABB<T,menor,igual>::ancho(std::queue<NodoABB<T, menor, igual> *> &nodos, std::vector<T> &datos) {
    nodos.push(this);
    while (!nodos.empty()) {
        NodoABB<T, menor, igual>* current = nodos.front();
        nodos.pop();
        datos.push_back(current->dato);
        if (current->hijo_izquierdo) {
            nodos.push(current->hijo_izquierdo);
        }
        if (current->hijo_derecho) {
            nodos.push(current->hijo_derecho);
        }
    }
}

template<typename T, bool menor(T,T), bool igual(T,T)>
NodoABB<T,menor,igual>* NodoABB<T,menor,igual>::sucesor() {
    NodoABB<T, menor, igual> * sucesor;
    if (hijo_derecho && hijo_izquierdo) {
        sucesor = hijo_derecho;
        while (sucesor->hijo_izquierdo != nullptr) {
            sucesor = sucesor->hijo_izquierdo;
        }
    } else {
        sucesor = nullptr;
    }
    return sucesor;
}

template<typename T,bool menor(T,T),bool igual(T,T)>
void NodoABB<T, menor, igual>::reiniciar_nodo() {
    this->hijo_izquierdo = nullptr;
    this->hijo_derecho = nullptr;
    this->padre = nullptr;
}

template <typename T, bool menor(T,T) , bool igual(T,T)>
NodoABB<T,menor,igual> * NodoABB<T, menor, igual>::baja_hoja()
{
    if (this == padre->hijo_izquierdo) {
        padre->hijo_izquierdo = nullptr;
    } else {
        padre->hijo_derecho = nullptr;
    }
    this->reiniciar_nodo();
    delete this;
    return nullptr;
}

template<typename T, bool menor(T,T), bool igual(T,T)>
NodoABB<T, menor, igual> * NodoABB<T, menor, igual>::baja_un_hijo() {

    NodoABB<T, menor, igual> * raiz_subarbol = nullptr;
    if (hijo_derecho) {
        raiz_subarbol = hijo_derecho;
        raiz_subarbol->padre = padre;
    } else if (hijo_izquierdo) {
        raiz_subarbol = hijo_izquierdo;
        raiz_subarbol->padre = padre;
    }
    this->reiniciar_nodo();
    delete this;
    return raiz_subarbol;

}

template<typename T, bool menor(T,T), bool igual (T,T)>
NodoABB<T,menor,igual> * NodoABB<T,menor,igual>::baja_dos_hijos() {
    NodoABB<T, menor, igual> *sucesor = this->sucesor();
    dato = sucesor->dato;
    sucesor->baja_hoja();
    return this;
}

template <typename T, bool menor(T,T), bool igual(T,T)>
NodoABB<T,menor,igual>* NodoABB<T,menor,igual>::baja(T dato_bajar) {
    NodoABB<T,menor,igual>* posible_raiz = nullptr;

    if (menor(dato_bajar,dato) && hijo_izquierdo) {
        hijo_izquierdo = hijo_izquierdo->baja(dato_bajar);
    } else if (menor(dato,dato_bajar) && hijo_derecho) {
        hijo_derecho = hijo_derecho->baja(dato_bajar);
    }

    if (igual(dato_bajar, dato)) {
        NodoABB<T,menor,igual>* raiz_nueva = nullptr;
        if (hijo_izquierdo && hijo_derecho) {
            raiz_nueva = baja_dos_hijos();
        } else if((hijo_izquierdo && !hijo_derecho) ||
                  (!hijo_izquierdo && hijo_derecho)) {
            raiz_nueva = baja_un_hijo();
        }  else {
            raiz_nueva = baja_hoja();
        }
        posible_raiz = raiz_nueva;
    }
    return posible_raiz;
}

template <typename T, bool menor(T,T), bool igual(T,T)>
void NodoABB<T, menor, igual>::ejecutar(void metodo(T)) {
    metodo(dato);
    if (hijo_izquierdo) {
        hijo_izquierdo->ejecutar(metodo);
    }
    if (hijo_derecho) {
        hijo_derecho->ejecutar(metodo);
    }
}

template <typename T, bool menor(T,T), bool igual(T,T)>
size_t NodoABB<T, menor, igual>::altura() {
    if (!hijo_izquierdo && !hijo_derecho) {
        return 1;
    }

    size_t altura_izquierda = (hijo_izquierdo) ? hijo_izquierdo->altura() : 0;
    size_t altura_derecha = (hijo_derecho) ? hijo_derecho->altura() : 0;

    return std::max(altura_izquierda, altura_derecha) + 1;
}

template<typename T, bool menor(T,T), bool igual(T,T)>
NodoABB<T,menor,igual>::~NodoABB() {
    if(hijo_izquierdo) {
        delete hijo_izquierdo;
    }
    if (hijo_derecho) {
        delete hijo_derecho;
    }
}
#endif
