#include <iostream>
#include <cmath>
#include <limits>
using namespace std;

template<typename T>
class Nodo {
public:
    T data;
    Nodo* izquierda;
    Nodo* derecha;
    Nodo* padre;
    Nodo* hijo;
    bool marcado;
    int grado;

    Nodo(T valor) : data(valor), izquierda(this), derecha(this), padre(nullptr), hijo(nullptr), marcado(false), grado(0) {}
};

template<typename T>
class FHeap {
private:
    Nodo<T>* min;  // Nodo mínimo en el heap
    int n;         // Número de nodos en el heap

    // Unir dos listas circulares de nodos
    void unionList(Nodo<T>* a, Nodo<T>* b) {
        if (a == nullptr || b == nullptr) return;

        Nodo<T>* a_right = a->derecha;
        Nodo<T>* b_left = b->izquierda;

        a->derecha = b;
        b->izquierda = a;

        a_right->izquierda = b_left;
        b_left->derecha = a_right;
    }

    // Cortar el nodo de su padre
    void cut(Nodo<T>* x, Nodo<T>* y) {
        if (x->derecha == x) {
            y->hijo = nullptr;
        } else {
            x->izquierda->derecha = x->derecha;
            x->derecha->izquierda = x->izquierda;
            if (y->hijo == x) {
                y->hijo = x->derecha;
            }
        }
        y->grado--;
        x->padre = nullptr;
        x->marcado = false;
        insertInRootList(x); // Volvemos a agregar el nodo a la lista raíz
    }

    // Realiza cortes en cascada
    void cascadingCut(Nodo<T>* y) {
        Nodo<T>* z = y->padre;
        if (z != nullptr) {
            if (!y->marcado) {
                y->marcado = true;
            } else {
                cut(y, z);
                cascadingCut(z);
            }
        }
    }

    // Insertar un nodo en la lista raíz
    void insertInRootList(Nodo<T>* nodo) {
        if (min == nullptr) {
            min = nodo;
        } else {
            unionList(min, nodo);
            if (nodo->data < min->data) {
                min = nodo;
            }
        }
    }

    // Consolidar el heap para mantener la estructura
    void consolidate() {
        int max_degree = static_cast<int>(log2(n)) + 1;
        Nodo<T>** A = new Nodo<T>*[max_degree];
        for (int i = 0; i < max_degree; i++) {
            A[i] = nullptr;
        }

        Nodo<T>* current = min;
        if (current == nullptr) return;

        Nodo<T>* start = current;
        do {
            Nodo<T>* x = current;
            int d = x->grado;
            while (A[d] != nullptr) {
                Nodo<T>* y = A[d];
                if (x->data > y->data) {
                    swap(x, y);
                }
                link(y, x);
                A[d] = nullptr;
                d++;
            }
            A[d] = x;
            current = current->derecha;
        } while (current != start);

        min = nullptr;
        for (int i = 0; i < max_degree; i++) {
            if (A[i] != nullptr) {
                insertInRootList(A[i]);
            }
        }
        delete[] A;
    }

    // Enlazar dos nodos, uno se convierte en hijo del otro
    void link(Nodo<T>* y, Nodo<T>* x) {
        if (y->derecha == y) {
            min = x;
        } else {
            y->izquierda->derecha = y->derecha;
            y->derecha->izquierda = y->izquierda;
        }
        y->padre = x;
        if (x->hijo == nullptr) {
            x->hijo = y;
            y->izquierda = y->derecha = y;
        } else {
            unionList(x->hijo, y);
        }
        x->grado++;
        y->marcado = false;
    }

    void visualizar_heap(Nodo<T>* nodo, int nivel) ;
    void visualizar() ;

public:
    FHeap() : min(nullptr), n(0) {}

    // Insertar un nuevo valor en el heap
    Nodo<T>* insert(T valor) {
        Nodo<T>* nuevo = new Nodo<T>(valor);
        insertInRootList(nuevo);
        n++;
        return nuevo;
    }

