#ifndef MAP_HPP
#define MAP_HPP

#include "pair.hpp"
#include "vector.hpp"

namespace ft
{
template <class Key, class T, class Compare = std::less<Key> >
class map
{

	
	public:

	typedef Key													key_type;
	typedef T													mapped_type;
	typedef pair<key_type, mapped_type>							value_type;
	typedef bool 												(*key_compare)();
	typedef typename vector<pair<Key, T> >::iterator			iterator;
	typedef typename vector<pair<Key, T> >::reverse_iterator	reverse_iterator;
	typedef unsigned int										size_type;
	typedef const iterator										const_iterator;
	typedef std::allocator<T>									allocator_type;


	class value_compare : public std::binary_function<value_type, value_type, bool>
	{
		public:
			bool operator()(const value_type& left, const value_type& right) const;
			value_compare(key_compare pred) : comp(pred)
			{

			}
		protected:
			key_compare comp;
	};

	private:
		vector<value_type>	_vector;
		Compare				_comp;

	public:

		//		CONSTRUCTORS/DESTRUCTOR
		//___________________________________
		map(const Compare& comp = Compare()) : _vector(vector<pair<Key, T> >())
		{
			this->_comp = comp;
		}
		map (const map &x)
		{
			iterator begin = x._vector.begin();
			iterator end = x._vector.end();

			vector<value_type> buff = x._vector;
			_vector = buff;
			_vector.assign(begin, end);
		}
		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare& comp = key_compare()) : _comp(comp)
		{
			_vector = vector<pair<Key, T> >();
			_vector.assign(first, last);
		}
		~map()
		{

		}


		//		OPERATORS
		//___________________________________
		map &operator=(const map &rhs)
		{
			_vector = rhs._vector;
		}
		mapped_type& operator[] (const key_type& k)
		{
			if (_vector.size() >= _vector.capacity())
				_vector.reserve(_vector.capacity() * 2);
			return insert(ft::make_pair(k, mapped_type())).first->second;
		}

		//		UTILS
		//___________________________________
		iterator begin()
		{
			return (_vector.begin());
		}
		const iterator begin() const
		{
			return (_vector.begin());
		}
		iterator end()
		{
			return (_vector.end());
		}
		const iterator end() const
		{
			return (_vector.end());
		}
		bool empty() const
		{
			return (_vector.empty());
		}
		size_type size() const
		{
			return (_vector.size());
		}
		size_type max_size() const
		{
			return (_vector.max_size());
		}

		iterator find (const key_type& k)
		{
			iterator ret = binary_search(k);
			// std::cout << (*ret).first << std::endl;
			return (ret);
		}
		const iterator find (const key_type &k) const
		{
			iterator ret = binary_search(k);
			return (const_cast<iterator>(ret));
		}

		pair<iterator,bool> insert(const value_type& val)
		{
			if (_vector.empty())
			{
				_vector.push_back(val);
				return (ft::make_pair(iterator(&_vector.back()), true));
			}
			iterator dup_key = find(val.first);
			if (dup_key != _vector.end()) // iterator's different from the end of the vector, this means we found a key the same as the one we want to insert
				return(ft::make_pair<iterator, bool>(dup_key, false));
			iterator insert_pos = this->insert_pos(val.first);
			if (insert_pos == _vector.end() && _vector.size() == 1)
			{
				iterator buff;
				if (_comp(val.first, _vector[0].first))
				{
					buff = iterator(&_vector[0]);
					_vector.insert(buff, val);
				}
				else
				{
					buff = iterator(&_vector.back());
					_vector.push_back(val);
				}
				return (ft::make_pair(buff, true));
			}
			_vector.insert(insert_pos, val);
			return (ft::make_pair<iterator, bool>(insert_pos, true));
		}

	private:
		iterator binary_search(const key_type &key)
		{
			int start = 0;
			int end = _vector.size() - 1;

			while (start <= end)
			{
				int mid = start + (end - start) / 2;
				if (key == _vector[mid].first)
					return (iterator(&_vector[mid]));
				else if (_comp(_vector[mid].first, key))
					start = mid + 1;
				else
					end = mid - 1;
			}
			return (_vector.end());
		}
		iterator insert_pos(const key_type &key)
		{
			int start = 0;
			int end = _vector.size() - 1;

			while (start <= end)
			{
				int mid = (start + end) / 2;
				if (_comp(_vector[mid].first, key))
					start = mid + 1;
				else
					end = mid - 1;
			}
			return (iterator(&_vector[end + 1]));
		}
		
