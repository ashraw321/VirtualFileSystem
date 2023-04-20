//
//  mystack.hpp
//  Assignment VFS
//
//  Created by Ashish Rawat on 19/04/23.
//
 /* mystack_hpp */
//
//  mystack.h
//  VFS
//
//  Created by Ashish Rawat on 19/04/23.
//

//  mystack.h
//  VIrtual_File_System
//
//  Created by Ashish Rawat on 15/04/23.
//

#ifndef mystack_h
#define mystack_h
#include <iostream>
#include <string>

using namespace std;

#define SIZE 1

template <typename T> class MyStack {
private:
    
    int top;
    int count;
    int capacity;
    string* st;
public:
    MyStack();
    ~MyStack();
    bool isFull();
    void push(T k);

    T pop();
    T topElement();

    
    bool isEmpty();

    int size();
    void printStack();
};











#endif /* mystack_h */


