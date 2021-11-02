#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include <typeinfo>
#include <type_traits>

#include "Iterator.hpp"
#include "utils.hpp"

double pow2(double num)
{
	return (num * num);
}

namespace ft
{

template <class T, class Alloc = std::allocator<T> >
class vector
{
	private:
		T							*_array;
		unsigned int				_capacity;
		unsigned int				_size;
		Alloc						_allocator;

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
				buff[i] = _array[i];
				i++;
			}
			_allocator.deallocate(_array, _capacity);
			_array = buff;
			_capacity = temp_cap;
		}

		public :
		class iterator : public ft::iterator<ft::random_access_iterator_tag, value_type, difference_type, pointer, reference>
		{
			private:

			public:

				T		*_pointer;
				typedef T								value_type;
				typedef ptrdiff_t						difference_type;
				typedef T*								pointer;
				typedef T&								reference;
				typedef const T&						const_reference;
		
			template <class Iterator>
			struct iterator_traits
			{
				typedef typename Iterator::value_type			value_type;
				typedef typename Iterator::difference_type		difference_type;
				typedef typename Iterator::pointer				pointer;
				typedef typename Iterator::reference			reference;
				typedef typename Iterator::iterator_category	iterator_category;

			};
			//		CONSTRUCTOR/DESTRUCTOR
			//___________________________________
			iterator() : _pointer(NULL)
			{
			}

			iterator(T *pointer) : _pointer(pointer)
			{
			}

			~iterator()
			{
			}

			iterator(iterator const &cpy) : _pointer(cpy._pointer)
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
			friend iterator operator+(iterator const &lhs, int n)
			{
				return (iterator(lhs._pointer + n));
			}
			friend iterator operator+(int n, iterator const &lhs)
			{
				return (iterator(lhs._pointer + n));
			}
			friend iterator operator-(iterator const &lhs, int n)
			{
				return (iterator(lhs._pointer - n));
			}
			difference_type operator-(iterator &n)
			{
				return(_pointer - n._pointer);
			}
			iterator operator+=(int n)
			{
				_pointer += n;
				return (*this);
			}
			iterator operator-=(int n)
			{
				_pointer -= n;
				return (*this);
			}
			iterator operator++(void)
			{	
				_pointer++;
				return (*this); 
			}
			iterator operator++(int blank)
			{
				(void)blank;
				iterator temp(*this);
				++*this;
				return (temp);
			}
			iterator operator--(void)
			{
				_pointer--;
				return (*this);
			}
			iterator operator--(int blank)
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
			// reference operator*() const
			// {
			// 	return (*_pointer);
			// }
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
			friend bool operator==(iterator const &lhs, iterator const &rhs)
			{
				return (rhs._pointer == lhs._pointer);
			}
			friend bool operator!=(iterator const &lhs, iterator const &rhs)
			{
				return (rhs._pointer != lhs._pointer);
			}
			friend bool operator<(iterator const &lhs, iterator const & rhs)
			{
				return (lhs._pointer < rhs._pointer);
			}
			friend bool operator<=(iterator const &lhs, iterator const &rhs)
			{
				return (lhs._pointer <= rhs._pointer);
			}
			friend bool operator>(iterator const &lhs, iterator const & rhs)
			{
				return (lhs._pointer > rhs._pointer);
			}
			friend bool operator>=(iterator const &lhs, iterator const &rhs)
			{
				return (lhs._pointer >= rhs._pointer);
			}
		};

		public :
		
		class const_iterator : public ft::iterator<ft::random_access_iterator_tag, value_type, difference_type, pointer, reference>
		{
			private:

			public:

				T		*_pointer;
				typedef T								value_type;
				typedef ptrdiff_t						difference_type;
				typedef T*								pointer;
				typedef T&								reference;
				typedef const T&						const_reference;
		
			template <class Iterator>
			struct iterator_traits
			{
				typedef typename Iterator::value_type			value_type;
				typedef typename Iterator::difference_type		difference_type;
				typedef typename Iterator::pointer				pointer;
				typedef typename Iterator::reference			reference;
				typedef typename Iterator::iterator_category	iterator_category;

			};

			//		CONSTRUCTOR/DESTRUCTOR
			//___________________________________
			const_iterator() : _pointer(NULL)
			{
			}
			const_iterator(T *pointer) : _pointer(pointer)
			{
			}

			~const_iterator()
			{
			}

			const_iterator(const_iterator const &cpy) : _pointer(cpy._pointer)
			{
			}

			const_iterator(iterator const &cpy) : _pointer(const_cast<const pointer>(cpy._pointer))
			{
			}

			//		OPERATORS
			//___________________________________
			const_iterator  &operator=(const_iterator const &rhs)
			{
				if (*this != rhs)
				{
					_pointer = rhs._pointer;
				}
				return (*this);
			}
			friend const_iterator operator+(const_iterator const &lhs, int n)
			{
				return (const_iterator(lhs._pointer + n));
			}
			friend const_iterator operator+(int n, const_iterator const &lhs)
			{
				return (const_iterator(lhs._pointer + n));
			}
			friend const_iterator operator-(const_iterator const &lhs, int n)
			{
				return (const_iterator(lhs._pointer - n));
			}
			difference_type operator-(const_iterator &n)
			{
				return(_pointer - n._pointer);
			}
			const_iterator operator+=(int n)
			{
				_pointer += n;
				return (*this);
			}
			const_iterator operator-=(int n)
			{
				_pointer -= n;
				return (*this);
			}
			const_iterator operator++(void)
			{	
				_pointer++;
				return (*this); 
			}
			const_iterator operator++(int blank)
			{
				(void)blank;
				const_iterator temp(*this);
				++*this;
				return (temp);
			}
			const_iterator operator--(void)
			{
				_pointer--;
				return (*this);
			}
			const_iterator operator--(int blank)
			{
				(void)blank;
				const_iterator temp(*this);
				--*this;
				return (temp);
			}
			const_reference operator*()
			{
				return (*_pointer);
			}
			const pointer operator->() const
			{
				return (_pointer);
			}
			const_reference operator[](int m)
			{
				return (*(_pointer + m));
			}
			friend bool operator==(const_iterator const &lhs, const_iterator const &rhs)
			{
				return (rhs._pointer == lhs._pointer);
			}
			friend bool operator!=(const_iterator const &lhs, const_iterator const &rhs)
			{
				return (rhs._pointer != lhs._pointer);
			}
			friend bool operator<(const_iterator const &lhs, const_iterator const & rhs)
			{
				return (lhs._pointer < rhs._pointer);
			}
			friend bool operator<=(const_iterator const &lhs, const_iterator const &rhs)
			{
				return (lhs._pointer <= rhs._pointer);
			}
			friend bool operator>(const_iterator const &lhs, const_iterator const & rhs)
			{
				return (lhs._pointer > rhs._pointer);
			}
			friend bool operator>=(const_iterator const &lhs, const_iterator const &rhs)
			{
				return (lhs._pointer >= rhs._pointer);
			}
		};

		
		class reverse_iterator : public ft::reverse_iterator<iterator> {};
		class const_reverse_iterator : public ft::const_reverse_iterator<iterator> {};
		
