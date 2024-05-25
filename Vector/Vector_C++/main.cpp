#include <iostream>
#include "vector.h"
using std::cout;
using std::endl;

int main()
{
    // an int vector of 10 elements
    vector int_v(10);

    for (size_t i = 0; i < int_v.size(); ++i)
        int_v[i] = i;

    // vector increases on demand
    int_v.insert(int_v.end(), 100); // append the number 100

    for (size_t i = 0; i < int_v.size(); ++i)
        cout << int_v[i] << ' ';

    cout << endl
         << endl;

    // use with and iterator
    for (vector::iterator I = int_v.begin(); I != int_v.end(); ++I)
        cout << *I << ' ';

    cout << endl
         << endl;

    vector new_v(20); // all elements are 0

    cout << "new_v = ";
    for (size_t i = 0; i < new_v.size(); ++i)
        cout << new_v[i] << ' ';

    // swapping two vectors
    new_v.swap(int_v);

    cout << "\nnew_v after swapping = ";
    for (size_t i = 0; i < new_v.size(); ++i)
        cout << new_v[i] << ' '; // old contents of int_v

    cout << "\nint_v after swapping = ";
    for (size_t i = 0; i < int_v.size(); ++i)
        cout << int_v[i] << ' '; // old contents of new_v

    cout << "\n\nint_v = ";
    cout << int_v;
    cout << "\nnew_v = ";
    cout << new_v;

    cout << endl;

    return 0;
}