/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 13:59:37 by schene            #+#    #+#             */
/*   Updated: 2021/02/08 18:46:30 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_HPP
# define FT_UTILS_HPP

namespace ft
{	
	/*
	** ********************************************************************
	** enable_if: if first parameter resolves to true, "::type" is defined.
	** it will allow us to do some static polymorphism (using SFINAE)
	** ********************************************************************
	*/
	template< bool condition, class T = void>
	struct enable_if{}; //nothing defined when not true.

	template<class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	/*
	** ********************************************************************
	** Iterator_traits:	interface to get the iterators's types
	** ********************************************************************
	*/
	template< typename Iterator >
	class iterator_traits
	{
		public:
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};
	//some specialisation for pointers and const pointers of iterator_traits goes here.

	/*
	** iterator_traits specialisation to get ride of all the integral types:
	*/
	template<> class iterator_traits<bool>{};
	template<> class iterator_traits<char>{};
	// template<> class iterator_traits<char16_t>{};
	// template<> class iterator_traits<char32_t>{};
	template<> class iterator_traits<wchar_t>{};
	template<> class iterator_traits<signed char>{};
	template<> class iterator_traits<short int>{};
	template<> class iterator_traits<int>{};
	template<> class iterator_traits<long>{};
	template<> class iterator_traits<long long>{};
	template<> class iterator_traits<unsigned char>{};
	template<> class iterator_traits<unsigned short int>{};
	template<> class iterator_traits<unsigned int>{};
	template<> class iterator_traits<unsigned long>{};
	template<> class iterator_traits<unsigned long long>{};

	template< typename IsIterator>
	struct is_iterator
	{
		typedef char yes[1];
		typedef char no[2]; //different sizes distinguished by sizeof().

		template <typename IsIterator_>
		static yes& test(typename iterator_traits<IsIterator_>::iterator_category* = NULL);

		template <typename C>
		static no& test(...);

		// If the "sizeof" of the result of calling test<T>(nullptr) is equal to
		// sizeof(yes), the first overload worked and T has a nested type named
		// value_type
		static const bool value = sizeof(test<IsIterator>(NULL)) == sizeof(yes);
	};
}

#endif