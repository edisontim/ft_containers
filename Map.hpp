#ifndef MAP_HPP
#define MAP_HPP

#include "Pair.hpp"
#include "Vector.hpp"
#include <functional>
#include "RBT/RBT.hpp"

namespace ft
{
template <class Key, class T, class Compare = std::less<Key> >
class map
{

	public:

	typedef Key													key_type;
	typedef T													mapped_type;
	typedef pair<const Key, T>									value_type;
	typedef const Compare 										key_compare;
	typedef std::ptrdiff_t										difference_type;
	typedef unsigned int										size_type;
	typedef std::allocator<T>									allocator_type;
	typedef RBTree<ft::map<Key, T, Compare> >					RBTree;
	typedef typename RBTree::Node_ptr							Node_ptr;
	typedef value_type*											pointer;
	typedef const pointer										const_pointer;
	typedef value_type&											reference;

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
		map(const key_compare& comp = key_compare(), const allocator_type &alloc = allocator_type()) : rbt(RBTree()), _alloc(alloc)
		{
			_comp = comp;
		}

		map (const map &x) : _comp(x._comp), _alloc(x._alloc)
		{
			rbt = x.copy_tree();
		}

		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type &alloc = allocator_type())
		{
			_alloc = alloc;
			
			while (first != last)
			{
				rbt.insert(first.p);
				first++;
			}
			_comp = comp;
		}

		~map()
		{
		}

		class iterator : public ft::iterator<ft::random_access_iterator_tag, T, difference_type, pointer, reference>
		{
			public :
				Node_ptr	p;
				RBTree		&rbt;

				iterator() : p(NULL) {}
				iterator(iterator const &x) : p(x.p), rbt(x.rbt) {}
				iterator(Node_ptr const &x, RBTree &cpy) : p(x), rbt(cpy) {}

				iterator &operator=(const iterator &ri)
				{
					p = ri.p;
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
					if (rbt.successor(p) == p)
					{
						++p;
						return (*this);
					}
					else
					{
						p = rbt.successor(p);
						return (*this);
					}
				}

				iterator operator++(int blank)
				{
					(void)blank;
					iterator ri(*this);
					++*this;
					return (ri);
				}

				iterator &operator--()
				{
					if (rbt.predecessor(p) == p)
					{
						++p;
						return (*this);
					}
					else
					{
						p = rbt.predecessor(p);
						return (*this);
					}
				}
				
				iterator operator--(int blank)
				{
					(void)blank;
					iterator ri(*this);
					--*this;
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
				Node_ptr p;

				const_iterator() : p(NULL) {}
				const_iterator(const_iterator const &x) : p(x.p) {}
				const_iterator(Node_ptr const &x) : p(x) {}
				const_iterator(iterator const &x) : p(x.p) {}
				~const_iterator(){};


				const_iterator &operator=(const const_iterator &ri)
				{
					p = ri.p;
					return (*this);
				}

				reference operator*() const
				{
					return ((*p).data);
				}

				const_pointer operator->() const
				{
					return &(operator*());
				}

				const_iterator &operator++()
				{
					if (rbt.successor(p) == p)
					{
						++p;
						return (*this);
					}
					else
					{
						p = rbt.successor(p);
						return (*this);
					}
				}

				const_iterator operator++(int blank)
				{
					(void)blank;
					const_iterator ri(*this);
					++this;
					return (ri);
				}

				const_iterator &operator--()
				{
					if (rbt.predecessor(p) == p)
					{
						++p;
						return (*this);
					}
					else
					{
						p = rbt.predecessor(p);
						return (*this);
					}
				}
				
				const_iterator operator--(int blank)
				{
					(void)blank;
					iterator ri(*this);
					--this;
					return (ri);
				}
		};
		
		friend bool operator==(const_iterator &a, const_iterator &b)
		{
			return (a.p == b.p);
		}

		friend bool operator!=(const_iterator &a, const_iterator &b)
		{
			return (a.p != b.p);
		}
		
		typedef typename ft::reverse_iterator<iterator>				reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>		const_reverse_iterator;

		//		OPERATORS
		//___________________________________
		map &operator=(const map &rhs)
		{
			if (*this != rhs)
			{
				rbt = rhs.copy_tree();
				_alloc = rhs._alloc;
				_comp = rhs.comp;
			}
		}

		mapped_type& operator[] (const key_type& k)
		{
			return (rbt.search_tree(k)->data.second);
		}

		//		UTILS
		//___________________________________
		iterator begin()
		{
			return (iterator(rbt.minimum(rbt.get_root()), rbt));
		}

