#include<iostream>
#include<iomanip>
#include<exception>
#include<sstream>
#include<string>
#include<time.h>
#include<stdlib.h>
using namespace std;

#ifndef MYQUEUE_H
#define MYQUEUE_H
template <typename T>
class MyQueue
{
    private:
        T *array;
        int capacity;    //Max Capacity of the Queue
        int size;        //current number of elements in the Queue
        int front;        //front of the Queue
        int rear;        //index where a new element will be added
    public:
        MyQueue();
        ~MyQueue();
        void enqueue(T);
        T dequeue();
        bool isEmpty();
        bool isFull();
        friend void display();
        friend class VFS_Tree;
        friend class Position;
};

#endif

