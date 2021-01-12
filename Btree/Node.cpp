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
	Node(int minimum_degree, Node<Type>* set) : t(minimum_degree)
	{
		minimum = numeric_limits<Type>::lowest();
		n = 0;
		leaf = true;
		keys = new Type[(2 * t - 1)];
		for (int i = 0; i < (2 * t - 1); i++)
		{
			keys[i] = minimum;
		}
		children = new Node<Type> *[(2 * t)];
		for (int i = 0; i < (2 * t); i++)
		{
			children[i] = NULL;
		}
		father = set;
	}

	bool get_leaf()
	{
		return leaf;
	}
	void set_leaf(bool set)
	{
		leaf = set;
	}

	int get_n()
	{
		return n;
	}
	void set_n(int set)
	{
		n = set;
	}
	bool full_node()
	{
		return n == (2 * t - 1);
	}
	bool empty_node()
	{
		return n == 0;
	}
	bool min_node()
	{
		return n == (t - 1);
	}

	Type get_minimum()
	{
		return minimum;
	}

	void add_key(Type key)
	{
		int i = n - 1;
		while (i > -1 && key < keys[i])
		{
			keys[i + 1] = keys[i];
			i--;
		}
		keys[i + 1] = key;
		n++;
	}
	Type get_ith_key(int index)
	{
		return keys[index];
	}
	void set_ith_key(int index, Type key)
	{
		keys[index] = key;
	}
	void shift_key_right(int index)
	{
		for (int j = n - 1; j > index - 1; j--)
		{
			keys[j + 1] = keys[j];
		}
	}
	void shift_key_left(int index)
	{
		for (int j = index; j < n - 1; j++)
		{
			keys[j] = keys[j + 1];
		}
		keys[n - 1] = minimum;
	}

	void add_ith_node(int index, Node<Type>* child)
	{
		children[index] = child;
	}
	Node<Type>* get_ith_child(int index)
	{
		return children[index];
	}
	void shift_child_right(int index)
	{
		for (int j = n; j > index - 1; j--)
		{
			children[j + 1] = children[j];
		}
	}
	void shift_child_left(int index)
	{
		for (int j = index; j < n; j++)
		{
			children[j] = children[j + 1];
		}
		children[n] = NULL;
	}
	Node<Type>* get_father()
	{
		return father;
	}
	void set_father(Node<Type>* set)
	{
		father = set;
	}

	void print()	//prima delle chiavi del nodo stampo quelle di suo padre (se questo risulta qualificato) in modo tale da rendere esplicito i legami tra i nodi
	{
		if (father != NULL)
		{
			cout << "(";
			for (int i = 0; i < father->get_n(); i++)
			{
				cout << father->get_ith_key(i);
				if (i != father->get_n() - 1)
				{
					cout << ' ';
				}
			}
			cout << ") ";
		}
		else
		{
			cout << "(NIL) ";
		}
		for (int i = 0; i < n; i++)
		{
			cout << keys[i] << ' ';
		}
	}

	int search(Type key)	//restituisce un indice i tale che keys[i]=key oppure children[i] potrebbe contenere il valore key
	{
		int i = 0;
		int j = n;
		while (i < j)
		{
			if (key <= keys[(int)floor((i + j) / 2)])
			{
				j = (int)floor((i + j) / 2);
			}
			else
			{
				i = (int)floor((i + j) / 2) + 1;
			}
		}
		return i;
	}
};

#endif