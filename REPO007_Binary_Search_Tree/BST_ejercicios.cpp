#include <iostream>
#include <algorithm> // std::max

// Crear la estructura del nodo
template<typename T>
struct Node {
    T key;
    Node* left;
    Node* right;

    Node(T key) : key(key), left(nullptr), right(nullptr) {} // constructor
};

// Función auxiliar para calcular la altura de un nodo
template<typename T>
int height(Node<T>* root) {
    if (root == nullptr) return -1; // La altura de un nodo nulo es -1
    return 1 + std::max(height(root->left), height(root->right));
}

// 1. Comprobar si el árbol binario está equilibrado en altura
template<typename T>
bool isBalanced(Node<T>* root) {
    if (root == nullptr) return true;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    if (std::abs(leftHeight - rightHeight) > 1) return false;

    // Verificamos recursivamente en los subárboles
    return isBalanced(root->left) && isBalanced(root->right);
}

// Función auxiliar para convertir un BST en un árbol balanceado sin usar vectores
template<typename T>
Node<T>* buildBalancedBST(Node<T>** nodes, int start, int end) {
    if (start > end) return nullptr;

    // Encontrar el nodo medio y establecerlo como raíz
    int mid = (start + end) / 2;
    Node<T>* root = nodes[mid];

    // Construir recursivamente los subárboles
    root->left = buildBalancedBST(nodes, start, mid - 1);
    root->right = buildBalancedBST(nodes, mid + 1, end);

    return root;
}

// Función auxiliar para almacenar los nodos en orden ascendente (sin vector)
template<typename T>
int storeBSTNodes(Node<T>* root, Node<T>** nodes, int i = 0) {
    if (root == nullptr) return i;

    // Almacenar los nodos en orden inorden
    i = storeBSTNodes(root->left, nodes, i);
    nodes[i++] = root;
    i = storeBSTNodes(root->right, nodes, i);

    return i;
}

// 2. Convertir el BST en un árbol balanceado
template<typename T>
Node<T>* balanceBST(Node<T>* root) {
    if (root == nullptr) return nullptr;

    // Contar el número de nodos en el BST
    int n = storeBSTNodes(root, nullptr);

    Node<T>* nodes[n]; // Array de punteros para almacenar los nodos

    // Llenar el array con nodos en inorden
    storeBSTNodes(root, nodes);

    // Construir el árbol balanceado a partir del array de nodos
    return buildBalancedBST(nodes, 0, n - 1);
}

// 3. Comprobar si subRoot es un subárbol de root
template<typename T>
bool isSameTree(Node<T>* root, Node<T>* subRoot) {
    if (root == nullptr && subRoot == nullptr) return true;
    if (root == nullptr || subRoot == nullptr) return false;

    // Comparar la estructura y los valores de los nodos
    return (root->key == subRoot->key) && isSameTree(root->left, subRoot->left) && isSameTree(root->right, subRoot->right);
}

template<typename T>
bool isSubtree(Node<T>* root, Node<T>* subRoot) {
    if (root == nullptr) return false;
    if (isSameTree(root, subRoot)) return true;

    // Verificar recursivamente en los subárboles
    return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
}

// 4. Encontrar el ancestro común más bajo de las hojas más profundas
template<typename T>
Node<T>* findDeepestLCA(Node<T>* root, int depth, int& deepest, Node<T>*& lca) {
    if (root == nullptr) return nullptr;

    if (!root->left && !root->right) {
        if (depth > deepest) {
            deepest = depth;
            lca = root;
        }
        return root;
    }

    Node<T>* leftLCA = findDeepestLCA(root->left, depth + 1, deepest, lca);
    Node<T>* rightLCA = findDeepestLCA(root->right, depth + 1, deepest, lca);

    if (leftLCA && rightLCA) {
        return root;
    }

    return (leftLCA != nullptr) ? leftLCA : rightLCA;
}

template<typename T>
Node<T>* lowestCommonAncestorDeepestLeaves(Node<T>* root) {
    if (root == nullptr) return nullptr;

    int deepest = 0;
    Node<T>* lca = nullptr;

    findDeepestLCA(root, 0, deepest, lca);

    return lca;
}

// Función principal para probar el BST
int main() {
    Node<int>* root = nullptr;
    root = new Node<int>(50);
    root->left = new Node<int>(30);
    root->right = new Node<int>(70);
    root->left->left = new Node<int>(20);
    root->left->right = new Node<int>(40);
    root->right->left = new Node<int>(60);
    root->right->right = new Node<int>(80);

    // 1. Verificar si el árbol está equilibrado
    if (isBalanced(root)) {
        std::cout << "El árbol está equilibrado en altura." << std::endl;
    } else {
        std::cout << "El árbol no está equilibrado en altura." << std::endl;
    }

    // 2. Balancear el BST
    Node<int>* balancedRoot = balanceBST(root);
    std::cout << "El árbol BST ha sido equilibrado." << std::endl;

    // 3. Verificar si subRoot es subárbol de root
    Node<int>* subRoot = new Node<int>(70);
    subRoot->left = new Node<int>(60);
    subRoot->right = new Node<int>(80);

    if (isSubtree(root, subRoot)) {
        std::cout << "subRoot es un subárbol de root." << std::endl;
    } else {
        std::cout << "subRoot no es un subárbol de root." << std::endl;
    }

    // 4. Encontrar el ancestro común más bajo de las hojas más profundas
    Node<int>* lcaDeepest = lowestCommonAncestorDeepestLeaves(root);
    if (lcaDeepest) {
        std::cout << "El ancestro común más bajo de las hojas más profundas es: " << lcaDeepest->key << std::endl;
    }

    return 0;
}
