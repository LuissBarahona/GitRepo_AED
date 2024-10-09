#ifndef COLA_H
#define COLA_H

#include <iostream>
// Nodo de la cola genérico
template <typename T>
struct NodoColaG {
    T valor;
    NodoColaG* siguiente;

    NodoColaG(T val) : valor(val), siguiente(nullptr) {}
};

// Implementación de la ColaGenerica genérica
template <typename T>
class ColaGenerica {
private:
    NodoColaG<T>* frente;
    NodoColaG<T>* atras;

public:
    ColaGenerica() : frente(nullptr), atras(nullptr) {}

    bool vacia() {
        return frente == nullptr;
    }

    void encolar(T valor) {
        NodoColaG<T>* nuevo = new NodoColaG<T>(valor);
        if (atras == nullptr) {
            frente = atras = nuevo;
        } else {
            atras->siguiente = nuevo;
            atras = nuevo;
        }
    }

    T desencolar() {
        if (vacia()) {
            return T(); // Devuelve un valor por defecto si la cola está vacía
        }
        T valor = frente->valor;
        NodoColaG<T>* temp = frente;
        frente = frente->siguiente;
        if (frente == nullptr) {
            atras = nullptr;
        }
        delete temp;
        return valor;
    }

    // Nueva función para imprimir los valores de la cola
    void imprimir() const {
        NodoColaG<T>* actual = frente;
        std::cout << "Valores en la cola: ";
        while (actual != nullptr) {
            std::cout << actual->valor << " ";  // Imprimir el valor genérico
            actual = actual->siguiente;
        }
        std::cout << std::endl;
    }
};

#endif // COLA_H
