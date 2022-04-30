/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:32:44 by sameye            #+#    #+#             */
/*   Updated: 2022/04/30 02:46:00 by sameye           ###   ########.fr       */
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
	std::cout << "res " << m1[1] << m1[2] << m1[4] << std::endl;
	std::cout << "insert in disorder" << std::endl;
	NAMESPACE::map<int, int> m2;
	m2.insert(NAMESPACE::make_pair(8, 1));
	m2.insert(NAMESPACE::make_pair(2, 2));
	m2.insert(NAMESPACE::make_pair(6, 3));
	m2.insert(NAMESPACE::make_pair(0, 4));
	//m2.print_tree();
	std::cout << "res " << m2[8] << m2[2] << m2[6] << m2[0] << std::endl;

	std::cout << "erase in disorder" << std::endl;
	NAMESPACE::map<int, char> m3;
	m3.insert(NAMESPACE::make_pair(8, 'a'));
	m3.insert(NAMESPACE::make_pair(2, 'b'));
	m3.insert(NAMESPACE::make_pair(6, 'c'));
	m3.insert(NAMESPACE::make_pair(0, 'd'));
	m3.erase(2);
	//m3.print_tree();
	m3.erase(6);
	std::cout << "res " << m3[8] << m3[0] << std::endl;


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

	std::cout << "empty & size" << std::endl;
	std::cout << std::boolalpha;
	std::cout << "is empty " << m6.empty() << std::endl;
	std::cout << "size " << m6.size() << std::endl;
	NAMESPACE::map<int, char>::iterator itb2;
	itb2 = m6.begin();
	for (;itb2 != ite;)
	{
		std::cout << "deleting key " << itb2->first << std::endl << std::flush;
		m6.erase(itb2->first);
		itb2 = m6.begin();
	}
	std::cout << "is empty " << m6.empty() << std::endl;
	std::cout << "size " << m6.size() << std::endl;
	std::cout << "max_size is not reached " << (m6.max_size() < m6.size()) << std::endl;

	std::cout << "add with []" << std::endl;
	m6[666] = 's';
	std::cout << m6[666] << std::endl;

	std::cout << "remove tricks" << std::endl;
	std::cout << "deleting unexisting val result : " << m6.erase(77) << std::endl;
	std::cout << "deleting existing val result : " << m6.erase(666) << std::endl;

	std::cout << "swap" << std::endl;
	NAMESPACE::map<int, char> m7;
	NAMESPACE::map<int, char> m8;
	m7.insert(NAMESPACE::make_pair(22, 'o'));
	m7.insert(NAMESPACE::make_pair(77, 'o'));
	m7.swap(m8);
	std::cout << m8[77] << m8[22] << std::endl;
	std::cout << m7.size() << m7[77] << std::endl;
	m7.insert(NAMESPACE::make_pair(22, 'o'));
	m8.insert(NAMESPACE::make_pair(77, 'o'));
	std::cout << m8[77] << m8[22] << std::endl;
	std::cout << m7.size() << m7[77] << std::endl;
}