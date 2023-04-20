//
//  vfs_tree.cpp
//  Assignment VFS
//
//  Created by Ashish Rawat on 19/04/23.
//

#include "vfs_tree.hpp"
//============================================================================
// Name         : DS Assignment#2
// Author       : Mai Oudah
// Version      : 2.0
// Date Created : 05-04-2023
// Date Modified:
// Description  : Virtual Filesystem - Tree class
//============================================================================


# define FOLDERSIZE 10
//#include "myvector.h" //create this header file where you define the vector class
//#include "mystack.h" //create this header file where you define the stack class
//#include "myqueue.h" //create this header file where you define the queue class
string create_date()
{
    string date="";
    time_t tmNow;
    tmNow =time(NULL);
    struct tm t=*localtime(&tmNow);
    date+=to_string(t.tm_mday);
    date+="-";
    date+=to_string(t.tm_mon+1);
    date+="-";
    date+=to_string((t.tm_year+2000)%100);
    return date;
}

///=========================================================================================
Inode* Position::getInode()
{
    return inode;
}
vector<Position*> Position::getChildren()
{
    return childrenPositions;
}
void Position::Update_parent()
{
    Parent= new Position(inode->getParent());
    return ;
}
Position::Position(Inode* inode)
{
    this->inode=inode;
    childrenPositions.clear();
}
void Position::setChildrenPositions()
{
    vector<Inode*> children1;
    childrenPositions.clear();
    for(int i=0;i<inode->getchildren().size();i++)
        children1.push_back(inode->getchildren()[i]);
    for(int i=0;i<children1.size();i++)
    {
        Position *child=new Position(children1[i]);
        childrenPositions.push_back(child);
    }
    return ;
}

void Position::setInode(Inode* inode)
{
    this->inode=inode;
    childrenPositions.clear();
}
Position* Position::getparent()
{
    return Parent;
}
//=============================================================================
bool VFS_Tree::empty() const
{
    if(n==0)
        return true;
    else return false;
}
Position* VFS_Tree::getPrevious_working_directory()
{
    return previous_working_directory;
}
void VFS_Tree::setPrevious_working_directory(Position* P)
{
    previous_working_directory=P;
    previous_working_directory->setChildrenPositions();
    return ;
}
Position* VFS_Tree::getRoot() const
{
    return root;
}
Position* VFS_Tree::getcurrentNode() const // returns the position to the current inode
{
    return currentNode;
}
VFS_Tree::VFS_Tree()
{
    load();
    
}
void VFS_Tree::VFSfull_TreeTraversal(Position* curr)const
{
    pwd(curr);

    for(int i=0;i<curr->getChildren().size();i++)
    {
        VFSfull_TreeTraversal(curr->getChildren()[i]);
    }
    return ;
}
void VFS_Tree::VFS_TreeTraversal(Position* curr,string name)const
{
    
    if(curr->getInode()->getName()==name)
    {
        pwd(curr);
    }
    curr->setChildrenPositions();
    for(int i=0;i<curr->getChildren().size();i++)
    {
        VFS_TreeTraversal(curr->getChildren()[i],name);
    }
    return ;
}
void VFS_Tree::find(string name) const
{
    root->setChildrenPositions();
    for(int i=0;i<root->getChildren().size();i++)
    {
        VFS_TreeTraversal(root->getChildren()[i],name);
    }
    return;
}


void VFS_Tree::touch(string filename, string s)
{
    if(s=="")
    {
        cout<<"please enter size";
        return ;
    }
    int size=stoi(s);
    Inode* File= new Inode(filename,size
                           ,true,create_date());
    
    size=stoi(s);
    if(currentNode->getInode()->getisFile())
    {
        cout<<"Error need to be present in a file"<<endl;
        throw exception();
    }
    if(!File->getisFile())
    {
        cout<<"need to be a file"<<endl;
        return;
    }
    string name=File->getName();
    if(Iffileexist(name))
    {
        cout<<"Already Exist give some another name"<<endl;
        return;
    }
    
    currentNode->getInode()->add_child(File);
    File->setParent(currentNode->getInode());
    currentNode->setChildrenPositions();
    Position* temp= new Position(currentNode->getInode());
    while(temp->getInode()!=root->getInode())
    {
        temp->getInode()->setFsize(temp->getInode()->getFsize()+size);
        temp->Update_parent();
        temp=temp->getparent();
    }
    root->getInode()->setFsize(root->getInode()->getFsize()+size);
    n++;
    return;
}



