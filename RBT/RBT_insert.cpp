#include <iostream>
#include <functional>
#include <cstdlib>  // exit

#include "RBT.hpp"
#include "../Pair.hpp"
#include <map>

int main()
{
	typedef ft::RBTree<std::map<char, int> > RBT_char_int;

	RBT_char_int    tree;
	std::map<char, int> a;
	a.insert(std::make_pair('t', 35));
	a.insert(std::make_pair('d', 35));
	a.insert(std::make_pair('v', 35));
	a.insert(std::make_pair('w', 10));
	a.insert(std::make_pair('s', 20));
	a.insert(std::make_pair('u', 15));
	a.insert(std::make_pair('i', 35));
	a.insert(std::make_pair('o', 35));
	a.insert(std::make_pair('p', 4));
	a.insert(std::make_pair('n', 35));
	a.insert(std::make_pair('g', 35));
	a.insert(std::make_pair('m', 35));
	a.insert(std::make_pair('e', 35));
	a.insert(std::make_pair('r', 35));
	a.insert(std::make_pair('y', 35));
	a.insert(std::make_pair('g', 10));
	a.insert(std::make_pair('g', 20));
	a.insert(std::make_pair('z', 15));
	a.insert(std::make_pair('m', 35));
	a.insert(std::make_pair('b', 35));
	a.insert(std::make_pair('c', 4));
	a.insert(std::make_pair('x', 35));
	a.insert(std::make_pair('f', 35));
	a.insert(std::make_pair('y', 35));



	tree.insert(std::make_pair('t', 35));
	tree.insert(std::make_pair('d', 35));
	tree.insert(std::make_pair('v', 35));
	tree.insert(std::make_pair('w', 10));
	tree.insert(std::make_pair('s', 20));
	tree.insert(std::make_pair('u', 15));
	tree.insert(std::make_pair('i', 35));
	tree.insert(std::make_pair('o', 35));
	tree.insert(std::make_pair('p', 4));
	tree.insert(std::make_pair('n', 35));
	tree.insert(std::make_pair('g', 35));
	tree.insert(std::make_pair('m', 35));
	tree.insert(std::make_pair('e', 35));
	tree.insert(std::make_pair('r', 35));
	tree.insert(std::make_pair('y', 35));
	tree.insert(std::make_pair('g', 10));
	tree.insert(std::make_pair('g', 20));
	tree.insert(std::make_pair('z', 15));
	tree.insert(std::make_pair('m', 35));
	tree.insert(std::make_pair('b', 35));
	tree.insert(std::make_pair('c', 4));
	tree.insert(std::make_pair('x', 35));
	tree.insert(std::make_pair('f', 35));
	tree.insert(std::make_pair('y', 35));

	tree.pretty_print();

	std::map<char, int>::iterator begin = a.begin();

	while (begin != a.end())
	{
		std::cout << (*begin).first << " ";
		begin++;
	}
	begin--;
	while (begin != (a.begin()))
	{
		std::cout << (*begin).first << " ";
		begin--;
	}
	
	std::cout << std::endl << (begin == a.end())<< std::endl;
	RBT_char_int new_tree = tree.copy_tree();
	new_tree.pretty_print();

	std::cout << new_tree.get_size() << std::endl;
	std::cout << tree.get_size() << std::endl;

	tree.in_order();
	std::cout << std::endl;
	new_tree.in_order();
}