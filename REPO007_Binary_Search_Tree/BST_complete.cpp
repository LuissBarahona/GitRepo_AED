//CONVENCIÓN PARA ESTE CODE
    //No existe el nivel 0, el root es el nivel 1

#include <iostream>
#include <queue>
#include <algorithm> // std::max

// Crear la estructura del nodo
template<typename T>
struct Node {
    T key;
    Node* left;
    Node* right;

    Node(T key) : key(key), left(nullptr), right(nullptr) {} // constructor
};

// Función para insertar un nodo en el árbol
template<typename T>
Node<T>* insert(Node<T>* root, T key) {
    if (root == nullptr) {
        return new Node<T>(key); // si el árbol está vacío, crear un nodo raíz
    }
    
    if (key < root->key) {
        root->left = insert(root->left, key); // insertar en el subárbol izquierdo
    } else if (key > root->key) {
        root->right = insert(root->right, key); // insertar en el subárbol derecho
    }

    return root;
}

// Búsqueda iterativa
template <typename T>
Node<T>* search_iterative(Node<T>* root, T key) {
    Node<T>* temp = root;
    while (temp != nullptr && temp->key != key) {
        if (temp->key < key) {
            temp = temp->right;
        } else {
            temp = temp->left;
        }
    }
    return temp;
}

// Búsqueda recursiva
template<typename T>
Node<T>* search_recursive(Node<T>* root, T key) {
    if (root == nullptr || root->key == key) return root;

    if (root->key < key)
        return search_recursive(root->right, key);

    return search_recursive(root->left, key);
}

// Función para encontrar el mínimo en un subárbol
template<typename T>
Node<T>* findMin(Node<T>* root) {
    while (root->left != nullptr) {
        root = root->left;
    }
    return root;
}

// Función para eliminar un nodo
template<typename T>
Node<T>* deleteNode(Node<T>* root, T key) {
    if (root == nullptr) return root;

    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    } else {
        // Caso 1: Sin hijos o un solo hijo
        if (root->left == nullptr) {
            Node<T>* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node<T>* temp = root->left;
            delete root;
            return temp;
        }

        // Caso 2: Dos hijos
        Node<T>* temp = findMin(root->right); // Encontrar el sucesor
        root->key = temp->key; // Reemplazar el valor
        root->right = deleteNode(root->right, temp->key); // Eliminar el sucesor
    }

    return root;
}

// Función para calcular el número de nodos (size)
template<typename T>
int size(Node<T>* root) {
    if (root == nullptr) return 0;
    return 1 + size(root->left) + size(root->right);
}

// Función para calcular la altura del árbol
template<typename T>
int height(Node<T>* root) {
    if (root == nullptr) return 0;
    return 1 + std::max(height(root->left), height(root->right));
}

// Recorridos del árbol

// Recorrido inorden
template<typename T>
void inorder(Node<T>* root) {
    if (root != nullptr) {
        inorder(root->left);
        std::cout << root->key << " ";
        inorder(root->right);
    }
}

// Recorrido preorden
template<typename T>
void preorder(Node<T>* root) {
    if (root != nullptr) {
        std::cout << root->key << " ";
        preorder(root->left);
        preorder(root->right);
    }
}

// Recorrido postorden
template<typename T>
void postorder(Node<T>* root) {
    if (root != nullptr) {
        postorder(root->left);
        postorder(root->right);
        std::cout << root->key << " ";
    }
}

// Recorrido en anchura (BFS)
template<typename T>
void breadthFirstTraversal(Node<T>* root) {
    if (root == nullptr) return;

    std::queue<Node<T>*> q;
    q.push(root);

    while (!q.empty()) {
        Node<T>* current = q.front();
        q.pop();

        std::cout << current->key << " ";

        if (current->left != nullptr)
            q.push(current->left);

        if (current->right != nullptr)
            q.push(current->right);
    }
}

