#ifndef DCLL_H
#define DCLL_H

#include <ostream>
using std::ostream;

class list;

class iterator;

ostream &operator<<(ostream &out, list &lst);

class node
{
    node *next;
    int data;
    node *prev;

    node();
    ~node();

    friend class list;
    friend class iterator;
    friend ostream &operator<<(ostream &out, list &lst);
};

class list
{
    node *head;
    node *tail;
    int counter;
    //////////////////////////////////////////////////////
public:
    class iterator
    {
        node *current_node;
        void set_current_node(node *set_node);

    public:
        iterator();
        ~iterator();
        bool operator==(iterator &iter);
        bool operator!=(iterator &iter);
        int operator*();
        iterator &operator++();
        iterator operator++(int);
        iterator &operator--();
        iterator operator--(int);

        friend class list;
    };

private:
    iterator start_iter;
    iterator end_iter;
    //////////////////////////////////////////////////////
public:
    list();
    ~list();
    bool is_empty();
    int count_nodes() const;
    // void display() const;
    void insert_first(int data);
    void insert_last(int data);
    void insert_at_position(int data, int pos);
    int delete_first();
    int delete_last();
    int delete_at_position(int pos);
    int search_first_occurrence(int key) const;
    int search_last_occurrence(int key) const;
    int search_all_occurrence(int key) const;
    void concat_list(list &new_list);
    void concat_at_position(list &new_list, int pos);
    void reverse_display() const;
    void physical_reverse();
    void delete_all();

    /////////////////////////////////////
    list::iterator &begin();
    list::iterator &end();
    /////////////////////////////////////

    friend class iterator;

    friend ostream &operator<<(ostream &out, list &lst);

    // friend void test_normal(const list &lst);
    // friend void test_reverse(const list &lst);
};

// void test_normal(const list &lst);
// void test_reverse(const list &lst);

#endif // DCLL_H