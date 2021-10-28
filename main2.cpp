#include <map>
#include <iostream>
#include <utility>
int main()
{
	std::map<int, int> a;
	a.insert(std::make_pair(10,10));
	a.insert(std::make_pair(10,20));
	std::cout << (a.begin())->second << std::endl;
}