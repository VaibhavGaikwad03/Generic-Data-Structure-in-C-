#include "list_server.h"
#include <iostream>
using std::cout;

/// node class member functions - start/////////////////////////////////////////////////
node::node()
{
    data = 0;
    prev = next = nullptr;
}

node::~node()
{
    data = 0;
    prev = next = nullptr;
}
/// node class member functions - end/////////////////////////////////////////////////
/// list class member functions - start/////////////////////////////////////////////////
list::list()
{
    counter = 0;
    head = tail = nullptr;
}

list::~list()
{
    if (head != nullptr)
        delete_all();
}

int list::count_nodes() const
{
    return counter;
}

bool list::is_empty()
{
    if (head == nullptr)
        return true;
    return false;
}

/*
void list::display() const
{
    node *temp_node = head;

    if (temp_node == nullptr)
    {
        cout << "\nList is empty.\n";
        return;
    }

    do
    {
        cout << temp_node->data << ' ';
        temp_node = temp_node->next;
    } while (temp_node != tail->next);
    cout << '\n';
}
*/

void list::reverse_display() const
{
    node *temp_node = tail;

    if (temp_node == nullptr)
    {
        cout << "\nList is empty.\n";
        return;
    }

    do
    {
        cout << temp_node->data << ' ';
        temp_node = temp_node->prev;
    } while (temp_node != head->prev);
    cout << '\n';
}

void list::insert_first(int data)
{
    node *new_node = nullptr;

    new_node = new node;
    if (new_node == nullptr)
        return;

    new_node->data = data;

    if (head == nullptr)
        head = tail = new_node;
    else
    {
        new_node->next = head;
        head->prev = new_node;
        head = new_node;
    }
    head->prev = tail;
    tail->next = head;
    counter++;
}

void list::insert_last(int data)
{
    node *new_node = nullptr;

    new_node = new node;
    if (new_node == nullptr)
        return;

    new_node->data = data;

    if (head == nullptr)
        head = tail = new_node;
    else
    {
        tail->next = new_node;
        new_node->prev = tail;
        tail = new_node;
    }
    head->prev = tail;
    tail->next = head;
    counter++;
}

void list::insert_at_position(int data, int pos)
{
    int i;
    node *new_node = nullptr;
    node *temp_node = nullptr;

    if (pos < 1 || pos > counter + 1)
        return;

    if (pos == 1)
        insert_first(data);
    else if (pos == counter + 1)
        insert_last(data);
    else
    {
        new_node = new node;
        if (new_node == nullptr)
            return;
        new_node->data = data;

        temp_node = head;

        for (i = 1; i < pos - 1; i++)
            temp_node = temp_node->next;
        new_node->next = temp_node->next;
        new_node->next->prev = new_node;
        temp_node->next = new_node;
        new_node->prev = temp_node;
        counter++;
    }
}

int list::delete_first()
{
    int deleted_data;
    node *temp_delete = nullptr;

    if (head == nullptr)
        return -1;

    deleted_data = head->data;

    if (head == tail)
    {
        head->next = head->prev = nullptr;
        delete head;
        head = tail = nullptr;
    }
    else
    {
        temp_delete = head;
        head = head->next;
        head->prev = tail;
        tail->next = head;
        temp_delete->next = temp_delete->prev = nullptr;
        delete temp_delete;
    }
    counter--;
    return deleted_data;
}

int list::delete_last()
{
    int deleted_data;
    node *temp_delete = nullptr;

    if (head == nullptr)
        return -1;

    deleted_data = tail->data;

    if (head == tail)
    {
        tail->next = tail->prev = nullptr;
        delete tail;
        head = tail = nullptr;
    }
    else
    {
        temp_delete = tail;
        tail = tail->prev;
        head->prev = tail;
        tail->next = head;
        temp_delete->next = temp_delete->prev = nullptr;
        delete temp_delete;
    }
    counter--;
    return deleted_data;
}

int list::delete_at_position(int pos)
{
    int i, deleted_data;
    node *temp_node = nullptr;
    node *temp_delete = nullptr;

    if (pos < 1 || pos > counter)
        return -1;

    if (pos == 1)
        return delete_first();
    else if (pos == counter)
        return delete_last();
    else
    {
        temp_node = head;

        for (i = 1; i < pos - 1; i++)
            temp_node = temp_node->next;

        temp_delete = temp_node->next;
        deleted_data = temp_delete->data;
        temp_node->next = temp_delete->next;
        temp_delete->next->prev = temp_node;
        temp_delete->next = temp_delete->prev = nullptr;
        delete temp_delete;
        temp_node = temp_delete = nullptr;
        counter--;
        return deleted_data;
    }
}

