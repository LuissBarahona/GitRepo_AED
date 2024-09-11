/* PRESENTATION
    Topic: Circular Doubly Linked List for a generic type
    Author: Luis Barahona
    Date: Sep 9, 2024
    Status Local: Funciona - Incomplete Library
    Status GitHub: No pushed
    Reference: https://www.geeksforgeeks.org/introduction-to-circular-doubly-linked-list/?ref=gcse_ind
*/

#include <iostream>

template<typename T>
struct Node{
    T data;
    Node* prev;
    Node* next;

    Node(T data):data(data), prev(nullptr), next(nullptr){} //Constructor
};

template<typename T>
class Cdll{
    private:
        Node<T>* sentinel;
    public:
        Node():sentinel(nullptr){} //constructor

        //Método para llenar la lista
        //Método para mostrar la lista completa
        /*
        // - Método para insertar un elemento en una determinada posición
    // - Método para retornar un elemento de una determinada posición
    // - Método para eliminar un elemento de una determinada posición
    // - Método para invertir el orden de la lista
    // - Método de búsqueda
    // - Método para determinar el tamaño de la lista
    // - Método para determinar si la lista está vacía o no (1:vacía)
    /*
        T front(); // Retorna el elemento al comienzo
        T back(); // Retorna el elemento al final
        void push_front(T); // Agrega un elemento al comienzo
        void push_back(T); // Agrega un elemento al final
        T pop_front(); // Remueve el elemento al comienzo
        T pop_back(); // Remueve el elemento al final
        void insert(T, int); // Inserta en cualquier posición
        void remove(int); // Remueve en cualquier posicion
        T operator[ ](int); // Retorna el elemento en la posición indicada
        bool empty(); // Retorna si la lista está vacía o no
        int size(); // Retorna el tamaño de la lista
        void clear(); // Elimina todos los elementos de la lista
        void reverse(); // Revierte la lista
            
    
    */
        */

};


int main(){


    return 0;
}