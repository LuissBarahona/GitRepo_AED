/*DETALLES
    Topic: Stack Implementation Using an Array - Fixed Size Array
    Author: LeetCode
    Date: Sep 11, 2024
    Status: Complete - Funciona

    Basic Operations:
        push() to insert an element into the stack
        pop() to remove an element from the stack
        top() Returns the top element of the stack.
        isEmpty() returns true if stack is empty else false.
        isFull() returns true if the stack is full else false. 
        peek() return the top without remove it
*/



#include <bits/stdc++.h>
#include<iostream>

using namespace std;

#define MAX 1000 //Tamaño máximo del stack

class Stack {
    private:
        int top; //Position of the last element (se considera la posición cero hasta MAX-1)
        int size; //tamaño actual ocupado del stack

    public:
        int a[MAX]; // Array with Maximum size of Stack

        Stack() { top = -1; } //Constructor
        bool push(int x);
        int pop();
        int peek();
        bool isEmpty();
        bool isFull();
        void display(Stack s); //display all elemnts of stack
        int get_size();
};

bool Stack::push(int x)
{
    /*ALGORITHM
        Before pushing the element to the stack, we check if the stack is full .
        If the stack is full (top == capacity-1) , then Stack Overflows and we cannot insert the element to the stack.
        Otherwise, we increment the value of top by 1 (top = top + 1) and the new value is inserted at top position .
        The elements can be pushed into the stack till we reach the capacity of the stack. 
    
    */
    if (top >= (MAX - 1)) {
        cout << "Stack Overflow";
        return false;
    }
    else {
        a[++top] = x;
        cout << x << " pushed into stack\n";
        return true;
    }
}

int Stack::pop() //Return the top element and delete it (apunta a una posición inferior: top--)
{
    /*ALGORITHM
        Before popping the element from the stack, we check if the stack is empty .
        If the stack is empty (top == -1), then Stack Underflows and we cannot remove any element from the stack.
        Otherwise, we store the value at top, decrement the value of top by 1 (top = top – 1) and return the stored top value. 
    */
    if (top < 0) {
        cout << "Stack Underflow";
        return 0;
    }
    else {
        int x = a[top--];
        return x;
    }
}

int Stack::peek() //Return the top element and doesn't delete it (no apunta a otro pado : top)
{
    /*ALGORITHM
        Before returning the top element from the stack, we check if the stack is empty.
        If the stack is empty (top == -1), we simply print “Stack is empty”.
        Otherwise, we return the element stored at index = top . 
    
    */
    if (top < 0) {
        cout << "Stack is Empty";
        return 0;
    }
    else {
        int x = a[top];
        return x;
    }
}

bool Stack::isEmpty()
{
    /* ALGORITHM
        Check for the value of top in stack.
        If (top == -1) , then the stack is empty so return true .
        Otherwise, the stack is not empty so return false . 
    */
    return (top < 0); //1 se está vacío (top=-1)
}

bool Stack::isFull()
{
    /*ALGORITHM
        Check for the value of top in stack.
        If (top == capacity-1), then the stack is full so return true.
        Otherwise, the stack is not full so return false. 
        
    */
    return (top==MAX-1); //retorna 1 si top apunta a la última posición disponible en el stack
}

int Stack::get_size()
{
    /*ALGORITHM
        int count=0;
        int temp = top;
        while (temp!=-1){
            cout<<a[temp--]<<", "; //primero imprime la posi deseada y luego disminuye la posi
            count++;
        }
        size = count;
        return size;
    */
    

    return top+1;
}

void Stack::display(Stack s)
{
    /*ALgorithm
        Crear una variable temp que actúe como top pero que sirva para recorrer todo el stack sin modificar el top
        Imprimir mientras que temp no sea igual a -1

        El primero en ser imprimido será el que útimo ingresó
    */
    int temp = top; 
    while (temp!=-1){
        cout<<a[temp--]<<", "; //primero imprime la posi deseada y luego disminuye la posi
    }
    cout<<"El tamaño del stack es: "<<s.get_size()<<endl;
}

// Driver program to test above functions
int main()
{
    class Stack s;
    s.push(10);
    s.push(20);
    s.push(30);
    s.display(s);
    cout<<"El tamanio ocupado del stack es: "<<s.get_size()<<endl;

    cout << s.pop() << " Popped from stack\n";
    s.display(s);
    cout<<"El tamanio ocupado del stack es: "<<s.get_size()<<endl;

    //print top element of stack after popping
    cout << "Top element is : " << s.peek() << endl;
  
    /* 
    print all elements in stack :
    cout <<"Elements present in stack : ";
    while(!s.isEmpty())
    {
        // print top element in stack
        cout << s.peek() <<" ";
        // remove top element in stack
        s.pop();
    }
    */

    //print el tamaño actual ocupado del stack
    cout<<"El tamanio ocupado del stack es: "<<s.get_size()<<endl;
    return 0;
}
//Code is Modified By Vinay Pandey
