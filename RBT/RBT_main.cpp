#include <iostream>
#include <functional>
#include <cstdlib>  // exit
#include "RBT.hpp"
#include <map>

int main()
{
    typedef ft::RBTree<std::map<char, int> > RBT_char_int;

    RBT_char_int    tree;

    tree.insert(std::make_pair('g', 10));
    tree.insert(std::make_pair('g', 20));
    tree.insert(std::make_pair('z', 15));
    tree.insert(std::make_pair('m', 35));
    tree.insert(std::make_pair('b', 35));
    tree.insert(std::make_pair('c', 4));
    tree.pretty_print();

    RBT_char_int::Node *find = tree.search_tree('b');
	std::cout << "find->data.first " << find->data.first << std::endl;
    if (find)
    {
        RBT_char_int::Node *succ = tree.successor(find);
        if (succ != tree.get_nullnode())
            std::cout << "successor of " << find->data.first << " is " << succ->data.first << std::endl;
        else
            std::cout << "could not find successor" << std::endl;

        RBT_char_int::Node *pred = tree.predecessor(find);
        if (pred != tree.get_nullnode())
            std::cout << "predecessor of " << find->data.first << " is " << pred->data.first << std::endl;
        else
            std::cout << "could not find predecessor" << std::endl;
    }
    else
        std::cout << "could not find key" << std::endl;

    tree.delete_node('b');
    tree.insert(std::make_pair('x', 35));
    tree.insert(std::make_pair('f', 35));
    tree.insert(std::make_pair('y', 35));
    tree.insert(std::make_pair('t', 35));
    tree.insert(std::make_pair('d', 35));
    tree.insert(std::make_pair('v', 35));
    tree.pretty_print();
    tree.delete_node('m');
    tree.pretty_print();
    // exit(0);
    tree.delete_node('g');
    tree.delete_node('t');
    tree.delete_node('y');
    tree.delete_node('a');
	int a;
    tree.pretty_print();
    exit(0);
    
    return (0);
}