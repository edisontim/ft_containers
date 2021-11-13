#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include <typeinfo>
#include <type_traits>
#include <cstddef>

#include "Iterator.hpp"
#include "utils.hpp"


namespace ft
{

template <class T, class Alloc = std::allocator<T> >
class vector
{

	public:
		typedef T											value_type;
		typedef Alloc										allocator_type;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef size_t										size_type;
		typedef std::ptrdiff_t								difference_type;
		typedef T*											iterator;
		typedef const T*									const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;


		//		ATTRIBUTES
		//___________________________________
	private:
		T							*_array;
		size_type					_capacity;
		size_type					_size;
		allocator_type				_allocator;

		//		ALLOC AND COPY FOR DYNAMIC ARRAY
		//_________________________________________
		void _alloc_copy(size_type temp_cap)
		{
			unsigned int	i;
			pointer		buff;
			
			try
			{
				buff = _allocator.allocate(temp_cap);
			}
			catch (std::exception &e)
			{
				std::cout << e.what() << std::endl;
				return;
			}
			i = 0;
			while (i < _size)
			{
				_allocator.construct(&buff[i], _array[i]);
				_allocator.destroy(&_array[i]);
				i++;
			}
			_allocator.deallocate(_array, _capacity);
			_array = buff;
			_capacity = temp_cap;
		}


	public:

		//		OPERATORS
		//___________________________________
		vector const &operator=(vector const &rhs)
		{
			unsigned int	i;

			i = 0;
			this->_allocator = rhs._allocator;
			clear();
			_allocator.deallocate(_array, _capacity);
			this->_capacity = rhs._capacity;
			i = 0;
			try
			{
				this->_array = _allocator.allocate(rhs._capacity);
			}
			catch (std::exception &e)
			{
				std::cout << e.what() << std::endl;
			}
			while (i < rhs._size)
			{
				_allocator.construct(&this->_array[i], rhs._array[i]);
				i++;
			}
			this->_size = rhs._size;
			return (*this);
		}

		value_type &operator[](int n)
		{
			return (*(_array + n));
		}

		const_reference operator[](int n) const
		{
			return (*(_array + n));
		}




		//		CONSTRUCTOR/DESTRUCTOR
		//___________________________________
		explicit vector(const allocator_type& alloc = allocator_type()) : _array(NULL), _capacity(0), _size(0), _allocator(alloc) {}

		explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _array(NULL), _capacity(0), _size(0), _allocator(alloc)
		{
			size_type	i;
			
			i = 0;
			while (i < n)
			{
				push_back(val);
				i++;
			}
		}

		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type*  = nullptr) : _array(NULL), _capacity(0), _size(0), _allocator(alloc)
		{
			assign(first, last);
		}

		vector (const vector& x) : _array(NULL), _capacity(0), _size(0), _allocator(Alloc())
		{
			const_iterator begin = x.begin();
			const_iterator last = x.end();

			assign(begin, last);
		}

		~vector()
		{
			size_type	i;

			i = 0;
			while (i < _size)
				_allocator.destroy(&_array[i++]);
			_allocator.deallocate(_array, _capacity);
		}

		//		UTILS
		//___________________________________
		iterator begin()
		{
			return (iterator(_array));
		}

		const_iterator begin() const
		{
			return (const_iterator(iterator(_array)));
		}

		iterator end()
		{
			return (iterator(_array + _size));
		}

		const_iterator end() const
		{
			return (iterator(_array + _size));
		}

		reverse_iterator rbegin()
		{
			return (reverse_iterator(iterator(_array + _size)));
		}

		const_reverse_iterator rbegin() const
		{
			return (const_reverse_iterator(const_iterator(_array + _size)));
		}

		reverse_iterator rend()
		{
			return (reverse_iterator(iterator(_array)));
		}

		const_reverse_iterator rend() const
		{
			return (const_reverse_iterator(const_iterator(_array)));
		}

		void push_back(const value_type &val)
		{
			if (_size < _capacity)
			{
				_allocator.construct(&_array[_size], val);
			}
			else
			{
				size_type	temp_cap;

				temp_cap = _capacity * 2;
				if (!_capacity)
					temp_cap = 1;
				if (temp_cap > max_size())
					throw std::exception();
				_alloc_copy(temp_cap);
				_allocator.construct(&_array[_size], val);
			}
			_size++;
		}

		void pop_back(void)
		{
			_allocator.destroy(&_array[_size - 1]);
			_size--;
		}

		size_type	size(void) const
		{
			return (_size);
		}
		// if our array is bigger than difference_type::max() then the subtraction of two pointers will be undefined behaviour, for example when using ft::distance(first, last)
		// capacity is unsigned int, so max number of objects is UINT_MAX
		size_type max_size() const
		{
			return (_allocator.max_size());
		}

		void resize(size_type n, value_type val = value_type())
		{
			if (n < _size)
			{
				while (n < _size)
					this->pop_back();
			}
			else if (n > _size)
			{
				while (n > _size)
					push_back(val);
			}
		}

