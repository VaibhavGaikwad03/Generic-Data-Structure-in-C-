#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::ostream;

// template <typename T>
// class node;

template <typename T>
class list;

template <typename T>
ostream &operator<<(ostream &out, const list<T> &lst);

template <typename T>
class node
{
    node *next;
    T data;
    node *prev;

    node();
    ~node();

    friend class list<T>;

    friend ostream &operator<< <T>(ostream &out, const list<T> &lst);
};

template <typename T>
class list
{
    node<T> *head;
    node<T> *tail;
    int counter;

public:
    list();
    ~list();
    bool is_empty();
    int count_nodes() const;
    void display() const;
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
    void reverse_display() const;
    void physical_reverse();
    void delete_all();

    friend ostream &operator<< <T>(ostream &out, const list &lst);
};

template <typename T>
ostream &operator<<(ostream &out, const list<T> &lst)
{
    node<T> *temp_node = lst.head;

    if (temp_node == nullptr)
        return out;

    do
    {
        out << temp_node->data << ' ';
        temp_node = temp_node->next;
    } while (temp_node != lst.head);

    return out;
}

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
list<T>::list()
{
    counter = 0;
    head = tail = nullptr;
}

template <typename T>
list<T>::~list()
{
    if (head != nullptr)
        delete_all();
}

template <typename T>
int list<T>::count_nodes() const
{
    return counter;
}

template <typename T>
bool list<T>::is_empty()
{
    if (head == nullptr)
        return true;
    return false;
}

template <typename T>
void list<T>::display() const
{
    node<T> *temp_node = head;

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

template <typename T>
void list<T>::reverse_display() const
{
    node<T> *temp_node = tail;

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

template <typename T>
void list<T>::insert_first(T data)
{
    node<T> *new_node = nullptr;

    new_node = new node<T>;
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

template <typename T>
void list<T>::insert_last(T data)
{
    node<T> *new_node = nullptr;

    new_node = new node<T>;
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

template <typename T>
T list<T>::delete_first()
{
    int deleted_data;
    node<T> *temp_delete = nullptr;

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

template <typename T>
T list<T>::delete_last()
{
    int deleted_data;
    node<T> *temp_delete = nullptr;

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

template <typename T>
T list<T>::delete_at_position(int pos)
{
    int i, deleted_data;
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

template <typename T>
int list<T>::search_first_occurrence(T key) const
{
    int i, position = 1;
    node<T> *temp_node = head;

    if (head == nullptr)
        return -1;

    for (i = 1; i <= counter; i++)
    {
        if (temp_node->data == key)
            return position;
        position++;
        temp_node = temp_node->next;
    }
    return -1;
}

template <typename T>
int list<T>::search_last_occurrence(T key) const
{
    node<T> *temp_node = head;
    int i, position = 1, ret_position = -1;

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

template <typename T>
int list<T>::search_all_occurrence(T key) const
{
    int i, count_occ = 0;
    node<T> *temp_node = head;

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

template <typename T>
void list<T>::concat_list(list<T> &new_list)
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

template <typename T>
void list<T>::concat_at_position(list<T> &new_list, int pos)
{
    int i;
    node<T> *temp_node = nullptr;

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

template <typename T>
void list<T>::physical_reverse()
{
    node<T> *current = head;
    node<T> *next = nullptr;

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

template <typename T>
void list<T>::delete_all()
{
    node<T> *temp_node = head;

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

int main()
{
    int flag = true, choice, result;
    int data, position, concat_position;
    list<int> list1;
    list<int> list2;

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

                    cout << "\nList is: " << list1 << endl;

                    break;

                case 2:

                    cout << "\nEnter the data: ";
                    cin >> data;

                    list1.insert_last(data);

                    cout << "\nList is: " << list1 << endl;

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

                    cout << "\nList is: " << list1 << endl;

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
                        cout << "\nList is: " << list1 << endl;

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
                        cout << "\nList is: " << list1 << endl;

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
                        cout << "\nList is: " << list1 << endl;

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

                    cout << "\nList after physical reverse: " << list1 << endl;

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

                            cout << "\nList is: " << list2 << endl;

                            break;

                        case 2:

                            cout << "\nEnter the data: ";
                            cin >> data;

                            list2.insert_last(data);

                            cout << "\nList is: " << list2 << endl;

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

                            cout << "\nList is: " << list2 << endl;

                            break;

                        case 4:

                            list1.concat_list(list2);

                            if (list1.is_empty())
                                cout << "\nList is empty.\n";
                            else
                                cout << "\nList is: " << list1 << endl;

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

                            cout << "\nList is: " << list2 << endl;

                            break;

                        case 2:

                            cout << "\nEnter the data: ";
                            cin >> data;

                            list2.insert_last(data);

                            cout << "\nList is: " << list2 << endl;

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

                            cout << "\nList is: " << list2 << endl;

                            break;

                        case 4:

                            list1.concat_at_position(list2, concat_position);

                            if (list1.is_empty())
                                cout << "\nList is empty.\n";
                            else
                                cout << "\nList is: " << list1 << endl;

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