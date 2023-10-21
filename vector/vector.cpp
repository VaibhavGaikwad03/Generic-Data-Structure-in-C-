#include <iostream>
#define CONTAINER_SIZE 10
using std::cout;
using std::endl;

template <class T>
class vector
{
    T* array;
    int _size;
    int index;

    void copy(T* dest, T* src)
    {
        int i;

        for (i = 0; i < index; i++)
            dest[i] = src[i];
    }

public:
    void display()
    {
        int i;

        for (i = 0; i < index; i++)
            cout << array[i] << " ";
        cout << endl;
    }

    void give_values()
    {
        int i;

        for (i = 0; i < size; i++)
            array[i] = i + 1;
    }

public:
    vector()
    {
        array = new T[CONTAINER_SIZE];
        _size = 0;
        index = 0;
    }

    vector(int size)
    {
        array = new T[size];
        _size = size;
        index = size;
    }

    ~vector()
    {
        delete[]array;
        _size = 0;
        index = 0;
    }

//  Element Access Start 
    T& at(int index)
    {
        return array[index];
    }

    T& front()
    {
        return array[0];
    }

    T& back()
    {
        return array[size - 1];
    }

    T* data()
    {
        return array;
    }
//  Element access end

    size_t size()
    {
        return index;
    }

    void push_back(T data)
    {
        T* temp = NULL;

        if (_size == index)
        {
            temp = array;
            array = new int[_size += 10];
            copy(array, temp);
            delete[]temp;
            temp = NULL;
        }

        array[index++] = data;
    }

};

int main(void)
{
    vector <int> v;

    cout << v.size() << endl;
    v.display();

    return 0;
}