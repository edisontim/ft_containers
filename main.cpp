#include <vector>
#include <iostream>
#include "Vector.hpp"
#include "Stack.hpp"
#include <stack>
#include "Pair.hpp"
#include "Map.hpp"
#include <map>
#include <string>

void output_s(std::stack<int> &t)
{
	std::cout << "______Original stack______" << std::endl;

	std::stack<int> buff;
	while (!t.empty())
	{
		buff.push(t.top());
		std::cout << t.top() << std::endl;
		t.pop();
	}
	while (!buff.empty())
	{
		t.push(buff.top());
		buff.pop();
	}
}

void output_my_s(ft::Stack<int> &t)
{
	ft::Stack<int> buff;
	std::cout << "______My stack______" << std::endl;

	while (!t.empty())
	{
		buff.push(t.top());
		std::cout << t.top() << std::endl;
		t.pop();
	}
	while (!buff.empty())
	{
		t.push(buff.top());
		buff.pop();
	}
}

void output_v(ft::Vector<int> &test)
{
	ft::Vector<int>::iterator begin;
	ft::Vector<int>::iterator end;

	begin = test.begin();
	end = test.end();

	std::cout << "My vector contains :" << std::endl;
	while (begin != end)
	{
		std::cout << "My vector |" << *begin <<  "|" << std::endl;
		begin++;
	}
}

void output(std::vector<int> &test)
{
	std::vector<int>::iterator begin;
	std::vector<int>::iterator end;

	begin = test.begin();
	end = test.end();

	std::cout << "Original vector contains :" << std::endl;
	while (begin != end)
	{
		std::cout << "Original vector |" << *begin <<  "|" << std::endl;
		begin++;
	}
}

void reverse_output_v(ft::Vector<int> &test)
{
	ft::Vector<int>::reverse_iterator rbegin;
	ft::Vector<int>::reverse_iterator rend;

	rbegin = test.rbegin();
	rend = test.rend();

	while (rbegin != rend)
	{
		std::cout << *rbegin << std::endl;
		rbegin++;
	}
}

void output_my_map(ft::Map<int, std::string> &a)
{	
	ft::Map<int, std::string>::iterator begin = a.begin();
	ft::Map<int, std::string>::iterator end = a.end();
	while (begin != end)
	{
		std::cout << ((*begin).first) << std::endl;
		begin++;
	}
}

