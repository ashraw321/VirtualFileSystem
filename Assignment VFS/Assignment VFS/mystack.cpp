//
//  mystack.cpp
//  Assignment VFS
//
//  Created by Ashish Rawat on 19/04/23.
//

#include "mystack.hpp"
template <typename T> MyStack<T>::MyStack()
{
    top = -1;
    capacity = SIZE;
    st = new T[capacity];
    count = 0;
}
template <typename T> MyStack<T>::~MyStack(){
    delete [] st;
}
template <typename T> bool MyStack<T>::isFull()
{
    if (count ==capacity-1)
        return 1;
    else
        return 0;
}
template <typename T>void MyStack<T>::push(T k)
{
    if (isFull())
    {
        T* temp = new T[2*capacity];
        for (int i = 0; i < capacity; i++) {
            temp[i] = st[i];
        }
        capacity=2*capacity;
        delete[] st;
        st = temp;
        delete[] temp;
        
    }
        top = top + 1;
        count++;
        st[top] = k;
}

template <typename T> T MyStack<T>::pop()
{
    T popped_element = st[top];

    top--;
    count--;

    return popped_element;
}
template <typename T> T MyStack<T>::topElement()
{
    T top_element = st[top];

    return top_element;
}


template <typename T> bool MyStack<T>::isEmpty()
{
if (top == -1)
    return true;
else
    return false;
}

template <typename T> int MyStack<T>::size()
{
    return count;
}
template <typename T> void MyStack<T>::printStack()
{
   cout<<"/";
   int i=0;
   for(;i<top;i++)
   {
       cout<<st[i];
       cout<<"/";
   }
   cout<<st[top]<<"\n";
   return;
}
