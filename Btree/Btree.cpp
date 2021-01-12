#ifndef BTREE_H
#define BTREE_H
#include "Node.cpp"

template <class Type> class Btree
{
	Node<Type>* root;
	const int t;

	void split_child(Node<Type>* x, int index_child)
	{
		cout << "AZIONE COMPENSATIVA - SPLIT CHILD" << endl;
		Node<Type>* z = new Node<Type>(t, x);
		Node<Type>* y = x->get_ith_child(index_child);
		z->set_leaf(y->get_leaf());
		for (int i = 0; i < (t - 1); i++)
		{
			z->set_ith_key(i, y->get_ith_key(i + t));
			y->set_ith_key(i + t, y->get_minimum());
		}
		if (!z->get_leaf())
		{
			Node<Type>* child;
			for (int i = 0; i < t; i++)
			{
				child = y->get_ith_child(i + t);
				child->set_father(z);
				z->add_ith_node(i, child);
				y->add_ith_node(i + t, NULL);
			}
		}
		x->shift_child_right(index_child);
		x->add_ith_node(index_child + 1, z);
		x->shift_key_right(index_child);
		x->set_ith_key(index_child, y->get_ith_key(t - 1));
		x->set_n(x->get_n() + 1);
		z->set_n(t - 1);
		y->set_n(t - 1);
		z->set_father(x);
	}
	void insert_nonfull(Node<Type>* x, Type key)
	{
		if (x->get_leaf())
		{
			x->add_key(key);
		}
		else
		{
			int index_child = x->search(key);
			Node<Type>* child = x->get_ith_child(index_child);
			if (child->full_node())
			{
				split_child(x, index_child);
				if (key > x->get_ith_key(index_child))
				{
					index_child++;
				}
			}
			child = x->get_ith_child(index_child);
			insert_nonfull(child, key);
		}
	}

	void inorder(Node<Type>* x)
	{
		if (x != NULL)
		{
			for (int i = 0; i < x->get_n(); i++)
			{
				inorder(x->get_ith_child(i));
				cout << x->get_ith_key(i) << ' ';
			}
			inorder(x->get_ith_child(x->get_n()));
		}
	}
	void preorder(Node<Type>* x)
	{
		if (x != NULL)
		{
			for (int i = 0; i < x->get_n(); i++)
			{
				cout << x->get_ith_key(i) << ' ';
				preorder(x->get_ith_child(i));
			}
			preorder(x->get_ith_child(x->get_n()));
		}
	}
	void postorder(Node<Type>* x)
	{
		if (x != NULL)
		{
			for (int i = 0; i < (x->get_n() + 1); i++)
			{
				postorder(x->get_ith_child(i));
			}
			x->print();
		}
	}
	void BSF_level(Node<Type>* x, int level)
	{
		if (x == NULL)
		{
			return;
		}
		if (level == 1)
		{
			x->print();
			cout << '\t';
		}
		else
		{
			if (level > 1)
			{
				for (int i = 0; i <= x->get_n(); i++)
				{
					BSF_level(x->get_ith_child(i), level - 1);
				}
			}
		}
	}
	void BFS()
	{
		int height = calculate_height(root);
		for (int i = 1; i <= height + 1; i++)
		{
			BSF_level(root, i);
			cout << endl;
		}
	}

	int calculate_height(Node<Type>* x)
	{
		if (x == NULL)
		{
			return -1;
		}
		else
		{
			return 1 + calculate_height(x->get_ith_child(0));
		}
	}

	bool btree_search(Node<Type>* x, Type key)
	{
		int i = x->search(key);
		if (i < x->get_n() && key == x->get_ith_key(i))
		{
			return true;
		}
		if (x->get_leaf())
		{
			return false;
		}
		Node<Type>* child = x->get_ith_child(i);
		return btree_search(child, key);
	}

	void concatenate_right(Node<Type>* father, Node<Type>* min_node, Node<Type>* right_brother, int index_z)
	{
		cout << "CONCATENATE RIGHT" << endl;
		min_node->set_ith_key(t - 1, father->get_ith_key(index_z));
		father->set_ith_key(index_z, right_brother->get_ith_key(0));
		right_brother->shift_key_left(0);
		if (!min_node->get_leaf())
		{
			min_node->add_ith_node(t, right_brother->get_ith_child(0));
			min_node->get_ith_child(t)->set_father(min_node);
			right_brother->shift_child_left(0);
		}
		min_node->set_n(t);
		right_brother->set_n(right_brother->get_n() - 1);
	}
	void concatenate_left(Node<Type>* father, Node<Type>* min_node, Node<Type>* left_brother, int index_z)
	{
		cout << "CONCATENATE LEFT" << endl;
		min_node->shift_key_right(0);
		min_node->set_ith_key(0, father->get_ith_key(index_z - 1));
		father->set_ith_key(index_z - 1, left_brother->get_ith_key(left_brother->get_n() - 1));
		if (!min_node->get_leaf())
		{
			min_node->shift_child_right(0);
			min_node->add_ith_node(0, left_brother->get_ith_child(left_brother->get_n()));
			min_node->get_ith_child(0)->set_father(min_node);
			left_brother->add_ith_node(left_brother->get_n(), NULL);
		}
		min_node->set_n(min_node->get_n() + 1);
		left_brother->set_n(left_brother->get_n() - 1);
	}
	void fusion_right(Node<Type>* father, Node<Type>* min_node, Node<Type>* right_node, int index_z)
	{
		cout << "FUSION RIGHT" << endl;
		min_node->set_ith_key(t - 1, father->get_ith_key(index_z));
		father->shift_key_left(index_z);
		father->shift_child_left(index_z + 1);
		father->set_n(father->get_n() - 1);
		for (int i = 0; i < right_node->get_n(); i++)
		{
			min_node->set_ith_key(t + i, right_node->get_ith_key(i));
		}
		if (!min_node->get_leaf())
		{
			for (int i = 0; i <= right_node->get_n(); i++)
			{
				min_node->add_ith_node(t + i, right_node->get_ith_child(i));
				min_node->get_ith_child(t + i)->set_father(min_node);
			}
		}
		min_node->set_n(2 * t - 1);
	}
	void fusion_left(Node<Type>* father, Node<Type>* min_node, Node<Type>* left_brother, int index_z)
	{
		cout << "FUSION LEFT" << endl;
		left_brother->set_ith_key(t - 1, father->get_ith_key(index_z - 1));
		father->shift_key_left(index_z - 1);
		father->shift_child_left(index_z);
		father->set_n(father->get_n() - 1);
		for (int i = 0; i < min_node->get_n(); i++)
		{
			left_brother->set_ith_key(t + i, min_node->get_ith_key(i));
		}
		if (!min_node->get_leaf())
		{
			for (int i = 0; i <= min_node->get_n(); i++)
			{
				left_brother->add_ith_node(t + i, min_node->get_ith_child(i));
				left_brother->get_ith_child(t + i)->set_father(left_brother);
			}
		}
		left_brother->set_n(2 * t - 1);
	}
	void fix_up(Node<Type>* father, Node<Type>* min_node, int index_z)
	{
		cout << "AZIONE COMPENSATIVA - FIX UP - ";
		if (index_z == 0)
		{
			Node<Type>* right_brother = father->get_ith_child(index_z + 1);
			if (!right_brother->min_node())
			{
				concatenate_right(father, min_node, right_brother, index_z);
			}
			else
			{
				fusion_right(father, min_node, right_brother, index_z);
			}
		}
		else if (index_z == father->get_n())
		{
			Node<Type>* left_brother = father->get_ith_child(index_z - 1);
			if (!left_brother->min_node())
			{
				concatenate_left(father, min_node, left_brother, index_z);
			}
			else
			{
				fusion_left(father, min_node, left_brother, index_z);
			}
		}
		else
		{
			Node<Type>* left_brother = father->get_ith_child(index_z - 1);
			if (!left_brother->min_node())
			{
				concatenate_left(father, min_node, left_brother, index_z);
			}
			else
			{
				Node<Type>* right_brother = father->get_ith_child(index_z + 1);
				if (!right_brother->min_node())
				{
					concatenate_right(father, min_node, right_brother, index_z);
				}
				else
				{
					//il passaggio di fusione a sinistra produce un albero diverso rispetto a quello presente nel libro
					fusion_left(father, min_node, left_brother, index_z);
					//sostituire l'istruzione precedente con: fusion_right(father, min_node, right_brother, index_z);
				}
			}
		}
	}
	void delete_nonmin(Node<Type>* x, Type key)
	{
		int i = x->search(key);
		if (i < x->get_n() && key == x->get_ith_key(i))
		{
			if (x->get_leaf())
			{
				x->shift_key_left(i);
				x->set_n(x->get_n() - 1);
			}
			else
			{
				Node<Type>* child = x->get_ith_child(i);
				if (child->min_node())
				{
					int counter_keys = x->get_n() - 1;
					fix_up(x, child, i);
					if (counter_keys == x->get_n())
					{
						if (i != 0)
						{
							i--;
						}
						/*in caso di cambio nella procedura fix_up, sostituire il precedente if con
						if (i == counter_keys + 1)
						{
							i--;
						}*/
					}
				}
				child = x->get_ith_child(i);
				if (x->get_ith_key(i) != key)
				{
					delete_nonmin(child, key);
				}
				else
				{
					delete_max(x, child, i);
				}
			}
		}
		else
		{
			Node<Type>* child = x->get_ith_child(i);
			if (child->min_node())
			{
				int counter_keys = x->get_n() - 1;
				fix_up(x, child, i);
				if (counter_keys == x->get_n())
				{
					if (i != 0)
					{
						i--;
					}
				}
			}
			child = x->get_ith_child(i);
			delete_nonmin(child, key);
		}
	}
	void delete_max(Node<Type>* x, Node<Type>* y, int index)
	{
		if (y->get_leaf())
		{
			x->set_ith_key(index, y->get_ith_key(y->get_n() - 1));
			y->set_n(y->get_n() - 1);
		}
		else
		{
			Node<Type>* z = y->get_ith_child(y->get_n());
			if (z->min_node())
			{
				fix_up(y, z, index);
			}
			delete_max(x, z, index);
		}
	}

	Node<Type>* get_node_min_key()
	{
		Node<Type>* iterator = root;
		if (iterator)
		{
			while (iterator->get_ith_child(0) != NULL)
			{
				iterator = iterator->get_ith_child(0);
			}
		}
		return iterator;
	}
public:
	Btree(int minimum_degree) : t(minimum_degree)
	{
		root = NULL;
	}

	Btree<Type>* insert(Type key)
	{
		cout << "inserisco la chiave " << key << endl;
		if (root != NULL)
		{
			if (!search(key))
			{
				Node<Type>* r_tmp = root;
				if (r_tmp->full_node())
				{
					Node<Type>* new_root = new Node<Type>(t, NULL);
					root = new_root;
					new_root->set_leaf(false);
					new_root->set_n(0);
					new_root->add_ith_node(0, r_tmp);
					r_tmp->set_father(new_root);
					split_child(new_root, 0);
					insert_nonfull(new_root, key);
				}
				else
				{
					insert_nonfull(root, key);
				}
				print();
			}
			else
			{
				cout << "chiave gia' presente nell'albero" << endl << endl;
			}
		}
		else
		{
			root = new Node<Type>(t, NULL);
			root->add_key(key);
			print();
		}
		return this;
	}

	void print()
	{
		if (root)
		{
			cout << "La struttura del Btree e': " << endl;
			BFS();
			cout << endl;
			cout << "Visita Btree inorder: ";
			inorder(root);
			cout << endl << endl;
			cout << "Visita Btree preorder: ";
			preorder(root);
			cout << endl << endl;
			cout << "Visita Btree postorder: ";
			postorder(root);
			cout << endl << endl;
		}
		else
		{
			cout << "La struttura del Btree e': (NIL)" << endl << endl;
		}
	}

	int get_height()
	{
		return calculate_height();
	}

	bool search(Type key)
	{
		return btree_search(root, key);
	}

	Btree<Type>* _delete(Type key)
	{
		cout << "tento di cancellare la chiave " << key << endl;
		if (root != NULL)
		{
			if (search(key))
			{
				delete_nonmin(root, key);
				if (root->empty_node())
				{
					Node<Type>* child = root->get_ith_child(0);
					if (child)
					{
						child->set_father(NULL);
					}
					root = child;
				}
				print();
			}
			else
			{
				cout << "chiave non presente nell'albero" << endl << endl;
			}
		}
		return this;
	}

	bool tree_empty()
	{
		return root == NULL;
	}

	Type get_min_key()
	{
		Node<Type>* min_node = get_node_min_key();
		return min_node->get_ith_key(0);
	}
};

#endif