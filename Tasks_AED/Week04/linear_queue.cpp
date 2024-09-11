
/*DETALLES
    rearic: Stack Implementation Using a Simple Linked List- Dynamic Size Array
    Author: Luis Barahona
    Date: Sep 11, 2024
    Status: Complete - Funciona

    Basic Operations:
        insert_rear -> es como un push_front en una simple linked list
        delete_front -> es como un pop_back en una simple linked list
        isEmpty
        isFull
        front -> retorna el elemento que yace al final de una simple linked list

    Mi convención
        
*/ 
#include <iostream>
using namespace std;
#include <bits/stdc++.h>
#include <string>

template<typename T>
struct Node{
    T data;
    Node* next;
    Node(T data):data(data), next(nullptr){} //constructor
};

template<typename T>
class LinearQueue{
    private:
        Node<T>* rear; // Apunta al inicio de la lista (nodo más nuevo)
        Node<T>* front; // Apunta al final de la lista (nodo más antiguo)
        int size;

    public:
        LinearQueue() : rear(nullptr), front(nullptr) {} // Constructor

        // insert an element to the rear o push_front in a linked list
        void enqueue(T data) {
            Node<T>* new_node = new Node<T>(data);
            new_node->next = rear;
            rear = new_node;

            if (front == nullptr) {
                front = new_node; // Si es el primer elemento, front también debe apuntar a este
            }
        }

        // Retorna el elemento al final de la lista, no lo elimina
        T front_element() {
            if (front != NULL) {
                return front->data;
            }
            throw std::out_of_range("La lista está vacía");
        }

        // Elimina el último elemento de la simple linked list - equivalente al pop_back de una simple linked list
        T dequeue() {
            if (rear == NULL) {
                throw std::out_of_range("La lista está vacía");
            }

            if (rear->next == NULL) {
                T data = rear->data;
                delete rear;
                rear = NULL;
                front = NULL;
                return data;
            }

            Node<T>* temp = rear;
            while (temp->next != front) {
                temp = temp->next;
            }

            T data = front->data;
            delete front;
            front = temp;
            front->next = nullptr;
            return data;
        }

        // Retorna true si la lista está vacía
        bool isEmpty() {
            return rear == nullptr;
        }

        // Retorna false ya que la lista dinámica no tiene un tamaño fijo (nunca está llena)
        bool isFull() {
            return false; // En una lista enlazada, no existe un límite fijo
        }

        // Retorna el tamaño de la lista
        //int size(); Retorna el tamaño de la lista.
        int get_size() {
            Node<T>* temp = rear;
            int count = 0;
            while (temp != NULL) {
                count++;
                temp = temp->next;
            }
            size = count;
            return size;
        }

        //Mostrar los elementos de la cola. Más a la izquierda va el último en ingresar, y más a la derecha el primero que saldrá
        void display_list() {
            cout<<"Left or Rear :";
            Node<T>* temp = rear; // Nos movemos al rear
            while (temp != NULL) { // Mientras no sea NULL
                cout << temp->data << " -> ";
                temp = temp->next;
            }
            cout << " :Rigth or Front" << endl; // Indicar el final de la lista
        }
};


int main() {
    // Crear una cola de enteros
    LinearQueue<int> queue;

    // Caso de prueba para enqueue
    std::cout << "=== Prueba de Enqueue ===" << std::endl;
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    queue.display_list();  // Debe mostrar: Left or Rear: 30 -> 20 -> 10 -> :Right or Front
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
        queue.display_list();  // Debe mostrar: Left or Rear: 30 -> 20 -> :Right or Front
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
