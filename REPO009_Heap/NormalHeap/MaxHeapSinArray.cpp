/*

    ESTADO: COMPLETO Y FUNCIONAL
*/

#include <iostream>
#include <queue>
#include <cmath>
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

    // Verifica si la cola está vacía
    bool vacia() {
        return frente == nullptr;
    }

    // Insertar en la cola
    void encolar(Nodo* valor) {
        NodoCola* nuevo = new NodoCola(valor);
        if (atras == nullptr) {
            frente = atras = nuevo;
        } else {
            atras->siguiente = nuevo;
            atras = nuevo;
        }
    }

    // Eliminar de la cola
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

class MaxHeap {
private:
    Nodo* raiz;
    int tamano;

    void heapifyUp(Nodo* nodo) {
        while (nodo->padre && nodo->valor > nodo->padre->valor) {
            std::swap(nodo->valor, nodo->padre->valor);
            nodo = nodo->padre;
        }
    }

    void heapifyDown(Nodo* nodo) {
        while (nodo->izquierdo) {
            Nodo* mayorHijo = nodo->izquierdo;
            if (nodo->derecho && nodo->derecho->valor > nodo->izquierdo->valor) {
                mayorHijo = nodo->derecho;
            }
            if (nodo->valor >= mayorHijo->valor) {
                break;
            }
            std::swap(nodo->valor, mayorHijo->valor);
            nodo = mayorHijo;
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

    // Encontrar el nodo con el valor especificado
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
        return nullptr; // No encontrado
    }

    // Calcular la altura de un nodo en relación a las hojas
    int calcularAltura(Nodo* nodo) {
        if (!nodo) return -1;  // Nodo nulo no tiene altura
        if (!nodo->izquierdo && !nodo->derecho) return 0;  // Las hojas tienen altura 0

        int alturaIzquierda = calcularAltura(nodo->izquierdo);
        int alturaDerecha = calcularAltura(nodo->derecho);

        return std::max(alturaIzquierda, alturaDerecha) + 1;
    }

    //MÉTODO QUE USAN EL ROOT PARA RECORRER

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
    MaxHeap() : raiz(nullptr), tamano(0) {}

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

    int obtenerMaximo() const {
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

    // Método para obtener la altura de un nodo con un valor específico
    int obtenerAltura(int valor) {
        Nodo* nodo = encontrarNodo(valor);
        if (!nodo) {
            throw std::runtime_error("Valor no encontrado en el heap.");
        }
        return calcularAltura(nodo);
    }

    //  //FUNCIONE SGENERICAS DE RECORRIDO PARA ARBOLES BINARIOS

    // Métodos de recorrido

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
        
        Stack<Nodo*> pila;  // Usamos nuestra implementación de Stack
        pila.push(raiz);
        
        std::cout << "Recorrido en Profundidad: ";
        
        while (!pila.vacia()) {  // Cambiamos el método a `vacia()`
            Nodo* nodo = pila.top();
            pila.pop();
            std::cout << nodo->valor << " ";
            
            // Apilamos el hijo derecho primero para que el izquierdo se procese primero
            if (nodo->derecho) pila.push(nodo->derecho);
            if (nodo->izquierdo) pila.push(nodo->izquierdo);
        }
        
        std::cout << std::endl;
    }
        

};


int main() {
    MaxHeap heap;

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

    std::cout << "Maximo: " << heap.obtenerMaximo() << std::endl;  // Debería ser 50
    std::cout << "Tamaño actual: " << heap.tamanoActual() << std::endl;  // Debería ser 5
    std::cout << "Altura actual: " << heap.alturaActual() << std::endl;  // Debería ser 2
    std::cout << "Altura actual de la raiz: " << heap.obtenerAltura(60) << std::endl;  // Debería ser 2
    std::cout << "Altura actual de 40: " << heap.obtenerAltura(40) << std::endl; //debería ser 1
    std::cout << "Altura actual de 20 u hoja: " << heap.obtenerAltura(20) << std::endl; //debería ser 0

    // Eliminar el máximo
    heap.eliminar(50);
    std::cout << "Maximo despues de eliminar 50: " << heap.obtenerMaximo() << std::endl;  // Debería ser 40

    // Eliminar otro valor
    heap.eliminar(30);
    std::cout << "Maximo despues de eliminar 30: " << heap.obtenerMaximo() << std::endl;  // Debería ser 40

    std::cout << "Tamaño final: " << heap.tamanoActual() << std::endl;  // Debería ser 3
    std::cout << "Altura final: " << heap.alturaActual() << std::endl;  // Debería ser 1

    return 0;
}
