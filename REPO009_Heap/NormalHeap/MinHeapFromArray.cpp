#include <iostream>
using namespace std;
#include <cmath>
#include "Stack.h"

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

// Clase ArrayToMinHeap para convertir un array en un MinHeap
class ArrayToMinHeap {
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

    // Método para encontrar un nodo con un valor dado
    Nodo* encontrarNodo(Nodo* nodo, int valor) {
        if (!nodo) return nullptr;
        if (nodo->valor == valor) return nodo;

        Nodo* encontrado = encontrarNodo(nodo->izquierdo, valor);
        if (encontrado) return encontrado;

        return encontrarNodo(nodo->derecho, valor);
    }

    // Método recursivo para calcular la altura de un nodo
    int altura(Nodo* nodo) {
        if (!nodo) return -1; // Si el nodo es nulo, la altura es -1
        int alturaIzquierda = altura(nodo->izquierdo);
        int alturaDerecha = altura(nodo->derecho);
        return 1 + std::max(alturaIzquierda, alturaDerecha); // 1 + el mayor entre las alturas de los hijos
    }

public:
    ArrayToMinHeap() : raiz(nullptr), tamano(0) {}

    // Método para insertar un valor en el heap
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

    // Método para eliminar un valor del heap
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

    // Método para convertir un array en un MinHeap
    void convertirArrayEnHeap(int arr[], int n) {
        for (int i = 0; i < n; ++i) {
            insertar(arr[i]);
        }
    }

    // Método para recorrer el árbol en anchura
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

    // Método para recorrer el árbol en profundidad
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

    int obtenerMinimo() const {
        if (raiz) {
            return raiz->valor;
        }
        throw std::runtime_error("El heap está vacío.");
    }

    int tamanoActual() const {
        return tamano;
    }

    // Método para imprimir el heap en preorden
    void preorderRec(Nodo* nodo) {
        if (nodo == nullptr) return; //caso base
        std::cout << nodo->valor << " ";
        preorderRec(nodo->izquierdo);//si el nodo en nullptr retorna y ejecuta la siuiente linea
        preorderRec(nodo->derecho);
    }

    void preorder() {
        std::cout << "Recorrido Preorden: ";
        preorderRec(raiz);
        std::cout << std::endl;
    }

    //Método para imprimir el heap en postorder
    void postorderRec(Nodo* nodo){
        if (nodo == nullptr) return;

        // Primero recorremos el subárbol izquierdo
        postorderRec(nodo->izquierdo);

        // Luego recorremos el subárbol derecho
        postorderRec(nodo->derecho);

        // Finalmente, visitamos el nodo actual
        std::cout << nodo->valor << " ";
    }

    void postorder(){
        std::cout << "Recorrido Postorder: ";
        postorderRec(raiz);
        std::cout << std::endl;
    }

    // Método para iniciar el recorrido inorden
    void inorderRec(Nodo* nodo) {
        if (nodo == nullptr) return;

        // Primero recorremos el subárbol izquierdo
        inorderRec(nodo->izquierdo);

        // Visitamos el nodo actual
        std::cout << nodo->valor << " ";

        // Luego recorremos el subárbol derecho
        inorderRec(nodo->derecho);
    }

    void inorder() {
        std::cout << "Recorrido Inorden: ";
        inorderRec(raiz);
        std::cout << std::endl;
    }

    // Método para calcular la altura de un valor dado
    int alturaDeValor(int valor) {
        Nodo* nodo = encontrarNodo(raiz, valor);
        if (!nodo) {
            throw std::runtime_error("Valor no encontrado en el heap.");
        }
        return altura(nodo);
    }


};

int main() {
    ArrayToMinHeap heap;

    // Array de ejemplo para convertir en MinHeap
    int arr[] = {20, 30, 10, 40, 50, 60};
    int n = sizeof(arr) / sizeof(arr[0]);

    // Convertir el array en un MinHeap
    heap.convertirArrayEnHeap(arr, n);

    // Probar los métodos de recorrido
    heap.anchuraRecorrido();
    heap.profundidadRecorrido();
    heap.preorder();
    heap.postorder();
    heap.inorder();

    // Probar el cálculo de altura de un valor
    int valor = 10;
    try {
        std::cout << "Altura del valor " << valor << ": " << heap.alturaDeValor(valor) << std::endl;
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    cout<<"minimo: "<<heap.obtenerMinimo()<<endl;
    return 0;
}
