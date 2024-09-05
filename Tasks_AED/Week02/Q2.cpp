/* DESCRIPTION
    Topic: Looking for the nth node using a Simple Linked List
    Author: Luis David Barahona
    Date: Sep 5, 2024
    Status: Done
*/

#include <iostream>

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

        
        int get_size(){
            int size=0;
            Node* temp=head;
            while (temp!=nullptr){
                temp=temp->next;
                size++;
            }
            return size;    
        }

        int get_nodo_nth(int position){
            Node* temp=head; //Nos movemos al nodo 0°

            for (int i=position;i>0;i--){ //Nos dirijimos a la posi nth
                temp=temp->next;    
            }
            return temp->data; //retorna la data del nodo n-ésimo
        }

        int get_nodo_central(){
            Node* temp=head; //Nos movemos al nodo 0°
            int size = get_size();
            int div_entera=size/2; //Identifica la posi del elemento central
            return get_nodo_nth(div_entera);
        }
};

int main(){

    SimpleLinkedList list; //creamos una lista enlazada simple

    list.fill_list(1);
    list.fill_list(2);
    list.fill_list(3);
    list.fill_list(4);
    list.fill_list(5);
    list.fill_list(6);
    list.display_list();
    std::cout<<list.get_nodo_nth(0)<<std::endl;
    std::cout<<list.get_nodo_nth(2)<<std::endl;
    std::cout<<list.get_nodo_central()<<std::endl;

    return 0;
}