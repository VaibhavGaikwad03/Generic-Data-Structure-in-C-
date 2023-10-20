#include <iostream>
using std::cout;
using std::endl;

template <class T>
class vector
{
    T* array;
    int size;

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
    }

    vector(int size)
    {
        array = new T[size];
        this->size = size;
    }

    ~vector()
    {

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
};

int main(void)
{
    vector <int> v(10);
    v.give_values();
    v.display();

    int* p = v.data();

    *p = 100;
    p++;
    *p = 200;
    p++;
    *p = 300;

    cout << v.at(0) << endl;
    cout << v.at(1) << endl;
    cout << v.at(2) << endl;

    v.display();

    return 0;
}
