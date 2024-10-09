template<typename T>
class Stack {
private:
    struct Nodo {
        T valor;
        Nodo* siguiente;
        Nodo(T val) : valor(val), siguiente(nullptr) {}
    };

    Nodo* cima;

public:
    Stack() : cima(nullptr) {}

    // Apilar
    void push(T valor) {
        Nodo* nuevo = new Nodo(valor);
        nuevo->siguiente = cima;
        cima = nuevo;
    }

    // Desapilar
    T pop() {
        if (!vacia()) {
            T valor = cima->valor;
            Nodo* temp = cima;
            cima = cima->siguiente;
            delete temp;
            return valor;
        }
        // Manejo de error en caso de pila vacía
        return T(); // Devuelve un valor por defecto
    }

    // Verificar si la pila está vacía
    bool vacia() {
        return cima == nullptr;
    }

    // Clase iteradora interna
    class Iterator {
    private:
        Nodo* actual;
    public:
        Iterator(Nodo* nodo) : actual(nodo) {}

        T operator*() {
            return actual->valor;
        }

        Iterator& operator++() {
            if (actual) actual = actual->siguiente;
            return *this;
        }

        bool operator!=(const Iterator& otro) const {
            return actual != otro.actual;
        }
    };

    Iterator begin() {
        return Iterator(cima);
    }

    Iterator end() {
        return Iterator(nullptr);
    }
};

/*
int main() {
    Stack<int> p;
    p.push(10);
    p.push(20);
    p.push(30);

    // Imprimir usando un bucle for basado en rango
    for (int valor : p) {
        std::cout << valor << std::endl;
    }

    return 0;
}
*/