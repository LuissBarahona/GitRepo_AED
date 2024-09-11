//I

#include <iostream>

template<typename T>
struct Node {
    T data;
    Node<T>* next;
    Node<T>* prev;
    Node(T data) : data(data), next(nullptr), prev(nullptr) {}
};

template<typename T>
class CircularQueue {
private:
    Node<T>* rear;  // Apunta al nodo más reciente (último en entrar)
    Node<T>* front; // Apunta al nodo más antiguo (primero en salir)
    int size;

public:
    // Constructor
    CircularQueue() : rear(nullptr), front(nullptr), size(0) {}

    // Insertar un elemento al final de la lista (inserción en la parte "trasera" de la cola)
    void enqueue(T data) {
        Node<T>* new_node = new Node<T>(data);
        if (rear == nullptr) {  // Si la cola está vacía
            rear = front = new_node;
            rear->next = rear;
            rear->prev = rear;
        } else {  // Añadir a la cola circular
            new_node->next = rear->next;
            rear->next->prev = new_node;
            rear->next = new_node;
            new_node->prev = rear;
            rear = new_node;
        }
        size++;
    }

    // Eliminar el elemento del frente (equivalente a pop_front en una lista doblemente enlazada)
    T dequeue() {
        if (rear == nullptr) {
            throw std::out_of_range("La cola está vacía.");
        }

        T data = front->data;

        if (rear == front) {  // Solo un elemento en la cola
            delete front;
            rear = front = nullptr;
        } else {
            Node<T>* temp = front;
            front->next->prev = rear;
            rear->next = front->next;
            front = front->next;
            delete temp;
        }

        size--;
        return data;
    }

    // Retorna el valor del nodo en el frente de la cola
    T front_element() {
        if (front == nullptr) {
            throw std::out_of_range("La cola está vacía.");
        }
        return front->data;
    }

    // Verifica si la cola está vacía
    bool isEmpty() {
        return rear == nullptr;
    }

    // Como es una lista doblemente enlazada circular, no hay límite de tamaño
    bool isFull() {
        return false;  // La cola nunca está llena
    }

    // Retorna el tamaño de la cola
    int get_size() {
        return size;
    }

    // Mostrar los elementos de la cola. Desde el frente hasta el rear en forma circular
    void display_list() {
        if (rear == nullptr) {
            std::cout << "La cola está vacía." << std::endl;
            return;
        }

        Node<T>* temp = front;
        std::cout << "Front -> ";
        do {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        } while (temp != front);
        std::cout << "Rear" << std::endl;
    }
};

int main() {
    // Crear una cola circular de enteros
    CircularQueue<int> queue;

    // Caso de prueba para enqueue
    std::cout << "=== Prueba de Enqueue ===" << std::endl;
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    queue.display_list();  // Debe mostrar: Front -> 10 -> 20 -> 30 -> Rear
    std::cout << std::endl;

    // Caso de prueba para front_element
    std::cout << "=== Prueba de Front Element ===" << std::endl;
    try {
        int frontValue = queue.front_element();
        std::cout << "Front element: " << frontValue << std::endl;  // Debe mostrar: Front element: 10
    } catch (const std::out_of_range& e) {
        std::cout << e.what() << std::endl;
    }
    std::cout << std::endl;

    // Caso de prueba para dequeue
    std::cout << "=== Prueba de Dequeue ===" << std::endl;
    try {
        int dequeuedValue = queue.dequeue();
        std::cout << "Dequeued element: " << dequeuedValue << std::endl;  // Debe mostrar: Dequeued element: 10
        queue.display_list();  // Debe mostrar: Front -> 20 -> 30 -> Rear
    } catch (const std::out_of_range& e) {
        std::cout << e.what() << std::endl;
    }
    std::cout << std::endl;

    // Caso de prueba para isEmpty
    std::cout << "=== Prueba de isEmpty ===" << std::endl;
    if (queue.isEmpty()) {
        std::cout << "La cola está vacía." << std::endl;
    } else {
        std::cout << "La cola NO está vacía." << std::endl;  // Debe mostrar: La cola NO está vacía.
    }
    std::cout << std::endl;

    // Caso de prueba para isFull
    std::cout << "=== Prueba de isFull ===" << std::endl;
    if (queue.isFull()) {
        std::cout << "La cola está llena." << std::endl;
    } else {
        std::cout << "La cola NO está llena." << std::endl;  // Debe mostrar: La cola NO está llena.
    }
    std::cout << std::endl;

    // Caso de prueba para get_size
    std::cout << "=== Prueba de Get Size ===" << std::endl;
    int size = queue.get_size();
    std::cout << "Tamaño actual de la cola: " << size << std::endl;  // Debe mostrar: Tamaño actual de la cola: 2
    std::cout << std::endl;

    return 0;
}
