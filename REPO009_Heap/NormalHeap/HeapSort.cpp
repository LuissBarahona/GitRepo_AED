#include <iostream>
using namespace std;

// Función para reorganizar el heap de manera que mantenga la propiedad de Heap (Max o Min)
void heapify(int arr[], int n, int i, bool ascending) {
    int largestOrSmallest = i; // Inicializar el nodo más grande o más pequeño como raíz
    int left = 2 * i + 1;      // Hijo izquierdo
    int right = 2 * i + 2;     // Hijo derecho

    if (ascending) {
        // Si el hijo izquierdo es más pequeño que la raíz
        if (left < n && arr[left] < arr[largestOrSmallest])
            largestOrSmallest = left;

        // Si el hijo derecho es más pequeño que el nodo más pequeño hasta ahora
        if (right < n && arr[right] < arr[largestOrSmallest])
            largestOrSmallest = right;
    } else {
        // Si el hijo izquierdo es más grande que la raíz
        if (left < n && arr[left] > arr[largestOrSmallest])
            largestOrSmallest = left;

        // Si el hijo derecho es más grande que el nodo más grande hasta ahora
        if (right < n && arr[right] > arr[largestOrSmallest])
            largestOrSmallest = right;
    }

    // Si el nodo más grande o más pequeño no es la raíz
    if (largestOrSmallest != i) {
        swap(arr[i], arr[largestOrSmallest]); // Intercambiar la raíz con el nodo más grande o más pequeño
        heapify(arr, n, largestOrSmallest, ascending); // Aplicar heapify en el subárbol afectado
    }
}

// Función principal para realizar HeapSort
void heapSort(int arr[], int n, bool ascending) {
    // Construir el Heap (Max Heap o Min Heap)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, ascending);

    // Extraer elementos del heap uno por uno
    for (int i = n - 1; i > 0; i--) {
        // Mover la raíz actual al final
        swap(arr[0], arr[i]);

        // Aplicar heapify en el heap reducido
        heapify(arr, i, 0, ascending);
    }
}

// Función para imprimir un array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << "\n";
}

// Programa principal para probar la función HeapSort
int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Array original:\n";
    printArray(arr, n);

    // Ordenar de menor a mayor
    heapSort(arr, n, true);
    cout << "Array ordenado de mayor a menor:\n";

    printArray(arr, n);

    // Ordenar de mayor a menor
    heapSort(arr, n, false);
    cout << "Array ordenado de menor a mayor:\n";
    printArray(arr, n);
    
    return 0;
}
