#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::ostream;

class list;

class iterator;

ostream &operator<<(ostream &out, list &lst);

class node
{
    node *prev;
    int data;
    node *next;

    node()
    {
        data = 0;
        prev = next = nullptr;
    }

    ~node()
    {
        data = 0;
        prev = next = nullptr;
    }

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

        void set_current_node(node *set_node)
        {
            current_node = set_node;
        }
        ///////////////////////////////////////////
        node *get_current_node()
        {
            return current_node;
        }
        ///////////////////////////////////////////
    public:
        iterator()
        {
            current_node = nullptr;
        }

        ~iterator()
        {
            current_node = nullptr;
        }

        bool operator==(iterator &iter)
        {
            return (current_node == iter.current_node);
        }

        bool operator!=(iterator &iter)
        {
            return (current_node != iter.current_node);
        }

        bool operator!=(const iterator &iter) const // New function for const
        {
            return (current_node != iter.current_node);
        }

        int operator*()
        {
            return (current_node->data);
        }

        iterator &operator++()
        {
            current_node = current_node->next;
            return *this;
        }

        iterator operator++(int)
        {
            iterator iter;
            iter.set_current_node(current_node);
            current_node = current_node->next;
            return iter;
        }

        iterator &operator--()
        {
            current_node = current_node->prev;
            return *this;
        }

        iterator operator--(int)
        {
            iterator iter;
            iter.set_current_node(current_node);
            current_node = current_node->prev;
            return iter;
        }

        friend class list;
    };

private:
    iterator start_iter;
    iterator end_iter;

