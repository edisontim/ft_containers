#ifndef UTILS_HPP
#define UTILS_HPP

#include "Iterator.hpp"

namespace ft
{
	template<class InputIterator>
	typename ft::iterator_traits<InputIterator>::difference_type
	distance (InputIterator first, InputIterator last)
	{
		typename ft::iterator_traits<InputIterator>::difference_type i = 0;
		while (first != last)
		{
			i++;
			first++;
		}
		return (i);
	}

	template <class InputIterator, class Distance>
	void advance (InputIterator& it, Distance n)
	{
		it += n;
	}


	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1) return (false);
			else if (*first1 < *first2) return (true);
			first1++;
			first2++;
		}
		return (first2 != last2);
	}

	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || comp(*first2,*first1)) return (false);
			else if (comp(*first1 < *first2)) return (true);
			first1++;
			first2++;
		}
		return (first2 != last2);
	}

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



	template<> struct is_integral_base<const bool>						: public std::true_type {};
	template<> struct is_integral_base<const char>						: public std::true_type {};
	template<> struct is_integral_base<const unsigned char>				: public std::true_type {};
	template<> struct is_integral_base<const char16_t>					: public std::true_type {};
	template<> struct is_integral_base<const char32_t>					: public std::true_type {};
	template<> struct is_integral_base<const wchar_t>						: public std::true_type {};
	template<> struct is_integral_base<const unsigned wchar_t>			: public std::true_type {};
	template<> struct is_integral_base<const short>						: public std::true_type {};
	template<> struct is_integral_base<const unsigned short>				: public std::true_type {};
	template<> struct is_integral_base<const int>							: public std::true_type {};
	template<> struct is_integral_base<const long>						: public std::true_type {};
	template<> struct is_integral_base<const unsigned long>				: public std::true_type {};
	template<> struct is_integral_base<const long long>					: public std::true_type {};
	template<> struct is_integral_base<const unsigned long long>			: public std::true_type {};



	template<> struct is_integral_base<volatile bool>						: public std::true_type {};
	template<> struct is_integral_base<volatile char>						: public std::true_type {};
	template<> struct is_integral_base<volatile unsigned char>				: public std::true_type {};
	template<> struct is_integral_base<volatile char16_t>					: public std::true_type {};
	template<> struct is_integral_base<volatile char32_t>					: public std::true_type {};
	template<> struct is_integral_base<volatile wchar_t>						: public std::true_type {};
	template<> struct is_integral_base<volatile unsigned wchar_t>			: public std::true_type {};
	template<> struct is_integral_base<volatile short>						: public std::true_type {};
	template<> struct is_integral_base<volatile unsigned short>				: public std::true_type {};
	template<> struct is_integral_base<volatile int>							: public std::true_type {};
	template<> struct is_integral_base<volatile long>						: public std::true_type {};
	template<> struct is_integral_base<volatile unsigned long>				: public std::true_type {};
	template<> struct is_integral_base<volatile long long>					: public std::true_type {};
	template<> struct is_integral_base<volatile unsigned long long>			: public std::true_type {};


	template<class T> struct is_integral : public is_integral_base<T> {};

}
#endif