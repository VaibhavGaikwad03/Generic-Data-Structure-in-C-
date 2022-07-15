#include<iostream>
using namespace std;

template<class T>
struct node
{
    T data;
    struct node *next;
};

template<class T>
class Stack
{
    private:
        struct node<T>* Head;
        int Count;

    public:
        Stack();
        int CountNode();
        void Display();
        void Push(T);
        void Pop();
};

template<class T>
Stack<T>::Stack()
{
    Head = NULL;
    Count = 0;
}

template<class T>
int Stack<T>::CountNode()
{
    return Count;
}

template<class T>
void Stack<T>::Display()
{
    struct node<T>* temp = Head;

    cout<<"Data from the stack is : "<<endl;
    while (temp != NULL)
    {
        cout<<"|"<<temp->data<<"|->";
        temp = temp->next;
    }
    cout<<"NULL"<<endl;
    
}

template<class T>
void Stack<T>::Push(T value)
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
void Stack<T>::Pop()
{
    if(Head == NULL)
    {
        cout<<"Stack is empty"<<endl;
        return;
    }

    if(Head->next == NULL)
    {
        delete Head;
        Head = NULL;
    }
    else
    {
        struct node<T>* temp = Head;

        Head = Head->next;
        delete temp;
    }
    Count--;
}