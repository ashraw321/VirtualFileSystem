VFS: main.o inode.o vfs_tree.o myvector.o mystack.o myqueue.o
	g++ main.o inode.o vfs_tree.o myvector.o mystack.o myqueue.o -o VFS
	
main.o: main.cpp
	g++ -c main.cpp

inode.o: inode.cpp inode.hpp
	g++ -c inode.cpp

vfs_tree.o: vfs_tree.cpp vfs_tree.hpp
	g++ -c vfs_tree.cpp

myvector.o: myvector.cpp myvector.hpp
	g++ -c myvector.cpp

mystack.o: mystack.cpp mystack.hpp
	g++ -c mystack.cpp

myqueue.o: myqueue.cpp myqueue.hpp
	g++ -c myqueue.cpp

clean:
	rm *.o VFS 
