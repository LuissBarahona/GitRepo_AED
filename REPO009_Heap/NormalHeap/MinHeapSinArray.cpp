#include <iostream>
#include <cmath> //for log2()
#include "Stack.h"

struct Nodo {
    int valor;
    Nodo* izquierdo;
    Nodo* derecho;
    Nodo* padre;

    Nodo(int val) : valor(val), izquierdo(nullptr), derecho(nullptr), padre(nullptr) {}
};


struct NodoCola {
    Nodo* valor;
    NodoCola* siguiente;

    NodoCola(Nodo* val) : valor(val), siguiente(nullptr) {}
};

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
            throw std::runtime_error("Cola vacía");
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
};

class MinHeap {
private:
    Nodo* raiz;
    int tamano;

    void heapifyUp(Nodo* nodo) {
        while (nodo->padre && nodo->valor < nodo->padre->valor) {
            std::swap(nodo->valor, nodo->padre->valor);
            nodo = nodo->padre;
        }
    }

    void heapifyDown(Nodo* nodo) {
        while (nodo->izquierdo) {
            Nodo* menorHijo = nodo->izquierdo;
            if (nodo->derecho && nodo->derecho->valor < nodo->izquierdo->valor) {
                menorHijo = nodo->derecho;
            }
            if (nodo->valor <= menorHijo->valor) {
                break;
            }
            std::swap(nodo->valor, menorHijo->valor);
            nodo = menorHijo;
        }
    }

    Nodo* encontrarSiguiente() {
        if (!raiz) return nullptr;
        Cola q;
        q.encolar(raiz);
        while (!q.vacia()) {
            Nodo* nodo = q.desencolar();
            if (!nodo->izquierdo || !nodo->derecho) {
                return nodo;
            }
            q.encolar(nodo->izquierdo);
            if (nodo->derecho) q.encolar(nodo->derecho);
        }
        return nullptr;
    }

    Nodo* encontrarNodo(int valor) {
        if (!raiz) return nullptr;

        Cola q;
        q.encolar(raiz);
        while (!q.vacia()) {
            Nodo* nodo = q.desencolar();
            if (nodo->valor == valor) {
                return nodo;
            }
            if (nodo->izquierdo) q.encolar(nodo->izquierdo);
            if (nodo->derecho) q.encolar(nodo->derecho);
        }
        return nullptr;
    }

    int calcularAltura(Nodo* nodo) {
        if (!nodo) return -1;
        if (!nodo->izquierdo && !nodo->derecho) return 0;

        int alturaIzquierda = calcularAltura(nodo->izquierdo);
        int alturaDerecha = calcularAltura(nodo->derecho);

        return std::max(alturaIzquierda, alturaDerecha) + 1;
    }

    void preorderRec(Nodo* nodo) {
        if (nodo == nullptr) return;
        std::cout << nodo->valor << " ";
        preorderRec(nodo->izquierdo);
        preorderRec(nodo->derecho);
    }

    void inorderRec(Nodo* nodo) {
        if (nodo == nullptr) return;
        inorderRec(nodo->izquierdo);
        std::cout << nodo->valor << " ";
        inorderRec(nodo->derecho);
    }

    void postorderRec(Nodo* nodo) {
        if (nodo == nullptr) return;
        postorderRec(nodo->izquierdo);
        postorderRec(nodo->derecho);
        std::cout << nodo->valor << " ";
    }

public:
    MinHeap() : raiz(nullptr), tamano(0) {}

    void insertar(int valor) {
        Nodo* nuevoNodo = new Nodo(valor);
        if (!raiz) {
            raiz = nuevoNodo;
        } else {
            Nodo* padre = encontrarSiguiente();
            nuevoNodo->padre = padre;
            if (!padre->izquierdo) {
                padre->izquierdo = nuevoNodo;
            } else {
                padre->derecho = nuevoNodo;
            }
            heapifyUp(nuevoNodo);
        }
        tamano++;
    }

