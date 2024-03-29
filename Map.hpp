#ifndef MAP_HPP
#define MAP_HPP

#include "Pair.hpp"
#include "Vector.hpp"
#include <functional>
#include "RBT/RBT.hpp"

namespace ft
{
template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T> > >
class map
{

	public:

		typedef Key													key_type;
		typedef T													mapped_type;
		typedef pair<const Key, T>									value_type;
		typedef std::size_t											size_type;
		typedef std::ptrdiff_t										difference_type;
		typedef Compare 											key_compare;
		typedef Allocator											allocator_type;
		typedef value_type&											reference;
		typedef const value_type&									const_reference;
		typedef value_type*											pointer;
		typedef const pointer										const_pointer;
		typedef RBTree<ft::map<Key, T, Compare>, allocator_type>	RBTree;
		typedef typename RBTree::Node_ptr							Node_ptr;

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

		RBTree								rbt;
		Compare								_comp;
		allocator_type						_alloc;

	public:

		//		CONSTRUCTORS/DESTRUCTOR
		//___________________________________
		explicit map(const key_compare& comp = key_compare(), 
				const allocator_type &alloc = allocator_type()) : rbt(RBTree()), _comp(comp), _alloc(alloc) {}

		template <class InputIterator>
		map(InputIterator first, InputIterator last, 
				const key_compare& comp = key_compare(), 
				const allocator_type &alloc = allocator_type())
		{
			_alloc = alloc;
			while (first != last)
			{
				rbt.insert(first.p->data);
				first++;
			}
			_comp = comp;
		}

		map (const map &x) : _comp(x._comp), _alloc(x._alloc)
		{
			rbt = x.rbt;
		}

		~map() {}


		map &operator=(const map &rhs)
		{
			rbt = rhs.rbt;
			_alloc = rhs._alloc;
			_comp = rhs._comp;
			return (*this);
		}

		allocator_type get_allocator() const
		{
			return (_alloc);
		}

		//		ITERATOR CLASSES
		//___________________________________

		class iterator : public ft::iterator<ft::random_access_iterator_tag, T, difference_type, pointer, reference>
		{
			public :
				Node_ptr	p;
				RBTree		*rbt;

				iterator() : p(NULL), rbt(NULL) {}
				iterator(iterator const &x) : p(x.p), rbt(x.rbt) {}
				iterator(Node_ptr const &x, RBTree *cpy) : p(x), rbt(cpy) {}

				iterator &operator=(const iterator &ri)
				{
					p = ri.p;
					rbt = ri.rbt;
					return (*this);
				}

				reference operator*() const
				{
					return ((*p).data);
				}

				pointer operator->() const
				{
					return &(operator*());
				}

				iterator &operator++()
				{
					p = rbt->successor(p);
					return (*this);
				}

				iterator operator++(int blank)
				{
					(void)blank;
					iterator ri(p, rbt);
					this->operator++();
					return (ri);
				}

				iterator &operator--()
				{
					p = rbt->predecessor(p);
					return (*this);
				}
				
				iterator operator--(int blank)
				{
					(void)blank;
					iterator ri(p, rbt);
					this->operator--();
					return (ri);
				}
		};

		friend bool operator==(const iterator &a, const iterator &b)
		{
			return (a.p == b.p);
		}

		friend bool operator!=(const iterator &a, const iterator &b)
		{
			return (a.p != b.p);
		}
		

		class const_iterator : public ft::iterator<ft::random_access_iterator_tag, T, difference_type, pointer, reference>
		{
			public :
				Node_ptr	p;
				const RBTree		*rbt;

				const_iterator() : p(NULL), rbt(NULL) {}
				const_iterator(const_iterator const &x) : p(x.p), rbt(x.rbt) {}
				const_iterator(iterator const &x) : p(x.p), rbt(x.rbt) {}
				const_iterator(Node_ptr const &x, RBTree *cpy) : p(x), rbt(cpy) {}
				const_iterator(Node_ptr const &x, const RBTree *cpy) : p(x), rbt(cpy) {}

				const_iterator &operator=(const const_iterator &ri)
				{
					p = ri.p;
					rbt = ri.rbt;
					return (*this);
				}

				reference operator*() const
				{
					return ((*p).data);
				}