// Recorrido en profundidad (DFS) (similar al preorden)
template<typename T>
void depthFirstTraversal(Node<T>* root) {
    if (root != nullptr) {
        std::cout << root->key << " ";
        depthFirstTraversal(root->left);
        depthFirstTraversal(root->right);
    }
}

// Función para encontrar el predecesor de un nodo
template<typename T>
Node<T>* findPredecessor(Node<T>* root, Node<T>* node) {
    if (node->left != nullptr) {
        return findMin(node->left);
    }

    Node<T>* predecessor = nullptr;
    while (root != nullptr) {
        if (node->key > root->key) {
            predecessor = root;
            root = root->right;
        } else if (node->key < root->key) {
            root = root->left;
        } else {
            break;
        }
    }
    return predecessor;
}

// Función para encontrar el sucesor de un nodo
template<typename T>
Node<T>* findSuccessor(Node<T>* root, Node<T>* node) {
    if (node->right != nullptr) {
        return findMin(node->right);
    }

    Node<T>* successor = nullptr;
    while (root != nullptr) {
        if (node->key < root->key) {
            successor = root;
            root = root->left;
        } else if (node->key > root->key) {
            root = root->right;
        } else {
            break;
        }
    }
    return successor;
}


///FFFF
// Función para encontrar el nivel de un nodo dado (considerando nivel 0)
template<typename T>
int findLevel(Node<T>* root, T key, int level = 0) {
    if (root == nullptr) {
        return -1; // nodo no encontrado
    }

    if (root->key == key) {
        return level; // se encontró el nodo
    }

    if (key < root->key) {
        return findLevel(root->left, key, level + 1); // buscar en el subárbol izquierdo
    } else {
        return findLevel(root->right, key, level + 1); // buscar en el subárbol derecho
    }
}

// Función para encontrar la altura de un nodo dado
template<typename T>
int findHeight(Node<T>* root, T key) {
    Node<T>* target = search_iterative(root, key); // buscar el nodo
    if (target == nullptr) return -1; // si el nodo no existe

    return height(target)-1; // altura del nodo (LE AGREGUE -1)
}


///FF
// Función principal para probar el BST
int main() {
    Node<int>* root = nullptr;
    root = insert(root, 8);
    insert(root, 3);
    insert(root, 10);
    insert(root, 1);
    insert(root, 6);
    insert(root, 14);
    insert(root, 4);
    insert(root, 7);
    insert(root, 13);

    std::cout << "Inorder traversal: ";
    inorder(root);
    std::cout << std::endl;

    std::cout << "Preorder traversal: ";
    preorder(root);
    std::cout << std::endl;

    std::cout << "Postorder traversal: ";
    postorder(root);
    std::cout << std::endl;

    std::cout << "Breadth-First traversal: ";
    breadthFirstTraversal(root);
    std::cout << std::endl;

    std::cout << "depthFirstTraversal: ";
    depthFirstTraversal(root);
    std::cout << std::endl;

    std::cout << "Tree height: " << height(root) << std::endl;

    std::cout << "Tree size: " << size(root) << std::endl;

    Node<int>* foundNode = search_iterative(root, 70);
    if (foundNode != nullptr) {
        std::cout << "Node 70 found!" << std::endl;
    } else {
        std::cout << "Node 70 not found!" << std::endl;
    }

    root = deleteNode(root, 50);
    std::cout << "Inorder traversal after deletion: ";
    inorder(root);
    std::cout << std::endl;

    //DFDF
    //DFDF
     int key = 8;
    int level = findLevel(root, key);
    int height = findHeight(root, key);

    if (level != -1) {
        std::cout << "El nodo con clave " << key << " está en el nivel " << level << std::endl;
        std::cout << "La altura del nodo con clave " << key << " es " << height << std::endl;
    } else {
        std::cout << "El nodo con clave " << key << " no se encuentra en el árbol." << std::endl;
    }

    return 0;
}
