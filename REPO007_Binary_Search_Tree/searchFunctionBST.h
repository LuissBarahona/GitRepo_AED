/* DETAILS OF THE PROYECT
    Author: Luis Barahona
    Date: Sep 23, 2024
    Format: Interactiva
*/

#include <iostream>

//Create the node structure
template<typename T>
struct Node{
    T key;
    Node* left;
    Node* right;

    Node(T key):key(key), left(nullptr), right(nullptr){} //constructor
};

//Create a function that returns a Node
template <typename T>
Node<T>* search_iterative(Node<T>* root, T key){ 
    //Inputs: Nodo root y el nodo a buscar

    Node<T>* temp = root; //nodo que recorrerá el árbol binario
    if (temp == NULL || temp->key == key){
        return temp; //caso base, el nodo root es igual al nodo buscado
    }

    while (temp != NULL && temp->key != key){
        if (temp->key < key){
            temp = temp->right; //nos movemos a la derecha 
        }
        else {
            temp = temp->left; //nos movemos a la izquierda
        }
        // Si por alguna razón el nodo que buscamos no está en el árbol
        // temp se convertirá en NULL e inmediatamente saldrá del bucle
    }
    // Salimos del bucle cuando encontramos al nodo

    return temp; //retornamos el nodo encontrado
}

template<typename T>
Node<T>* search_recursive(Node<T>* root, T key){

    // Base Cases: root is null or key 
    // is present at root
    if (root == NULL || root->key == key)
        return root; //rompe la recursividad (sale desde el nivel 4 por ejemplo si el key yace ahí)

    // Key is greater than root's key
    if (root->key < key)
        return search_recursive(root->right, key);

    // Key is smaller than root's key
    return search_recursive(root->left, key);

}