// 							ITERATOR_END
// _________________________________________________________________________



	public:
		// typedef reverse_iterator<iterator>	reverse_iterator;
		// typedef const_reverse_iterator<iterator>	const_reverse_iterator;
		//		OPERATORS
		//___________________________________
		vector const &operator=(vector const &rhs)
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
				buffer = _allocator.allocate(rhs._capacity);
			}
			catch (std::exception &e)
			{
				std::cout << e.what() << std::endl;
			}
			while (i < _size)
			{
				buffer[i] = rhs._array[i];
				i++;
			}
			this->_capacity = rhs._capacity;
			this->_size = rhs._size;
			this->_array = buffer;
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
		vector(const allocator_type& alloc = allocator_type()) : _array(NULL), _capacity(0), _size(0), _allocator(alloc) {}

		vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _size(static_cast<int>(n)), _allocator(alloc)
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
		vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) : _allocator(alloc)
		{
			assign(first, last);
		}

		vector (const vector& x)
		{
			iterator begin = x.begin();
			iterator last = x.end();

			assign(begin, last);
		}

		~vector()
		{
			unsigned int	i;

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
			return (const_reverse_iterator(iterator(_array + _size)));
		}
		reverse_iterator rend()
		{
			return (reverse_iterator(iterator(_array)));
		}
		const_reverse_iterator rend() const
		{
			if (empty())
				return (rbegin());
			return (const_reverse_iterator(iterator(_array)));
		}
		void push_back(const value_type val)
		{
			if (_size < _capacity)
			{
				_array[_size] = val;
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
			return (std::numeric_limits<difference_type>::max());
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
			if (_size <= n)
				throw std::exception();
			else
				return (_array[n]);
		}
		const_reference at(size_type n) const
		{
			if (n > _size - 1)
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
				_array[i] = value_type(first);
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

		private :

		iterator	single_val_opti_insert(iterator position, const value_type &val)
		{
			iterator	iter;
			int			i;

			i = _size;
			iter = end();
			while (iter != position)
			{
				_array[i] = _array[i - 1];
				iter--;
				i--;
			}
			_array[i] = val;
			_size++;
			return (iterator(&_array[i]));
		}

		public :

		iterator	insert(iterator position, const value_type& val)
		{
			pointer buff;
			unsigned int	i;
			unsigned int	temp_cap;

			i = 0;
			iterator iter = this->begin();
			iterator end = this->end();

			if (_size >= _capacity)
				temp_cap = _capacity * 2;
			else
				return (single_val_opti_insert(position, val));
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
			_size = _size - ft::distance<iterator>(first, last);
			return (deleted);
		}
		void swap (vector& x)
		{
			T*				_array_buff;
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


		template <class T, class Alloc>
		bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			unsigned int	i;

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
			typename ft::vector<T, Alloc>::iterator begin1 = lhs.begin();
			typename ft::vector<T, Alloc>::iterator last1 = lhs.end();

			typename ft::vector<T, Alloc>::iterator begin2 = rhs.begin();
			typename ft::vector<T, Alloc>::iterator end2 = rhs.end();
			return (ft::lexicographical_compare<typename ft::vector<T, Alloc>::iterator, typename ft::vector<T, Alloc>::iterator>(begin1, last1, begin2, end2));
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



}

#endif
