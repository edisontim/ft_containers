#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft
{
template <class T1, class T2>
class Pair
{

	private:

	public:
		T1 first;
		T2 second;

	typedef T1 first_type;
	typedef T2 second_type;


		//		CONSTRUCTORS/DESTRUCTOR
		//___________________________________
		Pair(void) : first(T1()), second(T2())
		{
			first = T1();
			second = T2();
		}
		Pair(const Pair &cpy) : first(T1(cpy.first)), second(T2(cpy.second))
		{

		}
		Pair (const first_type& a, const second_type& b) : first(T1(a)), second(T2(b))
		{
		}
		~Pair()
		{

		}
		
		//		OPERATORS
		//___________________________________
		Pair& operator=(const Pair &cpy)
		{
			this->first = T1(cpy.first);
			this->second = T2(cpy.second);
			return (*this);
		}
		bool operator==(const Pair &rhs)
		{
			return(first == rhs.first && second == rhs.second);
		}
		bool operator!=(const Pair &rhs)
		{
			return(first != rhs.first && second != rhs.second);
		}

		bool operator<(const Pair &rhs)
		{
			return(first < rhs.first && second < rhs.second);
		}

		bool operator<=(const Pair &rhs)
		{
			return(first <= rhs.first && second <= rhs.second);
		}

		bool operator>(const Pair &rhs)
		{
			return(first > rhs.first && second > rhs.second);
		}

		bool operator>=(const Pair &rhs)
		{
			return(first >= rhs.first && second >= rhs.second);
		}
};

template <class T1, class T2>
ft::Pair<T1,T2> make_pair (T1 x, T2 y)
{
	return (Pair<T1, T2>(x, y));
}


}


#endif