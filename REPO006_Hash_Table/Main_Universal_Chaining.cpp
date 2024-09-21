
#include <iostream>
#include "Universal_Chaining.h"

int main() {
    HashTable<int> hashTable(3, 3); // Tabla hash con 10 buckets y 3 nodos máximo por lista

    //Verificar si la tabla hash está vacía
    cout<<"vacia?: "<<hashTable.empty()<<endl;
    // Insertar algunos elementos
    hashTable.insert(5);
    hashTable.insert(15);
    hashTable.insert(25);
   

    // Mostrar la tabla hash
    hashTable.showHash();
    cout<<"vacia?: "<<hashTable.empty()<<endl;

    hashTable.insert(1);
    hashTable.insert(2);
    hashTable.insert(3);
    hashTable.insert(4);
    hashTable.insert(5);
    hashTable.insert(6);
    hashTable.insert(7);
    hashTable.insert(8);
    hashTable.insert(9);
    hashTable.insert(10);
    hashTable.showHash();

    // Buscar claves
    cout << "Buscar clave 25: " << (hashTable.search(25) ? "Encontrada" : "No encontrada") << endl;
    cout << "Buscar clave 100: " << (hashTable.search(100) ? "Encontrada" : "No encontrada") << endl;

    // Eliminar una clave
    hashTable.deleteKey(25);
    hashTable.showHash();

    // Hacer rehashing
    hashTable.rehashing(15);
    hashTable.showHash();

    return 0;
}
