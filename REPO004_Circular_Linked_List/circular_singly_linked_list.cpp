/* PRESENTATION
    Topic: Circular Singly Linked List for a generic type
    Author: Luis Barahona
    Date: Sep 9, 2024
    Status Local: Funciona - Incomplete Library
    Status GitHub: No pushed
    Reference: https://www.geeksforgeeks.org/circular-linked-list/?ref=gcse_ind 
*/

#include <iostream>
#include <string>
using namespace std;

//The Node Structure de tipo T
template<typename T> //Declaramos la plantilla con el tipo genérico T
struct Node{
    T data;
    Node* next;

    Node(T data):data(data), next(nullptr){} //Constructor
};

//The Class that represent the circular singly linked list
template<typename T>
class Csllist{
    private:
        Node<T>* last; //pointer to the last node
    public:
        Csllist():last(nullptr){}//Constructor
        //Método para llenar la lista
        void fill_list(T data){
            Node<T>* new_node = new Node<T>(data); //creamos un nuevo nodo
            if (last==nullptr){
                last = new_node; //el nodo last es igual al único nodo existente
                last->next = new_node; //hacemos que el único nodo se apunte a sí mismo
            }
            else {
                // Agregamos el nuevo nodo al final
                new_node->next = last->next; // El nuevo nodo apunta al primer nodo
                last->next = new_node; // El nodo 'last' apunta al nuevo nodo
                last = new_node; // Actualizamos 'last' para que sea el último nodo
            }
        }
        //Método para imprimir la lista
        void display(){

            if (last==nullptr){ //Si la lista está vacía retornar None
                cout<<"lista vacia" ;
            }

            Node<T>* temp = last->next; //nodo que apunta al primer nodo (0°)
            do {
                cout<<temp->data<<" -> "; //imprime 0°
                temp = temp -> next; //temp se conviernte en 1° garcias al do
            }while(temp!=last->next); //temp o nodo actual es igual al nodo 0°??, salir si es así para evitar imprimir de nuevo el nodo 0°
            cout<<"NULL"<<endl;
        }

        //Método para insertar un elemento en un determianda posición
        //Método para retornar un elemento de una determianda posición
        //Método para eliminar un elemento de una determinada posición
        //Método para invertir el orden de la lista
        //Método de búsqueda
        //Método para determinar el tamaño de la lista
        //Método para determinar si la lista está vacía o no (1:vacía)
};





int main(){
    Csllist<int> circular_list1; //Lista de enteros
    Csllist<string> circular_list2; //Lista de strings

    //CASO 1: LLENAR AMBAS LISTAS
    circular_list1.fill_list(4);
    circular_list1.fill_list(5);
    circular_list1.fill_list(6);
    circular_list2.fill_list("Hola");
    circular_list2.fill_list("Adios");
    circular_list2.fill_list("Noche");

    //CASO 2: IMPRIMIR LAS LISTAS
    circular_list1.display();
    circular_list2.display();
    return 0;
}