    // Extraer el nodo mínimo del heap
    T extractMin() {
        Nodo<T>* z = min;
        if (z != nullptr) {
            if (z->hijo != nullptr) {
                Nodo<T>* h = z->hijo;
                do {
                    h->padre = nullptr;
                    h = h->derecha;
                } while (h != z->hijo);
                unionList(min, z->hijo);
            }

            z->izquierda->derecha = z->derecha;
            z->derecha->izquierda = z->izquierda;

            if (z == z->derecha) {
                min = nullptr;
            } else {
                min = z->derecha;
                consolidate();
            }
            n--;
        }
        T ret = z->data;
        delete z;
        return ret;
    }

    // Decrecer el valor de un nodo
    void decreaseKey(Nodo<T>* x, T k) {
        if (k > x->data) {
            cout << "Nuevo valor es mayor que el valor actual" << endl;
            return;
        }
        x->data = k;
        Nodo<T>* y = x->padre;
        if (y != nullptr && x->data < y->data) {
            cut(x, y);
            cascadingCut(y);
        }
        if (x->data < min->data) {
            min = x;
        }
    }

    // Eliminar un nodo
    void deleteNode(Nodo<T>* x) {
        decreaseKey(x, numeric_limits<T>::min());
        extractMin();
    }

    // Buscar un nodo
    Nodo<T>* findNode(T valor) {
        return findNode(min, valor);
    }

    // Función recursiva sobrecargada para buscar un nodo a partir de un nodo dado
    Nodo<T>* findNode(Nodo<T>* nodo, T valor) { 
        if (nodo == nullptr) return nullptr;

        Nodo<T>* temp = nodo;
        do {
            if (temp->data == valor) return temp;
            if (temp->hijo != nullptr) {
                Nodo<T>* res = findNode(temp->hijo, valor);  // Recursivamente buscar en los hijos
                if (res != nullptr) return res;
            }
            temp = temp->derecha;
        } while (temp != nodo);
        return nullptr;
    }
};

template <typename T>
void FHeap<T>::visualizar_heap(Nodo<T>* nodo, int nivel) {
    if (nodo == nullptr) return;

    Nodo<T>* temp = nodo;
    do {
        // Imprimir el valor del nodo con una indentación basada en el nivel
        for (int i = 0; i < nivel; ++i) {
            std::cout << "  "; // 2 espacios por cada nivel de profundidad
        }
        std::cout << "└─ Nodo: " << temp->data << " (grado: " << temp->grado << ")" << std::endl;

        // Si el nodo tiene hijos, llamamos recursivamente para imprimirlos
        if (temp->hijo != nullptr) {
            visualizar_heap(temp->hijo, nivel + 1);
        }

        temp = temp->derecha;
    } while (temp != nodo);
}

template <typename T>
void FHeap<T>::visualizar() {
    std::cout << "Visualización del Fibonacci Heap:" << std::endl;
    if (min == nullptr) {
        std::cout << "Heap vacío." << std::endl;
        return;
    }
    visualizar_heap(min, 0);
}


// Pruebas en el main
int main() {
    FHeap<int> heap;

    // Insertar elementos en el heap
    heap.insert(10);
    heap.insert(20);
    heap.insert(30);
    Nodo<int>* nodo40 = heap.insert(40);
    Nodo<int>* nodo50 = heap.insert(50);

    cout << "Mínimo: " << heap.extractMin() << endl;  // Debería extraer 10

    // Disminuir clave
    heap.decreaseKey(nodo50, 5);
    cout << "Nuevo mínimo después de decreaseKey: " << heap.extractMin() << endl;  // Debería extraer 5

    // Eliminar nodo
    heap.deleteNode(nodo40);
    cout << "Mínimo después de eliminar el nodo 40: " << heap.extractMin() << endl;  // Debería extraer 20 o 30

    return 0;
}
