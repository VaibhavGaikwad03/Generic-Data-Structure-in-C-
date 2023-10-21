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
    T& at(int index) const 
    {
        return array[index];
    }

    T& front() const
    {
        return array[0];
    }

    T& back() const
    {
        return array[size - 1];
    }

    T* data() const
    {
        return array;
    }
//  Element access end

//  Capacity functions start
    size_t size() const
    {
        return index;
    }

    size_t capacity() const
    {
        return _size;
    }

    void resize(size_t new_size)
    {
        if (new_size < 0)
            return;

        if ((new_size < index || new_size > index) && new_size <= _size)
            index = new_size;
        else
        {

        }
        

    }

//  Capacity functions end

    void push_back(T data)
    {
        T* temp = NULL;

        if (_size == index)
        {
            temp = array;
            array = new int[_size += _size];
            copy(array, temp);
            delete[]temp;
            temp = NULL;
        }

        array[index++] = data;
    }

};

int main(void)
{
    vector <int> v(5);
    v.push_back(10);
    v.push_back(10);
    v.push_back(10);
    v.push_back(10);
    v.push_back(10);
    v.push_back(10);
    v.at(1) = 1;

    cout << v.size() << endl;
    cout << v.capacity() << endl;
    v.display();

    return 0;
}