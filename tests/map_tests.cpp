/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:32:44 by sameye            #+#    #+#             */
/*   Updated: 2022/05/02 15:34:56 by sameye           ###   ########.fr       */
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
	//m6.print_tree();
	for (int i = 0; i <= 50; i++)
		m6.erase(i);
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

	std::cout << "swap & clear" << std::endl;
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
	m8.insert(NAMESPACE::make_pair(98, 'o'));
	m8.clear();
	std::cout << m8.size() << std::endl;
	std::cout << m8[66] << m8.size() << std::endl;

	std::cout << "key_comp && value_comp" << std::endl;
	NAMESPACE::map<char,int> m9;
	NAMESPACE::map<char,int>::key_compare mykeycomp = m9.key_comp();
	NAMESPACE::map<char,int>::value_compare myvalcomp = m9.value_comp();
	m9['a']=100;
	m9['b']=200;
	m9['c']=300;
	std::cout << "mymap contains:\n";
	NAMESPACE::map<char,int>::iterator itb9 = m9.begin();
	NAMESPACE::map<char,int>::iterator ite9;
	(void) myvalcomp;
	while (itb9 != (ite9 = m9.end()))
	{
		std::cout << "key comparison : " << mykeycomp(itb9->first, (--(--ite9))->first) << std::endl;
		std::cout << "value comparison : " << myvalcomp(*itb9, *ite9) << std::endl;
		itb9++;
	}

	std::cout << "find" << std::endl;
	NAMESPACE::map<char,int> m10;
	NAMESPACE::map<char,int>::iterator it;
	m10['b']=100;
	m10['a']=50;
	m10['c']=150;
	m10['d']=200;
	it = m10.find('b');
	if (it != m10.end())
		m10.erase (it);
	std::cout << "elements in mymap:" << '\n';
	std::cout << "a => " << m10.find('a')->second << '\n';
	std::cout << "c => " << m10.find('c')->second << '\n';
	std::cout << "d => " << m10.find('d')->second << '\n';


	std::cout << "lower & upper bound" << std::endl;
	NAMESPACE::map<char,int> m11;
	m11['a']=1;
	m11['b']=2;
	m11['c']=3;
	m11['d']=4;
	m11['e']=5;
	m11['f']=6;
	std::cout << "lower bound of c : " << m11.lower_bound('c')->first << std::endl;
	std::cout << "upper bound of c : " << m11.upper_bound('c')->first << std::endl;
}