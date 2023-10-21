#include <iostream>
using std::cout;
using std::endl;
 
template <class T>
class vector
{
    T* array;
    int size;
    int index;

public:
    void display()
    {
        int i;

        for (i = 0; i < size; i++)
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
        array = new T[5];
        size = 5;
        index = 0;
    }

    vector(int size)
    {
        array = new T[size];
        this->size = size;
        index = 0;
    }

    ~vector()
    {
        delete[]array;
        size = 0;
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

    void push_back(T data)
    {
        array[index] = data;
        index++;
    }

};

int main(void)
{
    vector <int> v(10);
 
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);
    v.push_back(50);

    v.display();

    return 0;
}
