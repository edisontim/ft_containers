#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include <typeinfo>
#include <type_traits>

double pow2(double num)
{
	return (num * num);
}

namespace ft
{
template <class T>
class Vector
{
	private:
		T	*_array;
		unsigned int	_capacity;
		unsigned int	_size;
		std::allocator<T> _allocator;

	public:
		typedef T					value_type;
		typedef T*					pointer;
		typedef T const *			const_pointer;
		typedef T&					reference;
		typedef T const &			const_reference;
		typedef unsigned int		size_type;
		typedef std::allocator<T>	allocator_type;
		typedef std::ptrdiff_t		difference_type;

	private: 
		void _alloc_copy(size_type temp_cap)
		{
			unsigned int	i;
			value_type		*buff;
			
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
				buff[i] = _array[i];
				i++;
			}
			_allocator.deallocate(_array, _capacity);
			_array = buff;
			_capacity = temp_cap;
		}
	
	public:

		//		OPERATORS
		//___________________________________
		Vector const &operator=(Vector const &rhs)
		{
			T				*buffer;
			unsigned int	i;

			i = 0;
			this->_allocator = rhs._allocator;
			while (i < _size)
				_allocator.destroy(&_array[i++]);
			_allocator.deallocate(_array, _capacity);
			i = 0;
			try
			{
				this->_array = _allocator.allocate(rhs._capacity);
			}
			catch (std::exception &e)
			{
				std::cout << e.what() << std::endl;
				return;
			}
			while (i < this->_occupied_space)
			{
				buffer[i] = rhs._array[i];
				i++;
			}
			this->_capacity = rhs._capacity;
			this->_size = rhs._size;
			this->_array = buffer;
		}

		value_type &operator[](int n)
		{
			return (*(_array + n));
		}

		const_reference operator[](int n) const
		{
			return (*(_array + n));
		}

		bool operator==(const Vector<T> &rhs)
		{
			unsigned int	i;

			i = 0;
			if (_size != rhs._size)
				return (false);
			while (i < _size)
			{
				if (_array[i] != rhs._array[i])
					return (false);
				i++;
			}
			return (true);
		}
		bool operator!=(const Vector<T> &rhs)
		{
			unsigned int	i;

			i = 0;
			if (_size != rhs._size)
				return (true);
			while (i < _size)
			{
				if (_array[i] != rhs._array[i])
					return (true);
				i++;
			}
			return (false);
		}
		bool operator<(const Vector<T> &rhs)
		{
			unsigned int i;

			i = 0;
			while (i < _size && i < rhs._size)
			{
				if (_array[i] < rhs._array[i])
					return (true);
				if (_array[i] > rhs._array[i])
					return (false);
				i++;
			}
			return (_size < rhs._size ? true : false);
		}
		bool operator<=(const Vector<T> &rhs)
		{
			unsigned int i;

			i = 0;
			while (i < _size && i < rhs._size)
			{
				if (_array[i] <= rhs._array[i])
					return (true);
				if (_array[i] > rhs._array[i])
					return (false);
				i++;
			}
			return (_size <= rhs._size ? true : false);
		}
		bool operator>(const Vector<T> &rhs)
		{
			unsigned int i;

			i = 0;
			while (i < _size && i < rhs._size)
			{
				if (_array[i] > rhs._array[i])
					return (true);
				if (_array[i] < rhs._array[i])
					return (false);
				i++;
			}
			return (_size > rhs._size ? true : false);
		}
		bool operator>=(const Vector<T> &rhs)
		{
			unsigned int i;

			i = 0;
			while (i < _size && i < rhs._size)
			{
				if (_array[i] >= rhs._array[i])
					return (true);
				if (_array[i] < rhs._array[i])
					return (false);
				i++;
			}
			return (_size >= rhs._size ? true : false);
		}

// 							ITERATOR_BEGINNING
// _________________________________________________________________________

		class iterator
		{
			private:
				T		*_pointer;

			public:
				bool	rev;

				typedef T								value_type;
				typedef std::ptrdiff_t					difference_type;
				typedef T*								pointer;
				typedef T&								reference;
				typedef const T&						const_reference;
				typedef std::random_access_iterator_tag	iterator_category;