				pointer operator->() const
				{
					return &(operator*());
				}

				const_iterator &operator++()
				{
					p = rbt->successor(p);
					return (*this);
				}

				const_iterator operator++(int blank)
				{
					(void)blank;
					const_iterator ri(p, rbt);
					this->operator++();
					return (ri);
				}

				const_iterator &operator--()
				{
					p = rbt->predecessor(p);
					return (*this);
				}
				
				const_iterator operator--(int blank)
				{
					(void)blank;
					const_iterator ri(p, rbt);
					this->operator--();
					return (ri);
				}
		};
		
		friend bool operator==(const_iterator const &a, const_iterator const &b)
		{
			return (a.p == b.p);
		}

		friend bool operator!=(const_iterator const &a, const_iterator const &b)
		{
			return (a.p != b.p);
		}
		
		typedef typename ft::reverse_iterator<iterator>				reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>		const_reverse_iterator;

		//		ELEMENT ACCESS
		//___________________________________

		T& at(const key_type &key)
		{
			Node_ptr found = rbt.search_tree(key);
			if (found != rbt.get_nullnode())
				return (found->data.second);
			else
				throw std::out_of_range("Key not found");
		}
		
		const T& at(const key_type &key) const
		{
			Node_ptr found = rbt.search_tree(key);
			if (found != rbt.get_nullnode())
				return (found->data.second);
			else
				throw std::out_of_range("Key not found");
		}

		mapped_type& operator[] (const key_type& k)
		{
			return insert(ft::make_pair(k, T())).first->second;
		}

		//		ITERATORS
		//___________________________________
		iterator begin()
		{
			return (iterator(rbt.minimum(rbt.get_root()), &rbt));
		}

		const_iterator begin() const
		{
			return (const_iterator(rbt.minimum(rbt.get_root()), &rbt));
		}

		iterator end()
		{
			if (empty())
				return (begin());
			return (iterator(rbt.maximum(rbt.get_root()) + 1, &rbt));
		}

		const_iterator end() const
		{
			if (empty())
				return (begin());
			return (const_iterator(rbt.maximum(rbt.get_root()) + 1, &rbt));
		}

		reverse_iterator rbegin()
		{
			return (reverse_iterator(iterator(rbt.maximum(rbt.get_root()) + 1, &rbt)));
		}

		const_reverse_iterator rbegin() const
		{
			return (const_reverse_iterator(iterator(rbt.maximum(rbt.get_root()) + 1, &rbt)));
		}

		reverse_iterator rend()
		{
			return (reverse_iterator(iterator(rbt.minimum(rbt.get_root()), &rbt)));
		}

		const_reverse_iterator rend() const
		{
			return (const_reverse_iterator(iterator(rbt.minimum(rbt.get_root()), &rbt)));
		}

		//		CAPACITY
		//___________________________________

		bool empty() const
		{
			return (!rbt.get_size());
		}

		size_type size()
		{
			return (rbt.get_size());
		}

		size_type size() const
		{
			return (rbt.get_size());
		}

		size_type max_size() const
		{
			return (rbt.max_size());
		}

		//		MODIFIERS
		//___________________________________

		void clear()
		{
			rbt.set_root(rbt.clear(rbt.get_root()));
		}

		pair<iterator,bool> insert(const value_type& val)
		{
			Node_ptr found = rbt.search_tree(val.first);
			if (found != rbt.get_nullnode())
				return (ft::make_pair<iterator, bool>(iterator(found, &rbt), false));
			rbt.insert(val);
			return (ft::pair<iterator, bool>(iterator(rbt.search_tree(val.first), &rbt), true));
		}

