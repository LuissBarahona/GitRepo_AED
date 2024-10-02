#include <stack>
#include <queue>

void TreeAVL::recorridoZigZag() {
    if (!root) return;

    std::queue<NodeAVL*> nodosQueue;
    nodosQueue.push(root);
    bool izquierdaADerecha = true;

    while (!nodosQueue.empty()) {
        int tamanioNivel = nodosQueue.size();
        std::deque<int> nivelValores;

        for (int i = 0; i < tamanioNivel; i++) {
            NodeAVL* actual = nodosQueue.front();
            nodosQueue.pop();

            if (izquierdaADerecha) {
                nivelValores.push_back(actual->data);
            } else {
                nivelValores.push_front(actual->data);
            }

            if (actual->hijoIzquierdo) nodosQueue.push(actual->hijoIzquierdo);
            if (actual->hijoDerecho) nodosQueue.push(actual->hijoDerecho);
        }

        for (int val : nivelValores) {
            std::cout << val << " ";
        }
        std::cout << std::endl;

        izquierdaADerecha = !izquierdaADerecha; // Alternar el orden
    }
}