void VFS_Tree::mkdir(string foldername)
{
    if(currentNode->getInode()->getisFile())
    {
        cout<<"Error need to be a folder"<<endl;
        throw exception();
    }
    Inode* Folder= new Inode(foldername,10,false,create_date());
    if(Folder->getisFile())
    {
        cout<<"need to be a folder"<<endl;
        return;
    }
    string name=Folder->getName();
    if(Iffolderexist(name))
    {
        cout<<"Already Exist give some another name"<<endl;
        return;
    }
    currentNode->getInode()->add_child(Folder);
    Folder->setParent(currentNode->getInode());
    currentNode->setChildrenPositions();
    Position* temp= new Position(currentNode->getInode());
    while(temp->getInode()!=root->getInode())
    {
        temp->getInode()->setFsize(temp->getInode()->getFsize()+FOLDERSIZE);
        temp->Update_parent();
        temp=temp->getparent();
    }
    root->getInode()->setFsize(root->getInode()->getFsize()+FOLDERSIZE);
    n++;
    return;
}


void VFS_Tree::ls(){
    if(currentNode->getInode()->getisFile())
    {
        cout<<"Error it is not a folder"<<endl;
        throw exception();
    }
    currentNode->setChildrenPositions();
    for(int i=0;i<currentNode->getChildren().size();i++)
    {
        if(currentNode->getChildren()[i]->getInode()->getisFile())
            cout<<"file ";
        else cout<<"dir ";
        cout<<currentNode->getChildren()[i]->getInode()->getName()<<" ";
        cout<<currentNode->getChildren()[i]->getInode()->getFsize()<<" bytes ";
        cout<<currentNode->getChildren()[i]->getInode()->getDate()<<endl;
    }
    return;
}



void VFS_Tree::lsSort(){
    if(currentNode->getInode()->getisFile())
    {
        cout<<"Error"<<endl;
        throw exception();
    }
    currentNode->setChildrenPositions();
    currentNode->getInode()->bubblesort();
    currentNode->setChildrenPositions();
    for(int i=0;i<currentNode->getChildren().size();i++)
    {
        if(currentNode->getChildren()[i]->getInode()->getisFile())
            cout<<"file ";
        else cout<<"dir ";
        cout<<currentNode->getChildren()[i]->getInode()->getName()<<" ";
        cout<<currentNode->getChildren()[i]->getInode()->getFsize()<<" bytes ";
        cout<<currentNode->getChildren()[i]->getInode()->getDate()<<endl;
    }
    return;
}

