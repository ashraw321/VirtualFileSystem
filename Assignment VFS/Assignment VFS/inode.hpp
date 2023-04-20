//
//  inode.hpp
//  Assignment VFS
//
//  Created by Ashish Rawat on 19/04/23.
//

#ifndef inode_hpp
#define inode_hpp

#include <stdio.h>
//
//  inode.cpp
//  Assignment VFS
//
//  Created by Ashish Rawat on 19/04/23.
//
//============================================================================
// Name         : DS Assignment#2
// Author       : Mai Oudah
// Version      : 2.0
// Date Created : 01-04-2023
// Date Modified:
// Description  : Virtual Filesystem - iNode class
//============================================================================
#include<iostream>
#include<string>
#include <ctime>
#include <vector>
//#include "myvector.h" //create this header file where you define the vector class

using namespace std;


class Inode
{
    private:
        string fname; //inode name (filename or folder name)
        int size; //file/folder size
        string date; //creation date
        bool isFile; //capture the type; true if this is a file, false if this is a folder/directory
        Inode* parent; //the parent directory
        vector<Inode*> children; //the container of children, if this inode is a folder

    public:
    Inode(string name, int fSize, bool isFile, string date);
    
    
    void setName(string name);// returns whether if it is a file or folder true if it is file and false otherwise
        
    

    void setFsize(int fSize);
         
    void setDate(string date);
    void setisFile(bool isFile);
        
    void setParent(Inode* parent);
        
    void setChildren(vector<Inode*> children);
    
    string getName();
        
    int getFsize();
    
    string getDate();
        
    bool getisFile();
    
    Inode* getParent();
    vector<Inode*> getchildren();
    void delete_child(int it);
    void add_child(Inode* child);
    void bubblesort();
        
};
#endif /* inode_hpp */