		size_type capacity() const
		{
			return (this->_capacity);
		}

		bool empty() const
		{
			return (!_size);
		}

		void reserve(size_type n)
		{
			if (n > _capacity)
			{
				if (n > max_size())
					return ;
				_alloc_copy(n);
			}	
		}

		reference at(size_type n)
		{
			if (_size <= n)
				throw std::exception();
			else
				return (_array[n]);
		}

		const_reference at(size_type n) const
		{
			if (_size <= 1)
				throw std::exception();
			else
				return (_array[n]);
		}

		reference front()
		{
			return (_array[0]);
		}

		const_reference front() const
		{
			return (_array[0]);
		}

		reference back()
		{
			return (_array[_size - 1]);
		}

		const_reference back() const
		{
			return (_array[_size - 1]);
		}

		T* data()
		{
			return (_array);
		}

		template<typename InputIterator>
		void assign(InputIterator first, InputIterator last, typename ft::enable_if<!(ft::is_integral<InputIterator>::value) >::type*  = nullptr)
		{
			size_type i;

			i = 0;
			clear();
			if (static_cast<size_type>(last - first) > _capacity)
			{
				_allocator.deallocate(_array, _capacity);
				_capacity = (last - first) * 2;
				_array = _allocator.allocate(_capacity);
			}
			i = 0;
			while (first != last)
			{
				_allocator.construct(&_array[i++], *first);
				_size++;
				first++;
			}
		}

		void assign(size_type n, const value_type &val)
		{
			size_type i;
			clear();
			if (n > _capacity)
			{
				_allocator.deallocate(_array, _capacity);
				_capacity = n * 2;
				_array = _allocator.allocate(_capacity);
			}
			i = 0;
			while (i < n)
			{
				_allocator.construct(&_array[i], val);
				_size++;
				i++;
			}
		}

		private :

		iterator	single_val_opti_insert(iterator position, const value_type &val)
		{
			iterator	iter;
			int			i;

			i = _size;
			iter = end();
			while (iter != position)
			{
				_allocator.construct(&_array[i], _array[i - 1]);
				iter--;
				i--;
			}
			_allocator.construct(&_array[i], val);
			_size++;
			return (iterator(&_array[i]));
		}

		public :

		iterator	insert(iterator position, const value_type& val)
		{
			pointer		buff;
			size_type	i;
			size_type	temp_cap;

			i = 0;
			iterator iter = this->begin();
			iterator end = this->end();

			//if we've reached max capacity, we need to double _capacity
			if (_size == _capacity)
				temp_cap = _capacity * 2;
			else
				return (single_val_opti_insert(position, val));
			
			//in case allocation fails
			try
			{
				buff = _allocator.allocate(temp_cap);
			}
			catch (std::exception &e)
			{
				std::cerr << e.what() << std::endl;
				throw e;
			}
			//constructing a copy of elements in the original array until position to insert new one
			while (iter != position)
			{
				_allocator.construct(&buff[i], _array[i]);
				iter++;
				i++;
			}
			//inserting new element in the buffer array
			_allocator.construct(&buff[i], val);
			iterator to_ret(&buff[i]);
			i++;

			//copying the rest of the original array in the buffer array
			while (iter != end)
			{
				_allocator.construct(&buff[i], *iter);
				i++;
				iter++;
			}

			// clear the array and deallocate the space
			size_type temp_size = _size;
			clear();
			_allocator.deallocate(_array, _capacity);
			_array = buff;

			//size is + 1 because we inserted an extra element
			_size = temp_size + 1;
			_capacity = temp_cap;

			//returning iterator to position we inserted the element
			return (to_ret);
		}

