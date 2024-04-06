#include "list_server.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

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
                        display_iterator(list1);

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
                        display_iterator(list1);

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