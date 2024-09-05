/* DESCRIPTION
    Topic: Conversion Bin2dec using a Simple Linked List
    Author: Luis David Barahona
    Date: Sep 4, 2024
    Status: Done
*/

#include <iostream>
#include <cmath>


//Node Struct
struct Node{
    int data;
    Node* next;

    Node(int data):data(data), next(nullptr){} //Constructor
};


//Class Simple Linked List
class SimpleLinkedList{
    private:
        Node* head;
    public:
        SimpleLinkedList():head(nullptr){} //Constructor
        void fill_list(int data) {
            Node* new_node = new Node(data); // Crear nuevo nodo en el heap

            if (head == NULL) {
                head = new_node; // Hacer que el head apunte al nuevo nodo
            } else {
                Node* temp = head;
                while (temp->next != NULL) { // Encontrar el último nodo
                    temp = temp->next;
                }
                temp->next = new_node; // Hacer que el último nodo apunte al nuevo nodo
            }
        }

        void display_list() {
            Node* temp = head; // Nos movemos al head
            while (temp != NULL) { // Mientras no sea NULL
                std::cout << temp->data << " -> ";
                temp = temp->next;
            }
            std::cout << "NULL" << std::endl; // Indicar el final de la lista
        }

        
        int size_list(){
            int size=0;
            Node* temp=head;
            while (temp!=nullptr){
                temp=temp->next;
                size++;
            }
            return size;    
        }

        int bin2dec(){
            Node* temp = head;
            int decimal=0;
            int count=1;
            int size = size_list();
            int expo=size;
            while(expo>0){
                expo=size-count;
                decimal = decimal + temp->data*(pow(2,expo));
                temp=temp->next;
                count++;
            }
            return decimal;
        }
};

int main(){
    //Create a simple linked list
    SimpleLinkedList list;
    list.fill_list(1);
    list.fill_list(1);
    list.fill_list(1);
    list.fill_list(1);
    list.display_list();
    std::cout<<list.size_list()<<std::endl;
    std::cout<<list.bin2dec()<<std::endl;

}