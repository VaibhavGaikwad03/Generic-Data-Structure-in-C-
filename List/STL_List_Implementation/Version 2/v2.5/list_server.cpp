#include <iostream>
#include "list_server.h"

using std::cout;

template <typename T>
node<T>::node()
{
    data = 0;
    prev = next = nullptr;
}

template <typename T>
node<T>::~node()
{
    data = 0;
    prev = next = nullptr;
}

template <typename T>
void list<T>::iterator::set_current_node(node<T> *set_node)
{
    current_node = set_node;
}

template <typename T>
list<T>::iterator::iterator()
{
    current_node = nullptr;
}

template <typename T>
list<T>::iterator::~iterator()
{
    current_node = nullptr;
}

template <typename T>
bool list<T>::iterator::operator==(iterator &iter)
{
    return (current_node == iter.current_node);
}

template <typename T>
bool list<T>::iterator::operator!=(iterator &iter)
{
    return (current_node != iter.current_node);
}

template <typename T>
T list<T>::iterator::operator*()
{
    return (current_node->data);
}

template <typename T>
typename list<T>::iterator &list<T>::iterator::operator++()
{
    current_node = current_node->next;
    return *this;
}

template <typename T>
typename list<T>::iterator list<T>::iterator::operator++(int)
{
    iterator iter;
    iter.set_current_node(current_node);
    current_node = current_node->next;
    return iter;
}

template <typename T>
typename list<T>::iterator &list<T>::iterator::operator--()
{
    current_node = current_node->prev;
    return *this;
}

template <typename T>
typename list<T>::iterator list<T>::iterator::operator--(int)
{
    iterator iter;
    iter.set_current_node(current_node);
    current_node = current_node->prev;
    return iter;
}

template <typename T>
list<T>::list()
{
    counter = 0;
    dummy_node = nullptr;
    dummy_node = new node<T>;
    if (dummy_node == nullptr)
        return;
    dummy_node->next = dummy_node;
    dummy_node->prev = dummy_node;
}

template <typename T>
list<T>::~list()
{
    if (dummy_node->next != dummy_node)
        delete_all();
    delete dummy_node;
    dummy_node = nullptr;
}

template <typename T>
int list<T>::count_nodes() const
{
    return counter;
}

template <typename T>
bool list<T>::is_empty() const
{
    return (counter == 0);
}

template <typename T>
void list<T>::reverse_display() const
{
    node<T> *temp_node = dummy_node->prev;

    if (temp_node == nullptr)
    {
        cout << "\nList is empty.\n";
        return;
    }

    do
    {
        cout << temp_node->data << ' ';
        temp_node = temp_node->prev;
    } while (temp_node != dummy_node);
    cout << '\n';
}

template <typename T>
void list<T>::insert_first(T data)
{
    node<T> *new_node = nullptr;

    new_node = new node<T>;
    if (new_node == nullptr)
        return;

    new_node->data = data;

    new_node->next = dummy_node->next;
    new_node->next->prev = new_node;
    dummy_node->next = new_node;
    new_node->prev = dummy_node;

    counter++;
}

template <typename T>
void list<T>::insert_last(T data)
{
    node<T> *new_node = nullptr;

    new_node = new node<T>;
    if (new_node == nullptr)
        return;

    new_node->data = data;

    new_node->prev = dummy_node->prev;
    new_node->prev->next = new_node;
    new_node->next = dummy_node;
    dummy_node->prev = new_node;

    counter++;
}

template <typename T>
void list<T>::insert_at_position(T data, int pos)
{
    int i;
    node<T> *new_node = nullptr;
    node<T> *temp_node = nullptr;

    if (pos < 1 || pos > counter + 1)
        return;

    if (pos == 1)
        insert_first(data);
    else if (pos == counter + 1)
        insert_last(data);
    else
    {
        new_node = new node<T>;
        if (new_node == nullptr)
            return;
        new_node->data = data;

        temp_node = dummy_node->next;

        for (i = 1; i < pos - 1; i++)
            temp_node = temp_node->next;
        new_node->next = temp_node->next;
        new_node->next->prev = new_node;
        temp_node->next = new_node;
        new_node->prev = temp_node;
        counter++;
    }
}

template <typename T>
T list<T>::delete_first()
{
    T deleted_data;
    node<T> *temp_delete = nullptr;

    if (counter == 0) /* dummy_node->next == dummy_node */
        return -1;

    deleted_data = dummy_node->next->data;

    dummy_node->next = dummy_node->next->next;
    delete dummy_node->next->prev;
    dummy_node->next->prev = dummy_node;

    counter--;
    return deleted_data;
}

template <typename T>
T list<T>::delete_last()
{
    T deleted_data;
    node<T> *temp_delete = nullptr;

    if (counter == 0) /* dummy_node->next == dummy_node */
        return -1;

    deleted_data = dummy_node->prev->data;

    dummy_node->prev = dummy_node->prev->prev;
    delete dummy_node->prev->next;
    dummy_node->prev->next = dummy_node;

    counter--;
    return deleted_data;
}

