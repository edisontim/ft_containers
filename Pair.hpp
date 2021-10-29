#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft
{
template <class T1, class T2>
class pair
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
		
		template<class U, class V>
		pair(const pair<U, V> &cpy) : first(cpy.first), second(cpy.second) {}
		
		pair (const first_type& a, const second_type& b) : first(a), second(b){}
		
		~pair()
		{

		}
		
		//		OPERATORS
		//___________________________________
		pair& operator=(const pair &cpy)
		{
			this->first = T1(cpy.first);
			this->second = T2(cpy.second);
			
			return (*this);
		}
		bool operator==(const pair &rhs)
		{
			return(first == rhs.first && second == rhs.second);
		}
		bool operator!=(const pair &rhs)
		{
			return(first != rhs.first && second != rhs.second);
		}

		bool operator<(const pair &rhs)
		{
			return(first < rhs.first && second < rhs.second);
		}

		bool operator<=(const pair &rhs)
		{
			return(first <= rhs.first && second <= rhs.second);
		}

		bool operator>(const pair &rhs)
		{
			return(first > rhs.first && second > rhs.second);
		}

		bool operator>=(const pair &rhs)
		{
			return(first >= rhs.first && second >= rhs.second);
		}
};

template <class T1, class T2>
ft::pair<T1,T2> make_pair (T1 x, T2 y)
{
	return (pair<T1, T2>(x, y));
}

}


#endif