#include <iostream>
#include <string>
#include <time.h>
#include <sys/time.h>


#if 1 //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	#include "Map.hpp"
	#include "Stack.hpp"
	#include "Vector.hpp"
	#include "Pair.hpp"
#endif


void output_my_s(ft::stack<int> &t)
{
	ft::stack<int> buff;
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

void output_v(ft::vector<int> &test)
{
	ft::vector<int>::iterator begin;
	ft::vector<int>::iterator end;

	begin = test.begin();
	end = test.end();

	std::cout << "My vector contains :" << std::endl;
	while (begin != end)
	{
		std::cout << "My vector |" << *begin <<  "|" << std::endl;
		begin++;
	}
}


void reverse_output_v(ft::vector<int> &test)
{
	ft::vector<int>::reverse_iterator rbegin;
	ft::vector<int>::reverse_iterator rend;

	rbegin = test.rbegin();
	rend = test.rend();

	while (rbegin != rend)
	{
		std::cout << *rbegin << std::endl;
		rbegin++;
	}
}

void output_my_map(ft::map<int, std::string> &a)
{	
	ft::map<int, std::string>::iterator begin = a.begin();
	ft::map<int, std::string>::iterator end = a.end();
	
	std::cout << "Map is :" << std::endl;
	while (begin != end)
	{
		std::cout <<  "keys :" << "|" << ((*begin).first) << "|"  << "		values : |" << ((*begin).second) << "|" << std::endl;
		begin++;
	}
}

int main()
{
	
	struct timeval time;
	gettimeofday(&time, NULL); // Start Time

	long totalTime = (time.tv_sec * 1000000) + (time.tv_usec);

	ft::vector<int> test;
	ft::vector<int> test1;

	std::cout << "________________vector________________" << std::endl;

	std::cout << "capacity of test is " << test.capacity() << std::endl;
	std::cout << "size of test is " << test.size() << std::endl;
	std::cout << "max_size of test is " << test.max_size() << std::endl;


	test1.push_back(1);
	test1.push_back(1);
	test1.push_back(1);
	test1.push_back(1);



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


	// test.insert(test.begin(), 1000);
	ft::vector<int>::iterator begin = test.begin();
	ft::vector<int>::const_iterator end = test.end();

	std::cout << "Comparing const_iterator and iterator : " << (begin != end) << std::endl;


	std::cout << std::endl << std::endl << std::endl;
	
	
	std::cout << "BEFORE SWAP test is :" << std::endl;
	
	output_v(test);
	std::cout << "test1 is :" << std::endl;
	output_v(test1);

	test.swap(test1);
	
	
	std::cout << "AFTER SWAP test is :" << std::endl;
	output_v(test);
	std::cout << "test1 is :" << std::endl;
	output_v(test1);

	std::cout << std::endl << std::endl << std::endl;

	std::cout << "Are iterators still working ??" << std::endl;
	while (begin != end)
	{
		std::cout << (*begin) << std::endl;
		begin++;
	}
	
	std::cout << std::endl << std::endl << std::endl;

	std::cout << "is test smaller than test1 ? " << (test < test1) << std::endl;
	
	std::cout << std::endl << std::endl << std::endl;

	std::cout << "capacity of test is " << test.capacity() << std::endl;
	std::cout << "size of test is " << test.size() << std::endl;

	std::cout << std::endl << std::endl << std::endl;
	std::cout << std::endl << std::endl << std::endl;

	std::cout << "________________stack________________" << std::endl;

	ft::stack<int> georges;

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



	std::cout << "Before pop()" << std::endl;
	output_my_s(georges);

	while (!georges.empty())
		georges.pop();

	output_my_s(georges);
	
	
	std::cout << "________________pair________________" << std::endl;

	ft::pair<int, int> pairtest = ft::make_pair(100 , 1000);
	std::pair<int, int> real = std::make_pair(100, 1000);

	ft::pair<int, int> pairtest1 = ft::make_pair(100 , 1000);
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


	std::cout << "________________map________________" << std::endl;

	ft::map<int, std::string> map_test;

	std::string stringa = "Hello";

	map_test.insert(ft::make_pair(1, stringa));
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
	map_test.insert(ft::make_pair(772, std::string("adfhafadfhafadfhafadfhafadfhafadfhafadfhafadfhafadfhaf")));
	map_test.insert(ft::make_pair(2398402, std::string("yyyyyyyyyyy")));
	map_test.insert(ft::make_pair(19, std::string("aaaaaaaaaaa")));
	map_test.insert(ft::make_pair(100, std::string("pppppppppppppp")));
	map_test.insert(ft::make_pair(100, std::string("pppppppppppppp")));



	std::cout << "Before erase" << std::endl;
	std::cout << "Size before erase : " << map_test.size() << std::endl;

	
	
	// std::cout << "After erase" << std::endl;
	// map_test.erase(10);
	// map_test.erase(11);
	// output_my_map(map_test);

	std::cout << "map_test[-10] : " << map_test[-10] << std::endl;
	output_my_map(map_test);
	std::cout << "map_test.count(10) : " << map_test.count(10) << std::endl;
	ft::pair< ft::map<int, std::string>::iterator, ft::map<int, std::string>::iterator > pair = map_test.equal_range(0);
	std::cout << "map_test.equal_range(0) : " << (*pair.first).first << std::endl;



	// time differences 

	gettimeofday(&time, NULL);  //END-TIME

	totalTime = ((time.tv_sec * 1000000) + (time.tv_usec) - totalTime);

	std::cout << "Execution time is " << totalTime << std::endl;


}







// #include <sys/time.h>
// #include <iostream>
// #include <string>
// #include <deque>
// #if 0 //CREATE A REAL STL EXAMPLE
// 	#include <map>
// 	#include <stack>
// 	#include <vector>
// 	namespace ft = std;
// #else
// 	#include "Map.hpp"
// 	#include "Stack.hpp"
// 	#include "Vector.hpp"
// #endif

// #include <stdlib.h>

// #define MAX_RAM 4294967296
// #define BUFFER_SIZE 4096
// struct Buffer
// {
// 	int idx;
// 	char buff[BUFFER_SIZE];
// };


// #define COUNT (MAX_RAM / (int)sizeof(Buffer))

// template<typename T>
// class Mutantstack : public ft::stack<T>
// {
// public:
// 	Mutantstack() {}
// 	Mutantstack(const Mutantstack<T>& src) { *this = src; }
// 	Mutantstack<T>& operator=(const Mutantstack<T>& rhs) 
// 	{
// 		this->c = rhs.c;
// 		return *this;
// 	}
// 	~Mutantstack() {}

// 	typedef typename ft::stack<T>::container_type::iterator iterator;

// 	iterator begin() { return this->c.begin(); }
// 	iterator end() { return this->c.end(); }
// };

// int main(int argc, char** argv) {
// 	if (argc != 2)
// 	{
// 		std::cerr << "Usage: ./test seed" << std::endl;
// 		std::cerr << "Provide a seed please" << std::endl;
// 		std::cerr << "Count value:" << COUNT << std::endl;
// 		return 1;
// 	}
// 	const int seed = atoi(argv[1]);
// 	srand(seed);
	
// 	struct timeval time;
// 	gettimeofday(&time, NULL); // Start Time

// 	long totalTime = (time.tv_sec * 1000) + (time.tv_usec / 1000);


// 	ft::vector<std::string> vector_str;
// 	ft::vector<int> vector_int;
// 	ft::stack<int> stack_int;
// 	ft::vector<Buffer> vector_buffer;
// 	ft::stack<Buffer, std::deque<int> > stack_deq_buffer;
// 	ft::map<int, int> map_int;

// 	for (int i = 0; i < 10000; i++)
// 	{
// 		vector_buffer.push_back(Buffer());
// 	}

// 	for (int i = 0; i < 10000; i++)
// 	{
// 		const int idx = rand() % 10000;
// 		vector_buffer[idx].idx = 5;
// 	}
// 	ft::vector<Buffer>().swap(vector_buffer);
// 	try
// 	{
// 		for (int i = 0; i < 1000; i++)
// 		{
// 			const int idx = rand() % 10000;
// 			vector_buffer.at(idx);
// 			std::cerr << "Error: THIS vector SHOULD BE EMPTY!!" <<std::endl;
// 		}

// 	}
// 	catch(const std::exception& e)
// 	{
// 		//NORMAL ! :P
// 	}

// 	for (int i = 0; i < 10000; ++i)
// 	{
// 		map_int.insert(ft::make_pair(rand(), rand()));
// 	}
	

// 	int sum = 0;
// 	for (int i = 0; i < 10000; i++)
// 	{
// 		int access = rand();
// 		sum += map_int[access];
// 	}
// 	std::cout << "should be constant with the same seed: " << sum << std::endl;

// 	{
// 		ft::map<int, int> copy = map_int;
// 	}
// 	Mutantstack<char> iterable_stack;
// 	for (char letter = 'a'; letter <= 'z'; letter++)
// 		iterable_stack.push(letter);
// 	for (Mutantstack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
// 	{
// 		std::cout << *it;
// 	}
// 	std::cout << std::endl;

// 	gettimeofday(&time, NULL);  //END-TIME

// 	totalTime = (((time.tv_sec * 1000) + (time.tv_usec / 1000)) - totalTime);

// 	std::cout << "Execution time is " << totalTime << std::endl;

// 	std::cout << "ft::is_integral : " << ft::is_integral<unsigned int>::value << std::endl;
// 	return (0);
// }