/* PRESENTATION
    Topic: Circular Singly Linked List for a generic type
    Author: GPT
    Date: Sep 9, 2024
    Status Local: Funciona - Complete Library
    Status GitHub: No pushed
*/

#include <iostream>
#include <string>
using namespace std;

// Node structure de tipo T
template<typename T> 
struct Node {
    T data;
    Node* next;

    Node(T data) : data(data), next(nullptr) {} // Constructor del nodo
};

// Clase que representa la lista circular simplemente enlazada
template<typename T>
class Csllist {
private:
    Node<T>* last; // Puntero al último nodo
    int length; // Almacena el tamaño de la lista

public:
    Csllist() : last(nullptr), length(0) {} // Constructor de la lista

    // Método para llenar la lista con un nuevo nodo
    void fill_list(T data) {
        Node<T>* new_node = new Node<T>(data); // Creamos un nuevo nodo

        if (last == nullptr) { // Si la lista está vacía
            last = new_node; // El nuevo nodo será el único nodo (last)
            last->next = new_node; // Hacemos que apunte a sí mismo para cerrar el ciclo
        } else {
            new_node->next = last->next; // El nuevo nodo apunta al primer nodo
            last->next = new_node; // El nodo 'last' apunta al nuevo nodo
            last = new_node; // Actualizamos 'last' para que sea el último nodo
        }
        length++; // Aumentamos el tamaño
    }

    // Método para imprimir la lista
    void display() {
        if (last == nullptr) { // Si la lista está vacía
            cout << "Lista vacía" << endl;
            return;
        }

        Node<T>* temp = last->next; // Nodo que apunta al primer nodo (0°)
        do {
            cout << temp->data << " -> "; // Imprimimos el valor del nodo actual
            temp = temp->next; // Avanzamos al siguiente nodo
        } while (temp != last->next); // Salimos cuando volvemos al primer nodo
        cout << "NULL" << endl; // Marcamos el final de la lista
    }

    // Retorna el elemento en la primera posición (front)
    T front() {
        if (last == nullptr) throw out_of_range("Lista vacía");
        return last->next->data; // El primer nodo está después del nodo 'last'
    }

    // Retorna el elemento al final de la lista (back)
    T back() {
        if (last == nullptr) throw out_of_range("Lista vacía");
        return last->data;
    }

    // Agrega un elemento al frente de la lista
    void push_front(T data) {
        Node<T>* new_node = new Node<T>(data);
        if (last == nullptr) {
            last = new_node;
            last->next = new_node; // Cierre circular
        } else {
            new_node->next = last->next;
            last->next = new_node;
        }
        length++;
    }

    // Agrega un elemento al final de la lista
    void push_back(T data) {
        fill_list(data); // El comportamiento es el mismo que 'fill_list'
    }

    // Remueve el elemento al frente de la lista
    T pop_front() {
        if (last == nullptr) throw out_of_range("Lista vacía");

        Node<T>* temp = last->next;
        T removed_data = temp->data;

        if (last == last->next) {
            delete temp; // La lista tenía solo un nodo
            last = nullptr;
        } else {
            last->next = temp->next;
            delete temp;
        }
        length--;
        return removed_data;
    }

    // Remueve el elemento al final de la lista
    T pop_back() {
        if (last == nullptr) throw out_of_range("Lista vacía");

        Node<T>* temp = last->next;
        T removed_data = last->data;

        if (last == last->next) { // Solo hay un nodo
            delete last;
            last = nullptr;
        } else {
            // Encontramos el nodo antes del 'last'
            while (temp->next != last) {
                temp = temp->next;
            }
            temp->next = last->next;
            delete last;
            last = temp;
        }
        length--;
        return removed_data;
    }

    // Inserta un elemento en una posición específica
    void insert(T data, int position) {
        if (position < 0 || position > length) throw out_of_range("Índice fuera de rango");

        if (position == 0) {
            push_front(data);
        } else if (position == length) {
            push_back(data);
        } else {
            Node<T>* new_node = new Node<T>(data);
            Node<T>* temp = last->next;

            for (int i = 0; i < position - 1; i++) {
                temp = temp->next;
            }

            new_node->next = temp->next;
            temp->next = new_node;
            length++;
        }
    }

