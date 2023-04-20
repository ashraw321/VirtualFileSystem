#include "myvector.hpp"
#include "vfs_tree.hpp"
#include "inode.hpp"

using namespace std;

/* template <typename T>
void MyVector<T>::display()
{
    cout<<"+";
    
    for(int i=0; i<v_capacity; i++)
    {
        cout<<"----";
        if(i!=v_capacity-1) cout<<"+";
    }
    cout<<"+ size = "<<v_size<<endl;
    
    for(int i=0; i<v_capacity; i++)
    {
        cout<<"|";
        if(i<v_size)
            cout<<setw(4)<<data[i];
        else
            cout<<setw(4)<<" ";
    }
    if(v_capacity==0) cout<<"|";
    cout<<"|"<<endl<<"+";
    for(int i=0; i<v_capacity; i++)
    {
        cout<<"----";
        if(i != v_capacity-1) cout<<"+";
    }
    cout<<"+ capacity = "<<v_capacity<<endl;
} */

template <typename T>
MyVector<T> ::MyVector(int cap)
{
    v_size = 0;
    v_capacity = cap;
    //data = new T[v_capacity];
}

template <typename T>
MyVector<T> :: ~MyVector()
{
    delete[] data;
}

template <typename T>
void MyVector<T> :: push_back(T element)
{
    if(v_size == v_capacity)
    {
        if(v_capacity == 0)
        {
            v_capacity = 1;
        }
        else
        {
            v_capacity = v_capacity * 2;
        }
        //T* newData = new T[v_capacity];
        T* newData;
        for(int i = 0; i < v_size; i++)
        {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }
    data[v_size] = element;
    v_size++;
}

template <typename T>
void MyVector<T> :: insert(int index, T element)
{
    if (index < 0 || index > v_size-1)
    {
        throw out_of_range("Index is out of range");
    }

    if (v_size == v_capacity)
    {
        if (v_capacity == 0)
        {
            v_capacity = 1;
        }
        else
        {
            v_capacity = v_capacity * 2;
        }
        //T* newData = new T[v_capacity];
        T* newData;
        for (int i = 0; i < index; i++)
        {
            newData[i] = data[i];
        }
        newData[index] = element;
        for (int i = index; i < v_size; i++)
        {
            newData[i+1] = data[i];
        }
        delete[] data;
        data = newData;
    }
    else
    {
        for (int i = v_size-1; i >= index; i--)
        {
            data[i+1] = data[i];
        }
        data[index] = element;
    }
    v_size++;
}

template <typename T>
void MyVector<T> :: erase(int index)
{
    if (index < 0 || index > v_size-1)
    {
        throw out_of_range("Index is out of range");
    }
    for (int i = index; i < v_size-1; i++)
    {
        data[i] = data[i+1];
    }
    v_size--;
}

template <typename T>
T& MyVector<T> :: at(int index)
{
    if (index < 0 || index > v_size-1)
    {
        throw out_of_range("Index out of range");
    }
    return data[index];
}

template <typename T>
const T& MyVector<T> :: front()
{
    if (v_size == 0)
    {
        throw out_of_range("Vector is empty");
    }
    else
    {
        return data[0];
    }
}

template <typename T>
const T& MyVector<T> :: back()
{
    if (v_size == 0)
    {
        throw out_of_range("Vector is empty");
    }
    return data[v_size - 1];
}

template <typename T>
int MyVector<T> :: size() const
{
    return v_size;
}

template <typename T>
int MyVector<T> :: capacity() const
{
    return v_capacity;
}

template <typename T>
void MyVector<T> :: shrink_to_fit()
{
    if (v_size < v_capacity)
    {
        //T* newData = new T[v_size];
        T* newData;
        for (int i = 0; i < v_size; i++)
        {
            newData[i] = data[i];
        }
        v_capacity = v_size;
        delete[] data;
        data = newData;
    }
}

template <typename T>
bool MyVector<T> :: empty() const
{
    // cout << "vector size = " << v_size << endl;
    return v_size == 0;
}



