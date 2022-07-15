#include<iostream>
using namespace std;

template<class T>
struct node 
{
    T data;
    struct node *next;
    struct node *prev;
};

template<class T>
class DoublyLLL
{
    private:
        struct node<T>* Head;
        int Count;
    
    public:
        DoublyLLL();
        int CountNode();
        void Display();
        void InsertFirst(T);
        void InsertLast(T);
        void InsertAtPos(T, int);
        void DeleteFirst();
        void DeleteLast();
        void DeleteAtPos(int);

};

template<class T>
DoublyLLL<T>::DoublyLLL()
{
    Head = NULL;
    Count = 0;
}

template<class T>
int DoublyLLL<T>::CountNode()
{
    return Count;
}

template<class T>
void DoublyLLL<T>::Display()
{
    struct node<T>* temp = Head;

    cout<<"Data from the Linked List is : "<<endl;
    cout<<"NULL<=>";
    while(temp != NULL)
    {
        cout<<"|"<<temp->data<<"|<=>";
        temp = temp->next;
    }
    cout<<"NULL"<<endl;
}

template<class T>
void DoublyLLL<T>::InsertFirst(T value)
{
    struct node<T>* newn = NULL;
    newn = new struct node<T>;

    newn->data = value;
    newn->next = NULL;
    newn->prev = NULL;

    if(Count == 0)
    {
        Head = newn;
    }
    else
    {
        newn->next = Head;
        Head->prev = newn;
        Head = newn;
    }
    Count++;
}

template<class T>
void DoublyLLL<T>::InsertLast(T value)
{
    struct node<T>* newn = NULL;
    newn = new struct node<T>;

    newn->data = value;
    newn->next = NULL;
    newn->prev = NULL;

    if(Count == 0)
    {
        Head = newn;
    }
    else
    {
        struct node<T>* temp = Head;
        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newn;
        newn->prev = temp;
    }
    Count++;
}

template<class T>
void DoublyLLL<T>::InsertAtPos(T value, int iPos)
{
    int size = CountNode();

    if((iPos < 1) || (iPos > size+1))
    {
        cout<<"Invalid Position"<<endl;
        return;
    }

    if(iPos == 1)
    {
        InsertFirst(value);
    }
    else if(iPos == size+1)
    {
        InsertLast(value);
    }
    else
    {
        struct node<T>* newn = NULL;
        struct node<T>* temp = Head;
        newn = new struct node<T>;

        newn->data = value;
        newn->next = NULL;
        newn->prev = NULL;

        for(int i = 1; i < iPos-1; i++)
        {
            temp = temp->next;
        }
        newn->next = temp->next;
        temp->next->prev = newn;
        temp->next = newn;
        newn->prev = temp;

        Count++;
    }
}

template<class T>
void DoublyLLL<T>::DeleteFirst()
{
    if(Count == 0)
    {
        cout<<"Linked list is empty"<<endl;
        return;
    }
    
    if(Count == 1)
    {
        delete Head;
        Head = NULL;
    }
    else
    {
        Head = Head->next;
        delete Head->prev;
        Head->prev = NULL;
    }
    Count--;
}

template<class T>
void DoublyLLL<T>::DeleteLast()
{
    if(Count == 0)
    {
        cout<<"Linked list is empty"<<endl;
        return;
    }
    
    if(Count == 1)
    {
        delete Head;
        Head = NULL;
    }
    else
    {
        struct node<T>* temp = Head;
        while(temp->next->next != NULL)
        {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = NULL;
    }
    Count--;
}

template<class T>
void DoublyLLL<T>::DeleteAtPos(int iPos)
{
    int size = CountNode();

    if((iPos < 1) || (iPos > size))
    {
        cout<<"Invalid Position"<<endl;
        return;
    }

    if(iPos == 1)
    {
        DeleteFirst();
    }
    else if(iPos == size)
    {
        DeleteLast();
    }
    else
    {
        struct node<T>* temp = Head;

        for(int i = 1; i < iPos-1; i++)
        {
            temp = temp->next;
        }
        temp->next = temp->next->next;
        delete temp->next->prev;
        temp->next->prev = temp;

        Count--;
    }
}