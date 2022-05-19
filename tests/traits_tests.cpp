/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traits_tests.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:18:18 by sameye            #+#    #+#             */
/*   Updated: 2022/05/19 12:57:14 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <iterator> 
#include <time.h>

#include "../vector.hpp"
#include "../map.hpp"
#include "../stack.hpp"
#include "../vector_iterator.hpp"
#include "../map_iterator.hpp"

#include "test_utils.hpp"
#include "traits_tests.hpp"

template< class it >
void template_function( it i1, it i2 )
{
	std::cout << "USING TRAITS VALUE TYPE TO PRINT VALUE" << std::endl;
	while ( i1 != i2 )
	{
		typename NAMESPACE::iterator_traits<it>::value_type x;
		x = *i1;
		std::cout << x << " ";
		i1++;
	};
	std::cout << std::endl;
};

template<class traits>
void type_detector(void)
{
	std::cout << "ITERATOR TYPE DETECTOR" << std::endl;
	if (typeid(typename traits::iterator_category)==typeid(NAMESPACE::random_access_iterator_tag))
		std::cout << "random_access_iterator_tag" << std::endl;
	if (typeid(typename traits::iterator_category)==typeid(NAMESPACE::bidirectional_iterator_tag))
		std::cout << "bidirectional_iterator_tag" << std::endl;
	if (typeid(typename traits::iterator_category)==typeid(NAMESPACE::forward_iterator_tag))
		std::cout << "forward_iterator_tag" << std::endl;
	if (typeid(typename traits::iterator_category)==typeid(NAMESPACE::input_iterator_tag))
		std::cout << "input_iterator_tag" << std::endl;
	if (typeid(typename traits::iterator_category)==typeid(NAMESPACE::output_iterator_tag))
		std::cout << "output_iterator_tag" << std::endl;
}

void test_traits_main(void)
{
	{
		{
			typedef NAMESPACE::iterator_traits<int*> traits;
			type_detector<traits>();
		}
		{
			typedef NAMESPACE::iterator_traits<NAMESPACE::vector<char>::iterator> traits;
			type_detector<traits>();
		}
		{
			typedef NAMESPACE::iterator_traits<NAMESPACE::vector<int>::reverse_iterator> traits;
			type_detector<traits>();
		}
		{
			typedef NAMESPACE::iterator_traits<NAMESPACE::vector<int>::const_iterator> traits;
			type_detector<traits>();
		}
		{
			typedef NAMESPACE::iterator_traits<NAMESPACE::map<char, int>::iterator> traits;
			type_detector<traits>();
		}
		{
			typedef NAMESPACE::iterator_traits<NAMESPACE::map<char, int>::reverse_iterator> traits;
			type_detector<traits>();
		}
		{
			typedef NAMESPACE::iterator_traits<NAMESPACE::map<char, int>::const_reverse_iterator> traits;
			type_detector<traits>();
		}
	}
	{
		NAMESPACE::vector<char> vc(10,'a');
		template_function(vc.begin(), vc.end());
	}
}
