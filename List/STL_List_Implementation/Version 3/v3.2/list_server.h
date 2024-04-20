#ifndef LIST_SERVER_H
#define LIST_SERVER_H

#include <ostream>
using std::ostream;

class list;

class iterator;

ostream &operator<<(ostream &out, list &lst);

class node
{
    node *prev;
    int data;
    node *next;

    node();
    ~node();

    friend class list;
    friend class iterator;
    friend ostream &operator<<(ostream &out, list &lst);
};

class list
{
    node *dummy_node;
    int counter;

public:
    class iterator
    {
        node *current_node;

        void set_current_node(node *set_node);
        node *get_current_node();

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

public:
    list();
    list(list &lst);
    ~list();

    int count_nodes() const;
    bool is_empty() const;
    void reverse_display() const;
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
    void physical_reverse();
    void delete_all();

    void push_front(int data);
    void push_back(int data);
    void splice(iterator position, list &lst);
    void splice(iterator dest_pos, list &lst, iterator src_pos);
    void sort();
    void merge(list &lst);
    void unique();
    list &operator=(const list &lst);

    iterator &begin();
    iterator &end();

    friend class iterator;
    friend ostream &operator<<(ostream &out, list &lst);
};

list::iterator find(list::iterator start, list::iterator end, int key);

#endif // LIST_SERVER_H