Position *VFS_Tree::Pathfinder(Position*curr,queue<string> &path)
{
    string working=path.front();
    string curr_path_string=curr->getInode()->getName();
    if(path.front()!=curr->getInode()->getName())
        return NULL;
    else{
        
        path.pop();
        if(path.empty())
            return curr;
        else{
            curr->setChildrenPositions();
            Position* P=NULL;
            for(int i=0;i<curr->getChildren().size();i++)
            {
                P=Pathfinder(curr->getChildren()[i],path);
                if(P!=NULL)
                    return P;
            }
            return P;
        }
    }
}
void VFS_Tree::cd(string arg){
    
    if(arg=="/"||arg=="")
    {
        currentNode=new Position(root->getInode());
        currentNode->setChildrenPositions();
        return;
    }
    else if(arg=="..")
    {
        setPrevious_working_directory(currentNode);
        currentNode=new Position(currentNode->getInode()->getParent());
        
        currentNode->setChildrenPositions();
        return;
    }
    else if(arg=="-")
    {
        currentNode=getPrevious_working_directory();
        currentNode->setChildrenPositions();
        return;
    }
    else if(arg[0]=='/')
    {
        queue<string> path;
        string name="";
        int i=1;
        while(i<arg.length())
        {
            if(arg[i]=='/')
            {
                path.push(name);
                name="";
            }
            else
            name+=arg[i];
            i++;
        }
        path.push(name);
        Position* P=NULL;
        root->setChildrenPositions();
        for(int i=0;i<root->getChildren().size();i++)
        {
            Position* curr=root->getChildren()[i];
            queue<string> temp_queue=path;
            P=Pathfinder(curr,temp_queue);
            if(P)
            {
                break;
            }
        }
        if(P==NULL){
            cout<<"Invalid path";
            throw exception();
        }
        else{
            setPrevious_working_directory(currentNode);
            currentNode=P;
            currentNode->setChildrenPositions();
            return;
        }
    }
    else
    {
        if(Iffileexist(arg))
        {
            cout<<"Cannot go in file needs to be a folder"<<endl;
            throw exception();
        }
        currentNode->setChildrenPositions();
        bool flag= true;
        for(int i=0;i<currentNode->getChildren().size();i++)
        {
            if(currentNode->getChildren()[i]->getInode()->getName()==arg)
            {
                flag=false;
                currentNode=currentNode->getChildren()[i];
                currentNode->setChildrenPositions();
                break;
            }
        }
        if(flag)
            cout<<"No such file exsits"<<endl;
    }
 }




void VFS_Tree::realpath(string name) const{
    if(Iffileexist(name))
        {
            stack<string> s;
            Position *temp_pos=new Position(root->getInode());
            while(temp_pos->getInode()!=root->getInode())
            {
                s.push(temp_pos->getInode()->getName());
                temp_pos->Update_parent();
                temp_pos=temp_pos->getparent();
            }
            while(s.size())
            {
                cout<<"/"<<s.top();
                s.pop();
            }
            cout<<"/"<<name<<endl;
        }
        else {
            cout<<"Doesnot Exist for a folder needs to be a file"<<endl;
            throw exception();
        }
}
Inode* VFS_Tree::Iffileexist(string &name) const
{
    Inode* P=currentNode->getInode();
    for(int i=0;i<P->getchildren().size();i++)
    {
        if(P->getchildren()[i]->getName()==name&&(P->getchildren()[i]->getisFile()))
            return P->getchildren()[i];
    }
    return NULL;
}



string VFS_Tree::pwd(Position* current) const
{
    if(current->getInode()==root->getInode())
    {
        cout<<"/"<<endl;
        return "";
    }
    stack<string> s;
    Position *temp_pos=current;
    temp_pos->Update_parent();
    while(temp_pos->getInode()!=root->getInode())
    {
        s.push(temp_pos->getInode()->getName());
        temp_pos->Update_parent();
        temp_pos=temp_pos->getparent();
        
    }
    while(!s.empty())
    {
        cout<<"/"<<s.top();
        s.pop();
    }
    cout<<"\n";
    return "";
}

Inode* VFS_Tree::Iffolderexist(string &name) const
{
    Inode* P=currentNode->getInode();
    for(int i=0;i<P->getchildren().size();i++)
    {
        if(P->getchildren()[i]->getName()==name&&!(P->getchildren()[i]->getisFile()))
            return P->getchildren()[i];
    }
    return NULL;
}

void VFS_Tree::mv(string filename, string foldername)
{
    Inode* file= Iffileexist(filename);
    Inode* folder=Iffolderexist(foldername);
    currentNode->setChildrenPositions();
    if(file&&folder)
    {
        int itr=0;
        for(int i=0;i<currentNode->getChildren().size();i++)
        {
            if(filename==currentNode->getChildren()[i]->getInode()->getName())
            {
                itr+=i;
                break;
            }
        }
        int size=file->getFsize();
        currentNode->getInode()->delete_child(itr);
        cd(foldername);
        touch(filename,to_string(size));
        cd("..");
        currentNode->setChildrenPositions();
    }
}


