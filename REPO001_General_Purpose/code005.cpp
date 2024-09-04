/* DESCRIPTION
    Topic: Pointers
    Goal: Learn to use Pointers
    Author: Luis Barahoana
    Date: Aug 27, 2024
    Status:
*/

/*
    - Pointers in C++ are variables that store the memory address of another variable.
    - They allow direct manipulation of memory 
    1. BASIC SYNTAX
        #A pointer is declared using the * operator:
            int* ptr; // Declares a pointer to an integer
        #The & operator is used to get the address of a variable:
            int a = 10;
            int* ptr = &a; // ptr now holds the address of a

        #The * operator is also used to dereference a pointer, i.e., to access the value at the memory address stored by the pointer:
            int value = *ptr; // value is now 10

    2. POINTER ARITHMETIC
        Pointers can be incremented, decremented, and used in arithmetic operations:
        int arr[] = {1, 2, 3};
        int* ptr = arr;   // Points to the first element of arr
        ptr++;            // Now points to the second element of arr
        int second = *ptr; // second is 2

    3. ITERATE AN ARRAY WITH A POINTER
        int arr[] = {1, 2, 3};
        int* ptr = arr;
        for (int i = 0; i < 3; ++i) {
            cout << *(ptr + i) << " "; // Output: 1 2 3
        }

    4. POINTERS TO POINTERS
        Pointers can also point to other pointers
        int a = 10;
        int* ptr = &a;
        int** ptr2 = &ptr; // ptr2 is a pointer to pointer to an int

    5. DYNAMIC MEMORY ALLOCATION
        Pointers are used with new and delete to dynamically allocate and deallocate memory:
        int* ptr = new int(5); // Dynamically allocates memory for an int and initializes it to 5
        delete ptr;            // Deallocates the memory

        int* arr = new int[10]; // Allocates memory for an array of 10 ints
        delete[] arr;           // Deallocates the memory for the array

    6. FUNCTION POINTERS (Puntero que apunta a una función)


*/

#include <iostream>

int main(){

    //CASO 1: Desplazamiento usando punteros
    std::cout<<"CASO 1: Desplazamiento usando punteros"<<std::endl;

    int array[4]={1,2,3,4};
    int *ptr_a=&array[0]; 
    std::cout<<"ptr_a (direc): "<<ptr_a<<" *ptr_a: "<<*ptr_a<<std::endl; //Direccion original, arrya[0]
    std::cout<<"ptr_a (direc): "<<ptr_a<<" *(ptr_a+1): "<<*(ptr_a+1)<<std::endl; //Dirección original, array[1]
    std::cout<<"ptr_a (direc): "<<ptr_a<<" *ptr_a++: "<<*ptr_a++<<" ptr_a (nueva direc): "<<ptr_a<<std::endl; //Devuelve array[0] de direc original e incrementa la sirección
    std::cout<<"ptr_a (direc): "<<ptr_a<<" *++ptr_a: "<<*++ptr_a<<" ptr_a (nueva direc): "<<ptr_a<<std::endl; //Incrementa dirección y Devuelce array[2] (ubicada en la neuva dirección)


    //SUMARY : *ptr_a++ = *(ptr_a++)  (OJITO: SON CAPACES DE ACTUALIZAR EL VALOR DE LAS VARIABLES A LAS QUE APUNTAN)
        //*(ptr_a++) -> ptr_a++ devuelve la dirección de "a" y la incrementa. No devuelce la dirección incrementada.
        //Si volvemos a usar a ptr_a, su dirección será otra, pues a sido desplada o incrementada.


    //CASO 2: Punteros a punteros
    std::cout<<" \n CASO 2: Punteros a punteros"<<std::endl;

    int a = 10;
    int* ptr = &a;
    int** ptr2 = &ptr; // ptr2 is a pointer to pointer to an int
    int*** ptr3 = &ptr2;

    std::cout<<"valor de a: "<<a<< " "<<*ptr<<", direc de a: "<<&a<<" "<<ptr<<std::endl;
    std::cout<<"valor de ptr: "<<ptr<<" "<<*ptr2<<", direc de ptr: "<<&ptr<<" "<<ptr2<<std::endl; 
    std::cout<<"valor de ptr2: "<<ptr2<<" "<<*ptr3<<", direc de ptr2: "<<&ptr2<<" "<<ptr3<<std::endl; 

    //ptr3 -> devuelve la direc de ptr2
    //*ptr3 -> devuelce el contenido de ptr2: la direc de ptr
    //**ptr3 -> devuelve la direc de a
    //***ptr3 -> devuelve el valor de a
    return 0; //
}