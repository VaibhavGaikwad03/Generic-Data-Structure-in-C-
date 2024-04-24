#include <iostream>
using std::cin;
using std::cout;
using std::endl;
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
        node<T> *get_current_node();

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
    list(list &lst);
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

    list &operator=(const list &lst);
    void push_front(T data);
    void push_back(T data);
    void splice(iterator position, list &lst);
    void splice(iterator dest_pos, list &lst, iterator src_pos);
    void sort();
    void merge(list &lst);
    void unique();

    iterator &begin();
    iterator &end();

    friend class iterator;
    friend ostream &operator<< <T>(ostream &out, list<T> &lst);
};

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
node<T> *list<T>::iterator::get_current_node()
{
    return current_node;
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
list<T>::list(list &lst)
{
    node<T> *temp_node = nullptr;

    this->dummy_node = new node<T>;
    if (this->dummy_node == nullptr)
        return; // Memory allocation failed

    // this->counter = lst.counter;
    this->dummy_node->prev = this->dummy_node->next = this->dummy_node;

    if (lst.dummy_node->next != lst.dummy_node)
        temp_node = lst.dummy_node->next;

    for (int i = 0; i < lst.counter; i++)
    {
        this->insert_last(temp_node->data);
        temp_node = temp_node->next;
    }
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

template <typename T>
list<T> &list<T>::operator=(const list &lst) // Implement this later
{
    int lcnt;
    node<T> *dest_node = nullptr;
    node<T> *src_node = nullptr;

    if (this->counter == 0) // First list is empty
    {
        src_node = lst.dummy_node->next;

        for (lcnt = 0; lcnt < lst.counter; lcnt++)
        {
            this->insert_last(src_node->data);
            src_node = src_node->next;
        }
        return *this;
    }

    dest_node = this->dummy_node->next;
    src_node = lst.dummy_node->next;

    if (this->counter < lst.counter) // If elements are less
    {
        for (lcnt = 0; lcnt < lst.counter; lcnt++)
        {
            dest_node->data = src_node->data;

            if (lcnt >= this->counter)
                this->insert_last(src_node->data);
            else
                dest_node = dest_node->next;
            src_node = src_node->next;
        }
    }
    else if (this->counter > lst.counter) // If elements are more
    {
        int temp_counter = this->counter;

        for (lcnt = 0; lcnt < temp_counter; lcnt++)
        {
            dest_node->data = src_node->data;
            if (lcnt >= lst.counter)
            {
                this->delete_last();
                continue;
            }
            dest_node = dest_node->next;
            src_node = src_node->next;
        }
    }
    else // If elements are same
    {
        for (int lcnt = 0; lcnt < this->counter; lcnt++)
        {
            dest_node->data = src_node->data;
            dest_node = dest_node->next;
            src_node = src_node->next;
        }
    }
    return *this;
}

template <typename T>
void list<T>::push_front(T data)
{
    insert_first(data);
}

template <typename T>
void list<T>::push_back(T data)
{
    insert_last(data);
}

template <typename T>
void list<T>::splice(iterator position, list &lst)
{
    node<T> *temp_node = position.get_current_node();

    temp_node->prev->next = lst.dummy_node->next;
    lst.dummy_node->next->prev = temp_node->prev;
    lst.dummy_node->prev->next = temp_node;
    temp_node->prev = lst.dummy_node->prev;

    counter += lst.counter;

    lst.counter = 0;
    lst.dummy_node->prev = lst.dummy_node->next = lst.dummy_node;
}

template <typename T>
void list<T>::splice(iterator dest_pos, list &lst, iterator src_pos)
{
    node<T> *src_node = nullptr;
    node<T> *dest_node = nullptr;

    if (lst.is_empty())
        return;

    src_node = src_pos.get_current_node();
    dest_node = dest_pos.get_current_node();

    // Removing element from source
    src_node->prev->next = src_node->next;
    src_node->next->prev = src_node->prev;
    lst.counter--;

    // Inserting source node before destination node

    src_node->next = dest_node;
    src_node->prev = dest_node->prev;
    dest_node->prev->next = src_node;
    dest_node->prev = src_node;
    counter++;
}

template <typename T>
void list<T>::sort()
{
    if (counter <= 1)
    {
        return;
    }

    node<T> *min_node = nullptr;
    node<T> *temp_node = nullptr;
    node<T> *current = dummy_node->next;

    while (current != dummy_node)
    {
        min_node = current;
        temp_node = current->next;

        while (temp_node != dummy_node)
        {
            if (min_node->data > temp_node->data)
                min_node = temp_node;
            temp_node = temp_node->next;
        }

        if (min_node != current)
        {
            min_node->next->prev = min_node->prev;
            min_node->prev->next = min_node->next;

            min_node->next = current;
            current->prev->next = min_node;
            min_node->prev = current->prev;
            current->prev = min_node;
        }
        else
            current = current->next;
    }
}

template <typename T>
void list<T>::merge(list &lst)
{
    concat_list(lst);
    sort();
}

template <typename T>
void list<T>::unique()
{
    node<T> *temp_node1 = dummy_node->next;
    node<T> *temp_node2 = nullptr;
    node<T> *delete_node = nullptr;

    while (temp_node1 != dummy_node)
    {
        temp_node2 = temp_node1->next;

        while (temp_node2 != dummy_node)
        {
            if (temp_node2->data == temp_node1->data)
            {
                delete_node = temp_node2;
                temp_node2 = temp_node2->next;

                delete_node->next->prev = delete_node->prev;
                delete_node->prev->next = delete_node->next;
                counter--;
                delete delete_node;
            }
            else
                temp_node2 = temp_node2->next;
        }
        temp_node1 = temp_node1->next;
    }
}

template <typename T>
typename list<T>::iterator find(typename list<T>::iterator start, typename list<T>::iterator end, T key)
{
    while (start != end)
    {
        if (*start == key)
            return start;
        ++start;
    }
    return start;
}

template <typename T>
void display_iterator(list<T> &lst)
{
    cout << "\nIterator display start: Linked list is:\n";
    for (typename list<T>::iterator iter = lst.begin(); iter != lst.end(); ++iter)
        cout << "<-| " << *iter << " |->";
    cout << endl;
}

template <typename T>
void printLists(list<T> list1, list<T> list2)
{
    cout << "list1: ";
    for (typename list<T>::iterator iter = list1.begin(); iter != list1.end(); ++iter)
        cout << *iter << ' ';
    cout << endl;
    cout << "list2: ";
    for (typename list<T>::iterator iter = list2.begin(); iter != list2.end(); ++iter)
        cout << *iter << ' ';
    cout << endl
         << endl;
}

int main()
{
    // Create two empty lists
    list<char> list1, list2;

    // Fill both the lists with elements
    for (int i = 0; i < 6; i++)
    {
        list1.push_back(i + 65);
        list2.push_front(i + 65);
    }

    printLists(list1, list2);

    // Insert all elements of list1 before the first element with value E of list2
    // - find() returns an iterator to the first element with value E
    list2.splice(find(list2.begin(), list2.end(), // Destination position
                      'E'),
                 list1); // Source list

    printLists(list1, list2);

    // Move first element of list2 to the end
    list2.splice(list2.end(),    // Destination position
                 list2,          // Source list
                 list2.begin()); // Source positions

    printLists(list1, list2);

    // Sort second list =, assign to list1 and remove duplicates
    list2.sort();
    list1 = list2;
    list2.unique();

    printLists(list1, list2);

    // Merge both sorted lists into the first list
    list1.merge(list2);

    printLists(list1, list2);

    return 0;
}
