#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include <typeinfo>
#include <type_traits>
#include "Vector.hpp"
#include "Iterator.hpp"

namespace ft
{
	template <class T, class Container = vector<T> >
	class stack
	{
		protected :
			Container		c;

		public :
			typedef T				value_type;
			typedef Container		container_type;
			typedef unsigned int	size_type;

		//		CONSTRUCTOR/DESTRUCTOR
		//___________________________________
		
			stack()
			{
			}
			stack(const vector<T> &cpy)
			{
				typename ft::vector<T>::iterator begin = cpy.begin();
				typename ft::vector<T>::iterator end = cpy.end();

				c.assign(begin, end);
			}

		//		UTILS
		//___________________________________
		bool empty(void)
		{
			return (!c.size());
		}
		size_type size(void) const
		{
			return (c.size());
		}
		value_type& top() /*throw (std::exception)*/
		{
			if (empty())
				throw std::runtime_error("top() called on empty stack.");
			return (c.back());
		}
		const value_type& top() const
		{
			if (empty())
				throw std::runtime_error("top() called on empty stack.");
			return (c.back());
		}
		void push(const value_type& val)
		{
			c.push_back(val);
		}
		void pop(void)
		{
			if (empty())
				throw std::runtime_error("pop called on empty stack.");
			c.pop_back();
		}

		private :
		//		OPERATORS
		//___________________________________
		friend bool operator==(const stack<T> &lhs, const stack<T> &rhs)
		{
			return (lhs.c == rhs.c);
		}
		friend bool operator!=(const stack<T> &lhs, const stack<T> &rhs)
		{
			return (lhs.c != rhs.c);
		}
		friend bool operator<(const stack<T> &lhs, const stack<T> &rhs)
		{
			return (lhs.c < rhs.c);
		}
		friend bool operator<=(const stack<T> &lhs, const stack<T> &rhs)
		{
			return (lhs.c <= rhs.c);
		}
		friend bool operator>(const stack<T> &lhs, const stack<T> &rhs)
		{
			return (lhs.c > rhs.c);
		}
		friend bool operator>=(const stack<T> &lhs, const stack<T> &rhs)
		{
			return (lhs.c >= rhs.c);
		}
	};
}

#endif