#include <iostream>
using namespace std;

// Estructura para representar un nodo de la lista doblemente enlazada
struct Node {
    int data;
    Node* next;
    Node* prev;

    Node(int val) : data(val), next(NULL), prev(NULL) {}
};

// Clase para manejar las operaciones de la lista doblemente enlazada
class List {
private:
    Node* head; // Puntero al primer nodo de la lista
    Node* tail; // Puntero al último nodo de la lista
    int count;  // Contador de elementos en la lista

public:
    // Constructor
    List() : head(NULL), tail(NULL), count(0) {}

    // Método para añadir un valor al final de la lista
    void fill_list(int val) {
        Node* newNode = new Node(val);
        if (head == NULL) { // Si la lista está vacía
            head = tail = newNode;
        } else { // Añadir al final de la lista
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        count++; // Incrementar el contador
    }

    // Método para mostrar la lista de inicio a fin
    void display_list() {
        Node* current = head;
        while (current != NULL) {
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << "None" << endl;
    }

    // Método para mostrar la lista en orden inverso
    void display_list_reverse() {
        Node* current = tail;
        while (current != NULL) {
            cout << current->data << " -> ";
            current = current->prev;
        }
        cout << "None" << endl;
    }

    // Método alternativo para llenar la lista
    void fill_list_2(int data) {
        Node* new_node = new Node(data); // Crear nuevo nodo
        if (head == NULL) { // Si no hay ningún nodo
            head = tail = new_node;
        } else { // Si ya hay nodos en la lista
            tail->next = new_node; // Añadir el nodo al final
            new_node->prev = tail; // Establecer enlace bidireccional
            tail = new_node; // Actualizar el tail al nuevo nodo
        }
        count++; // Incrementar el contador
    }

    // Añadir un nodo al inicio de la lista
    void push_front(int data) {
        Node* newNode = new Node(data);
        if (head == NULL) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        count++;
    }

    // Añadir un nodo al final de la lista (reutilizando fill_list)
    void push_back(int data) {
        fill_list(data);
    }

    // Remover el nodo al frente de la lista
    void pop_front() {
        if (head == NULL) return; // Lista vacía
        Node* temp = head;
        if (head == tail) { // Solo un elemento
            head = tail = NULL;
        } else {
            head = head->next;
            head->prev = NULL;
        }
        delete temp;
        count--;
    }

    // Remover el nodo al final de la lista
    void pop_back() {
        if (tail == NULL) return; // Lista vacía

        Node* temp = tail;

        if (head == tail) { // Solo un elemento
            head = tail = NULL;
        } else {
            tail = tail->prev;
            tail->next = NULL;
        }

        delete temp;
        count--;
    }

    // Obtener el elemento al frente de la lista
    int front() {
        if (head != NULL) return head->data;
        return -1; // Lista vacía
    }

    // Obtener el elemento al final de la lista
    int back() {
        if (tail != NULL) return tail->data;
        return -1; // Lista vacía
    }

    // Comprobar si la lista está vacía
    bool empty() {
        return head == NULL;
    }

    // Obtener el tamaño de la lista
    int size() {
        return count;
    }

    // Limpiar toda la lista
    void clear() {
        while (!empty()) {
            pop_front();
        }
    }

    // Insertar en la posición n-ésima
    void insert_nth(int data, int position) {
        Node* newNode = new Node(data);

        if (position == 0) { // Insertar al inicio
            push_front(data);
            return;
        }

        Node* current = head;
        int currentIndex = 0;

        while (current != NULL && currentIndex < position - 1) {
            current = current->next;
            currentIndex++;
        }

        if (current == NULL || current->next == NULL) { // Insertar al final
            push_back(data);
        } else { // Insertar en medio
            newNode->next = current->next;
            newNode->prev = current;
            current->next->prev = newNode;
            current->next = newNode;
            count++;
        }
    }

    // Remover en cualquier posición
    void remove(int position) {
        if (head == NULL) return; // Lista vacía

        if (position == 0) { // Eliminar el primer nodo
            pop_front();
            return;
        }

        Node* temp = head;
        int currentIndex = 0;

        while (temp != NULL && currentIndex < position) {
            temp = temp->next;
            currentIndex++;
        }

        if (temp != NULL) { // Si la posición es válida
            if (temp->next != NULL) { // No es el último nodo
                temp->next->prev = temp->prev;
            } else {
                tail = temp->prev; // Si es el último nodo, actualizar tail
            }

            if (temp->prev != NULL) { // No es el primer nodo
                temp->prev->next = temp->next;
            }

            delete temp;
            count--;
        }
    }

    // Obtener el elemento en la posición n-ésima
    int get_nth(int position) {
        if (head == NULL) {
            throw out_of_range("La lista está vacía.");
        }

        Node* current = head;
        int currentIndex = 0;

        while (current != NULL && currentIndex < position) {
            current = current->next;
            currentIndex++;
        }

        if (current == NULL) {
            throw out_of_range("Posición fuera de rango.");
        }

        return current->data;
    }

    // Revertir la lista
    void reverse() {
        if (head == NULL) return; // Lista vacía

        Node* current = head;
        Node* temp = NULL;

        while (current != NULL) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }

        if (temp != NULL) {
            head = temp->prev;
        }
    }

    // Insertar un elemento en la lista manteniendo un orden ascendente
    void sortedinsert(int data) {
        Node* newNode = new Node(data);

        if (head == NULL) {
            head = tail = newNode;
            count++;
            return;
        }

        if (data <= head->data) {
            push_front(data);
            return;
        }

        Node* current = head;
        while (current->next != NULL && current->next->data < data) {
            current = current->next;
        }

        newNode->next = current->next;

        if (current->next != NULL) {
            current->next->prev = newNode;
        } else {
            tail = newNode;
        }

        newNode->prev = current;
        current->next = newNode;
        count++;
    }

    // Eliminar elementos repetidos en la lista
    void delete_repetidos() {
        if (head == NULL) return;

        Node* current = head;

        while (current != NULL) {
            Node* runner = current->next;

            while (runner != NULL) {
                if (runner->data == current->data) {
                    Node* temp = runner;
                    runner->prev->next = runner->next;

                    if (runner->next != NULL) {
                        runner->next->prev = runner->prev;
                    } else {
                        tail = runner->prev;
                    }

                    runner = runner->next;
                    delete temp;
                    count--;
                } else {
                    runner = runner->next;
                }
            }
            current = current->next;
        }
    }

    // Verificar si la lista es un palíndromo
    bool verificar_palindro() {
        if (head == NULL) return true; // Lista vacía es un palíndromo

        Node* start = head;
        Node* end = tail;

        while (start != end && start->prev != end) {
            if (start->data != end->data) {
                return false; // No es un palíndromo
            }
            start = start->next;
            end = end->prev;
        }

        return true; // Es un palíndromo
    }

    // Destructor para limpiar la memoria de la lista
    ~List() {
        clear();
    }
};

// Programa de prueba
int main() {
    List list;

    // Caso 1: Llenar la lista y mostrarla
    cout << "Caso 1: Llenar la lista y mostrarla" << endl;
    list.fill_list(10);
    list.fill_list(20);
    list.fill_list(30);
    list.display_list();

    // Caso 2: Mostrar lista en orden inverso
    cout << "Caso 2: Mostrar lista en orden inverso" << endl;
    list.display_list_reverse();

    // Caso 3: Obtener elementos al frente y al final
    cout << "Caso 3: Obtener elementos al frente y al final" << endl;
    cout << "Elemento al frente: " << list.front() << endl;
    cout << "Elemento al final: " << list.back() << endl;
    cout << "Tamaño de la lista: " << list.size() << endl;

    // Caso 4: Añadir elementos al frente y al final
    cout << "Caso 4: Añadir elementos al frente y al final" << endl;
    list.push_front(5);
    list.push_back(35);
    list.display_list();

    // Caso 5: Insertar en la posición n-ésima
    cout << "Caso 5: Insertar en la posición n-ésima" << endl;
    list.insert_nth(15, 2); // Insertar 15 en la posición 2
    list.display_list();

    // Caso 6: Eliminar elementos en posiciones específicas
    cout << "Caso 6: Eliminar elementos en posiciones específicas" << endl;
    list.remove(2); // Eliminar el elemento en la posición 2
    list.display_list();

    // Caso 7: Obtener el elemento en la posición n-ésima
    cout << "Caso 7: Obtener el elemento en la posición n-ésima" << endl;
    try {
        cout << "Elemento en la posición 2: " << list.get_nth(2) << endl;
    } catch (const out_of_range& e) {
        cout << e.what() << endl;
    }

    // Caso 8: Revertir la lista
    cout << "Caso 8: Revertir la lista" << endl;
    list.reverse();
    list.display_list();

    // Caso 9: Insertar en orden ascendente
    cout << "Caso 9: Insertar en orden ascendente" << endl;
    list.sortedinsert(25);
    list.sortedinsert(1);
    list.display_list();

    // Caso 10: Eliminar elementos repetidos
    cout << "Caso 10: Eliminar elementos repetidos" << endl;
    list.fill_list(10); // Añadir un elemento repetido
    list.fill_list(25); // Añadir un elemento repetido
    cout << "Lista antes de eliminar repetidos:" << endl;
    list.display_list();
    list.delete_repetidos();
    cout << "Lista después de eliminar repetidos:" << endl;
    list.display_list();

    // Caso 11: Verificar si la lista es un palíndromo
    cout << "Caso 11: Verificar si la lista es un palíndromo" << endl;
    List palindromList;
    palindromList.fill_list(1);
    palindromList.fill_list(2);
    palindromList.fill_list(3);
    palindromList.fill_list(2);
    palindromList.fill_list(1);
    cout << "Lista: ";
    palindromList.display_list();
    if (palindromList.verificar_palindro()) {
        cout << "La lista es un palíndromo." << endl;
    } else {
        cout << "La lista no es un palíndromo." << endl;
    }

    // Caso 12: Limpiar la lista
    cout << "Caso 12: Limpiar la lista" << endl;
    list.clear();
    cout << "Lista después de limpiar: ";
    list.display_list();

    return 0;
}
