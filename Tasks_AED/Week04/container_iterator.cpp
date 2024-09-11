#include <iostream>
#include <vector>

// Definición de una plantilla para un iterador genérico
template <typename T>
class Iterator {
private:
    T* ptr;

public:
    // Constructor
    Iterator(T* p = nullptr) : ptr(p) {}

    // Constructor de copia
    Iterator(const Iterator& other) : ptr(other.ptr) {}

    // Operador de asignación
    Iterator& operator=(const Iterator& other) {
        if (this != &other) {
            ptr = other.ptr;
        }
        return *this;
    }

    // Operador de dereferencia
    T& operator*() const {
        return *ptr;
    }

    // Operador de incremento (avance del iterador)
    Iterator& operator++() {
        ++ptr;
        return *this;
    }

    // Operador de decremento (retroceso del iterador)
    Iterator& operator--() {
        --ptr;
        return *this;
    }

    // Operador de comparación
    bool operator!=(const Iterator& other) const {
        return ptr != other.ptr;
    }

    // Operador de comparación de igualdad
    bool operator==(const Iterator& other) const {
        return ptr == other.ptr;
    }
};

// Clase de contenedor simple
template <typename T>
class Container {
private:
    T* elements;
    size_t size;

public:
    // Constructor
    Container(T* arr, size_t s) : elements(arr), size(s) {}

    // Método para obtener el iterador al inicio del contenedor
    Iterator<T> begin() {
        return Iterator<T>(elements);
    }

    // Método para obtener el iterador al final del contenedor
    Iterator<T> end() {
        return Iterator<T>(elements + size);
    }
};

// Función de prueba para iterar sobre un contenedor
template <typename T>
void print_elements(Container<T>& container) {
    for (Iterator<T> it = container.begin(); it != container.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}
int main() {
    // Crear un array de ejemplo
    int arr[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    // Crear un contenedor
    Container<int> container(arr, size);

    // Probar método begin() y operator*()
    Iterator<int> it = container.begin();
    std::cout << "Primero elemento (usando begin): " << *it << std::endl;  // Debe imprimir 1

    // Probar operator++()
    ++it;
    std::cout << "Segundo elemento (después de operator++): " << *it << std::endl;  // Debe imprimir 2

    // Probar operator--()
    --it;
    std::cout << "Primero elemento (después de operator--): " << *it << std::endl;  // Debe imprimir 1

    // Probar operator!= y operator==
    Iterator<int> it2 = container.end();
    std::cout << "Comparación de iteradores (it != it2): " << (it != it2) << std::endl;  // Debe imprimir 1 (true)

    // Probar operator=
    it2 = it;
    std::cout << "Comparación de iteradores (it == it2 después de operator=): " << (it == it2) << std::endl;  // Debe imprimir 1 (true)

    // Probar iteración completa usando begin() y end()
    std::cout << "Iteración sobre todos los elementos: ";
    for (Iterator<int> it = container.begin(); it != container.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;  // Debe imprimir 1 2 3 4 5

    return 0;
}