		iterator insert (iterator position, const value_type& val)
		{
			(void)position;
			iterator found(rbt.search_tree(val.first), &rbt);
			if (found != iterator(rbt.get_nullnode(), &rbt))
				return (found);
			rbt.insert(val);
			return (iterator(rbt.search_tree(val.first), &rbt));
		}

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				rbt.insert(*first);
				first++;
			}
		}

		void erase (iterator position)
		{
			rbt.delete_node((*position).first);
		}

		void erase (iterator first, iterator last)
		{
			iterator temp = first;
			iterator other_temp;
			while (first != last)
			{
				temp = first;
				first++;
				erase(temp);
			}
		}

		size_type erase(const key_type& k)
		{
			if (rbt.search_tree(k) != rbt.get_nullnode())
			{
				rbt.delete_node(k);
				return (1);
			}
			return (0);
		}

		void swap (map& x)
		{
			rbt.swap(x.rbt);
		}

		//		LOOKUP
		//___________________________________
		
		size_type count (const key_type &k)
		{
			const_iterator found(rbt.search_tree(k), &rbt);
			if (found != const_iterator(rbt.get_nullnode(), &rbt))
				return (1);
			return (0);
		}

		iterator find (const key_type& k)
		{
			return (iterator(rbt.search_tree(k), &rbt));
		}

		const_iterator find (const key_type &k) const
		{
			return (const_iterator(rbt.search_tree(k), &rbt));
		}

		pair<iterator,iterator>				equal_range (const key_type& k)
		{
			iterator to_find = find(k);
			if (to_find != end())
				return (ft::make_pair(lower_bound(k), upper_bound(k)));
			else
				return (ft::make_pair(upper_bound(k), upper_bound(k)));
		}

		pair<const_iterator,const_iterator>	equal_range (const key_type& k) const
		{
			iterator to_find = find(k);
			if (to_find != end())
				return (ft::make_pair(lower_bound(k), upper_bound(k)));
			else
				return (ft::make_pair(find(k), find(k)));
		}

		iterator lower_bound (const key_type& k)
		{
			iterator   it = this->begin();
			iterator   ite = this->end();

			while (it != ite && this->_comp(it->first, k))   // while current key < k
				++it;
			return (it);
		}

		const_iterator lower_bound (const key_type& k) const
		{
			const_iterator   it = this->begin();
			const_iterator   ite = this->end();

			while (it != ite && this->_comp(it->first, k))   // while current key < k
				++it;
			return (it);
		}

		iterator upper_bound (const key_type& k)
		{
			iterator	it = this->begin();
			iterator	ite = this->end();

			while (it != ite &&
				(this->_comp(it->first, k) ||
				(!_comp(it->first, k) && !_comp(k, it->first))))
				++it;
			return (it);
		}

		const_iterator upper_bound (const key_type& k) const
		{
			const_iterator	it = this->begin();
			const_iterator	ite = this->end();

			while (it != ite &&
				(this->_comp(it->first, k) ||
				(!_comp(it->first, k) && !_comp(k, it->first))))
				++it;
			return (it);
		}

		key_compare key_comp() const
		{
			return (_comp);
		}

		value_compare value_comp() const
		{
			return (value_compare(_comp));
		}

};
	template< class Key, class T, class Compare, class Alloc >
	bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs,
					const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		ptrdiff_t i = 0;
		Compare _comp;
		typename ft::map<Key,T,Compare,Alloc>::const_iterator itl = lhs.begin();
		typename ft::map<Key,T,Compare,Alloc>::const_iterator itr = rhs.begin();

		if (ft::distance(lhs.begin(), lhs.end()) != ft::distance(rhs.begin(), rhs.end()))
			return (false);
		while (i < ft::distance(lhs.begin(), lhs.end()))
		{
			if (!(!_comp(itl->first, itr->first) && !_comp(itr->first, itl->first)))
				return (false);
			itl++;
			itr++;
			i++;
			std::cout << i << std::endl;
		}
		return (true);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs,
					const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(lhs == rhs));
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs,
					const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		typename ft::map<Key,T,Compare,Alloc>::const_iterator itl = lhs.begin();
		typename ft::map<Key,T,Compare,Alloc>::const_iterator itr = rhs.begin();
		typename ft::map<Key,T,Compare,Alloc>::const_iterator endl = lhs.end();
		typename ft::map<Key,T,Compare,Alloc>::const_iterator endr = rhs.end();
		
		return (ft::lexicographical_compare(itr, endr, itl, endl));
	}
	
	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs,
					const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(rhs < lhs));
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs,
					const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return (rhs < lhs);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs,
					const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(lhs < rhs));
	}

	template< class Key, class T, class Compare, class Alloc >
	void swap( ft::map<Key,T,Compare,Alloc>& lhs,
			ft::map<Key,T,Compare,Alloc>& rhs )
	{
		lhs.swap(rhs);
	}


}



#endif