		void insert(iterator position, size_type n, const value_type& val)
		{
			T			*buff;
			size_type	i;
			size_type	j;
			size_type	temp_cap = _capacity;

			if (temp_cap == 0)
				temp_cap = 1;
			j = 0;
			i = 0;
			iterator iter = this->begin();
			iterator end = this->end();
			// if the current size + n is bigger than the current capacity we double it until capacity is bigger
			if (_size + n > _capacity)
			{
				while (temp_cap < (n + _size))
					temp_cap *= 2;
			}
			else
				temp_cap = _capacity;
			
			//in case allocation fails
			try
			{
				buff = _allocator.allocate(temp_cap);
			}
			catch (std::exception &e)
			{
				std::cout << e.what() << std::endl;
				throw e;
			}

			//constructing a copy of elements in the original array until position to insert new ones
			while (iter != position)
			{
				_allocator.construct(&buff[i], _array[i]);
				iter++;
				i++;
			}

			//constructing n copies of value in the buffer array
			while (j < n)
			{
				_allocator.construct(&buff[i], val);
				i++;
				j++;
			}

			//constructing a copy of the rest of the elements in the original array
			while (iter != end)
			{
				_allocator.construct(&buff[i], *iter);
				i++;
				iter++;
			}
			
			// clear the array and deallocate the space
			size_type temp_size = _size;
			clear();
			_allocator.deallocate(_array, _capacity);
			_capacity = temp_cap;
			_array = buff;

			//size is + 1 because we inserted n extra elements
			_size = temp_size + n;
		}

		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type*  = nullptr)
		{
			T			*buff;
			size_type	i;
			size_type	j;
			size_type	temp_cap = _capacity;

			if (temp_cap == 0)
				temp_cap = 1;
			i = 0;
			iterator iter = this->begin();
			iterator end = this->end();
			j = last - first;
			// if the current size + n is bigger than the current capacity we double it until capacity is bigger
			if (_size + j > _capacity)
			{
				while (temp_cap < (j + _size))
					temp_cap *= 2;
			}
			else
				temp_cap = _capacity;

			//in case allocation fails
			try
			{
				buff = _allocator.allocate(temp_cap);
			}
			catch (std::exception &e)
			{
				std::cout << e.what() << std::endl;
				return ;
			}

			//constructing a copy of elements in the original array until position to insert new ones
			while (iter != position)
			{
				_allocator.construct(&buff[i], _array[i]);
				iter++;
				i++;
			}

			//constructing a copy in buff of elements between first and last 
			while (first != last)
			{
				_allocator.construct(&buff[i], *first);
				i++;
				first++;
			}

			//constructing a copy of the rest of the array inside the buffer array
			while (iter != end)
			{
				_allocator.construct(&buff[i], *iter);
				i++;
				iter++;
			}
			size_type temp_size = _size;

			// clear the array and deallocate the space
			clear();
			_allocator.deallocate(_array, _capacity);
			_capacity = temp_cap;
			_array = buff;

			//size is + j because we inserted j extra elements (j = last - first)
			_size = temp_size + j;
		}

		iterator erase (iterator position)
		{
			iterator	iter = position;
			size_type	i;

			i = position - begin();

			//destroy elements at the specified position, and replacing that element by the following one, 
			//starting at the correct position
			while (iter != end())
			{
				_allocator.destroy(&(*iter));
				_allocator.construct(&(*iter), *(iter + 1));
				iter++;
			}
			_size--;
			return (iterator(&_array[i]));
		}

		iterator erase (iterator first, iterator last)
		{
			//getting the starting index of the erased elements
			difference_type position = first - begin();
			difference_type distance = last - first;
			difference_type pos_to_ret = position;
			
			if (first > last)
				return (NULL);
			
			//destroy the elements
			while (first != last)
			{	
				_allocator.destroy(&(*first));
				first++;
			}

			// constructing the elements after the last deleted one, at the index of the start of the deleted ones
			while (first != this->end())
			{
				_allocator.construct(&_array[position], *first);
				_allocator.destroy(&(*first));
				position++;
				first++;
			}
			_size = _size - distance;
			return (iterator(&_array[pos_to_ret]));
		}

		void swap (vector& x)
		{
			T*			_array_buff;
			size_type	_size_buff;
			size_type	_capacity_buff;

			_array_buff = this->_array;
			_size_buff = this->_size;
			_capacity_buff = this->_capacity;

			this->_array = x._array;
			this->_size = x._size;
			this->_capacity = x._capacity; 

			x._array = _array_buff;
			x._size = _size_buff;
			x._capacity = _capacity_buff;
		}

		void clear()
		{
			size_type	i;

			i = 0;
			while (i < _size)
			{
				_allocator.destroy(&_array[i]);
				i++;
			}
			_size = 0;
		}

		allocator_type get_allocator() const
		{
			return (_allocator);
		}


};


		template <class T, class Alloc>
		bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			unsigned long	i;

			i = 0;
			if (lhs.size() != rhs.size())
				return (false);
			while (i < lhs.size())
			{
				if (lhs[i] != rhs[i])
					return (false);
				i++;
			}
			return (true);
		}

		template <class T, class Alloc>
		bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return (!(lhs == rhs));
		}
		
		template <class T, class Alloc>
		bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			typename ft::vector<T, Alloc>::const_iterator begin1 = lhs.begin();
			typename ft::vector<T, Alloc>::const_iterator last1 = lhs.end();

			typename ft::vector<T, Alloc>::const_iterator begin2 = rhs.begin();
			typename ft::vector<T, Alloc>::const_iterator end2 = rhs.end();
			return (ft::lexicographical_compare<typename ft::vector<T, Alloc>::const_iterator, typename ft::vector<T, Alloc>::const_iterator>(begin1, last1, begin2, end2));
		}

		template <class T, class Alloc>
		bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return (!(rhs < lhs));
		}
		template <class T, class Alloc>
		bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return (rhs < lhs);
		}
		template <class T, class Alloc>
		bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return (!(lhs < rhs));
		}

		template< class T, class Alloc >
		void swap( ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs )
		{
			lhs.swap(rhs);
		}

}

#endif
