#ifndef COLA_H
#define COLA_H

#include <iostream>

// Nodo de un árbol binario
struct Nodo {
    int valor;
    Nodo* izquierdo;
    Nodo* derecho;
    Nodo* padre;

    Nodo(int val) : valor(val), izquierdo(nullptr), derecho(nullptr), padre(nullptr) {}
};

// Nodo de la cola
struct NodoCola {
    Nodo* valor;
    NodoCola* siguiente;

    NodoCola(Nodo* val) : valor(val), siguiente(nullptr) {}
};

// Implementación de la Cola
class Cola {
private:
    NodoCola* frente;
    NodoCola* atras;

public:
    Cola() : frente(nullptr), atras(nullptr) {}

    bool vacia() {
        return frente == nullptr;
    }

    void encolar(Nodo* valor) {
        NodoCola* nuevo = new NodoCola(valor);
        if (atras == nullptr) {
            frente = atras = nuevo;
        } else {
            atras->siguiente = nuevo;
            atras = nuevo;
        }
    }

    Nodo* desencolar() {
        if (vacia()) {
            return nullptr; // Devuelve nullptr si la cola está vacía
        }
        Nodo* valor = frente->valor;
        NodoCola* temp = frente;
        frente = frente->siguiente;
        if (frente == nullptr) {
            atras = nullptr;
        }
        delete temp;
        return valor;
    }

    // Nueva función para imprimir los valores de la cola
    void imprimir() const {
        NodoCola* actual = frente;
        std::cout << "Valores en la cola: ";
        while (actual != nullptr) {
            std::cout << actual->valor->valor << " ";  // Imprimir el valor del nodo del árbol
            actual = actual->siguiente;
        }
        std::cout << std::endl;
    }
};

#endif // COLA_H