		public : 

		void erase (iterator position)
		{
			_vector.erase(position);
		}
		size_type erase (const key_type& k)
		{
			iterator to_erase = find(k);
			if (to_erase == end())
				return (0);
			else
			{
				_vector.erase(to_erase);
				return (1);
			}
		}
		void erase (iterator first, iterator last)
		{
			_vector.erase(first, last);
		}
		void swap (map& x)
		{
			_vector.swap(x._vector);
		}
		void clear()
		{
			_vector.clear();
		}
		key_compare key_comp() const
		{
			return (key_comp);
		}
		value_compare value_comp() const
		{
			return (value_compare());
		}
		size_type count (const key_type &k)
		{
			if (this->find(k) != end())
				return (1);
			else
				return (0);
		}
		iterator lower_bound (const key_type& k)
		{
			unsigned int i;

			i = 0;
			while (i < size())
			{
				if (!_comp(_vector[i].first, k))
					return (iterator(&_vector[i]));
				i++;
			}
			return (end());
		}
		const_iterator lower_bound (const key_type& k) const
		{
			unsigned int i;

			i = 0;
			while (i < size())
			{
				if (!_comp(_vector[i].first, k))
					return (const_iterator(&_vector[i]));
				i++;
			}
			return (end());
		}
		iterator upper_bound (const key_type& k)
		{
			unsigned int i;

			i = 0;

			while (i < size())
			{
				if (_comp(k, _vector[i].first))
					return (iterator(&_vector[i]));
				i++;
			}
			return (end());
		}
		const_iterator upper_bound (const key_type& k) const
		{
			unsigned int i;

			i = 0;
			while (i < size())
			{
				if (_comp(k, _vector[i].first))
					return (const_iterator(&_vector[i]));
				i++;
			}
			return (end());
		}
		pair<const_iterator,const_iterator>	equal_range (const key_type& k) const
		{
			iterator to_find = find(k);
			if (to_find != end())
				return (ft::make_pair(lower_bound(k), upper_bound(k)));
			else
				return (ft::make_pair(find(k), find(k)));
		}
		pair<iterator,iterator>				equal_range (const key_type& k)
		{
			iterator to_find = find(k);
			if (to_find != end())
				return (ft::make_pair(lower_bound(k), upper_bound(k)));
			else
				return (ft::make_pair(upper_bound(k), upper_bound(k)));
		}
		allocator_type get_allocator() const
		{
			return (_vector.get_allocator());
		}
};
	template<bool Cond, class T = void> struct enable_if {};
	template<class T> struct enable_if<true, T> { typedef T type; };

	template<typename T> struct is_integral_base: std::false_type {};

	template<> struct is_integral_base<bool>						: public std::true_type {};
	
	template<> struct is_integral_base<char>						: public std::true_type {};
	template<> struct is_integral_base<unsigned char>				: public std::true_type {};
	
	template<> struct is_integral_base<char16_t>					: public std::true_type {};
	template<> struct is_integral_base<char32_t>					: public std::true_type {};
	
	template<> struct is_integral_base<wchar_t>						: public std::true_type {};
	template<> struct is_integral_base<unsigned wchar_t>			: public std::true_type {};

	template<> struct is_integral_base<short>						: public std::true_type {};
	template<> struct is_integral_base<unsigned short>				: public std::true_type {};
	
	template<> struct is_integral_base<int>							: public std::true_type {};
	
	template<> struct is_integral_base<long>						: public std::true_type {};
	template<> struct is_integral_base<unsigned long>				: public std::true_type {};
	
	template<> struct is_integral_base<long long>					: public std::true_type {};
	template<> struct is_integral_base<unsigned long long>			: public std::true_type {};

	template<class T> struct is_integral : public is_integral_base<typename std::remove_cv<T>::type > {};

}



#endif