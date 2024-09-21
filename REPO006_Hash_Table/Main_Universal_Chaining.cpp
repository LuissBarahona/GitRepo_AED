#include <iostream>
#include "Universal_Chaining.h"

int main() {
    // Crear una tabla hash con 3 buckets y 3 nodos máximo por lista enlazada
    HashTable<int> hashTable(3, 3);  

    // 1. Verificar si la tabla hash está vacía al inicio
    std::cout << "==============================\n";
    std::cout << "1. Verificación de tabla vacía\n";
    std::cout << "==============================\n";
    std::cout << "¿Tabla vacía?: " << (hashTable.empty() ? "Sí" : "No") << std::endl;
    std::cout << std::endl;

    // 2. Insertar algunos elementos en la tabla hash
    std::cout << "=================================\n";
    std::cout << "2. Insertar elementos en la tabla\n";
    std::cout << "=================================\n";
    hashTable.insert(5);
    hashTable.insert(15);
    hashTable.insert(25);
    std::cout << "Elementos insertados: {5, 15, 25}\n";
    std::cout << std::endl;

    // 3. Mostrar el estado de la tabla hash después de las primeras inserciones
    std::cout << "===============================================\n";
    std::cout << "3. Estado de la tabla hash después de inserciones\n";
    std::cout << "===============================================\n";
    hashTable.showHash();
    std::cout << std::endl;

    // 4. Verificar si la tabla sigue vacía después de las inserciones
    std::cout << "=========================================\n";
    std::cout << "4. Verificación de tabla vacía tras inserciones\n";
    std::cout << "=========================================\n";
    std::cout << "¿Tabla vacía?: " << (hashTable.empty() ? "Sí" : "No") << std::endl;
    std::cout << std::endl;

    // 5. Insertar más elementos en la tabla hash
    std::cout << "======================================\n";
    std::cout << "5. Insertar más elementos en la tabla\n";
    std::cout << "======================================\n";
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
    std::cout << "Elementos insertados: {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}\n";
    std::cout << std::endl;

    // 6. Mostrar el estado de la tabla hash después de las nuevas inserciones
    std::cout << "===========================================\n";
    std::cout << "6. Estado de la tabla tras nuevas inserciones\n";
    std::cout << "===========================================\n";
    hashTable.showHash();
    std::cout << std::endl;

    // 7. Buscar claves en la tabla hash
    std::cout << "===========================\n";
    std::cout << "7. Búsqueda de claves\n";
    std::cout << "===========================\n";
    std::cout << "Buscar clave 25: " << (hashTable.search(25) ? "Encontrada" : "No encontrada") << std::endl;
    std::cout << "Buscar clave 100: " << (hashTable.search(100) ? "Encontrada" : "No encontrada") << std::endl;
    std::cout << std::endl;

    // 8. Eliminar una clave de la tabla hash
    std::cout << "===============================\n";
    std::cout << "8. Eliminación de una clave\n";
    std::cout << "===============================\n";
    hashTable.deleteKey(25);
    std::cout << "Clave 25 eliminada.\n";
    std::cout << std::endl;

    // 9. Mostrar el estado de la tabla después de la eliminación
    std::cout << "=========================================\n";
    std::cout << "9. Estado de la tabla tras la eliminación\n";
    std::cout << "=========================================\n";
    hashTable.showHash();
    std::cout << std::endl;

    // 10. Rehashing de la tabla
    std::cout << "=============================\n";
    std::cout << "10. Rehashing de la tabla hash\n";
    std::cout << "=============================\n";
    hashTable.rehashing(15);  // Ajusta el tamaño del hash
    std::cout << "Tabla rehasheada con nuevo tamaño.\n";
    std::cout << std::endl;

    // 11. Mostrar el estado de la tabla después del rehashing
    std::cout << "==========================================\n";
    std::cout << "11. Estado de la tabla tras el rehashing\n";
    std::cout << "==========================================\n";
    hashTable.showHash();
    std::cout << std::endl;

    return 0;
}
