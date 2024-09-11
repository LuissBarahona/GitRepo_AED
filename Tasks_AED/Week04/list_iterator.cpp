#include<iostream>
#include<iterator> // for iterators
#include<list> // for lists
using namespace std;
int main()
{
    list<int> li = { 1, 2, 3, 4, 5 };
    // Declaring iterator to a list
    list<int>::iterator ptr;
    // Displaying list elements using begin() and end()
    cout << "The list elements are : ";
    for (ptr = li.begin(); ptr != li.end(); ++ptr)
    cout << *ptr << " ";
    return 0;
}