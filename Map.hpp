#ifndef MAP_HPP
#define MAP_HPP

#include "Pair.hpp"
#include "Vector.hpp"

namespace ft
{
template <class Key, class T, class Compare = std::less<Key> >
class Map
{
	public:

	typedef Key													key_type;
	typedef T													mapped_type;
	typedef Pair<key_type, mapped_type>							value_type;
	typedef bool 												(*key_compare)();
	typedef typename Vector<Pair<Key, T> >::iterator			iterator;
	typedef typename Vector<Pair<Key, T> >::reverse_iterator	reverse_iterator;
	
	private:
		Vector<Pair<Key, T> > _vector;
		Compare				_comp;

	public:
		//		CONSTRUCTORS/DESTRUCTOR
		//___________________________________
		Map(const Compare& comp = Compare()) : _vector(Vector<Pair<Key, T> >())
		{
			this->_comp = comp;
		}
		Map (const Map &x)
		{
			iterator begin = x._vector.begin();
			iterator end = x._vector.end();

			_vector = Vector<Pair<Key, T> >(x);
			_vector.assign(begin, end);
		}
		template <class InputIterator>
		Map(InputIterator first, InputIterator last, const key_compare& comp = key_compare()) : _comp(comp)
		{
			_vector = Vector<Pair<Key, T> >();
			_vector.assign(first, last);
		}
		~Map()
		{

		}


		//		OPERATORS
		//___________________________________
		Map &operator=(const Map &rhs)
		{
			_vector = rhs._vector;
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
		iterator find (const key_type& k)
		{
			const iterator ret = binary_search(0, _vector.size() - 1, k);
			return (ret);
		}
		const iterator find (const key_type &k) const
		{
			return (binary_search(0, _vector.size() - 1, k));
		}

		Pair<iterator,bool> insert(const value_type& val)
		{
			if (_vector.empty())
			{
				_vector.push_back(val);
				return (ft::make_pair(iterator(&_vector.back()), true));
			}
			iterator dup_key = find(val.first);
			if (dup_key != _vector.end()) // iterator's different from the end of the vector, this means we found a key the same as the one we want to insert
				return(ft::make_pair<iterator, bool>(dup_key, false));
			iterator insert_pos = this->insert_pos(0, _vector.size() - 1, val.first);
			if (insert_pos == _vector.end())
			{
				if (_comp(val.first, _vector[0].first))
					_vector.insert(iterator(&_vector[0]), val);
				else
					_vector.push_back(val);
				return (ft::make_pair(iterator(&_vector.back()), true));
			}
			_vector.insert(insert_pos, val);
			return (ft::make_pair<iterator, bool>(insert_pos, true));
		}

	private:
		iterator binary_search(int low, int high, const key_type &key)
		{
			if (high < low)
				return (_vector.end());
			int mid = (low + high) / 2;
			if (key == _vector[mid].first)
				return (iterator(&_vector[mid]));
			if (key > _vector[mid].first)
				return (binary_search(mid + 1, high, key));
			return (binary_search(low, (mid - 1), key));
		}
		iterator insert_pos(int low, int high, const key_type &key)
		{
			unsigned int mid = (low + high) / 2;
			if (mid + 1 == _vector.size())
				return (_vector.end());
			if (_vector[mid].first < key && key < _vector[mid + 1].first)
				return (iterator(&_vector[mid + 1]));
			if (_comp(_vector[mid].first, key))
				return (insert_pos(mid + 1, high, key));
			return (insert_pos(low, (mid - 1), key));
		}
};
}


#endif