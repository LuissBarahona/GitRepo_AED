#include <iostream>
#include <string>

// Función template para obtener el valor ASCII de un carácter
template <typename T>
int asciiValue(const T& c) {
    return static_cast<int>(c);
}

// Especialización para std::string que suma los valores ASCII de cada carácter
template <>
int asciiValue(const std::string& str) {
    int sum = 0;
    for (char c : str) {
        sum += static_cast<int>(c);
    }
    return sum;
}

// Función para manejar el tipo int (si es necesario por algún motivo)
int intValue(int a) {
    return a;
}

int main() {
    int a = 1;
    char c = 'A';
    std::string s = "Hola";

    std::cout << "El valor del int a: " << intValue(a) << std::endl;
    std::cout << "El valor ASCII de '" << c << "' es: " << asciiValue(c) << std::endl;
    std::cout << "La suma de los valores ASCII de \"" << s << "\" es: " << asciiValue(s) << std::endl;

    return 0;
}
