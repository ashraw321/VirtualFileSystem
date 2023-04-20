#include "myqueue.hpp"
#include "vfs_tree.hpp"

using namespace std;

template<typename T> MyQueue<T>::MyQueue()
{
    capacity = 20;
    size = 0;
    front = 0;
    rear = -1;
    array = new T[capacity];
}
template<typename T> MyQueue<T>::~MyQueue()
{
    delete[] array;
}
//===========================================
template<typename T> void MyQueue<T>::enqueue(T element)
{
    if (isFull())
    {
        stringstream ss;
        ss << "Error: Queue is full";
        throw runtime_error(ss.str());
        // throw exception(ss.str().c_str());
    }
    
    rear = (rear + 1) % capacity;
    array[rear] = element;
    size++;
}
//===========================================
template<typename T> T MyQueue<T>::dequeue()
{
    if (isEmpty())
    {
        stringstream ss;
        ss << "Error: Queue is empty";
        throw runtime_error(ss.str());
        // throw exception(ss.str().c_str());
    }

    T element = array[front];
    front = (front + 1) % capacity;
    size--;
    return element;

}
//===========================================
template<typename T> bool MyQueue<T>::isEmpty()
{
    if (size != 0)
    {
        return false;
    }
    return true;
}
//===========================================
template<typename T> bool MyQueue<T>::isFull()
{
    return size == capacity;
}