int list::search_first_occurrence(int key) const
{
    int i, position = 1;
    node *temp_node = head;

    if (head == nullptr)
        return -1;

    for (i = 1; i <= counter; i++)
    {
        if (temp_node->data == key)
            return position;
        position++;
        temp_node = temp_node->next;
    }
    return -2;
}

int list::search_last_occurrence(int key) const
{
    node *temp_node = head;
    int i, position = 1, ret_position = -2;

    if (head == nullptr)
        return -1;

    for (i = 1; i <= counter; i++)
    {
        if (temp_node->data == key)
            ret_position = position;
        position++;
        temp_node = temp_node->next;
    }
    return ret_position;
}

int list::search_all_occurrence(int key) const
{
    int i, count_occ = 0;
    node *temp_node = head;

    if (head == nullptr)
        return 0;

    for (i = 1; i <= counter; i++)
    {
        if (temp_node->data == key)
            count_occ++;
        temp_node = temp_node->next;
    }
    return count_occ;
}

void list::concat_list(list &new_list)
{
    if (new_list.head == nullptr)
        return;
    if (head == nullptr)
    {
        head = new_list.head;
        tail = new_list.tail;
        new_list.head = new_list.tail = nullptr;
        counter += new_list.counter;
        return;
    }

    tail->next = new_list.head;
    new_list.head->prev = tail;
    new_list.tail->next = head;
    head->prev = new_list.tail;
    tail = new_list.tail;
    counter += new_list.counter;
    new_list.counter = 0;
    new_list.head = new_list.tail = nullptr;
}

void list::concat_at_position(list &new_list, int pos)
{
    int i;
    node *temp_node = nullptr;

    if (pos < 1 || pos > counter + 1)
        return;

    if (new_list.head == nullptr)
        return;

    if (pos == 1)
    {
        new_list.concat_list(*this);
        head = new_list.head;
        tail = new_list.tail;
        counter = new_list.counter;
        new_list.head = new_list.tail = nullptr;
    }
    else if (pos == counter + 1)
        concat_list(new_list);
    else
    {
        temp_node = head;

        for (i = 1; i < pos - 1; i++)
            temp_node = temp_node->next;

        new_list.tail->next = temp_node->next;
        temp_node->next->prev = new_list.tail;
        temp_node->next = new_list.head;
        new_list.head->prev = temp_node;
        counter += new_list.counter;
        new_list.counter = 0;
        new_list.head = new_list.tail = nullptr;
    }
}

void list::physical_reverse()
{
    node *current = head;
    node *next = nullptr;

    if (head == nullptr)
        return;

    do
    {
        next = current->next;
        current->next = current->prev;
        current->prev = next;
        current = next;

    } while (current != head);

    head = tail;
    tail = current;
}

void list::delete_all()
{
    node *temp_node = head;

    if (head == nullptr)
        return;

    head->prev = nullptr;
    tail->next = nullptr;

    while (head != nullptr)
    {
        head = temp_node->next;
        temp_node->next = temp_node->prev = nullptr;
        delete temp_node;
        temp_node = head;
    }
}
/// list class member functions - end/////////////////////////////////////////////////
/// list class new member functions - start//////////////////////////////////////////////////
list::iterator &list::begin()
{
    start_iter.set_current_node(head);
    return start_iter;
}

list::iterator &list::end()
{
    end_iter.set_current_node(tail);
    return end_iter;
}
/// list class new member functions - end/////////////////////////////////////////////////////
/// iterator class member functions - start/////////////////////////////////////////////////////
list::iterator::iterator()
{
    current_node = nullptr;
}

list::iterator::~iterator()
{
    current_node = nullptr;
}

void list::iterator::set_current_node(node *set_node)
{
    current_node = set_node;
}

bool list::iterator::operator==(iterator &iter)
{
    return (current_node == iter.current_node);
}

bool list::iterator::operator!=(iterator &iter)
{
    return (current_node != iter.current_node);
}

int list::iterator::operator*()
{
    return (current_node->data);
}

list::iterator &list::iterator::operator++()
{
    current_node = current_node->next;
    return *this;
}

list::iterator list::iterator::operator++(int)
{
    iterator iter;
    iter.set_current_node(current_node);
    current_node = current_node->next;
    return iter;
}

list::iterator &list::iterator::operator--()
{
    current_node = current_node->prev;
    return *this;
}

list::iterator list::iterator::operator--(int)
{
    iterator iter;
    iter.set_current_node(current_node);
    current_node = current_node->prev;
    return iter;
}
/// iterator class member functions - end/////////////////////////////////////////////////////

ostream &operator<<(ostream &out, list &lst)
{
    node *temp_node = lst.head;

    if (temp_node == nullptr)
        return out;

    do
    {
        out << temp_node->data << ' ';
        temp_node = temp_node->next;
    } while (temp_node != lst.head);

    return out;
}