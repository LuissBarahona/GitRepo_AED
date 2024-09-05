#include <unordered_map>
#include <unordered_set>
#include <string>
#include <iostream>

// Nodo para la lista doblemente enlazada
class ChainNode {
public:
    std::unordered_set<std::string> elementos;  // Conjunto de elementos almacenados en el nodo
    ChainNode* nodoPrevio;                      // Puntero al nodo anterior en la lista
    ChainNode* nodoSiguiente;                   // Puntero al siguiente nodo en la lista

    // Constructor inicializando punteros a nullptr
    ChainNode() : nodoPrevio(nullptr), nodoSiguiente(nullptr) {}

    // Agrega un elemento al conjunto del nodo
    void agregarElemento(const std::string& elemento) {
        elementos.insert(elemento);
    }

    // Elimina un elemento del conjunto del nodo
    void removerElemento(const std::string& elemento) {
        elementos.erase(elemento);
    }

    // Devuelve cualquier elemento del conjunto, o una cadena vacía si no hay elementos
    std::string obtenerCualquierElemento() const {
        return elementos.empty() ? "" : *elementos.begin();
    }

    // Retorna si el conjunto de elementos está vacío
    bool sinElementos() const {
        return elementos.empty();
    }
};

// Lista doblemente enlazada para gestionar los contadores
class DualChain {
public:
    ChainNode* head;  // Nodo cabeza, marcador al inicio de la lista
    ChainNode* tail;  // Nodo cola, marcador al final de la lista

    // Constructor que inicializa la lista con nodos de cabeza y cola conectados
    DualChain() {
        head = new ChainNode();
        tail = new ChainNode();
        head->nodoSiguiente = tail;
        tail->nodoPrevio = head;
    }

    // Agrega un nuevo nodo después del nodo dado
    ChainNode* agregarDespues(ChainNode* nodo) {
        ChainNode* nuevoNodo = new ChainNode();
        nuevoNodo->nodoSiguiente = nodo->nodoSiguiente;
        nuevoNodo->nodoPrevio = nodo;
        nodo->nodoSiguiente->nodoPrevio = nuevoNodo;
        nodo->nodoSiguiente = nuevoNodo;
        return nuevoNodo;
    }

    // Agrega un nuevo nodo antes del nodo dado
    ChainNode* agregarAntes(ChainNode* nodo) {
        return agregarDespues(nodo->nodoPrevio);
    }

    // Elimina un nodo de la lista
    void separarNodo(ChainNode* nodo) {
        nodo->nodoPrevio->nodoSiguiente = nodo->nodoSiguiente;
        nodo->nodoSiguiente->nodoPrevio = nodo->nodoPrevio;
        delete nodo;
    }

    // Retorna el primer nodo (después del nodo cabeza)
    ChainNode* obtenerPrimerNodo() const {
        return head->nodoSiguiente;
    }

    // Retorna el último nodo (antes del nodo cola)
    ChainNode* obtenerUltimoNodo() const {
        return tail->nodoPrevio;
    }

    // Retorna el nodo cabeza
    ChainNode* obtenerHead() const {
        return head;
    }

    // Retorna el nodo cola
    ChainNode* obtenerTail() const {
        return tail;
    }
};

// Clase principal AllOne
class AllOne {
private:
    DualChain listaCadenas;  // Lista doblemente enlazada para gestionar los nodos
    std::unordered_map<std::string, int> contadorElementos;  // Mapa que asocia elementos con sus contadores
    std::unordered_map<int, ChainNode*> mapaContador;  // Mapa que asocia contadores con nodos

    // Elimina un elemento de un nodo según su contador y limpia el nodo si queda vacío
    void limpiarElementoDelNodo(int contador, const std::string& elemento) {
        ChainNode* nodo = mapaContador[contador];
        nodo->removerElemento(elemento);
        if (nodo->sinElementos()) {
            listaCadenas.separarNodo(nodo);
            mapaContador.erase(contador);
        }
    }

public:
    // Constructor inicializando el mapa de contadores con un nodo vacío para el contador 0
    AllOne() {
        mapaContador[0] = listaCadenas.obtenerHead();
    }

    // Incrementa el contador del elemento dado
    void inc(const std::string& clave) {
        int contadorActual = contadorElementos[clave]++;  // Incrementa el contador del elemento
        int nuevoContador = contadorActual + 1;           // Calcula el nuevo valor del contador

        // Si no existe un nodo para el nuevo contador, crea uno
        if (!mapaContador.count(nuevoContador)) {
            mapaContador[nuevoContador] = listaCadenas.agregarDespues(mapaContador[contadorActual]);
        }
        // Agrega el elemento al nodo correspondiente al nuevo contador
        mapaContador[nuevoContador]->agregarElemento(clave);

        // Limpia el elemento del nodo correspondiente al contador anterior
        if (contadorActual > 0) {
            limpiarElementoDelNodo(contadorActual, clave);
        }
    }

    // Decrementa el contador del elemento dado
    void dec(const std::string& clave) {
        int contadorActual = contadorElementos[clave]--;  // Decrementa el contador del elemento
        int nuevoContador = contadorActual - 1;           // Calcula el nuevo valor del contador

        // Si el contador del elemento llega a 0, se elimina del mapa
        if (contadorElementos[clave] == 0) {
            contadorElementos.erase(clave);
        }

        // Si el nuevo contador es mayor que 0, actualiza el nodo correspondiente
        if (nuevoContador > 0) {
            if (!mapaContador.count(nuevoContador)) {
                mapaContador[nuevoContador] = listaCadenas.agregarAntes(mapaContador[contadorActual]);
            }
            mapaContador[nuevoContador]->agregarElemento(clave);
        }

        // Limpia el elemento del nodo correspondiente al contador anterior
        limpiarElementoDelNodo(contadorActual, clave);
    }

    // Retorna una clave con el valor máximo (arbitraria si hay varias)
    std::string getMaxKey() {
        return listaCadenas.obtenerUltimoNodo()->obtenerCualquierElemento();
    }

    // Retorna una clave con el valor mínimo (arbitraria si hay varias)
    std::string getMinKey() {
        return listaCadenas.obtenerPrimerNodo()->obtenerCualquierElemento();
    }
};
