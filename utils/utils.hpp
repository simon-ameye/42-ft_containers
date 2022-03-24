/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 13:38:12 by sameye            #+#    #+#             */
/*   Updated: 2022/03/22 18:06:00 by sameye           ###   ########.fr       */
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

}
#endif