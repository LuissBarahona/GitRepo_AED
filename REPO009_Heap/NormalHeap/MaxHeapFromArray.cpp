/*

    MÉTODO GENÉRICOS QUE SE PUEDEN USAR CON CUALQUIER ÁRBOL BINARIO QUE USE NODOS:
    - encontrarNodo
    - obtenerAlturadeNodo
    . inordeer, preorder, postorder
*/

#include <iostream>
#include <stdexcept>
#include <cmath>
#include "Stack.h"
#include "Cola.h"

using namespace std;

//Ante yacía aquí el struct Nodo, NodoCola, Class Cola. Pero ahora se conviertieron en un .h

// Clase ArrayToMaxHeap para convertir un array en un MaxHeap
class ArrayToMaxHeap {
private:
    Nodo* raiz;
    int tamano;

    // Ajustar el heap hacia arriba
    void heapifyUp(Nodo* nodo) {
        while (nodo->padre && nodo->valor > nodo->padre->valor) { // Cambiar a > para Max Heap
            std::swap(nodo->valor, nodo->padre->valor);
            nodo = nodo->padre;
        }
    }

    // Ajustar el heap hacia abajo
    void heapifyDown(Nodo* nodo) {
        while (nodo->izquierdo) {
            Nodo* mayorHijo = nodo->izquierdo;
            if (nodo->derecho && nodo->derecho->valor > nodo->izquierdo->valor) { // Cambiar a > para Max Heap
                mayorHijo = nodo->derecho;
            }
            if (nodo->valor >= mayorHijo->valor) { // Cambiar a >= para Max Heap
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
    ArrayToMaxHeap() : raiz(nullptr), tamano(0) {}

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

    // Método para convertir un array en un MaxHeap
    void convertirArrayEnHeap(int arr[], int n) {
        for (int i = 0; i < n; ++i) {
            insertar(arr[i]);
        }
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

    int obtenerMaximo() const {
        if (raiz) {
            return raiz->valor;
        }
        throw std::runtime_error("El heap está vacío.");
    }

    int tamanoActual() const {
        return tamano;
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
    ArrayToMaxHeap heap;

    // Array de ejemplo para convertir en MaxHeap
    int arr[] = {20, 30, 10, 40, 50, 60};
    int n = sizeof(arr) / sizeof(arr[0]);

    // Convertir el array en un MaxHeap
    heap.convertirArrayEnHeap(arr, n);

    // Probar los métodos de recorrido
    heap.anchuraRecorrido();
    heap.profundidadRecorrido();
    heap.preorder();
    cout<<"altura de root 60: "<<heap.alturaDeValor(60)<<endl;
    cout<<"altura de hoja 20: "<<heap.alturaDeValor(20)<<endl;

    // Obtener el máximo
    try {
        cout << "Máximo: " << heap.obtenerMaximo() << endl;
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
    

    return 0;
}
