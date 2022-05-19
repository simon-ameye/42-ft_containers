/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 13:38:12 by sameye            #+#    #+#             */
/*   Updated: 2022/05/19 13:37:18 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <typeinfo>
#include <iterator>

namespace ft
{
	/* ****************************************** */
	/*                 Iterator traits            */
	/* ****************************************** */

	class random_access_iterator_tag { };
	class bidirectional_iterator_tag { };
	class forward_iterator_tag { };
	class input_iterator_tag { };
	class output_iterator_tag { };

	struct type_false	{};
	struct type_true	{};
	template <class T>
				struct type_is_integer						: public type_false {};
	template <>	struct type_is_integer<bool>				: public type_true {};
	template <>	struct type_is_integer<char>				: public type_true {};
	template <>	struct type_is_integer<signed char>			: public type_true {};
	template <>	struct type_is_integer<unsigned char>		: public type_true {};
	template <>	struct type_is_integer<wchar_t>				: public type_true {};
	template <>	struct type_is_integer<short>				: public type_true {};
	template <>	struct type_is_integer<unsigned short>		: public type_true {};
	template <>	struct type_is_integer<int>					: public type_true {};
	template <>	struct type_is_integer<unsigned int>		: public type_true {};
	template <>	struct type_is_integer<long>				: public type_true {};
	template <>	struct type_is_integer<unsigned long>		: public type_true {};
	template <>	struct type_is_integer<long long>			: public type_true {};
	template <>	struct type_is_integer<unsigned long long>	: public type_true {};

	/*	adapted iterator traits in case someone says it's use of stl	*/
	template <class Iterator>
	class iterator_traits {
	public:
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	template <class T>
	class iterator_traits<T*> {
	public:
		typedef std::ptrdiff_t	difference_type;
		typedef T				value_type;
		typedef T*				pointer;
		typedef T&				reference;
		typedef ft::random_access_iterator_tag	iterator_category;
	};

	template <class T>
	class iterator_traits<const T*> {
	public:
		typedef std::ptrdiff_t	difference_type;
		typedef T				value_type;
		typedef const T*		pointer;
		typedef const T&		reference;
		typedef ft::random_access_iterator_tag	iterator_category;
	};

	/* ****************************************** */
	/*                    PAIR                    */
	/* ****************************************** */
	template <typename T1, typename T2>
	class pair
	{
		public:
			/* *******************CONSTRUCTORS******************* */
			/* -------------default constructor------------- */
			pair() : first(), second() {};

			/* -------------init constructor------------- */
			pair(const T1& a, const T2& b) : first(a), second(b) {};

			/* -------------copy constructor------------- */
			pair(const pair<T1, T2>& copy) : first(copy.first), second(copy.second) {};

			/* -------------copy template constructor------------- */
			template <typename U, typename V>
			pair(const pair<U, V>& copy) : first(copy.first), second(copy.second) {};

			/* -------------destructor------------- */
			~pair() {};
		
			/* *******************OPERATOR OVERLOAD******************* */
			pair& operator=(const pair& assign)
			{
				if (this != &assign)
				{
					first = assign.first;
					second = assign.second;
				}
				return (*this);
			}
			/* *******************VARIABLES******************* */
			T1 first;
			T2 second;
	};

	/* *******************relational operators for pairs******************* */
	template <class T1, class T2>
	bool		operator==(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
	{	return (lhs.first == rhs.first && lhs.second == rhs.second);	}

	template <class T1, class T2>
	bool		operator!=(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
	{	return (!(lhs == rhs));	}

	template <class T1, class T2>
	bool		operator<(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
	{
		return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
	}

	template <class T1, class T2>
	bool		operator<=(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
	{	return (!(rhs < lhs));	}

	template <class T1, class T2>
	bool		operator>(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
	{	return (rhs < lhs);		}

	template <class T1, class T2>
	bool		operator>=(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
	{	return (!(lhs < rhs));	}

	/* ****************************************** */
	/*               MAKE PAIR                    */
	/* ****************************************** */
	template< class T1, class T2 >
	pair<T1,T2> make_pair( T1 t, T2 u )
	{
		return ( pair<T1,T2>(t,u) );
	}

	/* ****************************************** */
	/*                   ENABLE IF                */
	/* ****************************************** */
	//enable_if has a public member typedef type, equal to int; otherwise, there is no member typedef.
	template<bool B, class T = void>
	struct enable_if {};
	
	template<class T>
	struct enable_if<true, T> { typedef T type; };

	/* ****************************************** */
	/*                 IS INTEGRAL                */
	/* ****************************************** */
	template <typename T>
	struct is_integral { static const bool value = false; };

	template <>
	struct is_integral<bool> { static const bool value = true; };

	template <>
	struct is_integral<char> { static const bool value = true; };

	template <>
	struct is_integral<short> { static const bool value = true; };

	template <>
	struct is_integral<int> { static const bool value = true; };

	template <>
	struct is_integral<long> { static const bool value = true; };

	template <>
	struct is_integral<long long> { static const bool value = true; };

	template <>
	struct is_integral<unsigned char> { static const bool value = true; };

	template <>
	struct is_integral<unsigned short> { static const bool value = true; };

	template <>
	struct is_integral<unsigned int> { static const bool value = true; };

	template <>
	struct is_integral<unsigned long> { static const bool value = true; };

	template <>
	struct is_integral<unsigned long long> { static const bool value = true; };

	/* ****************************************** */
	/*     lexicographical_compare                */
	/* ****************************************** */
	template <class T1, class T2>
	struct _less_twotypes	: std::binary_function<T1, T2, bool> {
		bool	operator()(const T1& x, const T2& y) const
		{	return (x < y);		}
	};

	template <class InputIterator1, class InputIterator2, class Compare>
	bool	lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || comp(*first2, *first1))
				return (false);
			else if (comp(*first1, *first2))
				return (true);
			++first1;	++first2;
		}
		return (first2 != last2);
	}

	template <class InputIterator1, class InputIterator2>
	bool	lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
									InputIterator2 first2, InputIterator2 last2)
	{
		typedef typename ft::iterator_traits<InputIterator1>::value_type	type1;
		typedef typename ft::iterator_traits<InputIterator2>::value_type	type2;
		return (ft::lexicographical_compare(first1, last1, first2, last2, _less_twotypes<type1, type2>()));
	}

	/* ****************************************** */
	/*                 EQUAL                      */
	/* ****************************************** */
	template <class U, class X>
	bool equal(U lit, U lend, X rit, X rend)
	{
		while (lit != lend) {
			if (rit == rend || *rit != *lit)
				return (false);
			++lit, ++rit;
		}
		return (rit == rend);
	}

	/* ****************************************** */
	/*                 FalseXTrueY                */
	/* ****************************************** */
	template <bool Const, class X, class Y>
	struct FalseXTrueY {};

	template <class X, class Y>
	struct FalseXTrueY<false, X, Y>
	{ typedef X type; };

	template <class X, class Y>
	struct FalseXTrueY<true, X, Y>
	{ typedef Y type; };
}
#endif