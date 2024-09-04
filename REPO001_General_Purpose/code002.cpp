/* DESCRIPTION
   Topic: Bucles
   Goal: Learn about bucles in C++
   Author: Luis Barahoana
   Date: Aug 27, 2024
   Status: Done
*/



/*
    1. WHILE LOOP
        The while loop repeatedly executes a block of code while the condition is true.
        
        int i = 0;
        while (i < 5) {
            std::cout << i << std::endl;
            i++;
        }
        
    2. DO WHILE LOOP
        The do-while loop is similar to the while loop, but it checks the condition after executing the loop body. This ensures that the loop body is executed at least once.
        int i = 0;
        do {
            std::cout << i << std::endl;
            i++;
        } while (i < 5);

    3. FOR LOOP 
        The for loop is often used when the number of iterations is known beforehand. It includes initialization, condition, and increment/decrement in a single line.
        for (initialization; condition; increment/decrement) {
            // Code to be executed
        }
        for (int i = 0; i < 5; i++) {
            std::cout << i << std::endl;
        }

    4. RANGE-BASED FOR (For C++11 and later)
        This loop is used to iterate over elements in a container (like an array or vector) directly.
        for (type variable : container) {
            // Code to be executed
        }
        int arr[] = {1, 2, 3, 4, 5};
        for (int i : arr) {
            std::cout << i << std::endl;
        }

    5. BREAK STATEMENT
        The break statement is used to exit a loop prematurely, regardless of the loop's condition.
        for (int i = 0; i < 5; i++) {
            if (i == 3) {
                break; // Exits the loop when i is 3
            }
            std::cout << i << std::endl;
        }
        This loop will print 0, 1, 2, then exit before printing 3.
    
    6. CONTINUE STATEMENT
        The continue statement skips the remaining code in the current iteration and moves to the next iteration of the loop.
        for (int i = 0; i < 5; i++) {
            if (i == 3) {
                continue; // Skips the rest of the loop when i is 3
            }
            std::cout << i << std::endl;
        }
        This loop will print 0, 1, 2, 4, skipping the number 3.

    7. GOTO STATEMENT
        Although not recommended due to its potential to create confusing code, the goto statement can be used to jump to a labeled section of code.
        label:
            // Code to be executed

        goto label;

        int i = 0;
        start:
            std::cout << i << std::endl;
            i++;
            if (i < 5) {
                goto start; // Jumps back to the label "start"
            }




*/
#include <iostream>


int main() {
    
    int i=0;
    std::cout<<i<<std::endl;
    std::cout<<--i<<"---"<<&i<<std::endl; //Primero decrementa i y luego devuelve su valor actual: i=-1
    std::cout<<i--<<"---"<<&i<<std::endl; //Primero devuelve su valor actual (i=-1) y luego decrementa i: i=-2
    std::cout<<i<<"---"<<&i<<std::endl; //i=-2

    //SUMARY: --i e i-- -> i=i-1;
    //SUMARY: Lo mismo pasa con i++ e ++i 

    for (int i=5; i>0;--i){ 
        //La primera iteración usa a i=5 dentro del for y decrementa i
        std::cout<<"FOR con --i"<<std::endl;
        std::cout<<i<<"---"<<&i<<std::endl; 
    }

    for (int i=5; i>0;i--){ 
        //La primera iteración usa a i=5 dentro del for y decrementa i
        std::cout<<"FOR con i--"<<std::endl;
        std::cout<<i<<"---"<<&i<<std::endl; 
    }

    //SUMARY: Aambos hicieron lo mismo
    return 0;
}
