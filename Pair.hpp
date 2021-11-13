#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft
{
template <class T1, class T2>
struct pair
{

	private:

	public:
		T1 first;
		T2 second;

	typedef T1 first_type;
	typedef T2 second_type;


		//		CONSTRUCTORS/DESTRUCTOR
		//___________________________________
		pair(void) : first(T1()), second(T2()){}

		pair (const first_type& a, const second_type& b) : first(a), second(b){}
		
		template<class U, class V>
		pair(const pair<U, V> &cpy) : first(T1(cpy.first)), second(T2(cpy.second)) {}

		~pair()
		{

		}
		


		//IMPLICITELY DECLARED  =operator
		
};

template <class T1, class T2>
ft::pair<T1,T2> make_pair (T1 x, T2 y)
{
	return (pair<T1, T2>(x, y));
}


//		OPERATORS
//___________________________________
template< class T1, class T2 >
bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
{
	return(lhs.first == rhs.first && lhs.second == rhs.second);
}
template< class T1, class T2 >
bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
{
	return(lhs.first != rhs.first && lhs.second != rhs.second);
}

template< class T1, class T2 >
bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
{
	return(lhs.first < rhs.first && lhs.second < rhs.second);
}

template< class T1, class T2 >
bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
{
	return(lhs.first <= rhs.first && lhs.second <= rhs.second);
}

template< class T1, class T2 >
bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
{
	return(lhs.first > rhs.first && lhs.second > rhs.second);
}

template< class T1, class T2 >
bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
{
	return(lhs.first >= rhs.first && lhs.second >= rhs.second);
}

}


#endif