#ifndef LIST_SERVER_H
#define LIST_SERVER_H

#include <ostream>
using std::ostream;

template <typename T>
class list;

class iterator;

template <typename T>
ostream &operator<<(ostream &out, list<T> &lst);

template <typename T>
class node
{
    node *prev;
    T data;
    node *next;

    node();
    ~node();

    friend class list<T>;
    friend class iterator;
    friend ostream &operator<< <T>(ostream &out, list<T> &lst);
};

template <typename T>
class list
{
    node<T> *dummy_node;
    int counter;

public:
    class iterator
    {
        node<T> *current_node;

        void set_current_node(node<T> *set_node);

    public:
        iterator();
        ~iterator();

        bool operator==(iterator &iter);
        bool operator!=(iterator &iter);
        T operator*();

        iterator &operator++();
        iterator operator++(int);
        iterator &operator--();
        iterator operator--(int);

        friend class list<T>;
    };

private:
    iterator start_iter;
    iterator end_iter;

public:
    list();
    ~list();

    int count_nodes() const;
    bool is_empty() const;
    void reverse_display() const;
    void insert_first(T data);
    void insert_last(T data);
    void insert_at_position(T data, int pos);
    T delete_first();
    T delete_last();
    T delete_at_position(int pos);
    int search_first_occurrence(T key) const;
    int search_last_occurrence(T key) const;
    int search_all_occurrence(T key) const;
    void concat_list(list &new_list);
    void concat_at_position(list &new_list, int pos);
    void physical_reverse();
    void delete_all();

    iterator &begin();
    iterator &end();

    friend class iterator;
    friend ostream &operator<< <T>(ostream &out, list<T> &lst);
};

#endif // LIST_SERVER_H