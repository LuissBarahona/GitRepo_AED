#include <iostream>
#include <cstdlib>
#include <ctime>

const int P = 999991; // Número primo grande
const int EMPTY = -1; // Indicador de casilla vacía
const int DELETED = -2; // Indicador de entrada eliminada

class HashTable {
private:
    int* table; // Array de la tabla hash
    int m; // Tamaño de la tabla hash
    int a, b; // Parámetros de la función de hash
    int currentSize; // Cantidad de elementos en la tabla

    // Función de hash: h(k) = [(a*k + b) % p] % m
    int hashFunction(int key, int i) const {
        return ((a * key + b) % P + i) % m; // Open addressing con lineal probing
    }

public:
    // Constructor para inicializar la tabla con un tamaño m dado
    HashTable(int size) : m(size), currentSize(0) {
        table = new int[m];
        for (int i = 0; i < m; ++i) {
            table[i] = EMPTY; // Inicializa todas las casillas como vacías
        }
        srand(time(0));
        a = rand() % (P - 1) + 1; // a en {1, ..., P-1}
        b = rand() % P; // b en {0, ..., P-1}
    }

    // Destructor para liberar la memoria
    ~HashTable() {
        delete[] table;
    }

    // Método para insertar una clave en la tabla
    bool insert(int key) {
        if (currentSize == m) {
            std::cout << "Tabla llena, rehashing necesario.\n";
            return false;
        }

        for (int i = 0; i < m; ++i) {
            int hashIndex = hashFunction(key, i);
            if (table[hashIndex] == EMPTY || table[hashIndex] == DELETED) {
                table[hashIndex] = key;
                ++currentSize;
                return true;
            }
        }
        return false;
    }

    // Método para buscar una clave en la tabla
    bool search(int key) const {
        for (int i = 0; i < m; ++i) {
            int hashIndex = hashFunction(key, i);
            if (table[hashIndex] == EMPTY) {
                return false; // La clave no está
            }
            if (table[hashIndex] == key) {
                return true; // Clave encontrada
            }
        }
        return false;
    }

    // Método para eliminar una clave de la tabla
    bool remove(int key) {
        for (int i = 0; i < m; ++i) {
            int hashIndex = hashFunction(key, i);
            if (table[hashIndex] == EMPTY) {
                return false; // La clave no está
            }
            if (table[hashIndex] == key) {
                table[hashIndex] = DELETED;
                --currentSize;
                return true;
            }
        }
        return false;
    }

    // Método para rehashear (rehashing) cuando la tabla esté llena
    void rehashing() {
        int oldSize = m;
        int* oldTable = table;

        m *= 2; // Duplicamos el tamaño de la tabla
        table = new int[m];
        for (int i = 0; i < m; ++i) {
            table[i] = EMPTY; // Inicializamos la nueva tabla
        }

        currentSize = 0; // Reiniciamos el contador de elementos

        for (int i = 0; i < oldSize; ++i) {
            if (oldTable[i] != EMPTY && oldTable[i] != DELETED) {
                insert(oldTable[i]); // Reinsertamos las claves no vacías ni eliminadas
            }
        }

        delete[] oldTable; // Liberamos la tabla antigua
    }

    // Método para vaciar la tabla
    void empty() {
        for (int i = 0; i < m; ++i) {
            table[i] = EMPTY;
        }
        currentSize = 0;
    }

    // Método para mostrar la tabla (solo para pruebas)
    void display() const {
        for (int i = 0; i < m; ++i) {
            if (table[i] == EMPTY) {
                std::cout << "[EMPTY] ";
            } else if (table[i] == DELETED) {
                std::cout << "[DELETED] ";
            } else {
                std::cout << table[i] << " ";
            }
        }
        std::cout << std::endl;
    }

    int getCurrentSize(){
        return currentSize;
    }
};

//int main