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

void printLists(list list1, list list2)
{
    cout << "list1: ";
    for (list::iterator iter = list1.begin(); iter != list1.end(); ++iter)
        cout << *iter << ' ';
    cout << endl;
    cout << "list2: ";
    for (list::iterator iter = list2.begin(); iter != list2.end(); ++iter)
        cout << *iter << ' ';
    cout << endl
         << endl;
}

int main()
{
    // Create two empty lists
    list list1, list2;

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