#include "Btree.cpp"

int main()
{
	Btree<char>* t = new Btree<char>(3);

	//test libro - albero iniziale
	t->insert('d')->insert('e')->insert('g')->insert('j')->insert('k')->insert('a');
	t->insert('c')->insert('m')->insert('n')->insert('o')->insert('p');
	t->insert('r')->insert('s')->insert('x');
	t->insert('y')->insert('z')->insert('t');
	t->insert('u')->insert('v');

	cout << "L'altezza del Btree e': " << t->get_height() << endl << endl;

	//inserimenti a catena
	t->insert('b')->insert('q')->insert('l')->insert('f');

	//cancellazione a catena
	t->_delete('f')->_delete('m')->_delete('g')->_delete('d')->_delete('b');

	//test aggiuntivi - cancellazione di chiave insesistente (w) e inserimento di chiave ripetute (h)
	t->_delete('p')->insert('h')->_delete('n')->_delete('w')->insert('h');

	//svuoto l'albero
	while (!t->tree_empty())
	{
		t->_delete(t->get_min_key());
	}

	cout << "L'altezza del Btree e': " << t->get_height() << endl << endl;

	delete t;

	t = new Btree<char>(2);
	for (char i = 'a'; i <= 'z'; i++)
	{
		t->insert(i);
	}

	cout << "L'altezza del Btree e': " << t->get_height() << endl << endl;

	t->_delete('d')->insert('d')->_delete('j')->insert('j');

	//svuoto l'albero
	while (!t->tree_empty())
	{
		t->_delete(t->get_min_key());
	}
	cout << "L'altezza del Btree e': " << t->get_height() << endl << endl;

	delete t;

	return 1;
}