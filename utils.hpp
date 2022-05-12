/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 13:38:12 by sameye            #+#    #+#             */
/*   Updated: 2022/05/12 14:07:19 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <typeinfo>

namespace ft
{
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
	template<bool B>
	struct enable_if {};

	template<>
	struct enable_if<true> { typedef int type; };

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

	template<class T, class U>
	bool lexicographical_compare(T first1, T last1, U first2, U last2)
	{
		while (first1 != last1) {

			if (first2 == last2 || *first2 < *first1) return false;
			else if (*first1 < *first2) return true;

			++first1;
			++first2;

		}
		return first2 != last2;
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