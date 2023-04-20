
//============================================================================
// Name         : DS Assignment#2
// Author       : Mai Oudah
// Version      : 2.0
// Date Created : 17-03-2023
// Date Modified:
// Description  : Virtual Filesystem - Main Program
//============================================================================

#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<exception>
//#include "myqueue.hpp"
#include "mystack.hpp"
//#include "myvector.h"
#include "inode.hpp"
#include "vfs_tree.hpp"

using namespace std;


class Programme{
    public:
    VFS_Tree* myVFS_Tree;
    Programme(){
        myVFS_Tree=new VFS_Tree();
    }
    
    void pwd()
    {
        myVFS_Tree->pwd(myVFS_Tree->getcurrentNode());
        return;
    }
    void realpath(string file)
    {
        myVFS_Tree->realpath(file);
        return ;
    }
    void cd(string to)
    {
        myVFS_Tree->cd(to);
        return ;
    }
    void ls(string command)
    {
        if(command=="sort")
            myVFS_Tree->lsSort();
        else if(command=="")
            myVFS_Tree->ls();
        else throw exception();
        return;
    }
    void mkdir(string folderName)
    {
        myVFS_Tree->mkdir(folderName);
        return;
    }
    void touch(string fileName, string sizeInString)
    {
        myVFS_Tree->touch(fileName,sizeInString);
        return;
    }
    void find(string name)
    {
        myVFS_Tree->find(name);
        return;
    }
    void mv(string fileName, string folderName)
    {
        myVFS_Tree->mv(fileName,folderName);
        return;
    }
    void rm(string name)
    {
        myVFS_Tree->rm(name);
        return;
    }
    void size(string path)
    {
        myVFS_Tree->size(path);
        return ;
    }
    void emptybin()
    {
        myVFS_Tree->emptyBin();
        return;
    }
    void showbin()
    {
        myVFS_Tree->showBin();
        return;
    }
    void recover()
    {
        myVFS_Tree->recover();
        return;
    }
    void exit()
    {
        myVFS_Tree->exit();
    }
};

//=====================================
void listCommands()
{
    cout<<" ===================================================================================="<<endl
        <<" Welcome to the Virtual Filesystem!\n"<<endl
        <<" List of available Commands:"<<endl
        <<" pwd                     : Print full path to the current working directory"<<endl
        <<" realpath <filename>     : Print the absolute/full path of a given filename of a file within the current directory"<<endl
        <<" ls                      : List files and folders inside the current folder"<<endl
        <<" mkdir <foldername>      : Make a new directory/folder"<<endl
        <<" touch  <filename> <size>            : Create a new file"<<endl
        <<" find <filename|foldername>          : Return the path of the file (or the folder) if it exists"<<endl
        <<" cd <filename>                       : Change directory"<<endl
        <<" mv <filename> <foldername>          : Move a file"<<endl
        <<" rm <filename|foldername>            : Remove a file or a folder"<<endl
        <<" size <filename|foldername>          : Print size of an file/folder"<<endl
        <<" find <filename|foldername>          : Return the path of the file (or the folder) if it exists"<<endl
        <<" emptybin                            : Empty the trash"<<endl
        <<" showbin                 : Print the oldest file/folder of the bin"<<endl
        <<" recover                 : Recover the oldest file/folder form bin if path still exists"<<endl
        <<" help                    : Display the list of available commands"<<endl
        <<" exit                    : Exit the Program"<<endl
        <<" ====================================================================================\n"<<endl;
        
}



//=======================================
// main function
int main() {

    Programme P;

    listCommands();
    
    string user_input;
    string command;
    string params[3];
    do {
        params[0] = "";
        params[1] = "";
        params[2] = "";
        cout<<">";
        getline(cin,user_input);

        istringstream ss(user_input);
        int i = 0;
        while (ss >> command) {
            params[i] = command;
            i++;
        }
        
        try
        {
            if(command == "help")               listCommands();
            else if(params[0]=="pwd")           P.pwd();
            else if(params[0]=="realpath")      P.realpath(params[1]);
            else if(params[0]=="ls")            P.ls(params[1]);
            else if(params[0]=="mkdir")         P.mkdir(params[1]);
            else if(params[0]=="touch")         P.touch(params[1], params[2]);
            else if(params[0]=="cd")            P.cd(params[1]);
            else if(params[0]=="find")          P.find(params[1]);
            else if(params[0]=="mv")            P.mv(params[1], params[2]);
            else if(params[0]=="rm")            P.rm(params[1]);
            else if(params[0]=="size")          P.size(params[1]);
            else if(params[0]=="emptybin")      P.emptybin();
            else if(params[0]=="showbin")       P.showbin();
            else if(params[0]=="recover")       P.recover();
            else if(command == "exit")          {
                P.exit();
                break;
            }
            else if(user_input=="")             continue;
            else                                cout<<"Invalid Command!"<<endl;
        }
        catch(exception &e)
        {
            cout<<"Exception: "<<e.what()<<endl;
        }
    } while(command!="exit");
    
    
    return EXIT_SUCCESS;
}

// -----------------------------------------------------------------
// define the needed methods to execute the operations in the system (pwd, realpath, ls, ...) below



