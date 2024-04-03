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
    node *head;
    node *tail;
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
            dummy_node = new_list.dummy_node;
            new_list.dummy_node = nullptr;
            counter += new_list.counter;
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
            temp_node->next->prev = dummy_node->prev;
            new_list.dummy_node->next->prev = temp_node;
            temp_node->next = new_list.dummy_node->next;

            // new_list.tail->next = temp_node->next;
            // temp_node->next->prev = new_list.tail;
            // temp_node->next = new_list.head;
            // new_list.head->prev = temp_node;
            counter += new_list.counter;
            new_list.counter = 0;
            new_list.dummy_node->next = new_list.dummy_node->prev = new_list.dummy_node;
        }
    }

    void physical_reverse()
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

    void delete_all()
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

    friend class iterator;

    friend ostream &operator<<(ostream &out, list &lst);
};

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

void display_iterator(list &lst)
{
    cout << "\nIterator display start: Linked list is:\n";
    for (list::iterator iter = lst.begin(); iter != lst.end(); ++iter)
        cout << "<-| " << *iter << " |->";
    cout << endl;
}

int main()
{
    int flag = true, choice, result;
    int data, position, concat_position;
    list list1, list2;

    while (flag)
    {
        cout << "\n1. Insert\n2. Delete\n3. Search\n4. Count\n5. Reverse\n6. Concat\n7. Exit\n>_";
        cin >> choice;

        switch (choice)
        {
        case 1:

            while (flag)
            {
                cout << "\n1. Insert First\n2. Insert Last\n3. Insert at Position\n4. Back\n>_";
                cin >> choice;

                switch (choice)
                {
                case 1:

                    cout << "\nEnter the data: ";
                    cin >> data;

                    list1.insert_first(data);

                    display_iterator(list1);

                    break;

                case 2:

                    cout << "\nEnter the data: ";
                    cin >> data;

                    list1.insert_last(data);

                    display_iterator(list1);

                    break;

                case 3:

                    cout << "\nEnter the position: ";
                    cin >> position;

                    if (position < 1 || position > list1.count_nodes() + 1)
                    {
                        cout << "\nInvalid position.\n";
                        break;
                    }

                    cout << "\nEnter the data: ";
                    cin >> data;

                    list1.insert_at_position(data, position);

                    display_iterator(list1);

                    break;

                case 4:
                    flag = false;
                    break;

                default:
                    cout << "\nInvalid choice.\n";
                }
            }

            flag = true;

            break;

        case 2:

            if (list1.is_empty())
            {
                cout << "\nList is empty.\n";
                break;
            }

            while (flag)
            {
                cout << "\n1. Delete First\n2. Delete Last\n3. Delete at Position\n4. Back\n>_";
                cin >> choice;

                switch (choice)
                {
                case 1:

                    result = list1.delete_first();

                    if (result == -1)
                    {
                        cout << "\nList is empty.\n";
                        break;
                    }

                    cout << "\nDeleted data from the list is: " << result << endl;

                    if (list1.is_empty())
                        cout << "\nList is empty.\n";
                    else
                    {
                        display_iterator(list1);
                        list1.reverse_display();
                    }
                    break;

                case 2:

                    result = list1.delete_last();

                    if (result == -1)
                    {
                        cout << "\nList is empty.\n";
                        break;
                    }

                    cout << "\nDeleted data from the list is: " << result << endl;

                    if (list1.is_empty())
                        cout << "\nList is empty.\n";
                    else
                    {
                        display_iterator(list1);
                        list1.reverse_display();
                    }

                    break;

                case 3:

                    if (list1.is_empty())
                    {
                        cout << "\nList is empty.\n";
                        break;
                    }

                    cout << "\nEnter the position: ";
                    cin >> position;

                    if (position < 1 || position > list1.count_nodes())
                    {
                        cout << "\nInvalid position.\n";
                        break;
                    }

                    cout << "\nDeleted data from the list is: " << list1.delete_at_position(position) << endl;

                    if (list1.is_empty())
                        cout << "\nList is empty.\n";
                    else
                    {
                        display_iterator(list1);
                        list1.reverse_display();
                    }

                    break;

                case 4:

                    flag = false;

                    break;

                default:
                    cout << "\nInvalid choice.\n";
                }
            }

            flag = true;

            break;

        case 3:

            if (list1.is_empty())
            {
                cout << "\nList is empty.\n";
                break;
            }

            while (flag)
            {
                cout << "\n1. Search First Occurrence\n2. Search Last Occurrence\n3. Search All Occurrences\n4. Back\n>_";
                cin >> choice;

                if (choice >= 1 && choice <= 3)
                {
                    cout << "\nEnter the key to search: ";
                    cin >> data;
                }

                switch (choice)
                {
                case 1:

                    result = list1.search_first_occurrence(data);

                    if (result == -2)
                        cout << "\nKey not found.\n";
                    else
                        cout << "\nKey " << data << " first occurred at position: " << result << endl;

                    break;

                case 2:

                    result = list1.search_last_occurrence(data);

                    if (result == -2)
                        cout << "\nKey not found.\n";
                    else
                        cout << "\nKey " << data << " last occurred at position: " << result << endl;

                    break;

                case 3:

                    result = list1.search_all_occurrence(data);

                    cout << "\nKey " << data << " occurred " << result << " times.\n";

                    break;

                case 4:

                    flag = false;

                    break;

                default:
                    cout << "\nInvalid choice.\n";
                }
            }

            flag = true;

            break;

        case 4:

            cout << "\nCount of nodes is: " << list1.count_nodes() << endl;

            break;

        case 5:

            if (list1.is_empty())
            {
                cout << "\nList is empty.\n";
                break;
            }

            while (flag)
            {
                cout << "\n1. Physical Reverse\n2. Display Reverse\n3. Back\n>_";
                cin >> choice;

                switch (choice)
                {
                case 1:

                    list1.physical_reverse();

                    display_iterator(list1);

                    break;

                case 2:

                    cout << "\nReversed list is: ";
                    list1.reverse_display();

                    break;

                case 3:

                    flag = false;

                    break;

                default:
                    cout << "\nInvalid choice.\n";
                }
            }

            flag = true;

            break;

        case 6:

            while (flag)
            {
                cout << "\n1. Concat List\n2. Concat at Position\n3. Back\n>_";
                cin >> choice;

                switch (choice)
                {
                case 1:

                    while (flag)
                    {
                        cout << "\n1. Insert First\n2. Insert Last\n3. Insert at Position\n4. Concat & Back\n>_";
                        cin >> choice;

                        switch (choice)
                        {
                        case 1:

                            cout << "\nEnter the data: ";
                            cin >> data;

                            list2.insert_first(data);

                            display_iterator(list2);

                            break;

                        case 2:

                            cout << "\nEnter the data: ";
                            cin >> data;

                            list2.insert_last(data);

                            display_iterator(list2);

                            break;

                        case 3:

                            cout << "\nEnter the position: ";
                            cin >> position;

                            if (position < 1 || position > list2.count_nodes() + 1)
                            {
                                cout << "\nInvalid position.\n";
                                break;
                            }

                            cout << "\nEnter the data: ";
                            cin >> data;

                            list2.insert_at_position(data, position);

                            display_iterator(list2);

                            break;

                        case 4:

                            list1.concat_list(list2);

                            if (list1.is_empty())
                                cout << "\nList is empty.\n";
                            else
                                display_iterator(list1);

                            flag = false;

                            break;

                        default:
                            cout << "\nInvalid choice.\n";
                        }
                    }

                    flag = true;

                    break;

                case 2:

                    cout << "\nEnter the postion: ";
                    cin >> concat_position;

                    if (concat_position < 1 || concat_position > list1.count_nodes() + 1)
                    {
                        cout << "\nInvalid position.\n";
                        break;
                    }

                    while (flag)
                    {
                        cout << "\n1. Insert First\n2. Insert Last\n3. Insert at Position\n4. Concat & Back\n>_";
                        cin >> choice;

                        switch (choice)
                        {
                        case 1:

                            cout << "\nEnter the data: ";
                            cin >> data;

                            list2.insert_first(data);

                            display_iterator(list2);

                            break;

                        case 2:

                            cout << "\nEnter the data: ";
                            cin >> data;

                            list2.insert_last(data);

                            display_iterator(list2);

                            break;

                        case 3:

                            cout << "\nEnter the position: ";
                            cin >> position;

                            if (position < 1 || position > list2.count_nodes() + 1)
                            {
                                cout << "\nInvalid position.\n";
                                break;
                            }

                            cout << "\nEnter the data: ";
                            cin >> data;

                            list2.insert_at_position(data, position);

                            display_iterator(list2);

                            break;

                        case 4:

                            list1.concat_at_position(list2, concat_position);

                            if (list1.is_empty())
                                cout << "\nList is empty.\n";
                            else
                                display_iterator(list1);

                            flag = false;

                            break;

                        default:
                            cout << "\nInvalid choice.\n";
                        }
                    }

                    flag = true;

                    break;

                case 3:

                    flag = false;

                    break;

                default:
                    cout << "\nInvalid choice.\n";
                }
            }

            flag = true;

            break;

        case 7:

            list1.delete_all();

            flag = false;

            break;

        default:
            cout << "\nInvalid choice.\n";
        }
    }

    cout << "\nThank You!\n";

    return 0;
}