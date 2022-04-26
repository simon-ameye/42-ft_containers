/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:32:44 by sameye            #+#    #+#             */
/*   Updated: 2022/04/26 02:11:09 by sameye           ###   ########.fr       */
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
	std::cout << "insert in order" << std::endl;
	NAMESPACE::map<int, int> m1;
	m1.insert(NAMESPACE::make_pair(1, 1));
	m1.insert(NAMESPACE::make_pair(2, 2));
	m1.insert(NAMESPACE::make_pair(3, 3));
	m1.insert(NAMESPACE::make_pair(4, 4));
	std::cout << "res " << m1.at(1) << m1.at(2) << m1.at(3) << m1.at(4) << std::endl;

	std::cout << "insert in disorder" << std::endl;
	NAMESPACE::map<int, int> m2;
	m2.insert(NAMESPACE::make_pair(8, 1));
	m2.insert(NAMESPACE::make_pair(2, 2));
	m2.insert(NAMESPACE::make_pair(6, 3));
	m2.insert(NAMESPACE::make_pair(0, 4));
	std::cout << "res " << m2.at(8) << m2.at(2) << m2.at(6) << m2.at(0) << std::endl;

	std::cout << "erase in disorder" << std::endl;
	NAMESPACE::map<int, char> m3;
	m3.insert(NAMESPACE::make_pair(8, 'a'));
	m3.insert(NAMESPACE::make_pair(2, 'b'));
	m3.insert(NAMESPACE::make_pair(6, 'c'));
	m3.insert(NAMESPACE::make_pair(0, 'd'));
	m3.erase(2);
	m3.erase(6);
	std::cout << "res " << m3.at(8) << m3.at(0) << std::endl;


	std::cout << "big tree" << std::endl;
	NAMESPACE::map<int, char> m4;
	m4.insert(NAMESPACE::make_pair(4, 'c'));
	m4.insert(NAMESPACE::make_pair(6, 'f'));
	//m4.erase(6);
	m4.insert(NAMESPACE::make_pair(1, 'a'));
	m4.insert(NAMESPACE::make_pair(7, 'z'));
	m4.insert(NAMESPACE::make_pair(2, 'e'));
	//m4.erase(7);
	m4.insert(NAMESPACE::make_pair(0, 'r'));
	m4.insert(NAMESPACE::make_pair(77, 't'));
	m4.insert(NAMESPACE::make_pair(876, 'y'));
	//m4.erase(4);
	m4.insert(NAMESPACE::make_pair(65, 'f'));
	m4.insert(NAMESPACE::make_pair(55545, 'd'));
	m4.insert(NAMESPACE::make_pair(978679, 'e'));
	m4.insert(NAMESPACE::make_pair(87, 't'));
	m4.insert(NAMESPACE::make_pair(11, 'j'));
	m4.insert(NAMESPACE::make_pair(12, 'f'));
	m4.insert(NAMESPACE::make_pair(13, 'd'));
	m4.insert(NAMESPACE::make_pair(14, 'e'));
	m4.insert(NAMESPACE::make_pair(15, 't'));
	m4.insert(NAMESPACE::make_pair(16, 'j'));
	m4.insert(NAMESPACE::make_pair(17, 't'));
	m4.insert(NAMESPACE::make_pair(18, 'j'));

	//m4.erase(10);
	//m4.erase(1);
	//m4.erase(65);
	m4.insert(NAMESPACE::make_pair(299, 's'));
	NAMESPACE::map<int, char>::iterator itb = m4.begin();
	NAMESPACE::map<int, char>::iterator ite = m4.end();
	std::cout << "key : " << itb->first << " val : " << itb->second << std::endl;
	std::cout << "key : " << ite->first << " val : " << ite->second << std::endl;

	m4.print_tree();

	//while (itb != ite)
	//{
	//	std::cout << "key : " << (*itb).first << " val : " << itb->second << std::endl;
	//	itb++;
	//}
}