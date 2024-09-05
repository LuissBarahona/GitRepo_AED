#include <unordered_map>
using namespace std;

class LRUCache {
public:
    //estructura del nodo
    struct Nodo {
    public:
        int clave;
        int valor;
        Nodo* next;
        Nodo* prev;
        Nodo(int key, int val):clave(key), valor(val), next(nullptr), prev(nullptr){}
    };

    Nodo* head = new Nodo(0, 0);
    Nodo* tail = new Nodo(0, 0);

    int capacity;

    //creacion de mapa para guardar elementos de tipo clave:valor
    unordered_map<int, Nodo*> mapear;  

    //Constructor inicializador
    LRUCache(int capacity) {
        this->capacity = capacity;
        head->next = tail;
        tail->prev = head;
    }

    //funcion para agregar nodo, push_fronteo
    void agregar_nodo(Nodo* nodo1) {
        Nodo* temp = head->next;
        nodo1->next = temp;
        nodo1->prev = head;
        head->next = nodo1;
        temp->prev = nodo1;
    }

    //funcion para eliminar nodo de la lista doble enlazada
    void eliminar_nodo(Nodo* nodo2) {
        Nodo* prev = nodo2->prev;
        Nodo* next = nodo2->next;
        prev->next = next;
        next->prev = prev;
    }

    // devuelve el valor asocidado a una clave dentro del mapa
    int get(int key) {
        if (mapear.find(key) != mapear.end()) {
            Nodo* nodo3 = mapear[key];
            int num = nodo3->valor;
            mapear.erase(key);
            eliminar_nodo(nodo3);  
            agregar_nodo(nodo3);   
            mapear[key] = head->next; 
            return num;
        }
        return -1; //por defecto, si no existe el par, devuelve -1
    }


    //put permite actualzar la clave
    void put(int key, int value) {
        if (mapear.find(key) != mapear.end()) {
            Nodo* nodo4 = mapear[key];
            mapear.erase(key); // se eliminar la clave 
            eliminar_nodo(nodo4);
        }
        //para liberar memoria caché, se borra el nodo anterior a tail
        if (mapear.size() == capacity) {
            mapear.erase(tail->prev->valor);
            eliminar_nodo(tail->prev);
        }

        //Se agrega nodo al inicio
        agregar_nodo(new Nodo(key, value));
        mapear[key] = head->next;
    }
};