#ifndef BTREE_H
#define BTREE_H
#include "Node.cpp"

template <class Type> class Btree
{
	Node<Type>* root;
	const int t;

	void split_child(Node<Type>* x, int index_child);
	void insert_nonfull(Node<Type>* x, Type key);

	void inorder(Node<Type>* x);
	void preorder(Node<Type>* x);
	void postorder(Node<Type>* x);
	void BSF_level(Node<Type>* x, int level);
	void BFS();

	int calculate_height(Node<Type>* x);

	bool btree_search(Node<Type>* x, Type key);

	void concatenate_right(Node<Type>* father, Node<Type>* min_node, Node<Type>* right_brother, int index_z);
	void concatenate_left(Node<Type>* father, Node<Type>* min_node, Node<Type>* left_brother, int index_z);
	void fusion_right(Node<Type>* father, Node<Type>* min_node, Node<Type>* right_node, int index_z);
	void fusion_left(Node<Type>* father, Node<Type>* min_node, Node<Type>* left_brother, int index_z);
	void fix_up(Node<Type>* father, Node<Type>* min_node, int index_z);
	void delete_nonmin(Node<Type>* x, Type key);
	void delete_max(Node<Type>* x, Node<Type>* y, int index);

	Node<Type>* get_node_min_key();
public:
	Btree(int minimum_degree);

	Btree<Type>* insert(Type key);

	void print();

	int get_height();

	bool search(Type key);

	Btree<Type>* _delete(Type key);

	bool tree_empty();

	Type get_min_key();
};

#endif