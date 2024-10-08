/*
    - tabla hash
    - manejo de colisiones : encadenamiento o chaining usando simple linked lists
    - hash function: función universal basada en números primos
    - status: 100% funcional
*/


#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Libreria_Simple_Linked_List.h"
using namespace std;

//Libreria simple linked list

//***CREATE A CLASS FOR HASH TABLE ***
template <typename T>
class HashTable {
private:
    int m; // Number of buckets (rows)
    int n; // Maximum number of nodes per linked list
    float loadFactor; // Relation between the number of occupied spaces and the total number of spaces (m * n)
    List<T>* array; // Array of linked lists
    int occupiedBuckets; // Keeps track of how many buckets are occupied
    int P; // Prime number greater than m
    int a;
    int b;

    

public:
    HashTable(int buckets, int maxNodes) : m(buckets), n(maxNodes), occupiedBuckets(0) {
        array = new List<T>[m];
        loadFactor = 0.0;
        P = 101; // A large prime number (can be modified)
        srand(time(0)); // Seed for random number generation
        a = rand() % (P - 1) + 1;
        b = rand() % P;
    }
    // Helper function to calculate load factor
    void updateLoadFactor() {
        loadFactor = static_cast<float>(occupiedBuckets) / m;
    }

    // Rehashing function to double the number of buckets and redistribute keys
    void rehashing(int newM) {
        List<T>* oldArray = array;
        int oldM = m;

        m = newM; // Double the number of buckets
        array = new List<T>[m]; // Create a new array of linked lists
        occupiedBuckets = 0; // Reset the occupied buckets counter

        // Reinsert all keys from the old table to the new one
        for (int i = 0; i < oldM; i++) {
            Node<T>* temp = oldArray[i].getHead();
            while (temp != NULL) {
                insert(temp->data); // Reinsert each key
                temp = temp->next;
            }
        }

        delete[] oldArray; // Delete the old array
    }

    // Universal hash function that returns the index where the key will be stored
    int hashFunction(T key) {
        return ((a * key + b) % P) % m;
    }

    // Insert function with automatic rehashing
    void insert(T key) {
        int index = hashFunction(key);

        // If the list at the index is full, find an empty bucket
        if (array[index].size() >= n) {
            // Find an empty bucket
            bool inserted = false;
            for (int i = 0; i < m; i++) {
                if (array[i].empty()) {
                    array[i].add_node(key);
                    occupiedBuckets++;
                    inserted = true;
                    break;
                }
            }

            // If no empty bucket was found, trigger rehashing
            if (!inserted) {
                rehashing(m * 2); // Double the number of buckets
                insert(key); // Reinsert the key after rehashing
            }
        } else {
            // Insert the key into the appropriate linked list
            array[index].add_node(key);

            // If this was the first key in this bucket, increase the occupied count
            if (array[index].size() == 1) {
                occupiedBuckets++;
            }
        }

        // Update the load factor and check for rehashing
        updateLoadFactor();

        if (loadFactor >= 1.0) {
            rehashing(m * 2); // Double the number of buckets when the table is full
        }
    }

    // Function to display the entire hash table
    void showHash() {
        for (int i = 0; i < m; i++) {
            cout << i << ": ";
            array[i].display_list(); // Remember that each element of the array is a simple linked list
            cout << endl;
        }
        cout<<"load factor: "<<loadFactor<<endl;
    }

    // Function to search for a key in the hash table
    bool search(T key) {
        int index = hashFunction(key);
        Node<T>* temp = array[index].getHead();
        while (temp != NULL) {
            if (temp->data == key) {
                return true; // Key found
            }
            temp = temp->next;
        }
        return false; // Key not found
    }

    // Function to delete a key from the hash table
    void deleteKey(T key) {
        int index = hashFunction(key);
        array[index].delete_node(key); // Delete the value from the linked list
        // If the list becomes empty, decrease the occupied buckets count
        if (array[index].empty()) {
            occupiedBuckets--;
        }
        updateLoadFactor(); // Recalculate the load factor
    }

    bool empty(){
        return loadFactor==0;

    }
    // Destructor to free memory
    ~HashTable() {
        delete[] array;
    }
};


//int main() 