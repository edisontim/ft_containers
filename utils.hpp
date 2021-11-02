#ifndef UTILS_HPP
#define UTILS_HPP

#include "Iterator.hpp"

namespace ft
{
	template<class InputIterator>
	typename ft::iterator_traits<InputIterator>::difference_type
	distance (InputIterator first, InputIterator last)
	{
		return (last - first);
	}

	template <class InputIterator, class Distance>
	void advance (InputIterator& it, Distance n)
	{
		it = it + n;
	}


	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1) return (false);
			else if (*first1 < *first2) return (true);
			first1++;
			first2++;
		}
		return (first2 != last2);
	}

	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || comp(*first2,*first1)) return (false);
			else if (comp(*first1 < *first2)) return (true);
			first1++;
			first2++;
		}
		return (first2 != last2);
	}

	
	template <class Iter>
	class reverse_iterator : public ft::iterator <	typename iterator_traits<Iter>::iterator_category, 
												typename iterator_traits<Iter>::value_type, 
												typename iterator_traits<Iter>::difference_type, 
												typename iterator_traits<Iter>::pointer, 
												typename iterator_traits<Iter>::reference>
	{

		private:
		Iter	p;
		
		public:

			typedef typename iterator_traits<Iter>::value_type value_type;
			typedef typename iterator_traits<Iter>::difference_type difference_type;
			typedef typename iterator_traits<Iter>::pointer pointer;
			typedef typename iterator_traits<Iter>::reference reference;
			typedef typename iterator_traits<Iter>::iterator_category iterator_category;

		struct iterator_traits
		{
			typedef typename Iter::value_type			value_type;
			typedef typename Iter::difference_type		difference_type;
			typedef typename Iter::pointer				pointer;
			typedef typename Iter::reference			reference;
			typedef typename Iter::iterator_category	iterator_category;

		};
		
		//		CONSTRUCTOR/DESTRUCTOR
		//___________________________________
		reverse_iterator() : p() {}
		reverse_iterator(reverse_iterator const &cpy) : p(cpy.p - 1) {}
		reverse_iterator(Iter &i) : p(i - 1) {}
		~reverse_iterator() {}

		//		UTILS
		//___________________________________
		
		
		//		OPERATORS
		//___________________________________
		reverse_iterator  &operator=(reverse_iterator const &rhs)
		{
			if (*this != rhs)
			{
				p = rhs.p;
			}
			return (*this);
		}
		friend reverse_iterator operator+(reverse_iterator const &lhs, int n)
		{
			return (reverse_iterator(lhs.p - n));
		}
		friend reverse_iterator operator+(int n, reverse_iterator const &lhs)
		{
			return (reverse_iterator(lhs.p - n));
		}		
		friend reverse_iterator operator-(reverse_iterator const &lhs, int n)
		{
			return (reverse_iterator(lhs.p + n));
		}
		difference_type operator-(reverse_iterator &n)
		{
			return(n.p - p);
		}
		reverse_iterator operator+=(int n)
		{
			p = p - n;
			return (*this);
		}
		reverse_iterator operator-=(int n)
		{
			p = p + n;
			return (*this);
		}
		reverse_iterator operator++(void)
		{
			p--;
			return (*this); 
		}
		reverse_iterator operator++(int blank)
		{
			(void)blank;
			reverse_iterator temp(*this);
			++*this;
			return (temp);
		}
		reverse_iterator operator--(void)
		{
			p++;
			return (*this);
		}
		reverse_iterator operator--(int blank)
		{
			(void)blank;
			reverse_iterator temp(*this);
			--*this;
			return (temp);
		}
		reference operator*()
		{
			return (*p);
		}
		pointer operator->()
		{
			return (p.operator->());
		}
		const pointer operator->() const
		{
			return (p.operator->());
		}
		reference operator[](int m)
		{
			return (*(this + m));
		}
		friend bool operator==(reverse_iterator const &lhs, reverse_iterator const &rhs)
		{
			return (rhs.p == lhs.p);
		}
		friend bool operator!=(reverse_iterator const &lhs, reverse_iterator const &rhs)
		{
			return (rhs.p != lhs.p ? true : false);
		}
		friend bool operator<(reverse_iterator const &lhs, reverse_iterator const &rhs)
		{
			return (lhs.p < rhs.p ? false : true);
		}
		friend bool operator<=(reverse_iterator const &lhs, reverse_iterator const &rhs)
		{
			return (!(rhs < lhs));
		}
		friend bool operator>(reverse_iterator const &lhs, reverse_iterator const &rhs)
		{
			return (lhs.p > rhs.p ? false : true);
		}
		friend bool operator>=(reverse_iterator const &lhs, reverse_iterator const &rhs)
		{
			return (!(lhs < rhs));
		}
	};

	// template <class Iter>
	// class const_reverse_iterator : public reverse_iterator <Iter>
	// {

	// 	private:
	// 	Iter	p;
		
	// 	public:

	// 		typedef typename iterator_traits<Iter>::value_type value_type;
	// 		typedef typename iterator_traits<Iter>::difference_type difference_type;
	// 		typedef typename iterator_traits<Iter>::pointer pointer;
	// 		typedef typename iterator_traits<Iter>::reference reference;
	// 		typedef typename iterator_traits<Iter>::iterator_category iterator_category;

	// 	struct iterator_traits
	// 	{
	// 		typedef typename Iter::value_type			value_type;
	// 		typedef typename Iter::difference_type		difference_type;
	// 		typedef typename Iter::pointer				pointer;
	// 		typedef typename Iter::reference			reference;
	// 		typedef typename Iter::iterator_category	iterator_category;

	// 	};
		
	// 	//		CONSTRUCTOR/DESTRUCTOR
	// 	//___________________________________
	// 	const_reverse_iterator() : p() {}
	// 	const_reverse_iterator(const_reverse_iterator const &cpy) : p(cpy.p) {}
	// 	const_reverse_iterator(reverse_iterator<Iter> cpy): p(cpy.p) {}
	// 	const_reverse_iterator(Iter const &i) : p(i - 1) {}
	// 	~const_reverse_iterator() {}


	// 	//		UTILS
	// 	//___________________________________
		
		
	// 	//		OPERATORS
	// 	//___________________________________
	// 	const_reverse_iterator  &operator=(const_reverse_iterator const &rhs)
	// 	{
	// 		if (*this != rhs)
	// 		{
	// 			p = rhs.p;
	// 		}
	// 		return (*this);
	// 	}
	// 	friend const_reverse_iterator operator+(const_reverse_iterator const &lhs, int n)
	// 	{
	// 		return (const_reverse_iterator(lhs.p - n));
	// 	}
	// 	friend const_reverse_iterator operator+(int n, const_reverse_iterator const &lhs)
	// 	{
	// 		return (const_reverse_iterator(lhs.p - n));
	// 	}		
	// 	friend const_reverse_iterator operator-(const_reverse_iterator const &lhs, int n)
	// 	{
	// 		return (const_reverse_iterator(lhs.p + n));
	// 	}
	// 	difference_type operator-(const_reverse_iterator &n)
	// 	{
	// 		return(n.p - p);
	// 	}
	// 	const_reverse_iterator operator+=(int n)
	// 	{
	// 		p = p - n;
	// 		return (*this);
	// 	}
	// 	const_reverse_iterator operator-=(int n)
	// 	{
	// 		p = p + n;
	// 		return (*this);
	// 	}
	// 	const_reverse_iterator operator++(void)
	// 	{
	// 		p--;
	// 		return (*this); 
	// 	}
	// 	const_reverse_iterator operator++(int blank)
	// 	{
	// 		(void)blank;
	// 		const_reverse_iterator temp(*this);
	// 		++*this;
	// 		return (temp);
	// 	}
	// 	const_reverse_iterator operator--(void)
	// 	{
	// 		p++;
	// 		return (*this);
	// 	}
	// 	const_reverse_iterator operator--(int blank)
	// 	{
	// 		(void)blank;
	// 		const_reverse_iterator temp(*this);
	// 		--*this;
	// 		return (temp);
	// 	}
	// 	const reference operator*()
	// 	{
	// 		return (*p);
	// 	}
	// 	const pointer operator->() const
	// 	{
	// 		return (p.operator->());
	// 	}
	// 	reference operator[](int m)
	// 	{
	// 		return (*(this + m));
	// 	}
	// 	// friend bool operator==(const_reverse_iterator const &lhs, const_reverse_iterator const &rhs)
	// 	// {
	// 	// 	return (rhs.p == lhs.p);
	// 	// }
	// 	// friend bool operator!=(const_reverse_iterator const &lhs, const_reverse_iterator const &rhs)
	// 	// {
	// 	// 	return (rhs.p != lhs.p ? true : false);
	// 	// }
	// 	// friend bool operator<(const_reverse_iterator const &lhs, const_reverse_iterator const &rhs)
	// 	// {
	// 	// 	return (lhs.p < rhs.p ? false : true);
	// 	// }
	// 	// friend bool operator<=(const_reverse_iterator const &lhs, const_reverse_iterator const &rhs)
	// 	// {
	// 	// 	return (!(rhs < lhs));
	// 	// }
	// 	// friend bool operator>(const_reverse_iterator const &lhs, const_reverse_iterator const &rhs)
	// 	// {
	// 	// 	return (lhs.p > rhs.p ? false : true);
	// 	// }
	// 	// friend bool operator>=(const_reverse_iterator const &lhs, const_reverse_iterator const &rhs)
	// 	// {
	// 	// 	return (!(lhs < rhs));
	// 	// }
	// };
}
#endif