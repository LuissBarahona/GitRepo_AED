/*DETALLES
    Topic: Stack Implementation Using a Simple Linked List- Dynamic Size Array
    Author: Luis Barahona
    Date: Sep 11, 2024
    Status: Complete - Funciona

    Basic Operations:
        push() to insert an element into the stack -> igual al push front de simple linkes list
        pop() to remove an element from the stack 
        peek () para extraer el top element pero sin eliminarlo -> similar al pop front de simple linked list
        top() Returns the top element of the stack.
        isEmpty() returns true if stack is empty else false.
        isFull() returns true if the stack is full else false. 
    Mi convención
        El primer elemento de una simple linked list es el top element.
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
class Stack{
    private:
        Node<T>* top; //nodo que siempre estaría apuntando al último nodo que ingresó
        //top ocupa el mismo rol que ocupada top en una simple linked list->100% igual
        int size; //tamaño actual ocupado del stack

    public:
        Stack():top(nullptr){} //Constructor

        //void push_front(T data); Agrega un elemento al comienzo de la lista.
        void push(T data) {
            Node<T>* new_node = new Node<T>(data);
            new_node->next = top;
            top = new_node;
        }

        //T pop() Retorna el elemento al comienzo de la lista y lo elimina
        int pop() {
            Node<T>* temp = top;
            if (temp != NULL) {
                top = top->next; //elimina el elemento que antes era el top o top
                return temp->data; //pero primero lo retorna
            }
            else {
                throw std::out_of_range("La lista está vacía");
            }
        }

        //similar a T pop_front() de simple linked list; Retorna el elemento al comienzo de la lista o elemento TOP
        int peek() {
            if (top != NULL) {
                return top->data;
            }
            throw std::out_of_range("La lista está vacía");
        }

        //int size(); Retorna el tamaño de la lista.
        int get_size() {
            Node<T>* temp = top;
            int count = 0;
            while (temp != NULL) {
                count++;
                temp = temp->next;
            }
            size = count;
            return size;
        }

        //bool empty();Retorna si la lista está vacía o no.
        bool isEmpty() {
            return top == NULL; //bota 1 si head es igual a NULL, y 0 en el caso contrario
        }

        string isFull(){
            return "This is a dynamic stack, there isn't a max capacity";
        }
        //Mostrar los elementos del stack. Primero va el último elemento que ingresó ...
        void display_list() {
            cout<<"UP STACK :";
            Node<T>* temp = top; // Nos movemos al top
            while (temp != NULL) { // Mientras no sea NULL
                cout << temp->data << " -> ";
                temp = temp->next;
            }
            cout << " :DOWN STACK" << endl; // Indicar el final de la lista
        }

        //top -> valor del elemento almacenado en el top del stack
        T get_top(){
            return top->data;
        }


};

int main(){
    Stack<int> s; //stack de enteros
    s.push(10);
    s.push(20);
    s.push(30);
    s.display_list();
    cout<<"empty: "<<s.isEmpty()<<endl;
    cout<<"size: "<<s.get_size()<<endl;
    cout<<"peek: "<<s.peek()<<endl;
    cout<<"pop: "<<s.pop()<<endl;
    cout<<"top: "<<s.get_top()<<endl;
    s.display_list();
    cout<<"size: "<<s.get_size()<<endl;
    cout<<"peek: "<<s.peek()<<endl;
    cout<<"pop: "<<s.pop()<<endl;
    s.display_list();
    cout<<"pop: "<<s.pop()<<endl;
    s.display_list();
    cout<<"size: "<<s.get_size()<<endl;
    cout<<"empty: "<<s.isEmpty()<<endl;
    cout<<"full: "<<s.isFull()<<endl;
    return 0;
}