int main()
{
	std::vector<int> a;
	std::vector<int> a1;
	ft::Vector<int> test;
	ft::Vector<int> test1;

	std::cout << "________________VECTOR________________" << std::endl;

	std::cout << "capacity of test is " << test.capacity() << std::endl;
	std::cout << "capacity of a is " << a.capacity() << std::endl;
	std::cout << "size of test is " << test.size() << std::endl;
	std::cout << "size of a is " << a.size() << std::endl;
	std::cout << "max_size of test is " << test.max_size() << std::endl;
	std::cout << "max_size of a is " << a.max_size() << std::endl;


	test1.push_back(1);
	test1.push_back(1);
	test1.push_back(1);
	test1.push_back(1);

	a1.push_back(1);
	a1.push_back(1);
	a1.push_back(1);
	a1.push_back(1);

	test.push_back(1);
	test.push_back(0);
	test.push_back(3);
	test.push_back(4);
	test.push_back(5);
	test.push_back(7);
	test.push_back(6);
	test.push_back(2);
	test[4] = 4;
	test.push_back(9);
	test.push_back(8);
	test.push_back(10);
	a.push_back(0);
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(4);
	a[4] = 4;
	a.push_back(5);
	a.push_back(6);
	a.push_back(7);
	a.push_back(8);
	a.push_back(9);
	a.push_back(10);

	ft::Vector<int>::iterator begin = test.begin();
	// std::vector<int>::iterator beginA = a.begin();

	ft::Vector<int>::iterator end = test.end();
	// std::vector<int>::iterator endA = a.end();
	output_v(test);
	// std::sort(begin, end);




	std::cout << "capacity of test is " << test.capacity() << std::endl;
	std::cout << "capacity of a is " << a.capacity() << std::endl;
	std::cout << "size of test is " << test.size() << std::endl;
	std::cout << "size of a is " << a.size() << std::endl;


	std::cout << "________________STACK________________" << std::endl;

	ft::Stack<int> georges;
	std::stack<int> good;

	georges.push(0);
	georges.push(1);
	georges.push(2);
	georges.push(3);
	georges.push(4);
	georges.push(5);
	georges.push(6);
	georges.push(7);
	georges.push(8);
	georges.push(9);


	good.push(0);
	good.push(1);
	good.push(2);
	good.push(3);
	good.push(4);
	good.push(5);
	good.push(6);
	good.push(7);
	good.push(8);
	good.push(9);

	std::cout << "Before pop()" << std::endl;
	output_my_s(georges);
	output_s(good);

	while (!georges.empty())
	{
		good.pop();
		georges.pop();
	}
	output_my_s(georges);
	output_s(good);
	
	
	std::cout << "________________PAIR________________" << std::endl;

	ft::Pair<int, int> pairtest = ft::make_pair(100 , 1000);
	std::pair<int, int> real = std::make_pair(100, 1000);

	ft::Pair<int, int> pairtest1 = ft::make_pair(100 , 1000);
	std::pair<int, int> real1 = std::make_pair(100, 1000);

	std::cout << "Comparison operators for pair test > test1 " << (pairtest > pairtest1) << std::endl;
	std::cout << "Comparison operators for pair real > real1 " << (real > real1) << std::endl;

	std::cout << "Comparison operators for pair test < test1 " << (pairtest < pairtest1) << std::endl;
	std::cout << "Comparison operators for pair real < real1 " << (real < real1) << std::endl;

	std::cout << "Comparison operators for pair test >= test1 " << (pairtest >= pairtest1) << std::endl;
	std::cout << "Comparison operators for pair real >= real1 " << (real >= real1) << std::endl;

	std::cout << "Comparison operators for pair test <= test1 " << (pairtest <= pairtest1) << std::endl;
	std::cout << "Comparison operators for pair real <= real1 " << (real <= real1) << std::endl;

	std::cout << "Comparison operators for pair test == test1 " << (pairtest == pairtest1) << std::endl;
	std::cout << "Comparison operators for pair real == real1 " << (real == real1) << std::endl;

	std::cout << "Comparison operators for pair test != test1 " << (pairtest != pairtest1) << std::endl;
	std::cout << "Comparison operators for pair real != real1 " << (real != real1) << std::endl;


	std::cout << "________________MAP________________" << std::endl;

	ft::Map<int, std::string> map_test;
	std::map<int, std::string> map_real;

	std::string stringa = "Hello";

	map_test.insert(ft::make_pair(1, std::string("Hello")));
	map_test.insert(ft::make_pair(10, std::string("lo")));
	map_test.insert(ft::make_pair(8, std::string("LOL")));
	map_test.insert(ft::make_pair(2, std::string("aisufdha")));
	map_test.insert(ft::make_pair(4, std::string("1002391093")));
	map_test.insert(ft::make_pair(5, std::string("blabalbla")));
	map_test.insert(ft::make_pair(7, std::string("lolooloo")));
	map_test.insert(ft::make_pair(3, std::string("lulu")));
	map_test.insert(ft::make_pair(6, std::string("lala")));
	map_test.insert(ft::make_pair(11, std::string("haha")));
	map_test.insert(ft::make_pair(25, std::string("huhu")));
	map_test.insert(ft::make_pair(-10, std::string("hihi")));
	map_test.insert(ft::make_pair(-2, std::string("Bro")));
	map_test.insert(ft::make_pair(772, std::string("adfhafasdfadfasdfasdfadsf")));
	map_test.insert(ft::make_pair(2398402, std::string("yyyyyyyyyyy")));
	map_test.insert(ft::make_pair(19, std::string("aaaaaaaaaaa")));
	map_test.insert(ft::make_pair(100, std::string("pppppppppppppp")));


	output_my_map(map_test);

	std::cout << map_test[-10] << std::endl;
}