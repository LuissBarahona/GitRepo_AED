template <typename T>
class NodoPila {
public:
    T valor;
    NodoPila* siguiente;

    NodoPila(T valor) {
        this->valor = valor;
        this->siguiente = nullptr;
    }
};

template <typename T>
class Stack {
private:
    NodoPila<T>* cima;  // Apunta al último nodo insertado
    int tamano;

public:
    Stack() {
        cima = nullptr;
        tamano = 0;
    }

    // Agregar un elemento a la pila (push)
    void push(T valor) {
        NodoPila<T>* nuevoNodo = new NodoPila<T>(valor);
        nuevoNodo->siguiente = cima;  // El nuevo nodo apunta al antiguo cima
        cima = nuevoNodo;             // Ahora el nuevo nodo es la cima
        tamano++;
    }

    // Eliminar el elemento de la cima de la pila (pop)
    void pop() {
        if (cima == nullptr) {
            std::cout << "La pila está vacía. No se puede realizar pop." << std::endl;
            return;
        }

        NodoPila<T>* nodoEliminar = cima;
        cima = cima->siguiente;  // La nueva cima es el siguiente nodo
        delete nodoEliminar;     // Eliminar el nodo anterior
        tamano--;
    }

    // Obtener el valor de la cima sin eliminarlo (top)
    T top() {
        if (cima == nullptr) {
            throw std::runtime_error("La pila está vacía.");
        }
        return cima->valor;
    }

    // Verificar si la pila está vacía
    bool vacia() {
        return cima == nullptr;
    }

    // Obtener el tamaño actual de la pila
    int tamanoActual() {
        return tamano;
    }
};
