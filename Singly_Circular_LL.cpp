#include<iostream>
using namespace std;

template<class T>
struct node 
{
    T data;
    struct node *next;
};

template<class T>
class SinglyCLL
{
    private:
        struct node<T>* Head;
        struct node<T>* Tail;
        int Count;
    
    public:
        SinglyCLL();
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
SinglyCLL<T>::SinglyCLL()
{
    Head = NULL;
    Tail = NULL;
    Count = 0;
}

template<class T>
int  SinglyCLL<T>::CountNode()
{
    return Count;
}

template<class T>
void SinglyCLL<T>::Display()
{   
    struct node<T>* temp = Head;
    cout<<"Data from Linked List is : "<<endl;
    do
    {
        cout<<"|"<<temp->data<<"|->";
        temp = temp->next;
    }while (temp != Head);

    cout<<"NULL"<<endl;
}

template<class T>
void SinglyCLL<T>::InsertFirst(T value)
{
    struct node<T>* newn = NULL;
    newn = new struct node<T>;

    newn->data = value;
    newn->next = NULL;

    if((Head == NULL) || (Tail == NULL))
    {
        Head = newn;
        Tail = newn;
    }
    else
    {
        newn->next = Head;
        Head = newn;
    }
    Tail->next = Head;

    Count++;
}

template<class T>
void SinglyCLL<T>::InsertLast(T value)
{
    struct node<T>* newn = NULL;
    newn = new struct node<T>;

    newn->data = value;
    newn->next = NULL;

    if((Head == NULL) || (Tail == NULL))
    {
        Head = newn;
        Tail = newn;
    }
    else
    {
        Tail->next = newn;
        Tail = newn;
    }
    Tail->next = Head;

    Count++;
}

template<class T>
void SinglyCLL<T>::InsertAtPos(T value, int iPos)
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
void SinglyCLL<T>::DeleteFirst()
{
    if((Head == NULL) || (Tail == NULL))
    {
        cout<<"Linked List is empty"<<endl;\
        return;
    }

    if(Head->next == Tail)
    {
        delete Head;
        Head = NULL;
        Tail = NULL;
    }
    else
    {
        Head = Head->next;
        delete Tail->next;
    }
    Tail->next = Head;

    Count--;
}

template<class T>
void SinglyCLL<T>::DeleteLast()
{
    if((Head == NULL) || (Tail == NULL))
    {
        cout<<"Linked List is empty"<<endl;\
        return;
    }

    if(Head->next == Tail)
    {
        delete Head;
        Head = NULL;
        Tail = NULL;
    }
    else
    {
        struct node<T>* temp = Head;

        while (temp->next->next != Head)
        {
            temp = temp->next;
        }
        delete temp->next;
        Tail = temp;
    }
    Tail->next = Head;

    Count--;
}

template<class T>
void SinglyCLL<T>::DeleteAtPos(int iPos)
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
        struct node<T>* tempdelete = NULL;

        for(int i = 1; i < iPos-1; i++)
        {
            temp = temp->next;
        }
        tempdelete = temp->next;
        temp->next = temp->next->next;
        delete tempdelete;

        Count--;
    }   
}