			//		CONSTRUCTOR/DESTRUCTOR
			//___________________________________
			iterator() : _pointer(NULL), rev(0)
			{
			}
			iterator(T *pointer) : _pointer(pointer), rev(0)
			{
			}
			~iterator()
			{
			}
			iterator(iterator const &cpy) : _pointer(cpy._pointer), rev(0)
			{
			}
			//		OPERATORS
			//___________________________________
			iterator  &operator=(iterator const &rhs)
			{
				if (*this != rhs)
				{
					_pointer = rhs._pointer;
				}
				return (*this);
			}
			iterator operator+(int n)
			{
				return (iterator(_pointer + n));
			}
			iterator operator-(int n)
			{
				return (iterator(_pointer - n));
			}
			difference_type operator-(iterator &n)
			{
				return(_pointer - n._pointer);
			}
			iterator const &operator++(void)
			{
				_pointer++;
				return (*this); 
			}
			iterator const &operator++(int blank)
			{
				(void)blank;
				iterator temp(*this);
				++*this;
				return (*this);
			}
			iterator const &operator--(void)
			{
				_pointer--;
				return (*this);
			}
			iterator const &operator--(int blank)
			{
				(void)blank;
				iterator temp(*this);
				--*this;
				return (temp);
			}
			reference operator*()
			{
				return (*_pointer);
			}
			pointer operator->()
			{
				return (_pointer);
			}
			const pointer operator->() const
			{
				return (_pointer);
			}
			reference operator[](int m)
			{
				return (*(_pointer + m));
			}
			bool operator==(iterator &rhs)
			{
				return (rhs._pointer == _pointer);
			}
			bool operator==(iterator const &rhs) const
			{
				return (rhs._pointer == _pointer);
			}
			bool operator!=(iterator const &rhs) const
			{
				return (rhs._pointer != _pointer ? true : false);
			}
			bool operator>(iterator const & rhs) const
			{
				return (_pointer > rhs._pointer ? true : false); 
			}
			bool operator<(iterator const & rhs) const
			{
				return (_pointer < rhs._pointer ? true : false);
			}
		};

		class reverse_iterator
		{
			private:
				T		*_pointer;

			public:
				bool	rev;

				typedef T value_type;
				typedef std::ptrdiff_t difference_type;
				typedef T* pointer;
				typedef T& reference;
				typedef std::random_access_iterator_tag iterator_category;
			
			//		CONSTRUCTOR/DESTRUCTOR
			//___________________________________
			reverse_iterator() : _pointer(NULL), rev(1)
			{
			}
			reverse_iterator(T *pointer) : _pointer(pointer), rev(1)
			{
			}
			reverse_iterator(reverse_iterator const &cpy) : _pointer(cpy._pointer), rev(1)
			{
			}
			~reverse_iterator()
			{
			}
			//		OPERATORS
			//___________________________________
			reverse_iterator  &operator=(reverse_iterator const &rhs)
			{
				if (*this != rhs)
				{
					_pointer = rhs._pointer;
				}
				return (*this);
			}
			reverse_iterator operator+(int n)
			{
				return (reverse_iterator(_pointer - n));
			}
			reverse_iterator operator-(int n)
			{
				return (reverse_iterator(_pointer + n));
			}
			difference_type operator-(reverse_iterator &n)
			{
				return(n._pointer - _pointer);
			}
			reverse_iterator const &operator++(void)
			{
				_pointer--;
				return (*this); 
			}
			reverse_iterator const &operator++(int blank)
			{
				(void)blank;
				reverse_iterator temp(*this);
				++*this;
				return (*this);
			}
			reverse_iterator const &operator--(void)
			{
				_pointer++;
				return (*this);
			}
			reverse_iterator const &operator--(int blank)
			{
				(void)blank;
				reverse_iterator temp(*this);
				--*this;
				return (temp);
			}
			reference operator*()
			{
				return (*_pointer);
			}
			pointer operator->()
			{
				return (_pointer);
			}
			const pointer operator->() const
			{
				return (_pointer);
			}
			reference operator[](int m)
			{
				return (*(_pointer + m));
			}
			bool operator==(reverse_iterator const &rhs)
			{
				return (rhs._pointer == _pointer);
			}
			bool operator!=(reverse_iterator const &rhs) const
			{
				return (rhs._pointer != _pointer ? true : false);
			}
			bool operator>(reverse_iterator const & rhs) const
			{
				return (_pointer > rhs._pointer ? false : true);
			}
			bool operator<(reverse_iterator const & rhs) const
			{
				return (_pointer < rhs._pointer ? false : true);
			}
		};

// 							ITERATOR_END
// _________________________________________________________________________

	
		//		CONSTRUCTOR/DESTRUCTOR
		//___________________________________
		Vector() :  _array(NULL), _capacity(0), _size(0), _allocator(allocator_type())
		{
		}

		Vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _size(static_cast<int>(n)), _allocator(alloc)
		{
			size_type	i;
			
			i = 0;
			while (i < n)
				push_back(val);
		}

		~Vector()
		{
			unsigned int	i;

			i = 0;
			while (i < _size)
				_allocator.destroy(&_array[i++]);
			_allocator.deallocate(_array, _capacity);
		}

		Vector(iterator first, iterator last, const allocator_type& alloc = allocator_type()) : _allocator(alloc), _size(0), _capacity(0) 
		{
			while (first != last)
			{
				push_back(*first);
				first++;
			}
		}

		//		UTILS
		//___________________________________
		iterator begin()
		{
			return (iterator(_array));
		}
		const iterator begin() const
		{
			return (iterator(_array));
		}
		iterator end()
		{
			if (empty())
				return (begin());
			return (iterator(_array + _size));
		}
		const iterator end() const
		{
			if (empty())
				return (begin());
			return (iterator(_array + _size));
		}
		reverse_iterator rbegin()
		{
			return (reverse_iterator(_array + _size - 1));
		}
		const reverse_iterator rbegin() const
		{
			return (reverse_iterator(_array + _size - 1));
		}
		reverse_iterator rend()
		{
			if (empty())
				return (rbegin());
			return (reverse_iterator(_array - 1));
		}
		const reverse_iterator rend() const
		{
			if (empty())
				return (rbegin());
			return (reverse_iterator(_array - 1));
		}
		void push_back(const value_type val)
		{
			if (_size != _capacity)
				_array[_size] = val;
			else
			{
				size_type	temp_cap;

				if (!_capacity)
					temp_cap = 1;
				else
					temp_cap = _capacity * 2;
				if (temp_cap > max_size())
					return ;
				_alloc_copy(temp_cap);
				_array[_size] = val;
			}
			_size++;
		}
		void pop_back(void)
		{
			_allocator.destroy(&_array[_size - 1]);
			_size--;
		}
		unsigned int	size(void) const
		{
			return (_size);
		}
		// if our array is bigger than difference_type::max() then the subtraction of two pointers will be undefined behaviour, for example when using ft::distance(first, last)
		// capacity is unsigned int, so max number of objects is UINT_MAX
		size_type max_size() const
		{
			return (std::min(std::numeric_limits<difference_type>::max(), static_cast<long>(UINT_MAX)));
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
			if (n > static_cast<size_type>(_capacity))
			{
				size_type	temp_cap = n * 2;

				if (temp_cap > max_size())
					return ;
				_alloc_copy(temp_cap);
			}	
		}
		reference at(size_type n)
		{
			if (n > _size - 1)
				throw std::out_of_range("Not in the range of the vector");
			else
				return (_array[n]);
		}
		const_reference at(size_type n) const
		{
			if (n > _size - 1)
				throw std::out_of_range("Not in the range of the vector");
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
		template<typename InputIterator>
		void assign(InputIterator first, InputIterator last)
		{
			size_type i;

			i = 0;
			clear();
			InputIterator iter = first;
			while (iter != last)
			{
				iter++;
				i++;
			}
			if (i > _capacity)
			{
				_allocator.deallocate(_array, _capacity);
				_capacity = i * 2;
				_array = _allocator.allocate(_capacity);
			}
			i = 0;
			while (first != last)
			{
				_array[i] = *first;
				_size++;
				first++;
			}
		}
		void assign(size_type n, const value_type &val)
		{
			size_type i;

			clear();
			if (n > static_cast<size_type>(_capacity))
			{
				_allocator.deallocate(_array, _capacity);
				_capacity = n * 2;
				_array = _allocator.allocate(_capacity);
			}
			i = 0;
			while (i < n)
			{
				_array[i] = value_type(val);
				_size++;
				i++;
			}
		}
		iterator insert(iterator position, const value_type& val)
		{
			pointer buff;
			unsigned int	i;
			unsigned int	temp_cap;

			i = 0;
			iterator iter = this->begin();
			iterator end = this->end();
			if (_size + 1 > _capacity)
				temp_cap= _capacity + 1;
			else 
				temp_cap = _capacity;
			try
			{
				buff = _allocator.allocate(temp_cap);
			}
			catch (std::exception &e)
			{
				std::cerr << e.what() << std::endl;
				return NULL;
			}
			while (iter != position)
			{
				buff[i] = _array[i];
				iter++;
				i++;
			}
			buff[i] = val;
			i++;
			while (iter != end)
			{
				buff[i] = *iter;
				i++;
				iter++;
			}
			_allocator.deallocate(_array, _capacity);
			_array = buff;
			_size++;
			_capacity = temp_cap;
			return (++position);
		}
		void insert(iterator position, size_type n, const value_type& val)
		{
			T			*buff;
			unsigned int			i;
			size_type	j;
			unsigned int			temp_cap;

			j = 0;
			i = 0;
			iterator iter = this->begin();
			iterator end = this->end();
			if (_size + _size > _capacity)
				temp_cap = _capacity + n;
			else
				temp_cap = _capacity;
			try
			{
				buff = _allocator.allocate(temp_cap);
			}
			catch (std::exception &e)
			{
				std::cout << e.what() << std::endl;
				throw e;
			}
			while (iter != position)
			{
				buff[i] = _array[i];
				iter++;
				i++;
			}
			while (j < n)
			{
				buff[i] = val;
				i++;
				j++;
			}
			while (iter != end)
			{
				buff[i] = *iter;
				i++;
				iter++;
			}
			_allocator.deallocate(_array, _capacity);
			_capacity = temp_cap;
			_array = buff;
			_size += n;
		}
		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last)
		{
			T			*buff;
			unsigned int			i;
			size_type	j;
			unsigned int			temp_cap;


			i = 0;
			iterator iter = this->begin();
			iterator end = this->end();
			j = distance(first, last);
			if (_size + j > _capacity)
				temp_cap = _capacity + j;
			else
				temp_cap = _capacity;
			try
			{
				buff = _allocator.allocate(temp_cap);
			}
			catch (std::exception &e)
			{
				std::cout << e.what() << std::endl;
				return ;
			}
			while (iter != position)
			{
				buff[i] = _array[i];
				iter++;
				i++;
			}
			while (first != last)
			{
				buff[i] = *first;
				i++;
				first++;
			}
			while (iter != end)
			{
				buff[i] = *iter;
				i++;
				iter++;
			}
			_allocator.deallocate(_array, _capacity);
			_capacity = temp_cap;
			_array = buff;
			_size += j;
		}
		iterator erase (iterator position)
		{
			iterator	iter;
			T			*buff;
			unsigned int			i;
			iterator	deleted;

			i = 0;
			_allocator.destroy(&(*position));
			deleted = this->end();
			if (position != this->end() - 1)
			{
				buff = _allocator.allocate(_capacity);
				iter = begin();
				while (iter != position)
				{
					buff[i] = *iter;
					i++;
					iter++; 
				}
				iter++;
				deleted = iter;
				while (iter != this->end())
				{
					buff[i] = *iter;
					iter++;
					i++;
				}
				_allocator.deallocate(_array, _capacity);
				_array = buff;
			}
			_size--;
			return (deleted);
		}
		iterator erase (iterator first, iterator last)
		{
			iterator	iter;
			T			*buff;
			unsigned int			i;
			iterator	deleted;

			i = 0;
			buff = _allocator.allocate(_capacity);
			iter = begin();
			if (first > last)
				return (NULL);
			while (iter != first)
			{
				buff[i] = *iter;
				i++;
				iter++; 
			}
			while (iter != last)
			{	
				_allocator.destroy(&(*iter));
				iter++;
			}
			deleted = iter;
			while (iter != this->end())
			{
				buff[i] = *iter;
				iter++;
				i++;
			}
			_allocator.deallocate(_array, _capacity);
			_array = buff;
			_size = _size - distance(first, last);
			return (deleted);
		}
		void swap (Vector& x)
		{
			T*	_array_buff;
			unsigned int	_size_buff;
			unsigned int	_capacity_buff;

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
			unsigned int	i;

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

	template<class InputIterator>
	typename std::iterator_traits<InputIterator>::difference_type
	distance (InputIterator first, InputIterator last)
	{
		return (last - first);
	}
	template <class InputIterator, class Distance>
	void advance (InputIterator& it, Distance n)
	{
		it = it + n;
	}
}

#endif