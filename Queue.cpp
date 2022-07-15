#include<iostream>
using namespace std;

template<class T>
struct node 
{
    T data;
    struct node *next;
};

template<class T>
class Queue
{   
    private:
        struct node<T>* Head;
        int Count;
    
    public:
        Queue();
        int CountNode();
        void Display();
        void Enqueue(T);
        void Dequeue();
};

template<class T>
Queue<T>::Queue()
{
    Head = NULL;
    Count = 0;
}

template<class T>
int Queue<T>::CountNode()
{
    return Count;
}

template<class T>
void Queue<T>::Display()
{
    struct node<T>* temp = Head;

    cout<<"Data from the Queue is : "<<endl;
    while (temp != NULL)
    {
        cout<<"|"<<temp->data<<"|->";
        temp = temp->next;
    }
    cout<<"NULL"<<endl;
}

template<class T>
void Queue<T>::Enqueue(T value)
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
void Queue<T>::Dequeue()
{
    if(Head == NULL)
    {
        cout<<"Queue is empty"<<endl;
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