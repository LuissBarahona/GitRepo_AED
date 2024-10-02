#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

const int P = 999991; // Número primo grande
const int VACIO = -1; // Indicador de casilla vacía
const int ELIMINADO = -2; // Indicador de entrada eliminada

class TablaHash {
private:
    int* tabla; // Array de la tabla hash
    int m; // Tamaño de la tabla hash
    float constante; // Parámetro de la función de hash
    int tamañoActual; // Cantidad de elementos en la tabla

    // Función de hash: h(clave) = [(constante * clave) % (2^w)] >> (w - r)
    int funcionHash(int clave, int i) const {
        int w = sizeof(int) * 8; // Número de bits en un entero
        int r = std::log2(m); // r es el logaritmo en base 2 de m
        return static_cast<int>((constante * clave - std::floor(constante * clave)) * (1 << w)) >> (w - r);
    }

public:
    // Constructor para inicializar la tabla con un tamaño m dado
    TablaHash(int tamaño) : m(tamaño), tamañoActual(0) {
        tabla = new int[m];
        for (int i = 0; i < m; ++i) {
            tabla[i] = VACIO; // Inicializa todas las casillas como vacías
        }
        srand(time(0));
        constante = static_cast<float>(rand()) / (RAND_MAX + 1); // a en [0, 1)
    }

    // Destructor para liberar la memoria
    ~TablaHash() {
        delete[] tabla;
    }

    // Método para insertar una clave en la tabla
    bool insertar(int clave) {
        if (tamañoActual == m) {
            std::cout << "Tabla llena, rehashing necesario.\n";
            return false;
        }

        for (int i = 0; i < m; ++i) {
            int indiceHash = funcionHash(clave, i);
            if (tabla[indiceHash] == VACIO || tabla[indiceHash] == ELIMINADO) {
                tabla[indiceHash] = clave;
                ++tamañoActual;
                return true;
            }
        }
        return false;
    }

    // Método para buscar una clave en la tabla
    bool buscar(int clave) const {
        for (int i = 0; i < m; ++i) {
            int indiceHash = funcionHash(clave, i);
            if (tabla[indiceHash] == VACIO) {
                return false; // La clave no está
            }
            if (tabla[indiceHash] == clave) {
                return true; // Clave encontrada
            }
        }
        return false;
    }

    // Método para eliminar una clave de la tabla
    bool eliminar(int clave) {
        for (int i = 0; i < m; ++i) {
            int indiceHash = funcionHash(clave, i);
            if (tabla[indiceHash] == VACIO) {
                return false; // La clave no está
            }
            if (tabla[indiceHash] == clave) {
                tabla[indiceHash] = ELIMINADO;
                --tamañoActual;
                return true;
            }
        }
        return false;
    }

    // Método para rehashear (rehashing) cuando la tabla esté llena
    void rehashing() {
        int antiguoTamaño = m;
        int* tablaAntigua = tabla;

        m *= 2; // Duplicamos el tamaño de la tabla
        tabla = new int[m];
        for (int i = 0; i < m; ++i) {
            tabla[i] = VACIO; // Inicializamos la nueva tabla
        }

        tamañoActual = 0; // Reiniciamos el contador de elementos

        for (int i = 0; i < antiguoTamaño; ++i) {
            if (tablaAntigua[i] != VACIO && tablaAntigua[i] != ELIMINADO) {
                insertar(tablaAntigua[i]); // Reinsertamos las claves no vacías ni eliminadas
            }
        }

        delete[] tablaAntigua; // Liberamos la tabla antigua
    }

    // Método para vaciar la tabla
    void vaciar() {
        for (int i = 0; i < m; ++i) {
            tabla[i] = VACIO;
        }
        tamañoActual = 0;
    }

    // Método para mostrar la tabla (solo para pruebas)
    void mostrar() const {
        for (int i = 0; i < m; ++i) {
            if (tabla[i] == VACIO) {
                std::cout << "[VACIO] ";
            } else if (tabla[i] == ELIMINADO) {
                std::cout << "[ELIMINADO] ";
            } else {
                std::cout << tabla[i] << " ";
            }
        }
        std::cout << std::endl;
    }

    int obtenerTamañoActual() {
        return tamañoActual;
    }
};