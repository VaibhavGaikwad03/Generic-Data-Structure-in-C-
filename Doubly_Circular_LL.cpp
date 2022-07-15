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
class DoublyCLL
{
    private:
        struct node<T>* Head;
        struct node<T>* Tail;
        int Count;

    public:
        DoublyCLL();
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
DoublyCLL<T>::DoublyCLL()
{
    Head = NULL;
    Tail = NULL;
    Count = 0;
}

template<class T>
int DoublyCLL<T>::CountNode()
{
    return Count;
}

template<class T>
void DoublyCLL<T>::Display()
{
    struct node<T>* temp = Head;

    cout<<"Data from the Linked List is : "<<endl;
    do
    {
        cout<<"|"<<temp->data<<"|<=>";
        temp = temp->next;
    }while(temp != Head);

    cout<<endl;

}

template<class T>
void DoublyCLL<T>::InsertFirst(T value)
{
    struct node<T>* newn = NULL;
    newn = new struct node<T>;

    newn->data = value;
    newn->next = NULL;
    newn->prev = NULL;

    if(Count == 0)
    {
        Head = newn;
        Tail = newn;
    }
    else
    {
        newn->next = Head;
        Head->prev = newn;
        Head = newn;
    }
    Head->prev = Tail;
    Tail->next = Head;

    Count++;
}

template<class T>
void DoublyCLL<T>::InsertLast(T value)
{
    struct node<T>* newn = NULL;
    newn = new struct node<T>;

    newn->data = value;
    newn->next = NULL;
    newn->prev = NULL;

    if(Count == 0)
    {
        Head = newn;
        Tail = newn;
    }
    else
    {
        Tail->next = newn;
        newn->prev = Tail;
        Tail = newn;
    }
    Head->prev = Tail;
    Tail->next = Head;

    Count++;
}

template<class T>
void DoublyCLL<T>::InsertAtPos(T value, int iPos)
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
        newn->next->prev = newn;
        temp->next = newn;
        newn->prev = temp;

        Count++;
    }
}

template<class T>
void DoublyCLL<T>::DeleteFirst()
{
    if(Count == 0)
    {
        cout<<"Linked List is empty"<<endl;
        return;
    }

    if(Count == 1)
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
    Head->prev = Tail;
    Tail->next = Head;

    Count--;
}   

template<class T>
void DoublyCLL<T>::DeleteLast()
{
    if(Count == 0)
    {
        cout<<"Linked List is empty"<<endl;
        return;
    }

    if(Count == 1)
    {
        delete Head;
        Head = NULL;
        Tail = NULL;
    }
    else
    {
        Tail = Tail->prev;
        delete Head->prev;
    }
    Head->prev = Tail;
    Tail->next = Head;

    Count--;
}

template<class T>
void DoublyCLL<T>::DeleteAtPos(int iPos)
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