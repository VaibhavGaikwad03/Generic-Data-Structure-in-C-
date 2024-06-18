#include <iostream>
#include <string.h>
#include "vector.h"
using std::cout;
using std::endl;
       
// iterator overloaded operators
int &vector::iterator::operator*()
{
    return array[index];
}

bool vector::iterator::operator==(const iterator &iter)
{
    return (index == iter.index);
}

bool vector::iterator::operator<(const iterator &iter)
{
    return (index < iter.index);
}

bool vector::iterator::operator>(const iterator &iter)
{
    return (index > iter.index);
}

bool vector::iterator::operator<=(const iterator &iter)
{
    return (index <= iter.index);
}

bool vector::iterator::operator>=(const iterator &iter)
{
    return (index >= iter.index);
}

vector::iterator &vector::iterator::operator++()
{
    index++;
    return *this;
}

vector::iterator vector::iterator::operator++(int)
{
    iterator iter;
    iter.set_index(index);
    index++;
    return iter;
}

vector::iterator &vector::iterator::operator--()
{
    index--;
    return *this;
}

vector::iterator vector::iterator::operator--(int)
{
    iterator iter;
    iter.set_index(index);
    index--;
    return iter;
}

bool vector::iterator::operator!=(const vector::iterator &iter)
{
    return (index != iter.get_index());
}

// iterator member functions
void vector::iterator::set_index(int index)
{
    this->index = index;
}

int vector::iterator::get_index() const
{
    return index;
}

// vector member functions
vector::vector()
{
    array = nullptr;
    array_size = 0;
}

vector::vector(int n)
{
    array = new int[n];
    if (array == nullptr)
        return;

    memset(array, 0, n * sizeof(int));

    array_size = n;
}

size_t vector::size()
{
    return array_size;
}

void vector::memcopy(int *dest, int *src, int index, int data)
{
    for (int counter = 0; counter < index; counter++)
        dest[counter] = src[counter];

    dest[index] = data;

    for (int counter = index + 1; counter <= array_size; counter++)
        dest[counter] = src[counter - 1];
}

void vector::insert(iterator iter, int data)
{
    int index = iter.get_index();

    int *temp = nullptr;
    temp = new int[array_size + 1];
    if (temp == nullptr)
        return;

    memcopy(temp, array, index, data);
    array_size += 1;

    delete[] array;

    array = temp;
    temp = nullptr;
}

void vector::swap(vector &v)
{
    int *temp_address = array;
    array = v.array;
    v.array = temp_address;

    // int temp_size = array_size;
    // array_size = v.array_size;
    // v.array_size = temp_size;

    array_size = array_size + v.array_size;
    v.array_size = array_size - v.array_size;
    array_size = array_size - v.array_size;
}

vector::iterator vector::begin()
{
    return iterator(array, 0);
}

vector::iterator vector::end()
{
    return iterator(array, array_size);
}

// vector overloaded operator
int &vector::operator[](int index)
{
    return array[index];
}

ostream &operator<<(ostream &out, vector &v)
{
    // int *array = v.array;
    cout << "\nVector is:\n";
    for (int counter = 0; counter < v.array_size; counter++)
        out
            << v.array[counter] << ' ';
    out << endl;

    return out;
}
