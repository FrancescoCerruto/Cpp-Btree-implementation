#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <cmath>
#include<limits>
using namespace std;

template <class Type> class Node
{
	Type* keys;
	Node<Type>** children;
	const int t;
	int n;
	bool leaf;

	Type minimum;
	Node<Type>* father;

public:
	Node(int minimum_degree, Node<Type>* set);

	bool get_leaf();
	void set_leaf(bool set);

	int get_n();
	void set_n(int set);
	bool full_node();
	bool empty_node();
	bool min_node();

	Type get_minimum();

	void add_key(Type key);
	Type get_ith_key(int index);
	void set_ith_key(int index, Type key);
	void shift_key_right(int index);
	void shift_key_left(int index);

	void add_ith_node(int index, Node<Type>* child);
	Node<Type>* get_ith_child(int index);
	void shift_child_right(int index);
	void shift_child_left(int index);
	Node<Type>* get_father();
	void set_father(Node<Type>* set);

	void print();

	int search(Type key);
};

#endif
