/*

    Status: El compilador no identifica como int a "variable" cuando llega al return intVAlue()
*/

#include <iostream>
#include <string>
#include <type_traits> // Para if constexpr y std::is_integral_v

// Función para obtener el valor ASCII de un carácter
int asciiValue(char c) {
    return static_cast<int>(c);
}

// Sobrecarga para std::string que suma los valores ASCII de cada carácter
int asciiValue(const std::string& str) {
    int sum = 0;
    for (char c : str) {
        sum += static_cast<int>(c);
    }
    return sum;
}

// Función para manejar el tipo int
int intValue(int a) {
    return a;
}

// Función template para obtener el valor ASCII o el valor int
template<typename T>
int getAscii(T variable) {
    if constexpr (std::is_integral_v<T>) { // Si el tipo es un entero (int, char, etc.)
        // Agregamos un cast explícito a int para asegurarnos
        return intValue(static_cast<int>(variable));
    } else { // Si el tipo es std::string o algo más
        return asciiValue(variable);
    }
}

int main() {
    int a = 1;
    char c = 'A';
    std::string s = "Hola";

    // Llamadas utilizando la función template
    std::cout << "El valor del int a (usando template): " << getAscii(a) << std::endl;
    std::cout << "El valor ASCII de '" << c << "' (usando template): " << getAscii(c) << std::endl;
    std::cout << "La suma de los valores ASCII de \"" << s << "\" (usando template): " << getAscii(s) << std::endl;

    return 0;
}
