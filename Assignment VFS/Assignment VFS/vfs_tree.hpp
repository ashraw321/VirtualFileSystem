
#ifndef vfs_tree_hpp
#define vfs_tree_hpp

#include<iostream>
#include<string>
#include <ctime>
#include "inode.hpp"
#include <queue>
#include <fstream>
#include<cstdlib>

#include "mystack.hpp"
//#include "myvector.hpp"

using namespace std;
class Position
{
    private:
        Inode* inode;
        vector<Position*> childrenPositions;
        Position* Parent;
    public:
    Position(Inode* inode);
        ~Position();
    void Update_parent();
        bool isRoot() const;
        bool isExternal() const;
        
    void setChildrenPositions();
        
    void setInode(Inode* inode);
    Position* getparent();
    vector<Position*> getChildren();
    Inode* getInode();
};



class VFS_Tree
{
    private:
        Position* root;  //the root inode
        Position* currentNode;  //the current inode
        int n; //number of inodes in the tree
        queue<Position*> bin; // the bin queue to store removed inodes
        Position* previous_working_directory;
    public:
        VFS_Tree();
        ~VFS_Tree();
        
    bool empty() const;
    Position* getPrevious_working_directory();
    void setPrevious_working_directory(Position* P);
    // check if the tree is empty
    Position* getRoot() const;
    // returns the position to the root inode
    Position* getcurrentNode() const; // returns the position to the }
        void find(string name) const;
        void touch(string filename, string size);
        void mkdir(string foldername);
        void ls();
        void lsSort();
        void cd(string arg);
        void realpath(string name) const;
        string pwd(Position* current) const;
        void mv(string filename, string foldername);
        void rm(string name);
        void emptyBin();
        void showBin();
        void recover();
        //add any other necessary code and additional supporting methods here to achieve the capabilities of the system
        Inode* Iffileexist(string &name) const;
        void size(string arg);
        void VFS_TreeTraversal(Position* curr,string name)const;
        Inode* Iffolderexist(string &name) const;
        Position *Pathfinder(Position*curr,queue<string> &path);
        void clear(Inode* node);
        void VFSfull_TreeTraversal(Position* curr)const;
        void exit()const;
        void saveVFS_Tree(Position* curr,ofstream &OutputFile)const;
        string filepwd(Position* current,ofstream &OutputFile) const;
        bool load();
        void Createfileorfolder(Inode* curr,queue<string>&pathdata ,Inode*FileorFolder);
 
};

#endif

