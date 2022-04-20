/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:32:44 by sameye            #+#    #+#             */
/*   Updated: 2022/04/20 18:31:17 by sameye           ###   ########.fr       */
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
}