template <typename T>
T list<T>::delete_at_position(int pos)
{
    int i;
    T deleted_data;
    node<T> *temp_node = nullptr;
    node<T> *temp_delete = nullptr;

    if (pos < 1 || pos > counter)
        return -1;

    if (pos == 1)
        return delete_first();
    else if (pos == counter)
        return delete_last();
    else
    {
        temp_node = dummy_node->next;

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

template <typename T>
int list<T>::search_first_occurrence(T key) const
{
    int i, position = 1;
    node<T> *temp_node = dummy_node->next;

    if (counter == 0) /* dummy_node->next == dummy_node */
        return -1;

    // do
    // {
    //     if (temp_node->data == key)
    //         return position;
    //     position++;
    //     temp_node = temp_node->next;
    // } while (temp_node != dummy_node->next);

    for (i = 1; i <= counter; i++)
    {
        if (temp_node->data == key)
            return position;
        position++;
        temp_node = temp_node->next;
    }
    return -2;
}

template <typename T>
int list<T>::search_last_occurrence(T key) const
{
    node<T> *temp_node = dummy_node->next;
    int i, position = 1, ret_position = -2;

    if (counter == 0) /* dummy_node->next == dummy_node */
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

template <typename T>
int list<T>::search_all_occurrence(T key) const
{
    int i, count_occ = 0;
    node<T> *temp_node = dummy_node->next;

    if (counter == 0) /* dummy_node->next == dummy_node */
        return 0;

    for (i = 1; i <= counter; i++)
    {
        if (temp_node->data == key)
            count_occ++;
        temp_node = temp_node->next;
    }
    return count_occ;
}

template <typename T>
void list<T>::concat_list(list<T> &new_list)
{
    if (new_list.counter == 0) /* new_list.dummy_node->next == dummy_node */
        return;
    if (counter == 0) /* dummy_node->next == dummy_node */
    {
        dummy_node->next = new_list.dummy_node->next;
        dummy_node->prev = new_list.dummy_node->prev;
        dummy_node->next->prev = dummy_node;
        dummy_node->prev->next = dummy_node;
        counter = new_list.counter;
        new_list.counter = 0;
        new_list.dummy_node->next = new_list.dummy_node->prev = new_list.dummy_node;
        return;
    }

    dummy_node->prev->next = new_list.dummy_node->next;
    new_list.dummy_node->next->prev = dummy_node->prev;
    dummy_node->prev = new_list.dummy_node->prev;
    new_list.dummy_node->prev->next = dummy_node;
    counter += new_list.counter;
    new_list.counter = 0;
    new_list.dummy_node->next = new_list.dummy_node->prev = new_list.dummy_node;
}

template <typename T>
void list<T>::concat_at_position(list<T> &new_list, int pos)
{
    int i;
    node<T> *temp_node = nullptr;

    if (pos < 1 || pos > counter + 1)
        return;

    if (new_list.counter == 0) /* new_list.dummy_node->next == new_list.dummy_node */
        return;

    if (pos == 1)
    {
        new_list.concat_list(*this);
        dummy_node->next = new_list.dummy_node->next;
        dummy_node->prev = new_list.dummy_node->prev;
        new_list.dummy_node->next->prev = dummy_node;
        new_list.dummy_node->prev->next = dummy_node;
        counter = new_list.counter;
        new_list.counter = 0;
        new_list.dummy_node->next = new_list.dummy_node->prev = new_list.dummy_node;
    }
    else if (pos == counter + 1)
        concat_list(new_list);
    else
    {
        temp_node = dummy_node->next;

        for (i = 1; i < pos - 1; i++)
            temp_node = temp_node->next;

        new_list.dummy_node->prev->next = temp_node->next;
        temp_node->next->prev = new_list.dummy_node->prev;
        temp_node->next = new_list.dummy_node->next;
        new_list.dummy_node->next->prev = temp_node;

        counter += new_list.counter;
        new_list.counter = 0;
        new_list.dummy_node->next = new_list.dummy_node->prev = new_list.dummy_node;
    }
}

template <typename T>
void list<T>::physical_reverse()
{
    node<T> *current = dummy_node;
    node<T> *next = nullptr;

    if (counter == 0) /* dummy_node->next == dummy_node */
        return;

    do
    {
        next = current->next;
        current->next = current->prev;
        current->prev = next;
        current = next;
    } while (current != dummy_node);
}

template <typename T>
void list<T>::delete_all()
{
    node<T> *temp_delete = nullptr;
    node<T> *temp_node = dummy_node->next;

    if (counter == 0) /* dummy_node->next == dummy_node */
        return;

    dummy_node->prev->next = nullptr;

    while (temp_node != nullptr)
    {
        temp_delete = temp_node;
        temp_node = temp_node->next;
        temp_delete->prev = temp_delete->next = nullptr;
        delete temp_delete;
    }
    counter = 0;
    dummy_node->next = dummy_node->prev = dummy_node;
}

template <typename T>
typename list<T>::iterator &list<T>::begin()
{
    start_iter.set_current_node(dummy_node->next);
    return start_iter;
}

template <typename T>
typename list<T>::iterator &list<T>::end()
{
    end_iter.set_current_node(dummy_node);
    return end_iter;
}

template <typename T>
ostream &operator<<(ostream &out, const list<T> &lst)
{
    node<T> *temp_node = lst.dummy_node->next;

    if (temp_node == nullptr)
        return out;

    do
    {
        out << temp_node->data << ' ';
        temp_node = temp_node->next;
    } while (temp_node != lst.dummy_node->next);

    return out;
}