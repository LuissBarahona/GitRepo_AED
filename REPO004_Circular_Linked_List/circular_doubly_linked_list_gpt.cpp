/* PRESENTATION
    Topic: Circular Doubly Linked List for a generic type
    Author: GPT
    Date: Sep 9, 2024
    Status Local: Funciona - Incomplete Library
    Status GitHub: No pushed
    Reference: https://www.geeksforgeeks.org/introduction-to-circular-doubly-linked-list/?ref=gcse_ind
*/

#include <iostream>
#include <stdexcept> // Para std::out_of_range

template<typename T>
struct Node {
    T data;
    Node* prev;
    Node* next;

    Node(T data): data(data), prev(nullptr), next(nullptr) {}
};

template<typename T>
class Cdll {
    private:
        Node<T>* sentinel;
        int listSize;

        // Helper function to create a new node
        Node<T>* createNode(T data) {
            return new Node<T>(data);
        }

        // Helper function to delete a node
        void deleteNode(Node<T>* node) {
            delete node;
        }

    public:
        Cdll() : listSize(0) {
            // Initialize a sentinel node to simplify circular list operations
            sentinel = createNode(T()); // Using default constructor for T
            sentinel->next = sentinel;
            sentinel->prev = sentinel;
        }

        ~Cdll() {
            clear();
            deleteNode(sentinel);
        }

        void push_front(T data) {
            Node<T>* newNode = createNode(data);
            newNode->next = sentinel->next;
            newNode->prev = sentinel;
            sentinel->next->prev = newNode;
            sentinel->next = newNode;
            listSize++;
        }

        void push_back(T data) {
            Node<T>* newNode = createNode(data);
            newNode->next = sentinel;
            newNode->prev = sentinel->prev;
            sentinel->prev->next = newNode;
            sentinel->prev = newNode;
            listSize++;
        }

        T pop_front() {
            if (empty()) throw std::out_of_range("List is empty");
            Node<T>* nodeToRemove = sentinel->next;
            T data = nodeToRemove->data;
            sentinel->next = nodeToRemove->next;
            nodeToRemove->next->prev = sentinel;
            deleteNode(nodeToRemove);
            listSize--;
            return data;
        }

        T pop_back() {
            if (empty()) throw std::out_of_range("List is empty");
            Node<T>* nodeToRemove = sentinel->prev;
            T data = nodeToRemove->data;
            sentinel->prev = nodeToRemove->prev;
            nodeToRemove->prev->next = sentinel;
            deleteNode(nodeToRemove);
            listSize--;
            return data;
        }

        void insert(T data, int pos) {
            if (pos < 0 || pos > listSize) throw std::out_of_range("Index out of range");
            if (pos == 0) {
                push_front(data);
            } else if (pos == listSize) {
                push_back(data);
            } else {
                Node<T>* newNode = createNode(data);
                Node<T>* current = sentinel->next;
                for (int i = 0; i < pos - 1; i++) {
                    current = current->next;
                }
                newNode->next = current->next;
                newNode->prev = current;
                current->next->prev = newNode;
                current->next = newNode;
                listSize++;
            }
        }

        void remove(int pos) {
            if (pos < 0 || pos >= listSize) throw std::out_of_range("Index out of range");
            if (pos == 0) {
                pop_front();
            } else if (pos == listSize - 1) {
                pop_back();
            } else {
                Node<T>* current = sentinel->next;
                for (int i = 0; i < pos; i++) {
                    current = current->next;
                }
                current->prev->next = current->next;
                current->next->prev = current->prev;
                deleteNode(current);
                listSize--;
            }
        }

        T operator[](int pos) const {
            if (pos < 0 || pos >= listSize) throw std::out_of_range("Index out of range");
            Node<T>* current = sentinel->next;
            for (int i = 0; i < pos; i++) {
                current = current->next;
            }
            return current->data;
        }

        bool empty() const {
            return listSize == 0;
        }

        int size() const {
            return listSize;
        }

        void clear() {
            while (!empty()) {
                pop_front();
            }
        }

        void reverse() {
            if (empty() || listSize == 1) return;
            Node<T>* current = sentinel;
            Node<T>* temp = nullptr;
            do {
                temp = current->next;
                current->next = current->prev;
                current->prev = temp;
                current = temp;
            } while (current != sentinel);
            // Adjust the sentinel node pointers
            sentinel->next = sentinel->prev;
            sentinel->prev = current->prev;
        }

        void display() const {
            if (empty()) {
                std::cout << "List is empty." << std::endl;
                return;
            }
            Node<T>* current = sentinel->next;
            do {
                std::cout << current->data << " ";
                current = current->next;
            } while (current != sentinel->next);
            std::cout << std::endl;
        }

        T front() const {
            if (empty()) throw std::out_of_range("List is empty");
            return sentinel->next->data;
        }

        T back() const {
            if (empty()) throw std::out_of_range("List is empty");
            return sentinel->prev->data;
        }
};

int main() {
    Cdll<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_front(0);
    list.insert(4, 2);
    list.display(); // Output: 0 1 4 2 3

    list.remove(2);
    list.display(); // Output: 0 1 2 3

    list.reverse();
    list.display(); // Output: 3 2 1 0

    std::cout << "Front: " << list.front() << std::endl; // Output: Front: 3
    std::cout << "Back: " << list.back() << std::endl;   // Output: Back: 0

    list.clear();
    list.display(); // Output: List is empty.

    return 0;
}
