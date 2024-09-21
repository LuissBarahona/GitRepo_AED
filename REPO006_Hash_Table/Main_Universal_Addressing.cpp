#include <iostream>
#include "Universal_Addressing.h"

int main() {
    // 1. Crear una tabla hash con tamaño 7
    std::cout << "=================================\n";
    std::cout << "1. Creación de la tabla hash\n";
    std::cout << "=================================\n";
    HashTable ht(7);  
    std::cout << "Tabla hash creada con tamaño 7.\n";
    std::cout << "Tamaño actual: " << ht.getCurrentSize() << "\n\n";

    // 2. Insertar algunas claves en la tabla hash
    std::cout << "=================================\n";
    std::cout << "2. Inserción de claves\n";
    std::cout << "=================================\n";
    ht.insert(10);
    ht.insert(20);
    ht.insert(30);
    ht.insert(5);
    std::cout << "Claves insertadas: {10, 20, 30, 5}\n";
    std::cout << "Tamaño actual: " << ht.getCurrentSize() << "\n\n";

    // 3. Mostrar el estado de la tabla hash después de las inserciones
    std::cout << "===============================================\n";
    std::cout << "3. Estado de la tabla hash después de inserciones\n";
    std::cout << "===============================================\n";
    std::cout << "Tabla hash:\n";
    ht.display();
    std::cout << std::endl;

    // 4. Búsqueda de claves en la tabla hash
    std::cout << "=================================\n";
    std::cout << "4. Búsqueda de claves\n";
    std::cout << "=================================\n";
    std::cout << "Buscar 10: " << (ht.search(10) ? "Encontrado" : "No encontrado") << std::endl;
    std::cout << "Buscar 25: " << (ht.search(25) ? "Encontrado" : "No encontrado") << std::endl;
    std::cout << std::endl;

    // 5. Eliminar una clave de la tabla hash
    std::cout << "=================================\n";
    std::cout << "5. Eliminación de una clave\n";
    std::cout << "=================================\n";
    ht.remove(20);
    std::cout << "Clave 20 eliminada.\n\n";

    // 6. Mostrar el estado de la tabla hash después de la eliminación
    std::cout << "===============================================\n";
    std::cout << "6. Estado de la tabla hash después de eliminar 20\n";
    std::cout << "===============================================\n";
    ht.display();
    std::cout << std::endl;

    // 7. Rehashing de la tabla hash
    std::cout << "=================================\n";
    std::cout << "7. Rehashing de la tabla hash\n";
    std::cout << "=================================\n";
    ht.rehashing();
    std::cout << "Rehashing completado.\n\n";

    // 8. Mostrar el estado de la tabla hash después del rehashing
    std::cout << "===============================================\n";
    std::cout << "8. Estado de la tabla hash después del rehashing\n";
    std::cout << "===============================================\n";
    ht.display();
    std::cout << "Tamaño actual: " << ht.getCurrentSize() << std::endl;

    return 0;
}
