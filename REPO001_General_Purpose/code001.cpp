/* DESCRIPTION
    Topic: Arrays 
    Goal: Learn to use arrays
    Author: Luis Barahona
    Date: Aug 27, 2024
    Status:Done
*/

/*ARRAYS
    - Contiguos memory 
    - Allows you to store multiple values of the same type in a contiguous block of memory.
    - Format: type arrayName[size]; int numbers[5];
    - Accessing Elements: arrayName[index]; //idex = size-1 for the last element
        numbers[0] = 10;  // Assigns 10 to the first element
        int value = numbers[0];  // Retrieves the first element (value is 10)
    - Initializing Arrays: int numbers[5] = {1,2,3,4}; //the remaining elements are automatically initialized to 0:
    - Multidimensional Arrays: type arrayName[rows][columns];
        int matrix[3][3] = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        };
    - Array Size: 
        int numbers[5] = {1, 2, 3, 4, 5};
        int size = sizeof(numbers) / sizeof(numbers[0]); // size is 5
    - Arrays as Function Arguments
        You can pass arrays to functions. When you do so, the array’s base address is passed, not the entire array, so changes to the array inside the function will affect the original array.
        void printArray(int arr[], int size) {
            for(int i = 0; i < size; i++) {
                std::cout << arr[i] << " ";
            }
        }
    - Limitations
        Fixed Size: The size of an array is fixed at compile-time and cannot be changed dynamically (unless using dynamic memory allocation with pointers).
        No Boundary Checking: C++ does not perform boundary checking on arrays. Accessing an element outside the bounds of an array can lead to undefined behavior.
    - Dynamics Arrays:
        For dynamic arrays, you can use pointers and the new keyword to allocate memory at runtime:
        int* dynamicArray = new int[size]; // Allocates a dynamic array
        .
        .
        .
        delete[] dynamicArray; //Remember to free the allocated memory using delete[]:
    - Standard Library Alternatives:
        The C++ Standard Library offers more flexible alternatives to arrays, such as std::vector, which allows dynamic resizing, boundary checking, and other features.
        #include <vector>
        std::vector<int> numbers = {1, 2, 3, 4, 5};

    - Summary: Arrays in C++ are a powerful but low-level tool for managing collections of data. While they are efficient, they require careful handling due to their fixed size and lack of boundary checking. For more advanced and flexible data management, C++ offers alternatives like std::vector.
*/


/* MODIFY ARRAYS
    - Contiguos memory



*/
#include <iostream>

void fillArray(int array[]);
void printArray(int array[]);

int main() { 
    // Crear array
    int array[5];
    // Llenar array
    fillArray(array);
    // Imprimir array
    printArray(array);

    // Print the last element
    int array2[5] ={1,2,3,4}; //The 5th element is 0.
    int size = sizeof(array2)/sizeof(array2[0]);

    std::cout<<array2[size-1]<<std::endl; //RTA: 0

    // Push Front (It isn't posible because of the fixed size at compile-time)
    // Push Back (It isn't posible because of the fixed size at compile-time)
    // Pop Front (It isn't posible because of the fixed size to compile-time)
    // Pop Back (It isn't posible because of the fixed size to compile-time)
    // Insert n to location m (It isn't posible because of the fixed size to compile-time)
    // Clear (the size of a fixed array is immutable)


    return 0; // Agregar una declaración de retorno en main
}

void fillArray(int array[]) {
    for (int i = 0; i < 5; i++) { // Cambiar el incremento de 'i++' a 'i'
        array[i] = i; // Asignar 'i' al array en lugar de 'i++'
    }
}

void printArray(int array[]) {
    for (int i = 0; i < 5; i++) { // Cambiar 'i <= 4' a 'i < 5' para mayor claridad
        std::cout << array[i] << std::endl;
    }
}
