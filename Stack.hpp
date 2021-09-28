#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include <typeinfo>
#include <type_traits>
#include "Vector.hpp"

namespace ft
{
	template <class T>
	class Stack
	{
		private :
			Vector<T>		_vector;

		public :
			typedef T				value_type;
			typedef Vector<T>		container_type;
			typedef unsigned int	size_type;

		//		CONSTRUCTOR/DESTRUCTOR
		//___________________________________
		
			Stack()
			{
			}
			Stack(const Vector<T> &cpy)
			{
				typename ft::Vector<T>::iterator begin = cpy.begin();
				typename ft::Vector<T>::iterator end = cpy.end();

				_vector.assign(begin, end);
			}

		//		UTILS
		//___________________________________
		bool empty(void)
		{
			return (!_vector.size());
		}
		size_type size(void) const
		{
			return (_vector.size());
		}
		value_type& top() /*throw (std::exception)*/
		{
			if (empty())
				throw std::runtime_error("top() called on empty stack.");
			return (_vector.back());
		}
		const value_type& top() const
		{
			if (empty())
				throw std::runtime_error("top() called on empty stack.");
			return (_vector.back());
		}
		void push(const value_type& val)
		{
			_vector.push_back(val);
		}
		void pop(void)
		{
			if (empty())
				throw std::runtime_error("pop called on empty stack.");
			_vector.pop_back();
		}

		//		OPERATORS
		//___________________________________
		bool operator==(const Stack<T> &rhs)
		{
			return (_vector == rhs._vector);
		}
		bool operator!=(const Stack<T> &rhs)
		{
			return (_vector != rhs._vector);
		}
		bool operator<(const Stack<T> &rhs)
		{
			return (_vector < rhs._vector);
		}
		bool operator<=(const Stack<T> &rhs)
		{
			return (_vector <= rhs._vector);
		}
		bool operator>(const Stack<T> &rhs)
		{
			return (_vector > rhs._vector);
		}
		bool operator>=(const Stack<T> &rhs)
		{
			return (_vector >= rhs._vector);
		}
	};
}

#endif