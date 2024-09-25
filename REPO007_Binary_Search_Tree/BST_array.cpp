#include <iostream>
#include <limits.h> // Para utilizar INT_MIN y INT_MAX

// Estructura de Nodo para el árbol binario
template<typename T>
struct Node {
    T key;
    Node* left;
    Node* right;

    Node(T key) : key(key), left(nullptr), right(nullptr) {} // constructor
};

// Función recursiva para construir el BST desde preorden
template<typename T>
Node<T>* buildBSTFromPreorder(T pre[], int& index, T minVal, T maxVal, int size) {
    // Si todos los elementos han sido procesados o el valor actual no está dentro del rango, retornar nullptr
    if (index >= size || pre[index] < minVal || pre[index] > maxVal) {
        return nullptr;
    }

    // El primer valor del preorder actual es la raíz de este subárbol
    T rootVal = pre[index];
    Node<T>* root = new Node<T>(rootVal);

    index++; // Avanzamos al siguiente elemento en preorden

    // Todos los valores menores que rootVal forman parte del subárbol izquierdo
    root->left = buildBSTFromPreorder(pre, index, minVal, rootVal, size);

    // Todos los valores mayores que rootVal forman parte del subárbol derecho
    root->right = buildBSTFromPreorder(pre, index, rootVal, maxVal, size);

    return root;
}

// Función principal que inicia la construcción del BST
template<typename T>
Node<T>* constructBSTFromPreorder(T pre[], int size) {
    int index = 0;
    return buildBSTFromPreorder(pre, index, INT_MIN, INT_MAX, size);
}

// Funciones para imprimir el BST en preorden (para verificar el resultado)
template<typename T>
void printPreorder(Node<T>* node) {
    if (node == nullptr) return;
    std::cout << node->key << " ";
    printPreorder(node->left);
    printPreorder(node->right);
}

// Función principal para probar la construcción del BST
int main() {
    int pre[] = {10, 5, 1, 7, 40, 50}; // Recorrido preorden
    int size = sizeof(pre) / sizeof(pre[0]);

    Node<int>* root = constructBSTFromPreorder(pre, size);

    // Imprimir el BST en preorden para verificar que se construyó correctamente
    std::cout << "El BST construido (en preorden) es: ";
    printPreorder(root);
    std::cout << std::endl;

    return 0;
}
