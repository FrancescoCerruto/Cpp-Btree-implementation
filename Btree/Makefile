all: a.out

a.out: Node.o Btree.o Main.o
	g++ -o a.out Node.o Btree.o Main.o

Node.o: Node.cpp Node.h
	g++ -c Node.cpp

Btree.o: Node.cpp Btree.cpp Btree.h
	g++ -c Node.cpp
	g++ -c Btree.cpp

Main.o: Node.cpp Btree.cpp Main.cpp
	g++ -c Node.cpp
	g++ -c Btree.cpp
	g++ -c Main.cpp

