#ifndef VECTOR_H
#define VECTOR_H

#include <ostream>
using std::ostream;

class vector
{
    int *array;
    int array_size;

    void memcopy(int *dest, int *src, int index, int data);

public:
    class iterator
    {
        int *array;
        int index;

    public:
        // Member functions
        iterator() : array(nullptr), index(0) {}
        iterator(int *ptr, int idx) : array(ptr), index(idx) {}
        ~iterator() {}
        void set_index(int index);
        int get_index() const;

        // Overloaded operators
        bool operator!=(const iterator &iter);
        iterator &operator++();
        iterator operator++(int);
        iterator &operator--();
        iterator operator--(int);
        int &operator*();
        bool operator<(const iterator &iter);
        bool operator>(const iterator &iter);
        bool operator<=(const iterator &iter);
        bool operator>=(const iterator &iter);
        bool operator==(const iterator &iter);
    };

    // Member functions
    vector();
    vector(int n);
    size_t size();
    void insert(iterator it, int data);
    void swap(vector &v);

    iterator begin();
    iterator end();

    int &operator[](int index);

    // private:
    //     iterator start_iter;
    //     iterator end_iter;

    friend ostream &operator<<(ostream &out, vector &v);
};

#endif // VECTOR_H