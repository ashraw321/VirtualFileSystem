//
//  inode.cpp
//  Assignment VFS
//
//  Created by Ashish Rawat on 19/04/23.
//

#include "inode.hpp"
//============================================================================
// Name         : DS Assignment#2
// Author       : Mai Oudah
// Version      : 2.0
// Date Created : 01-04-2023
// Date Modified:
// Description  : Virtual Filesystem - iNode class
//============================================================================
#ifndef inode_h
#define inode_h

#include<iostream>
#include<string>
#include <ctime>
#include <vector>
//#include "myvector.h" //create this header file where you define the vector class

using namespace std;

void Inode::setName(string name)// returns whether if it is a file or folder true if it is file and false otherwise
{
    if(name=="")
    {
        this->fname="" ;
        return;
    }
    
    int dot_count=1;
    char ch=name[0];
    if(!((ch>='A'&&ch<='Z')||(ch>='0'&&ch<='9')||(ch>='a'&&ch<='z')))
    {
        throw exception();
    }
    for(int i=1;i<name.length();i++)
    {
        if(name[i]=='.')
        {
            dot_count--;
            if(dot_count<0)
            {
                throw exception();
            }
        }
        else if(!((ch>='A'&&ch<='Z')||(ch>='0'&&ch<='9')||(ch>='a'&&ch<='z')))
        {
            throw exception();
        }
        
        
    }
    this->fname=name;
    if(dot_count==1)
        this->setisFile(false);
    else this->setisFile(true);
    return;

}
void Inode::setFsize(int fSize)
{
    size=fSize;
}
 
void Inode::setDate(string date)
{
    this->date=date;
    return;
}

void Inode::setisFile(bool isFile)
{
    this->isFile=isFile;
    return;
}
void Inode::setParent(Inode* parent)
{
    this->parent=parent;
    return ;
}
string Inode::getName()
{
    return fname;
}
void Inode::setChildren(vector<Inode*> children)
{
    this->children=children;
    return;
}
int Inode::getFsize()
{
    return size;
}
bool Inode::getisFile()
{
    return isFile;
}
string Inode::getDate()
{
    return date;
}

Inode* Inode::getParent()
{
    return parent;
}
vector<Inode*> Inode::getchildren()
{
    return children;
}
Inode::Inode(string name, int fSize, bool isFile, string date)
{
    setName(name);
    setFsize(fSize);
    setDate(date);
}
void Inode::delete_child(int it)
{
    children[it]=children[children.size()-1];
    children.pop_back();
    return;
}
void Inode::add_child(Inode*child)
{
    children.push_back(child);
    return ;
}
bool greaterthan(Inode* I1,Inode* I2)
{
    string first=I1->getName();
    string second=I2->getName();
    const unsigned long int m=min(first.length(),second.length());
    for(int i=0;i<m;i++)
    {
        if(first[i]==second[i])
            continue;
        else if(first[i]>second[i])
            return true;
        else return false;
    }
    return true;
}
void swap(Inode*& I1,Inode*& I2)
{
    Inode * temp=I1;
    I1=I2;
    I2=temp;
    return;
}
void Inode::bubblesort()
{
    const long unsigned int n=children.size();
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-1;j++)
            if(greaterthan(children[j],children[j+1]))
                swap(children[j],children[j+1]);
        
    }
}

#endif





