#include <iostream>
#include <queue>
#include <algorithm>

struct NodeAVL {
    int data;
    NodeAVL* hijoDerecho;
    NodeAVL* hijoIzquierdo;
    int altura;

    NodeAVL(int val) : data(val), hijoDerecho(nullptr), hijoIzquierdo(nullptr), altura(1) {}
};

class TreeAVL {
private:
    NodeAVL* insertar(NodeAVL* node, int data);
    NodeAVL* eliminar(NodeAVL* node, int data);
    NodeAVL* buscar(NodeAVL* node, int data);
    NodeAVL* rotacionDerecha(NodeAVL* y);
    NodeAVL* rotacionIzquierda(NodeAVL* x);
    int obtenerAltura(NodeAVL* node);
    int obtenerBalance(NodeAVL* node);
    void preorder(NodeAVL* node);
    void postorder(NodeAVL* node);
    void recorridoAnchura(NodeAVL* node);
    void recorridoProfundidad(NodeAVL* node);
    
public:
    NodeAVL* root;

    TreeAVL() : root(nullptr) {}
    void insertar(int data);
    void eliminar(int data);
    bool buscar(int data);
    void preorder();
    void postorder();
    void recorridoAnchura();
    void recorridoProfundidad();
};

// Métodos privados
int TreeAVL::obtenerAltura(NodeAVL* node) {
    return node ? node->altura : 0;
}

int TreeAVL::obtenerBalance(NodeAVL* node) {
    return node ? obtenerAltura(node->hijoIzquierdo) - obtenerAltura(node->hijoDerecho) : 0;
}

NodeAVL* TreeAVL::rotacionDerecha(NodeAVL* y) {
    NodeAVL* x = y->hijoIzquierdo;
    NodeAVL* T2 = x->hijoDerecho;

    x->hijoDerecho = y;
    y->hijoIzquierdo = T2;

    y->altura = std::max(obtenerAltura(y->hijoIzquierdo), obtenerAltura(y->hijoDerecho)) + 1;
    x->altura = std::max(obtenerAltura(x->hijoIzquierdo), obtenerAltura(x->hijoDerecho)) + 1;

    return x;
}

NodeAVL* TreeAVL::rotacionIzquierda(NodeAVL* x) {
    NodeAVL* y = x->hijoDerecho;
    NodeAVL* T2 = y->hijoIzquierdo;

    y->hijoIzquierdo = x;
    x->hijoDerecho = T2;

    x->altura = std::max(obtenerAltura(x->hijoIzquierdo), obtenerAltura(x->hijoDerecho)) + 1;
    y->altura = std::max(obtenerAltura(y->hijoIzquierdo), obtenerAltura(y->hijoDerecho)) + 1;

    return y;
}

NodeAVL* TreeAVL::insertar(NodeAVL* node, int data) {
    if (!node) {
        return new NodeAVL(data);
    }

    if (data < node->data) {
        node->hijoIzquierdo = insertar(node->hijoIzquierdo, data);
    } else if (data > node->data) {
        node->hijoDerecho = insertar(node->hijoDerecho, data);
    } else {
        return node;
    }

    node->altura = 1 + std::max(obtenerAltura(node->hijoIzquierdo), obtenerAltura(node->hijoDerecho));

    int balance = obtenerBalance(node);

    if (balance > 1 && data < node->hijoIzquierdo->data) {
        return rotacionDerecha(node);
    }

    if (balance < -1 && data > node->hijoDerecho->data) {
        return rotacionIzquierda(node);
    }

    if (balance > 1 && data > node->hijoIzquierdo->data) {
        node->hijoIzquierdo = rotacionIzquierda(node->hijoIzquierdo);
        return rotacionDerecha(node);
    }

    if (balance < -1 && data < node->hijoDerecho->data) {
        node->hijoDerecho = rotacionDerecha(node->hijoDerecho);
        return rotacionIzquierda(node);
    }

    return node;
}

NodeAVL* TreeAVL::buscar(NodeAVL* node, int data) {
    if (!node || node->data == data) {
        return node;
    }

    if (data < node->data) {
        return buscar(node->hijoIzquierdo, data);
    }

    return buscar(node->hijoDerecho, data);
}

// Métodos públicos
void TreeAVL::insertar(int data) {
    root = insertar(root, data);
}

bool TreeAVL::buscar(int data) {
    return buscar(root, data) != nullptr;
}

void TreeAVL::preorder(NodeAVL* node) {
    if (node) {
        std::cout << node->data << " ";
        preorder(node->hijoIzquierdo);
        preorder(node->hijoDerecho);
    }
}

void TreeAVL::preorder() {
    preorder(root);
    std::cout << std::endl;
}

void TreeAVL::postorder(NodeAVL* node) {
    if (node) {
        postorder(node->hijoIzquierdo);
        postorder(node->hijoDerecho);
        std::cout << node->data << " ";
    }
}

void TreeAVL::postorder() {
    postorder(root);
    std::cout << std::endl;
}

void TreeAVL::recorridoAnchura(NodeAVL* node) {
    if (!node) return;

    std::queue<NodeAVL*> q;
    q.push(node);

    while (!q.empty()) {
        NodeAVL* current = q.front();
        q.pop();
        std::cout << current->data << " ";

        if (current->hijoIzquierdo) q.push(current->hijoIzquierdo);
        if (current->hijoDerecho) q.push(current->hijoDerecho);
    }
}

void TreeAVL::recorridoAnchura() {
    recorridoAnchura(root);
    std::cout << std::endl;
}

void TreeAVL::recorridoProfundidad(NodeAVL* node) {
    if (node) {
        recorridoProfundidad(node->hijoIzquierdo);
        std::cout << node->data << " ";
        recorridoProfundidad(node->hijoDerecho);
    }
}

void TreeAVL::recorridoProfundidad() {
    recorridoProfundidad(root);
    std::cout << std::endl;
}

int main() {
    TreeAVL arbol;

    // Insertar nodos
    arbol.insertar(10);
    arbol.insertar(20);
    arbol.insertar(30);
    arbol.insertar(40);
    arbol.insertar(50);
    arbol.insertar(25);

    // Recorridos
    std::cout << "Preorder: ";
    arbol.preorder();

    std::cout << "Postorder: ";
    arbol.postorder();

    std::cout << "Recorrido en anchura: ";
    arbol.recorridoAnchura();

    std::cout << "Recorrido en profundidad: ";
    arbol.recorridoProfundidad();

    return 0;
}