    void eliminar(int valor) {
        if (!raiz) return;

        Cola q;
        q.encolar(raiz);
        Nodo* nodoEliminar = nullptr;
        Nodo* ultimoNodo = nullptr;
        while (!q.vacia()) {
            Nodo* nodo = q.desencolar();
            if (nodo->valor == valor) {
                nodoEliminar = nodo;
            }
            if (nodo->izquierdo) q.encolar(nodo->izquierdo);
            if (nodo->derecho) q.encolar(nodo->derecho);
            ultimoNodo = nodo;
        }

        if (!nodoEliminar) return;

        nodoEliminar->valor = ultimoNodo->valor;

        if (ultimoNodo->padre) {
            if (ultimoNodo->padre->izquierdo == ultimoNodo) {
                ultimoNodo->padre->izquierdo = nullptr;
            } else {
                ultimoNodo->padre->derecho = nullptr;
            }
        } else {
            raiz = nullptr;
        }

        delete ultimoNodo;
        tamano--;

        heapifyDown(nodoEliminar);
    }

    int obtenerMinimo() const {
        if (raiz) {
            return raiz->valor;
        }
        throw std::runtime_error("El heap está vacío.");
    }

    int tamanoActual() const {
        return tamano;
    }

    int alturaActual() const {
        if (!raiz) return -1;
        return std::log2(tamano);
    }

    int obtenerAltura(int valor) {
        Nodo* nodo = encontrarNodo(valor);
        if (!nodo) {
            throw std::runtime_error("Valor no encontrado en el heap.");
        }
        return calcularAltura(nodo);
    }

    void preorder() {
        std::cout << "Recorrido Preorden: ";
        preorderRec(raiz);
        std::cout << std::endl;
    }

    void inorder() {
        std::cout << "Recorrido Inorden: ";
        inorderRec(raiz);
        std::cout << std::endl;
    }

    void postorder() {
        std::cout << "Recorrido Postorden: ";
        postorderRec(raiz);
        std::cout << std::endl;
    }

    void anchuraRecorrido() {
        if (!raiz) return;
        Cola q;
        q.encolar(raiz);
        std::cout << "Recorrido en Anchura: ";
        while (!q.vacia()) {
            Nodo* nodo = q.desencolar();
            std::cout << nodo->valor << " ";
            if (nodo->izquierdo) q.encolar(nodo->izquierdo);
            if (nodo->derecho) q.encolar(nodo->derecho);
        }
        std::cout << std::endl;
    }

    void profundidadRecorrido() {
        if (!raiz) return;
        
        Stack<Nodo*> pila;
        pila.push(raiz);
        
        std::cout << "Recorrido en Profundidad: ";
        
        while (!pila.vacia()) {
            Nodo* nodo = pila.top();
            pila.pop();
            std::cout << nodo->valor << " ";
            
            if (nodo->derecho) pila.push(nodo->derecho);
            if (nodo->izquierdo) pila.push(nodo->izquierdo);
        }
        
        std::cout << std::endl;
    }
};

int main() {
    MinHeap heap;

    // Insertar valores en el heap
    heap.insertar(20);
    heap.insertar(30);
    heap.insertar(10);
    heap.insertar(40);
    heap.insertar(50);
    heap.insertar(60);
    heap.anchuraRecorrido();
    heap.profundidadRecorrido();
    heap.preorder();
    heap.inorder();
    heap.postorder();

    std::cout << "Minimo: " << heap.obtenerMinimo() << std::endl;
    std::cout << "Tamaño actual: " << heap.tamanoActual() << std::endl;
    std::cout << "Altura actual: " << heap.alturaActual() << std::endl;
    std::cout << "Altura actual de la raiz: " << heap.obtenerAltura(10) << std::endl;
    std::cout << "Altura actual de la hoja: " << heap.obtenerAltura(60) << std::endl;

    heap.eliminar(10);
    heap.anchuraRecorrido();
    heap.profundidadRecorrido();
    heap.preorder();
    heap.inorder();
    heap.postorder();

    return 0;
}
