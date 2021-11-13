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

#include <deque>

namespace ft
{
	template <class T, class Container = std::deque<T> >
	class stack
	{

		public :
			typedef Container							container_type;
			typedef typename Container::value_type		value_type;
			typedef typename Container::size_type		size_type;
			typedef typename Container::reference		reference;
			typedef typename Container::const_reference	const_reference;

		protected :
			container_type		c;

		public :
		//		CONSTRUCTOR/DESTRUCTOR
		//___________________________________
		
			stack(const Container &cont = Container()) : c(cont) {}

			stack(const stack &cpy) : c(cpy.c) {}

			~stack() {}

			stack &operator=(const stack &other)
			{
				if (this != &other)
				{
					c = other.c;
				}
				return (*this);
			}
			
		//		UTILS
		//___________________________________
			reference top()
			{
				return (c.back());
			}

			const_reference top() const
			{
				return (c.back());
			}

			bool empty(void) const
			{
				return (!c.size());
			}

			size_type size(void) const
			{
				return (c.size());
			}

			void push(const value_type& val)
			{
				c.push_back(val);
			}

			void pop(void)
			{
				c.pop_back();
			}

		//		OPERATORS
		//___________________________________

		friend bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
		{
			return (lhs.c == rhs.c);
		}

		friend bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
		{
			return (lhs.c != rhs.c);
		}

		friend bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
		{
			return (lhs.c < rhs.c);
		}

		friend bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
		{
			return (lhs.c <= rhs.c);
		}

		friend bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
		{
			return (lhs.c > rhs.c);
		}

		friend bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
		{
			return (lhs.c >= rhs.c);
		}
	};

}

#endif