#include <iostream>
#include <chrono> // Incluir para medir el tiempo
using namespace std;

#include "searchFunctionBST.h"

int main (){
    // Crear nodo directamente
    Node<int>* root = new Node<int>(8); // Crear nodo root
    root->left = new Node<int>(5);
    root->right = new Node<int>(12);

    root->left->left = new Node<int>(2);
    root->left->right = new Node<int>(7);
    root->right->right = new Node<int>(16);

    root->left->right->left = new Node<int>(6);
    root->right->right->left = new Node<int>(14); // Valor corregido a 14
    root->right->right->right = new Node<int>(20); // Valor corregido a 20

    // Medir tiempo de búsqueda ITERATIVA
    auto start = chrono::high_resolution_clock::now(); // Tiempo inicial
    (search_iterative(root, 13) != NULL) ? cout << "Found (Iterative)\n" : cout << "Not Found (Iterative)\n";
    auto end = chrono::high_resolution_clock::now(); // Tiempo final

    chrono::duration<double> elapsed = end - start; // Calcular tiempo transcurrido
    cout << "Time taken for iterative search (13): " << elapsed.count() << " seconds\n";

    start = chrono::high_resolution_clock::now(); // Tiempo inicial
    (search_iterative(root, 20) != NULL) ? cout << "Found (Iterative)\n" : cout << "Not Found (Iterative)\n";
    end = chrono::high_resolution_clock::now(); // Tiempo final

    elapsed = end - start; // Calcular tiempo transcurrido
    cout << "Time taken for iterative search (20): " << elapsed.count() << " seconds\n";

    // Medir tiempo de búsqueda RECURSIVA
    start = chrono::high_resolution_clock::now(); // Tiempo inicial
    (search_recursive(root, 13) != NULL) ? cout << "Found (Recursive)\n" : cout << "Not Found (Recursive)\n";
    end = chrono::high_resolution_clock::now(); // Tiempo final

    elapsed = end - start; // Calcular tiempo transcurrido
    cout << "Time taken for recursive search (13): " << elapsed.count() << " seconds\n";

    start = chrono::high_resolution_clock::now(); // Tiempo inicial
    (search_recursive(root, 20) != NULL) ? cout << "Found (Recursive)\n" : cout << "Not Found (Recursive)\n";
    end = chrono::high_resolution_clock::now(); // Tiempo final

    elapsed = end - start; // Calcular tiempo transcurrido
    cout << "Time taken for recursive search (20): " << elapsed.count() << " seconds\n";

    return 0;
}
