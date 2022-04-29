/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:32:44 by sameye            #+#    #+#             */
/*   Updated: 2022/04/29 15:06:21 by sameye           ###   ########.fr       */
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
	m1.erase(3);
	//m1.print_tree();
	std::cout << "res " << m1.at(1) << m1.at(2) << m1.at(4) << std::endl;
	std::cout << "insert in disorder" << std::endl;
	NAMESPACE::map<int, int> m2;
	m2.insert(NAMESPACE::make_pair(8, 1));
	m2.insert(NAMESPACE::make_pair(2, 2));
	m2.insert(NAMESPACE::make_pair(6, 3));
	m2.insert(NAMESPACE::make_pair(0, 4));
	//m2.print_tree();
	std::cout << "res " << m2.at(8) << m2.at(2) << m2.at(6) << m2.at(0) << std::endl;

	std::cout << "erase in disorder" << std::endl;
	NAMESPACE::map<int, char> m3;
	m3.insert(NAMESPACE::make_pair(8, 'a'));
	m3.insert(NAMESPACE::make_pair(2, 'b'));
	m3.insert(NAMESPACE::make_pair(6, 'c'));
	m3.insert(NAMESPACE::make_pair(0, 'd'));
	m3.erase(2);
	//m3.print_tree();
	m3.erase(6);
	std::cout << "res " << m3.at(8) << m3.at(0) << std::endl;


	std::cout << "big trees" << std::endl;
	std::cout << "increasing integers" << std::endl;
	NAMESPACE::map<int, char> m4;
	for (int i = 0; i < 10000; i++)
		m4.insert(NAMESPACE::make_pair(i, 'o'));
	//m4.print_tree();

	std::cout << "decreasing integers" << std::endl;
	NAMESPACE::map<int, char> m5;
	for (int i = 100; i > 0; i--)
		m5.insert(NAMESPACE::make_pair(i, 'o'));
	//m5.print_tree();

	std::cout << "random list integers" << std::endl;
	NAMESPACE::map<int, char> m6;
	int foo[] = {8, 22, 15, 76, 69, 63, 72, 17, 24, 53, 91, 2, 28, 97, 5, 38, 98, 79, 78, 99, 9, 11, 52, 88, 71, 21, 70, 87, 37, 92, 7, 48, 50, 84, 90, 94, 82, 35, 65, 36, 43, 31, 1, 23, 39, 27, 32, 45, 74, 58, 40, 67, 57, 51, 13, 61, 64, 25, 89, 95, 16, 73, 26, 0, 49, 86, 10, 6, 46, 62, 34, 93, 30, 47, 54, 41, 85, 75, 18, 33, 77, 80, 55, 56, 83, 44, 60, 59, 68, 42, 4, 20, 81, 96, 19, 66, 12, 3, 29, 14};
	for (int i = 0; i < 100; i++)
		m6.insert(NAMESPACE::make_pair(foo[i], 'a' + i % 26));
	for (int i = 0; i <= 50; i++)
		m6.erase(i);
	//m6.print_tree();
	NAMESPACE::map<int, char>::iterator itb = m6.begin();
	std::cout << "begin key : " << itb->first << " val : " << itb->second << std::endl;
	NAMESPACE::map<int, char>::iterator ite = m6.end();
	for (;itb != ite; itb++)
		std::cout << "key : " << itb->first << " val : " << itb->second << std::endl;




	//m4.erase(10);
	//m4.erase(1);
	//m4.erase(65);
	//m4.insert(NAMESPACE::make_pair(299, 's'));
	//NAMESPACE::map<int, char>::iterator itb = m4.begin();
	//NAMESPACE::map<int, char>::iterator ite = m4.end();

	//m4.pre0rder();

	//while (itb != ite)
	//{
	//	std::cout << "key : " << (*itb).first << " val : " << itb->second << std::endl;
	//	itb++;
	//}
}