public:
    list()
    {
        counter = 0;
        dummy_node = nullptr;
        dummy_node = new node;
        if (dummy_node == nullptr)
            return;
        dummy_node->next = dummy_node;
        dummy_node->prev = dummy_node;
    }

    //////////////////////////////////////////////////
    list(list &lst)
    {
        node *temp_node = nullptr;

        this->dummy_node = new node;
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
    //////////////////////////////////////////////////

    ~list()
    {
        if (dummy_node->next != dummy_node)
            delete_all();
        delete dummy_node;
        dummy_node = nullptr;
    }

    int count_nodes() const
    {
        return counter;
    }

    bool is_empty() const
    {
        return (counter == 0);
    }

    void reverse_display() const
    {
        node *temp_node = dummy_node->prev;

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

    void insert_first(int data)
    {
        node *new_node = nullptr;

        new_node = new node;
        if (new_node == nullptr)
            return;

        new_node->data = data;

        new_node->next = dummy_node->next;
        new_node->next->prev = new_node;
        dummy_node->next = new_node;
        new_node->prev = dummy_node;

        counter++;
    }

    void insert_last(int data)
    {
        node *new_node = nullptr;

        new_node = new node;
        if (new_node == nullptr)
            return;

        new_node->data = data;

        new_node->prev = dummy_node->prev;
        new_node->prev->next = new_node;
        new_node->next = dummy_node;
        dummy_node->prev = new_node;

        counter++;
    }

    void insert_at_position(int data, int pos)
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

    int delete_first()
    {
        int deleted_data;
        node *temp_delete = nullptr;

        if (counter == 0) /* dummy_node->next == dummy_node */
            return -1;

        deleted_data = dummy_node->next->data;

        dummy_node->next = dummy_node->next->next;
        delete dummy_node->next->prev;
        dummy_node->next->prev = dummy_node;

        counter--;
        return deleted_data;
    }

    int delete_last()
    {
        int deleted_data;
        node *temp_delete = nullptr;

        if (counter == 0) /* dummy_node->next == dummy_node */
            return -1;

        deleted_data = dummy_node->prev->data;

        dummy_node->prev = dummy_node->prev->prev;
        delete dummy_node->prev->next;
        dummy_node->prev->next = dummy_node;

        counter--;
        return deleted_data;
    }

    int delete_at_position(int pos)
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

    int search_first_occurrence(int key) const
    {
        int i, position = 1;
        node *temp_node = dummy_node->next;

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

    int search_last_occurrence(int key) const
    {
        node *temp_node = dummy_node->next;
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

    int search_all_occurrence(int key) const
    {
        int i, count_occ = 0;
        node *temp_node = dummy_node->next;

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

    void concat_list(list &new_list)
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

    void concat_at_position(list &new_list, int pos)
    {
        int i;
        node *temp_node = nullptr;

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

    void physical_reverse()
    {
        node *current = dummy_node;
        node *next = nullptr;

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

    void delete_all()
    {
        node *temp_delete = nullptr;
        node *temp_node = dummy_node->next;

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

    iterator &begin()
    {
        start_iter.set_current_node(dummy_node->next);
        return start_iter;
    }

    iterator &end()
    {
        end_iter.set_current_node(dummy_node);
        return end_iter;
    }

    ///////////////////////////////////////////////////////////

    list &operator=(const list &lst) // Implement this later
    {
        int lcnt;
        node *dest_node = nullptr;
        node *src_node = nullptr;

        if (this->counter == 0) // First list is empty
        {
            cout << "Empty\n";
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

        if (this->counter < lst.counter)
        {
            cout << "Less\n";

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
        else if (this->counter > lst.counter)
        {
            cout << "More\n";

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
        else
        {
            cout << "Equal\n";

            for (int lcnt = 0; lcnt < this->counter; lcnt++)
            {
                dest_node->data = src_node->data;
                dest_node = dest_node->next;
                src_node = src_node->next;
            }
        }

        // this->dummy_node = new node;
        // node *temp_node = lst.dummy_node->next;

        // this->counter = lst.counter;
        // if (this->counter != 0) // If
        //     this->counter = 0;

        // this->dummy_node->prev = this->dummy_node->next = this->dummy_node;

        // for (int i = 0; i < lst.counter; i++)
        // {
        //     this->insert_last(temp_node->data);
        //     temp_node = temp_node->next;
        // }
        return *this;
    }

    void push_front(int data)
    {
        insert_first(data);
    }

    void push_back(int data)
    {
        insert_last(data);
    }

    void splice(iterator position, list &lst)
    {
        node *temp_node = position.get_current_node();

        temp_node->prev->next = lst.dummy_node->next;
        lst.dummy_node->next->prev = temp_node->prev;
        lst.dummy_node->prev->next = temp_node;
        temp_node->prev = lst.dummy_node->prev;

        counter += lst.counter;

        lst.counter = 0;
        lst.dummy_node->prev = lst.dummy_node->next = lst.dummy_node;
    }

    void splice(iterator dest_pos, list &lst, iterator src_pos)
    {
        node *temp_node = src_pos.get_current_node();

        
    }

    void merge(list &lst)
    {
        this->concat_list(lst);
    }

    ///////////////////////////////////////////////////////////

    friend class iterator;
    friend ostream &operator<<(ostream &out, list &lst);
};

ostream &operator<<(ostream &out, list &lst)
{
    node *temp_node = lst.dummy_node->next;

    if (temp_node == nullptr)
        return out;

    do
    {
        out << temp_node->data << ' ';
        temp_node = temp_node->next;
    } while (temp_node != lst.dummy_node->next);

    return out;
}

void display_iterator(list lst)
{
    cout << "\nIterator display start: Linked list is:\n";
    for (list::iterator iter = lst.begin(); iter != lst.end(); ++iter)
        cout << "<-| " << *iter << " |->";
    cout << endl;
}

void printLists(list list1, list list2)
{
    cout << "list1: ";
    for (list::iterator iter = list1.begin(); iter != list1.end(); ++iter)
        cout << *iter << ' ';
    cout << endl;
    cout << "list2: ";
    for (list::iterator iter = list2.begin(); iter != list2.end(); ++iter)
        cout << *iter << ' ';
    cout << endl;
}

list::iterator find(list::iterator start, list::iterator end, int key)
{
    while (start != end)
    {
        if (*start == key)
            return start;
        ++start;
    }
    return start;
}

/*int main()
{
    list ls1, ls2;
    ls1.push_back(60);
    ls1.push_back(70);
    ls1.push_back(80);
    ls1.push_back(90);
    ls1.push_back(100);

    ls2.push_back(10);
    ls2.push_back(20);
    ls2.push_back(30);
    ls2.push_back(40);
    ls2.push_back(50);

    printLists(ls1, ls2);
    cout << ls1.count_nodes() << endl
         << ls2.count_nodes() << endl;

    ls1 = ls2;

    printLists(ls1, ls2);
    cout << ls1.count_nodes() << endl
         << ls2.count_nodes() << endl;

    return 0;
}*/

int main()
{
    int a = 10;

    // Create two empty lists
    list list1, list2, list3;

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
                      69),
                 list1); // Source list

    printLists(list1, list2);

    // Move first element of list2 to the end
    // list2.splice(list2.end(),    // Destination position
    //              list2,          // Source list
    //              list2.begin()); // Source positions

    // printLists(list1, list2);

    // Merge both sorted lists into the first list
    list1.merge(list2);

    printLists(list1, list2);

    return 0;
}