void VFS_Tree::rm(string name)
{
    if(bin.size()>=20)
    {
        cout<<"Bin is FUll"<<endl;
        throw exception();
    }
    Inode* file=Iffileexist(name);
    Inode* folder=Iffolderexist(name);
    currentNode->setChildrenPositions();
    if(file||folder)
    {
        int size=0;
        if(file)
            size=file->getFsize();
        else
            size=folder->getFsize();
        int itr=0;
        int i=0;
        for(;i<currentNode->getChildren().size();i++)
        {
            if(name==currentNode->getChildren()[i]->getInode()->getName())
            {
                itr+=i;
                break;
            }
        }
        Inode* N=currentNode->getChildren()[i]->getInode();
        
        currentNode->getInode()->delete_child(itr);
        Position* B=new Position(N);
        bin.push(B);
        Position* temp= new Position(currentNode->getInode());
        while(temp->getInode()!=root->getInode())
        {
            temp->getInode()->setFsize(temp->getInode()->getFsize()-size);
            temp->Update_parent();
            temp=temp->getparent();
        }
        root->getInode()->setFsize(root->getInode()->getFsize()-size);
    }
    else {
        cout<<"No such folder or file exists to delete"<<endl;
        throw exception();
    }
    
}
void VFS_Tree::size(string arg)
{
    
    if(arg=="/")
    {
        cout<<root->getInode()->getFsize()<<" bytes"<<endl;
        return;
    }
    if(arg[0]!='/')
    {
        Inode* File=Iffileexist(arg);
        Inode* Folder=Iffolderexist(arg);
        if(File!=NULL)
        {
            cout<<File->getFsize()<<" bytes"<<endl;
        }
        else if(Folder!=NULL)
        {
            cout<<Folder->getFsize()<<" bytes"<<endl;
        }
        else{
            cout<<"File or Folder doesnot exist in current working directory"<<endl;
            throw exception();
        }
        return;
    }
    queue<string> path;
    string name="";
    int i=1;
    while(i<arg.length())
    {
        if(arg[i]=='/')
        {
            path.push(name);
            name="";
        }
        else
        {
            name+=arg[i];
        }
        i++;
    }
    path.push(name);
    Position* P=NULL;
    root->setChildrenPositions();
    for(int i=0;i<root->getChildren().size();i++)
    {
        Position* curr=root->getChildren()[i];
        queue<string> temp=path ;
        P=Pathfinder(curr,temp);
        if(P!=NULL)
        {
            cout<<P->getInode()->getFsize()<<" bytes"<<endl;
            return;
        }
    }
    if(!P){
        cout<<"Invalid path";
        throw exception();
    }
    return;
}
void VFS_Tree::clear(Inode* node)
{
    for(int i=0;i<node->getchildren().size();i++)
        clear(node->getchildren()[i]);
    delete node;
    return;
}
void VFS_Tree::emptyBin()
{
    while(!bin.empty())
    {
        clear(bin.front()->getInode());
        bin.pop();
    }
    return;
}

