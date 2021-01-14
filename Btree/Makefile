all: a.out

a.out: Node.o Btree.o Main.o
	g++ -o a.out Node.o Btree.o Main.o -Wall

Node.o: Node.cpp Node.h
	g++ -c Node.cpp -Wall

Btree.o: Node.h Btree.cpp Btree.h
	g++ -c Node.cpp -Wall
	g++ -c Btree.cpp -Wall

Main.o: Node.h Btree.h Main.cpp
	g++ -c Node.cpp -Wall
	g++ -c Btree.cpp -Wall
	g++ -c Main.cpp -Wall

clean:
	rm *.o
