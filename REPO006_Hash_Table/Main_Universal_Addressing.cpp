#include <iostream>
#include "Universal_Addressing.h"

int main() {
    HashTable ht(7); // Crear una tabla hash con tamaño 7

    // Insertamos algunas claves
    std::cout<<"size: "<< ht.getCurrentSize()<<std::endl;
    ht.insert(10);
    ht.insert(20);
    ht.insert(30);
    ht.insert(5);
    std::cout<<"size: "<< ht.getCurrentSize()<<std::endl;

    std::cout << "Tabla hash después de inserciones: \n";
    ht.display();

    // Buscamos algunas claves
    std::cout << "Buscar 10: " << (ht.search(10) ? "Encontrado" : "No encontrado") << std::endl;
    std::cout << "Buscar 25: " << (ht.search(25) ? "Encontrado" : "No encontrado") << std::endl;

    // Eliminamos una clave
    ht.remove(20);
    std::cout << "Tabla hash después de eliminar 20: \n";
    ht.display();

    // Rehashing
    ht.rehashing();
    std::cout << "Tabla hash después de rehashing: \n";
    ht.display();
    std::cout<<"size: "<< ht.getCurrentSize()<<std::endl;
    return 0;
}
