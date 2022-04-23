/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:32:44 by sameye            #+#    #+#             */
/*   Updated: 2022/04/23 21:26:39 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <iterator> 

#include "../containers/map.hpp"
#include "../iterators/map_iterator.hpp"
#include "test_utils/test_utils.hpp"

#include "test_utils/test_utils.hpp"
#include "map_tests.hpp"

void test_map_assign(void)
{
	NAMESPACE::map<int, int> map_instance;
	map_instance.insert(NAMESPACE::make_pair(5, 1));
	map_instance.insert(NAMESPACE::make_pair(2, 2));
	map_instance.insert(NAMESPACE::make_pair(6, 3));
	map_instance.insert(NAMESPACE::make_pair(1, 4));
	map_instance.erase(2);
	std::cout << map_instance.at(1) << std::endl;
	std::cout << map_instance.at(6) << std::endl;

	NAMESPACE::map<char, char> map_instance2;
	map_instance2.insert(NAMESPACE::make_pair('r', 'y'));
	map_instance2.insert(NAMESPACE::make_pair('t', 'g'));
	std::cout << map_instance2.at('t') << std::endl;

	NAMESPACE::map<int, int> map2;
	map2.insert(NAMESPACE::make_pair(5, 1));
	map2.insert(NAMESPACE::make_pair(2, 2));
	map2.insert(NAMESPACE::make_pair(6, 3));
	map2.insert(NAMESPACE::make_pair(1, 4));
	NAMESPACE::map<int, int>::iterator it;
	NAMESPACE::map<int, int>::iterator itb = map2.begin(), ite = map2.end();
	std::cout << itb->first << std::endl;
	std::cout << (*ite).first << std::endl;

}