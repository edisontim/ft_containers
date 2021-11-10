#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <type_traits>

namespace ft
{
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	template <typename Category, typename T, typename Distance = ptrdiff_t, typename Pointer = T*, typename Reference = T&>
	struct iterator
	{
		typedef Category	iterator_category; 
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
	};

	template <typename Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::iterator_category iterator_category;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
	};

	template <typename T>
	struct iterator_traits <T *>
	{
		typedef ft::random_access_iterator_tag	iterator_category;
		typedef T								value_type;
		typedef ptrdiff_t						difference_type;
		typedef T*								pointer;
		typedef T&								reference;
	};

	template <typename T>
	struct iterator_traits<const T *>
	{
		typedef ft::random_access_iterator_tag	iterator_category;
		typedef T								value_type;
		typedef ptrdiff_t						difference_type;
		typedef const T*						pointer;
		typedef const T&						reference;
	};

	template <typename Iterator>
	class reverse_iterator : public iterator <	typename ft::iterator_traits<Iterator>::iterator_category, 
												typename ft::iterator_traits<Iterator>::value_type,
												typename ft::iterator_traits<Iterator>::difference_type,
												typename ft::iterator_traits<Iterator>::pointer,
												typename ft::iterator_traits<Iterator>::reference>
	{
		public :
			typedef Iterator													iterator_type;
			typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
			typedef typename ft::iterator_traits<Iterator>::reference			reference;
			typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;

		public :
			Iterator mIterator;
			
			reverse_iterator() : mIterator() {}
			
			explicit reverse_iterator(iterator_type i) : mIterator(i) {}

			template <class Iter>
			reverse_iterator (const reverse_iterator<Iter> &rev_it) : mIterator(rev_it.mIterator) {}

			template <typename U>
			reverse_iterator<Iterator>& operator=(const reverse_iterator<U> &ri)
			{
				mIterator = ri.base();
				return (*this);
			}

			iterator_type base() const
			{
				return (mIterator);
			}

			reference operator*() const
			{
				iterator_type i(mIterator);
				return *--i;
			}

			pointer operator->() const
			{
				return &(operator*());
			}

			reverse_iterator &operator++()
			{
				--mIterator;
				return (*this);
			}

			reverse_iterator operator++(int blank)
			{
				(void)blank;
				reverse_iterator ri(*this);
				--mIterator;
				return (ri);
			}

			reverse_iterator &operator--()
			{
				++mIterator;
				return (*this);
			}

			reverse_iterator operator--(int blank)
			{
				(void)blank;
				reverse_iterator ri(*this);
				mIterator++;
				return (ri);
			}

			reverse_iterator operator+(difference_type n) const
			{
				return (reverse_iterator(mIterator - n));
			}

			reverse_iterator &operator+=(difference_type n)
			{
				mIterator -= n;
				return (*this);
			}

			reverse_iterator operator-(difference_type n) const
			{
				return reverse_iterator(mIterator + n);
			}

			reverse_iterator &operator-=(difference_type n)
			{
				mIterator += n;
				return (*this);
			}

			reference operator[](difference_type n) const
			{
				return (mIterator[-n - 1]);
			}
	};
		
		template <typename Iterator1, typename Iterator2>
		bool operator==(const reverse_iterator<Iterator1> &a, const reverse_iterator<Iterator2> &b)
		{
			return (a.base() == b.base());
		}

		template <typename Iterator1, typename Iterator2>
		bool operator<(const reverse_iterator<Iterator1> &a, const reverse_iterator<Iterator2> &b)
		{
			return (a.base() > b.base());
		}

		template <typename Iterator1, typename Iterator2>
		bool operator!=(const reverse_iterator<Iterator1> &a, const reverse_iterator<Iterator2> &b)
		{
			return (a.base() != b.base());
		}

		template <typename Iterator1, typename Iterator2>
		bool operator>(const reverse_iterator<Iterator1> &a, const reverse_iterator<Iterator2> &b)
		{
			return (a.base() < b.base());
		}

		template <typename Iterator1, typename Iterator2>
		bool operator<=(const reverse_iterator<Iterator1> &a, const reverse_iterator<Iterator2> &b)
		{
			return (a.base() >= b.base());
		}

		template <typename Iterator1, typename Iterator2>
		bool operator>=(const reverse_iterator<Iterator1> &a, const reverse_iterator<Iterator2> &b)
		{
			return (a.base() <= b.base());
		}

		template <typename Iterator1, typename Iterator2>
		typename reverse_iterator<Iterator1>::difference_type operator-(const reverse_iterator<Iterator1> &a, const reverse_iterator<Iterator2> &b)
		{
			return (b.base() - a.base());
		}

		template <typename Iterator>
		reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> &a)
		{
			return (reverse_iterator<Iterator> (a.base() - n));
		}
}

#endif
