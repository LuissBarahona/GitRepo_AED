/* DESCRIPTION
    Topic: Simple Linked Lists o Forward Lists with Template 
    Goal: Learn to create Simple Linked Lists
    Author: Luis Barahona
    Date: Sep 3, 2024
    Status:Done
*/


#include <iostream>
using namespace std;

template<typename T>
struct Node {
    T data;
    Node<T>* next;
    
    // Constructor para inicializar un nodo con datos y apuntando a NULL
    Node(T data) : data(data), next(NULL) {}
};

template<typename T>
class List {
    private:
        Node<T>* head;
    public:
        List<T>() : head(NULL) {} // Constructor de la clase

        void add_node(T data) {
            Node<T>* new_node = new Node<T>(data); // Crear nuevo nodo en el heap

            if (head == NULL) {
                head = new_node; // Hacer que el head apunte al nuevo nodo
            } else {
                Node<T>* temp = head;
                while (temp->next != NULL) { // Encontrar el último nodo
                    temp = temp->next;
                }
                temp->next = new_node; // Hacer que el último nodo apunte al nuevo nodo
            }
        }

        void display_list() {
            Node<T>* temp = head; // Nos movemos al head
            while (temp != NULL) { // Mientras no sea NULL
                cout << temp->data << " -> ";
                temp = temp->next;
            }
            cout << "NULL" << endl; // Indicar el final de la lista
        }

        void insert_into_nth(T data, int n) {
            Node<T>* new_node = new Node<T>(data); // Crear un nuevo nodo

            if (n == 0) {
                // Caso 1: Insertar al inicio de la lista
                new_node->next = head; // Hacer que el nuevo nodo apunte al head actual
                head = new_node; // Actualizar head para que apunte al nuevo nodo
            } else {
                // Caso 2: Insertar en cualquier otra posición
                Node<T>* temp = head;
                for (int i = 0; i < n - 1 && temp != NULL; i++) { //n-1 veces
                    temp = temp->next; // Moverse al nodo anterior a la posición n
                }
                if (temp != NULL) {
                    new_node->next = temp->next; // Hacer que el nuevo nodo apunte al siguiente nodo en la lista
                    temp->next = new_node; // Hacer que el nodo anterior apunte al nuevo nodo
                } else {
                    cout << "La posición es inválida, fuera de los límites de la lista." << endl;
                    delete new_node; // Liberar memoria si la posición es inválida
                }
            }
        }


        void delet_nth(int n){
            Node<T>* temp = head; //HAcer que temp apunte al nodo head 0°
            Node<T>* temp2;
            if (n==0){
                
                temp = temp->next; //Temp se convierte en 1°
                head = temp; //El nodo head ahora es igual al nodo temp
            }
            else {
                for (int i=n-1;i>0;i--){ //n-1 veces
                    temp = temp->next;
                }
                temp2=temp;
                temp2 = temp2->next;
                temp->next = temp2->next;
            }
        }

        void reverse() {
            Node<T>* prev = NULL; // Puntero para rastrear el nodo anterior
            Node<T>* current = head; // Puntero para rastrear el nodo actual
            Node<T>* next = NULL; // Puntero para rastrear el siguiente nodo

            while (current != NULL) {
                next = current->next; // Guardar el siguiente nodo
                current->next = prev; // Invertir el enlace actual
                prev = current; // Mover `prev` a `current`
                current = next; // Mover `current` a `next`
            }
            head = prev; // Actualizar head para que apunte al nuevo primer nodo
        }


        void bubble_sort() { //Ascendente
            // Si la lista está vacía, no hay nada que ordenar
            if (head == NULL) {
                return;
            }

            bool swapped;       // Variable para rastrear si hubo un intercambio en la iteración actual
            Node<T>* ptr1;         // Puntero que recorre la lista
            Node<T>* lptr = NULL;  // Puntero que marca el final de la porción ordenada de la lista

            // Repetir el proceso hasta que no haya más intercambios
            do {
                swapped = false;    // Resetear el indicador de intercambio
                ptr1 = head;        // Iniciar desde el comienzo de la lista

                // Recorrer la lista hasta el nodo antes de `lptr`
                while (ptr1->next != lptr) {
                    // Si el valor del nodo actual es mayor que el siguiente, intercambiarlos
                    if (ptr1->data > ptr1->next->data) {
                        // Intercambiar los datos de los nodos adyacentes
                        int temp = ptr1->data;
                        ptr1->data = ptr1->next->data;
                        ptr1->next->data = temp;
                        swapped = true;   // Marcar que se hizo un intercambio
                    }
                    ptr1 = ptr1->next;    // Moverse al siguiente nodo
                }
                lptr = ptr1;    // El último nodo ahora es parte de la lista ordenada
            } while (swapped);  // Repetir el proceso si hubo algún intercambio en la iteración
        }

