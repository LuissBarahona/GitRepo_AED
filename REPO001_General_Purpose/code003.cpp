/* DESCRIPTION
   Topic: Bucles
   Goal: Learn about bucles in C++
   Author: Luis Barahoana
   Date: Aug 27, 2024
   Status: Done
*/

/* 
    1. FUNCTION DECLARATION (Prototype)
        return_type function_name(parameter_type1 parameter_name1, parameter_type2 parameter_name2, ...);

        int add(int a, int b);
        void printMessage();

    2. FUNCTION DEFINITION
        return_type function_name(parameter_type1 parameter_name1, parameter_type2 parameter_name2, ...) {
            // Code to be executed
            return value; // Optional: only if return_type is not void
        }

        int add(int a, int b) {
            return a + b;
        }

        void printMessage() {
            std::cout << "Hello, World!" << std::endl;
        }

    3. FUNCTION CALL
        function_name(argument1, argument2, ...);

        int result = add(5, 3);  // Calls the add function, result is 8
        printMessage();          // Calls the printMessage function, outputs "Hello, World!"

    4. Function Parameters and Arguments
        Parameters: Variables defined in the function declaration and used within the function.
        Arguments: Values passed to the function when you call it

    5. DEFAULT PARAMETERS
        You can provide default values for parameters. If an argument is not passed for a parameter, the default value is used.
        
        int multiply(int a, int b = 2) { // b has a default value of 2
            return a * b;
        }

    6. FUNCTION OVERLOADING
        C++ allows you to define multiple functions with the same name but different parameter lists. This is called function overloading.
        
        int add(int a, int b) {
            return a + b;
        }

        double add(double a, double b) {
            return a + b;
        }
    
    7. INLINE FUNCTIONS
        Suggest to the compiler to reduce the overhead of small functions.
        
        inline int square(int x) {
            return x * x;
        }

*/


#include <iostream>

// Function declaration (prototype)
int add(int a, int b);
void printMessage();

int main() {
    // Function call
    int result = add(10, 20);
    std::cout << "Result: " << result << std::endl;

    printMessage();
    
    return 0;
}

// Function definition
int add(int a, int b) {
    return a + b;
}

void printMessage() {
    std::cout << "This is a message from a function." << std::endl;
}
