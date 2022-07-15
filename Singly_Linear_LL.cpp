#include<iostream>
using namespace std;

template<class T>
struct node 
{
    T data;
    struct node *next;
};

template<class T>
class SinglyLLL
{
    private:
        struct node<T>*Head;
        int Count;

    public:
        SinglyLLL();
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
SinglyLLL<T>::SinglyLLL()
{
    Head = NULL;
    Count = 0;
}

template<class T>
int  SinglyLLL<T>::CountNode()
{
    return Count;
}

template<class T>
void SinglyLLL<T>::Display()
{   
    struct node<T>* temp = Head;
    cout<<"Data from Linked List is : "<<endl;
    while(temp != NULL)
    {
        cout<<"|"<<temp->data<<"|->";
        temp = temp->next;
    }
    cout<<"NULL"<<endl;
}

template<class T>
void SinglyLLL<T>::InsertFirst(T value)
{
    struct node<T>* newn = NULL;
    newn = new struct node<T>;

    newn->data = value;
    newn->next = NULL;

    if(Head == NULL)
    {
        Head = newn;
    }
    else
    {
        newn->next = Head;
        Head = newn;
    }
    Count++;
}

template<class T>
void SinglyLLL<T>::InsertLast(T value)
{
    struct node<T>* newn = NULL;
    newn = new struct node<T>;

    newn->data = value;
    newn->next = NULL;

    if(Head == NULL)
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
    }
    Count++;
}

template<class T>
void SinglyLLL<T>::InsertAtPos(T value, int iPos)
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
        newn = new struct node<T>;
        
        newn->data = value;
        newn->next = NULL;

        struct node<T>* temp = Head;

        for(int i = 1; i < iPos-1; i++)
        {
            temp = temp->next;
        }
        newn->next = temp->next;
        temp->next = newn;
        Count++;
    }
}

template<class T>
void SinglyLLL<T>::DeleteFirst()
{
    if(Head == NULL)
    {
        cout<<"Linked list is empty"<<endl;
        return;
    }

    struct node<T>* temp = Head;

    Head = Head->next;
    delete temp;

    Count--;
}

template<class T>
void SinglyLLL<T>::DeleteLast()
{
    if(Head == NULL)
    {
        cout<<"Linked list is empty"<<endl;
        return;
    }

    struct node<T>* temp = Head;

    while (temp->next->next != NULL)
    {
        temp = temp->next;
    }
    delete(temp->next);
    temp->next = NULL;
    Count--;
}

template<class T>
void SinglyLLL<T>::DeleteAtPos(int iPos)
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
        struct node<T>* tempdelete = temp->next;
        temp->next = temp->next->next;
        delete tempdelete;

        Count--;
    }
}