void VFS_Tree::showBin()
{
    if(bin.empty())
    {
        cout<<"The Bin is empty"<<endl;
        throw exception();
    }
    Position* inodetop=bin.front();
    Position* temp=new Position(currentNode->getInode());
    currentNode=new Position(inodetop->getInode());
    if(currentNode->getInode()->getisFile())
        cout<<"file"<<" ";
    else cout<<"dir ";
    cout<<currentNode->getInode()->getName()<<" "<<currentNode->getInode()->getDate()<<" "<<
    currentNode->getInode()->getFsize();
    cout<<" bytes ";
    pwd(currentNode);
    currentNode=new Position(temp->getInode());
    currentNode->setChildrenPositions();
    return;
}
void VFS_Tree::recover()
{
    if(bin.size()==0)
    {
        cout<<"Nothing to recover "<<endl;
    }
    Position* oldest=bin.front();
    Inode* C=oldest->getInode();
    Inode *P=oldest->getInode()->getParent();
    P->add_child(C);
    currentNode->setChildrenPositions();
    bin.pop();
    return;
    
}
string VFS_Tree::filepwd(Position* current,ofstream &OutputFile) const
{
    if(current->getInode()==root->getInode())
    {
        OutputFile<<"/"<<","<<current->getInode()->getFsize()<<","<<current->getInode()->getDate()<<endl;
        return "";
    }
    stack<string> s;
    Position *temp_pos=current;
    while(temp_pos->getInode()!=root->getInode())
    {
        s.push(temp_pos->getInode()->getName());
        temp_pos->Update_parent();
        temp_pos=temp_pos->getparent();
        
    }
    while(!s.empty())
    {
        
        OutputFile<<"/"<<s.top();
        s.pop();
    }
    OutputFile<<","<<current->getInode()->getFsize()<<","<<current->getInode()->getDate()<<endl;
    return "";
}
void VFS_Tree::saveVFS_Tree(Position* curr,ofstream &OutputFile)const
{
    
    filepwd(curr,OutputFile);
    curr->setChildrenPositions();
    for(int i=0;i<curr->getChildren().size();i++)
        saveVFS_Tree(curr->getChildren()[i],OutputFile);
}
void VFS_Tree::exit()const
{
    ofstream fout;
    fout.open("vfs.dat",ios::out|ios::binary|ofstream::trunc);
    if(!fout)
        cout<<"cannot open file"<<endl;
    stack<string> path_name_stack;
    saveVFS_Tree(root,fout);
    fout.close();
    return;
}
bool VFS_Tree::load()
{
    ifstream iout;
    root=NULL;
    Inode *R=new Inode("root",false,0,create_date());
    root=new Position(R);
    currentNode=new Position(R);
    iout.open("vfs.dat",ios::in|ios::binary);
    if(!iout)
    {
        cout<<"file not opened"<<endl;
        return true;
    }
    if(iout.is_open())
    {
        
        string rootdata="";
        getline(iout,rootdata);
        string rsize="";
        string rdate="";
        int ri=2;
        if(rootdata=="")
        {
            iout.close();
            return true;
        }
        while(rootdata[ri]!=',')
        {
            rsize+=rootdata[ri];
            ri++;
        }
        ri++;
        while(ri<rootdata.size())
        {
            rdate+=rootdata[ri];
            ri++;
        }
        Inode *R=new Inode("root",false,stoi(rsize),rdate);
        root->getInode()->setDate(rdate);
        root->getInode()->setFsize(stoi(rsize));
        currentNode=new Position(root->getInode());
        previous_working_directory=new Position(root->getInode());
        while(iout)
        {
            string NAME="";
            string data="";
            getline(iout,data);
            string arg="";
            int j=0;
            while(data[j]!=',')
            {
                arg+=data[j];
                j++;
            }
            j++;
            queue<string> pathdata;
            string name="";
            int i=1;
            while(i<arg.length())
            {
                if(arg[i]=='/')
                {
                    pathdata.push(name);
                    name="";
                }
                else
                name+=arg[i];
                i++;
            }
            pathdata.push(name);
            NAME=name;
            string sizedata="";
            while(data[j]!=',')
            {
                sizedata+=data[j];
                j++;
            }
            j++;
            string datedata="";
            while(j<data.size())
            {
                datedata+=data[j];
                j++;
            }
            Inode* FileorFolder=new Inode(NAME,false,stoi(sizedata),datedata);
            currentNode->setInode(root->getInode());
            Createfileorfolder(root->getInode(),pathdata,FileorFolder);
        }
        iout.close();
        currentNode->setInode(root->getInode());
    }
    return true ;
        
}
void VFS_Tree::Createfileorfolder(Inode* curr,queue<string>&pathdata,Inode*FileorFolder)
{
    currentNode=new Position(curr);
    string name=FileorFolder->getName();
    Inode* file = Iffileexist(name);
    Inode* folder=Iffolderexist(name);
    if(!(file||folder)&&pathdata.size()==1)
    {
        curr->add_child(FileorFolder);
        FileorFolder->setParent(curr);
        return;
    }
    name=pathdata.front();
    pathdata.pop();
    folder=Iffolderexist(name);
    if(folder)
    {
        Createfileorfolder(folder,pathdata,FileorFolder);
    }
    else if(file)
    {
        Createfileorfolder(file,pathdata,FileorFolder);
    }
    else
    {
        cout<<"wrong data"<<endl;
    }
    return;
}

