#include <iostream>
using namespace std;

template<typename T>
struct Node {
    T data;
    Node<T>* next;

    Node(T data) : data(data), next(NULL) {}
};

template<typename T>
class List {
    private:
        Node<T>* head;
        int node_count; // Contador de nodos

    public:
        List<T>() : head(NULL), node_count(0) {} // Constructor

        // Método para obtener el puntero al primer nodo
        Node<T>* getHead() {
            return head;
        }

        // Añadir nodo solo si no se excede el máximo de 3 nodos
        bool add_node(T data) {
            if (node_count >= 3) {
                return false; // Lista llena, no se puede añadir
            }

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
            node_count++; // Incrementa el número de nodos
            return true;
        }

        // Buscar un nodo con la clave
        bool search(T key) {
            Node<T>* temp = head;
            while (temp != NULL) {
                if (temp->data == key) {
                    return true; // Clave encontrada
                }
                temp = temp->next;
            }
            return false; // Clave no encontrada
        }

        // Eliminar un nodo con la clave
        bool delete_node(T key) {
            if (head == NULL) return false; // Lista vacía

            if (head->data == key) {
                Node<T>* temp = head;
                head = head->next;
                delete temp;
                node_count--; // Decrementar el número de nodos
                return true;
            }

            Node<T>* temp = head;
            while (temp->next != NULL && temp->next->data != key) {
                temp = temp->next;
            }

            if (temp->next == NULL) return false; // Clave no encontrada

            Node<T>* node_to_delete = temp->next;
            temp->next = node_to_delete->next;
            delete node_to_delete;
            node_count--; // Decrementar el número de nodos
            return true;
        }

        // Mostrar la lista enlazada
        void display_list() {
            Node<T>* temp = head;
            while (temp != NULL) {
                cout << temp->data << " -> ";
                temp = temp->next;
            }
            cout << "NULL";
        }

        // Retornar el número de nodos
        int size() {
            return node_count;
        }

        // Verificar si la lista está vacía
        bool empty() {
            return head == NULL;
        }

        ~List() {
            Node<T>* temp;
            while (head != NULL) {
                temp = head;
                head = head->next;
                delete temp;
            }
        }
};