		const_iterator begin() const
		{
			return (const_iterator(rbt.minimum(rbt.get_root()), rbt));
		}

		iterator end()
		{
			return (iterator(rbt.maximum(rbt.get_root()) + 1, rbt));
		}

		const_iterator end() const
		{
			return (const_iterator(rbt.maximum(rbt.get_root()) + 1, rbt));
		}

		reverse_iterator rbegin()
		{
			return (reverse_iterator(rbt.maximum(rbt.get_root()), rbt));
		}

		const_reverse_iterator rbegin() const
		{
			return (const_reverse_iterator(rbt.maximum(rbt.get_root()), rbt));
		}

		reverse_iterator rend()
		{
			return (const_reverse_iterator(rbt.minimum(rbt.get_root()) - 1, rbt));
		}

		const_reverse_iterator rend() const
		{
			return (const_reverse_iterator(rbt.minimum(rbt.get_root()) - 1, rbt));
		}

		bool empty() const
		{
			return (rbt.get_size());
		}

		size_type size()
		{
			return (rbt.get_size());
		}

		size_type max_size() const
		{
			return (_alloc.max_size());
		}

		iterator find (const key_type& k)
		{
			return (iterator(rbt.search_tree(k), rbt));
		}

		const_iterator find (const key_type &k) const
		{
			return (const_iterator(rbt.search_tree(k), rbt));
		}

		pair<iterator,bool> insert(const value_type& val)
		{
			Node_ptr found = rbt.search_tree(val.first);
			if (found != rbt.get_nullnode())
				return (ft::make_pair<iterator, bool>(iterator(found, rbt), false));
			rbt.insert(val);
			return (ft::pair<iterator, bool>(iterator(found, rbt), true));
		}
		
		iterator insert (iterator position, const value_type& val)
		{
			(void)position;
			iterator found(rbt.search_tree(val.first), rbt);
			if (found != iterator(rbt.get_nullnode(), rbt))
				return (ft::make_pair<iterator, bool>(found, false));
			rbt.insert(val);
			return (ft::make_pair(iterator(rbt.search_tree(val.first), rbt), true));
		}

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				insert(*first);
				first++;
			}
		}
		
		public : 

		void erase (iterator position)
		{
			rbt.delete_node((*position).first);
		}

		size_type erase (const key_type& k)
		{
			rbt.delete_node(k);
		}

		void erase (iterator first, iterator last)
		{
			while (first != last)
			{
				erase(first);
			}
		}

		void swap (map& x)
		{
			Compare comp_buff = x._comp;
			allocator_type alloc_buff = x._alloc;
			RBTree rbt_buff = x.rbt;

			x.rbt = rbt;
			x._alloc = _alloc;
			x._comp = _comp;

			_comp = comp_buff;
			_alloc = alloc_buff;
			rbt = rbt_buff;
		}

		void clear()
		{
			rbt.~RBTree();
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
			iterator found(rbt.search_tree(k), rbt);
			if (found != iterator(rbt.get_nullnode(), rbt))
				return (1);
			return (0);
		}

		iterator lower_bound (const key_type& k)
		{
			unsigned int i;

			i = 0;
			Node_ptr iter = rbt.minimum(rbt.get_root());
			while (i < size())
			{
				if (!_comp(iter->data.first, k))
					return (iterator(iter, rbt));
				i++;
				iter = rbt.successor(iter);
			}
			return (end());
		}

		const_iterator lower_bound (const key_type& k) const
		{
			unsigned int i;

			i = 0;
			Node_ptr iter = rbt.minimum(rbt.get_root());
			while (i < size())
			{
				if (!_comp(iter->data.first, k))
					return (const_iterator(iter, rbt));
				i++;
				iter = rbt.successor(iter);
			}
			return (end());
		}

		iterator upper_bound (const key_type& k)
		{
			unsigned int i;

			i = 0;

			Node_ptr iter = rbt.minimum(rbt.get_root());
			while (i < size())
			{
				if (_comp(iter->data.first, k))
					return (iterator(iter, rbt));
				i++;
				iter = rbt.successor(iter);
			}
			return (end());
		}

		const_iterator upper_bound (const key_type& k) const
		{
			unsigned int i;

			i = 0;

			Node_ptr iter = rbt.minimum(rbt.get_root());
			while (i < size())
			{
				if (_comp(iter->data.first, k))
					return (const_iterator(iter, rbt));
				i++;
				iter = rbt.successor(iter);
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
			return (_alloc);
		}
};

}



#endif