    // Remueve un nodo en una posición específica
    void remove(int position) {
        if (position < 0 || position >= length) throw out_of_range("Índice fuera de rango");

        if (position == 0) {
            pop_front();
        } else if (position == length - 1) {
            pop_back();
        } else {
            Node<T>* temp = last->next;
            for (int i = 0; i < position - 1; i++) {
                temp = temp->next;
            }

            Node<T>* node_to_delete = temp->next;
            temp->next = node_to_delete->next;
            delete node_to_delete;
            length--;
        }
    }

    // Retorna si la lista está vacía
    bool empty() {
        return last == nullptr;
    }

    // Retorna el tamaño de la lista
    int size() {
        return length;
    }

    // Elimina todos los elementos de la lista
    void clear() {
        while (!empty()) {
            pop_front();
        }
    }

    // Invierte el orden de la lista
    void reverse() {
        if (last == nullptr || last->next == last) return; // No es necesario revertir si hay 0 o 1 nodos

        Node<T>* prev = nullptr;
        Node<T>* current = last->next;
        Node<T>* next = nullptr;
        Node<T>* first = current;

        do {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        } while (current != first);

        first->next = prev;
        last = first;
    }
};
int main() {
    Csllist<int> circular_list1; // Lista de enteros
    Csllist<string> circular_list2; // Lista de strings

    // PRUEBAS CON LISTA DE ENTEROS
    cout << "=== PRUEBAS CON LISTA DE ENTEROS ===" << endl;

    // CASO 1: Llenar la lista con enteros
    circular_list1.fill_list(4);
    circular_list1.fill_list(5);
    circular_list1.fill_list(6);
    cout << "Lista después de llenar: ";
    circular_list1.display(); // Imprime: 4 -> 5 -> 6 -> NULL

    // CASO 2: Insertar al frente
    circular_list1.push_front(3);
    cout << "Después de insertar al frente (3): ";
    circular_list1.display(); // Imprime: 3 -> 4 -> 5 -> 6 -> NULL

    // CASO 3: Insertar al final
    circular_list1.push_back(7);
    cout << "Después de insertar al final (7): ";
    circular_list1.display(); // Imprime: 3 -> 4 -> 5 -> 6 -> 7 -> NULL

    // CASO 4: Insertar en una posición intermedia
    circular_list1.insert(10, 2); // Insertar en la posición 2
    cout << "Después de insertar en posición 2 (10): ";
    circular_list1.display(); // Imprime: 3 -> 4 -> 10 -> 5 -> 6 -> 7 -> NULL

    // CASO 5: Eliminar el primer elemento
    circular_list1.pop_front();
    cout << "Después de eliminar el primer elemento: ";
    circular_list1.display(); // Imprime: 4 -> 10 -> 5 -> 6 -> 7 -> NULL

    // CASO 6: Eliminar el último elemento
    circular_list1.pop_back();
    cout << "Después de eliminar el último elemento: ";
    circular_list1.display(); // Imprime: 4 -> 10 -> 5 -> 6 -> NULL

    // CASO 7: Revertir la lista
    circular_list1.reverse();
    cout << "Después de invertir la lista: ";
    circular_list1.display(); // Imprime: 6 -> 5 -> 10 -> 4 -> NULL

    // CASO 8: Tamaño de la lista
    cout << "Tamaño de la lista: " << circular_list1.size() << endl; // Imprime: 4

    // CASO 9: Vaciar la lista
    circular_list1.clear();
    cout << "Después de vaciar la lista: ";
    circular_list1.display(); // Imprime: Lista vacía
    cout << "Tamaño de la lista: " << circular_list1.size() << endl; // Imprime: 0

    // PRUEBAS CON LISTA DE STRINGS
    cout << "\n=== PRUEBAS CON LISTA DE STRINGS ===" << endl;

    // CASO 1: Llenar la lista con strings
    circular_list2.fill_list("Hola");
    circular_list2.fill_list("Adios");
    circular_list2.fill_list("Noche");
    cout << "Lista de strings después de llenar: ";
    circular_list2.display(); // Imprime: Hola -> Adios -> Noche -> NULL

    // CASO 2: Insertar un string al frente
    circular_list2.push_front("Inicio");
    cout << "Después de insertar al frente (Inicio): ";
    circular_list2.display(); // Imprime: Inicio -> Hola -> Adios -> Noche -> NULL

    // CASO 3: Eliminar el primer string
    circular_list2.pop_front();
    cout << "Después de eliminar el primer string: ";
    circular_list2.display(); // Imprime: Hola -> Adios -> Noche -> NULL

    return 0;
}
