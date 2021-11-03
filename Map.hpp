#ifndef MAP_HPP
#define MAP_HPP

#include "Pair.hpp"
#include "Vector.hpp"
#include <functional>

namespace ft
{
template <class Key, class T, class Compare = std::less<Key> >
class map
{

	
	public:

	typedef Key													key_type;
	typedef T													mapped_type;
	typedef pair<Key, T>										value_type;
	typedef const Compare 										key_compare;
	typedef typename vector<value_type>::iterator				iterator;
	typedef typename vector<value_type>::reverse_iterator		reverse_iterator;
	typedef unsigned int										size_type;
	typedef typename vector<value_type>::const_iterator			const_iterator;
	typedef typename vector<value_type>::const_reverse_iterator	const_reverse_iterator;
	typedef std::allocator<T>									allocator_type;


	class value_compare : public std::binary_function<value_type, value_type, bool>
	{
		public:
			bool operator()(const value_type& left, const value_type& right) const
			{
				return (comp(left.first, right.first));
			}
			value_compare(key_compare pred) : comp(pred) {}
		protected:
			key_compare comp;
	};

	private:
		vector<value_type>	_vector;
		Compare				_comp;

	public:

		//		CONSTRUCTORS/DESTRUCTOR
		//___________________________________
		map(const key_compare& comp = key_compare(), const allocator_type &alloc = allocator_type())
		{
			_vector = vector<value_type>(alloc);
			_comp = comp;
		}
		map (const map &x)
		{
			const_iterator begin = x._vector.begin();
			const_iterator end = x._vector.end();

			vector<value_type> buff = x._vector;
			_vector = buff;
			_comp = Compare();
			_vector.assign(begin, end);
		}
		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type &alloc = allocator_type())
		{
			_vector.allocator = alloc;
			_vector = vector<pair<Key, T> >();
			_vector.assign(first, last);
			_comp = comp;
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
			if (!_vector.size() && !_vector.capacity())
				_vector.reserve(1);
			else if (_vector.size() >= _vector.capacity())
				_vector.reserve(_vector.capacity() * 2);
			pair<iterator, bool> a = insert(ft::make_pair(k, mapped_type()));
			return a.first->second;
		}

		//		UTILS
		//___________________________________
		iterator begin()
		{
			return (_vector.begin());
		}
		const_iterator begin() const
		{
			return (_vector.begin());
		}
		iterator end()
		{
			return (_vector.end());
		}
		const_iterator end() const
		{
			return (_vector.end());
		}
		reverse_iterator rbegin()
		{
			return (_vector.rbegin());
		}
		const_reverse_iterator rbegin() const
		{
			return (_vector.rbegin());
		}
		reverse_iterator rend()
		{
			return (_vector.rend());
		}
		const_reverse_iterator rend() const
		{
			return (_vector.rend());
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
				return (ft::make_pair(_vector.begin(), true));
			}
			iterator dup_key = find(val.first);
			if (dup_key != _vector.end()) // iterator's different from the end of the vector, this means we found a key the same as the one we want to insert
				return (ft::make_pair<iterator, bool>(dup_key, false));
			iterator insert_pos = this->insert_pos(val.first);
			_vector.insert(insert_pos, val);
			return (ft::make_pair<iterator, bool>(insert_pos, true));
		}
		
		iterator insert (iterator position, const value_type& val)
		{
			iterator dup_key = find(val.first);
			if (dup_key != _vector.end()) // iterator's different from the end of the vector, this means we found a key the same as the one we want to insert
				return (dup_key);
			if (_comp(position->first, val.first) && _comp(val.first, (*(position + 1)).first))
				return (_vector.insert(position + 1, value_type(val)));
			else
				return (insert(val).first);
		}

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last)
		{
			InputIterator iter = first;
			while (iter != last)
			{
				insert(*iter);
				iter++;
			}
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
			return (_comp);
		}
		value_compare value_comp() const
		{
			return (value_compare(_comp));
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

}



#endif