#include <iostream> 
#include <cstring>
using std::cin;
using std::cout;
using std::endl;
using std::ostream;

template <typename T>
class vector
{
    T *array;
    int array_size;

    void memcopy(T *dest, T *src, int index, T data) const;

public:
    class iterator
    {
        T *array;
        int index;

    public:
        // Member functions
        iterator() : array(nullptr), index(0) {}
        iterator(T *ptr, int idx) : array(ptr), index(idx) {}
        ~iterator() = default;
        void set_index(int indx);
        int get_index() const;

        // Overloaded operators
        bool operator!=(const iterator &iter) const;
        iterator &operator++();
        iterator operator++(int);
        iterator &operator--();
        iterator operator--(int);
        T &operator*();
        bool operator<(const iterator &iter) const;
        bool operator>(const iterator &iter) const;
        bool operator<=(const iterator &iter) const;
        bool operator>=(const iterator &iter) const;
        bool operator==(const iterator &iter) const;
    };

    // Member functions
    vector();
    explicit vector(int n);
    size_t size() const;
    void insert(iterator it, T data);
    void swap(vector &v);

    iterator begin();
    iterator end();

    // Overloaded operators
    T &operator[](int index);

    // private:
    //     iterator start_iter;
    //     iterator end_iter;

    template <typename T1>
    friend ostream &operator<<(ostream &out, vector<T1> &v);
};

// iterator overloaded operators
template <typename T>
T &vector<T>::iterator::operator*()
{
    return array[index];
}

template <typename T>
bool vector<T>::iterator::operator==(const iterator &iter) const
{
    return (index == iter.index);
}

template <typename T>
bool vector<T>::iterator::operator<(const iterator &iter) const
{
    return (index < iter.index);
}

template <typename T>
bool vector<T>::iterator::operator>(const iterator &iter) const
{
    return (index > iter.index);
}

template <typename T>
bool vector<T>::iterator::operator<=(const iterator &iter) const
{
    return (index <= iter.index);
}

template <typename T>
bool vector<T>::iterator::operator>=(const iterator &iter) const
{
    return (index >= iter.index);
}

template <typename T>
typename vector<T>::iterator &vector<T>::iterator::operator++()
{
    index++;
    return *this;
}

template <typename T>
typename vector<T>::iterator vector<T>::iterator::operator++(int)
{
    iterator iter;
    iter.set_index(index);
    index++;
    return iter;
}

template <typename T>
typename vector<T>::iterator &vector<T>::iterator::operator--()
{
    index--;
    return *this;
}

template <typename T>
typename vector<T>::iterator vector<T>::iterator::operator--(int)
{
    iterator iter;
    iter.set_index(index);
    index--;
    return iter;
}

template <typename T>
bool vector<T>::iterator::operator!=(const vector<T>::iterator &iter) const
{
    return (index != iter.get_index());
}

// iterator member functions
template <typename T>
void vector<T>::iterator::set_index(int indx)
{
    this->index = indx;
}

template <typename T>
int vector<T>::iterator::get_index() const
{
    return index;
}

// vector member functions
template <typename T>
vector<T>::vector() : array(nullptr), array_size(0) {}

template <typename T>
vector<T>::vector(int n) : array(new T[n]), array_size(n)
{
    memset(array, 0, n * sizeof(T));
}

template <typename T>
size_t vector<T>::size() const
{
    return array_size;
}

template <typename T>
void vector<T>::memcopy(T *dest, T *src, int index, T data) const
{
    for (int counter = 0; counter < index; counter++)
        dest[counter] = src[counter];

    dest[index] = data;

    for (int counter = index + 1; counter <= array_size; counter++)
        dest[counter] = src[counter - 1];
}

template <typename T>
void vector<T>::insert(iterator iter, T data)
{
    int index = iter.get_index();

    T *temp;
    temp = new T[array_size + 1];
    if (temp == nullptr)
        return;

    memcopy(temp, array, index, data);
    array_size += 1;

    delete[] array;

    array = temp;
}

template <typename T>
void vector<T>::swap(vector &v)
{
    T *temp_address = array;
    array = v.array;
    v.array = temp_address;

    array_size = array_size + v.array_size;
    v.array_size = array_size - v.array_size;
    array_size = array_size - v.array_size;
}

template <typename T>
typename vector<T>::iterator vector<T>::begin()
{
    return {array, 0};
}

template <typename T>
typename vector<T>::iterator vector<T>::end()
{
    return {array, array_size};
}

// vector overloaded operator
template <typename T>
T &vector<T>::operator[](int index)
{
    return array[index];
}

template <typename T>
ostream &operator<<(ostream &out, vector<T> &v)
{
    cout << "\nVector is:\n";
    for (int counter = 0; counter < v.array_size; counter++)
        out << v.array[counter] << ' ';
    out << endl;

    return out;
}

int main()
{
    // an int vector of 10 elements
    vector<int> int_v(10);

    for (size_t i = 0; i < int_v.size(); ++i)
        int_v[i] = i;

    // vector increases on demand
    int_v.insert(int_v.end(), 100); // append the number 100

    for (size_t i = 0; i < int_v.size(); ++i)
        cout << int_v[i] << ' ';

    cout << endl
         << endl;

    // use with and iterator
    for (vector<int>::iterator I = int_v.begin(); I != int_v.end(); ++I)
        cout << *I << ' ';

    cout << endl
         << endl;

    vector<int> new_v(20); // all elements are 0

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