        void bubble_sort_descending() {
            // Si la lista está vacía, no hay nada que ordenar
            if (head == NULL) {
                return;
            }

            bool swapped;       // Variable para rastrear si hubo un intercambio en la iteración actual
            Node<T>* ptr1;         // Puntero que recorre la lista
            Node<T>* lptr = NULL;  // Puntero que marca el final de la porción ordenada de la lista

            // Repetir el proceso hasta que no haya más intercambios
            do {
                swapped = false;    // Resetear el indicador de intercambio
                ptr1 = head;        // Iniciar desde el comienzo de la lista

                // Recorrer la lista hasta el nodo antes de `lptr`
                while (ptr1->next != lptr) {
                    // Si el valor del nodo actual es menor que el siguiente, intercambiarlos
                    if (ptr1->data < ptr1->next->data) {
                        // Intercambiar los datos de los nodos adyacentes
                        T temp = ptr1->data;
                        ptr1->data = ptr1->next->data;
                        ptr1->next->data = temp;
                        swapped = true;   // Marcar que se hizo un intercambio
                    }
                    ptr1 = ptr1->next;    // Moverse al siguiente nodo
                }
                lptr = ptr1;    // El último nodo ahora es parte de la lista ordenada
            } while (swapped);  // Repetir el proceso si hubo algún intercambio en la iteración
        }

        //T front(); Retorna el elemento al comienzo de la lista
        int front() {
            if (head != NULL) {
                return head->data;
            }
            throw std::out_of_range("La lista está vacía");
        }

        //T back(); Retorna el elemento al final de la lista.
        int back() {
            if (head != NULL) {
                Node<T>* temp = head;
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                return temp->data;
            }
            throw std::out_of_range("La lista está vacía");
        }

        //void push_front(T data); Agrega un elemento al comienzo de la lista.
        void push_front(T data) {
            Node<T>* new_node = new Node<T>(data);
            new_node->next = head;
            head = new_node;
        }

        //void push_back(T data); Agrega un elemento al final de la lista.
        void push_back(T data) {
            Node<T>* new_node = new Node<T>(data);
            if (head == NULL) {
                head = new_node;
            } else {
                Node<T>* temp = head;
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = new_node;
            }
        }

        //T pop_front(); Remueve el elemento al comienzo de la lista y lo retorna.
        int pop_front() {
            if (head != NULL) {
                Node<T>* temp = head;
                T data = temp->data; //T data
                head = head->next;
                delete temp;
                return data;
            }
            throw std::out_of_range("La lista está vacía");
        }

        //T operator[](int index); Retorna el elemento en la posición indicada.
        int operator[](int index) {
            Node<T>* temp = head;
            int count = 0;
            while (temp != NULL) {
                if (count == index) {
                    return temp->data;
                }
                count++;
                temp = temp->next;
            }
            throw std::out_of_range("Índice fuera de rango");
        }

        //bool empty();Retorna si la lista está vacía o no.
        bool empty() {
            return head == NULL; //bota 1 si head es igual a NULL, y 0 en el caso contrario
        }

        //int size(); Retorna el tamaño de la lista.
        int size() {
            Node<T>* temp = head;
            int count = 0;
            while (temp != NULL) {
                count++;
                temp = temp->next;
            }
            return count;
        }


        //void clear(); Elimina todos los elementos de la lista.
        void clear() {
            Node<T>* temp;
            while (head != NULL) {
                temp = head;
                head = head->next;
                delete temp;
            }
        }



        ~List() {
            // Liberar la memoria de todos los nodos
            Node<T>* temp;
            while (head != NULL) {
                temp = head;
                head = head->next;
                delete temp;
            }
        }
};

int main() {
    List<int> linked_list;
    linked_list.add_node(5);
    linked_list.add_node(4);
    linked_list.add_node(10);
    linked_list.add_node(2);
     linked_list.display_list();
    linked_list.insert_into_nth(100,0);
    linked_list.display_list();
    linked_list.delet_nth(0);
    linked_list.display_list();
    linked_list.delet_nth(1);
    linked_list.display_list();
    linked_list.reverse();
    linked_list.display_list();
    linked_list.bubble_sort();
    linked_list.display_list();
    linked_list.bubble_sort_descending();
    linked_list.display_list();
    int a = linked_list.front();
    cout<<a<<endl;
    //linked_list.clear();
    linked_list.display_list();
    cout<<linked_list.empty()<<endl;
    return 0;
}
