/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_tests.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:38:23 by sameye            #+#    #+#             */
/*   Updated: 2022/05/05 14:51:55 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <list>
#include <iterator> 

#include "../containers/vector.hpp"
#include "../iterators/vector_iterator.hpp"
#include "test_utils/test_utils.hpp"

#include "test_utils/test_utils.hpp"
#include "vector_tests.hpp"

void test_vector_assign(void)
{
	NAMESPACE::vector<int> vct(7);
	NAMESPACE::vector<int> vct_two(4);
	NAMESPACE::vector<int> vct_three;
	NAMESPACE::vector<int> vct_four;

	for (size_t i = 0; i < vct.size(); ++i)
		vct[i] = (vct.size() - i);
	print_vector(vct, "vct");
	vct_two = vct;
	vct_two.pop_back();
	print_vector(vct_two, "vct_two");
	vct_three.assign(vct.begin(), vct.end());
	vct.assign(vct_two.begin(), vct_two.end());
	vct_two.assign(2, 42);
	vct_four.assign(4, 21);
	print_vector(vct, "vct");
	print_vector(vct_two, "vct_two");
	print_vector(vct_three, "vct_three");
	print_vector(vct_four, "vct_four");
}

void test_vector_at_const(void)
{
	NAMESPACE::vector<int> vct(7);

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct.at(i) = (vct.size() - i);
	print_vector(vct, "vct");

	NAMESPACE::vector<int> const vct_c(vct);

	std::cout << "front(): " << vct.front() << " " << vct_c.front() << std::endl;
	std::cout << "back(): " << vct.back() << " " <<  vct_c.back() << std::endl;

	for (unsigned long int i = 0; i < vct_c.size(); ++i)
		std::cout << "vct_c.at(): " << vct_c.at(i) << std::endl;
	try {
		std::cout << vct_c.at(10) << std::endl;
	}
	catch (std::out_of_range &e) {
		std::cout << "out_of_range exception!" << std::endl;
	}
	catch (std::exception &e) {
		std::cout << "Catch exception: " << e.what() << std::endl;
	}
	print_vector(vct_c, "vct_c");
}

void test_vector_copy(void)
{
	NAMESPACE::vector<int> vct(5);
	NAMESPACE::vector<int>::iterator it = vct.begin(), ite = vct.end();

	std::cout << "len: " << (ite - it) << std::endl;
	for (; it != ite; ++it)
		*it = (ite - it);

	it = vct.begin();
	NAMESPACE::vector<int> vct_range(it, --(--ite)); // range copy
	for (int i = 0; it != ite; ++it)
		*it = ++i;
	it = vct.begin();
	NAMESPACE::vector<int> vct_copy(vct); // copy construct
	vct_copy.push_back(42);
	vct_copy.push_back(21);

	print_vector(vct, "vct");
	print_vector(vct_range, "vct_range");
	print_vector(vct_copy, "vct_copy");
}

void test_vector_insert(void)
{
	NAMESPACE::vector<int> vct(10);
	NAMESPACE::vector<int> vct2;

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = (vct.size() - i) * 3;
	print_vector(vct, "vct");

	vct2.insert(vct2.end(), 42);
	vct2.insert(vct2.begin(), 2, 21);
	print_vector(vct2, "vct2");
	vct2.insert(vct2.end() - 2, 42);
	print_vector(vct2, "vct2");

	vct2.insert(vct2.end(), 2, 84);
	print_vector(vct2, "vct2");

	vct2.resize(4);
	print_vector(vct2, "vct2");

	vct2.insert(vct2.begin() + 2, vct.begin(), vct.end());
	vct.clear();
	print_vector(vct2, "vct2");

	print_vector(vct, "vct2");
}

void test_vector_erase(void)
{
	NAMESPACE::vector<int> vct(7);
	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = (vct.size() - i);
	print_vector(vct, "vct");
	vct.erase(vct.begin()); //erase an element
	print_vector(vct, "vct");
	std::cout << "returned value" << *(vct.erase(vct.begin(), vct.end() - 3)) << std::endl; //erase range and show returned value
	print_vector(vct, "vct");
	//std::cout << (vct.erase(vct.begin(), vct.end() + 1)).getElemPtr(); //Undefined behavior !
	//print_vector(vct, "vct");
}

void test_vector_iterators(void)
{
	std::cout << "construction" << std::endl;
	NAMESPACE::vector<int> vct(70);
	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = (vct.size() - i);
	NAMESPACE::vector<int>::iterator it1(vct.begin());
	NAMESPACE::vector<int>::iterator it2;
	it2 = vct.end();
	it2 -= 30;
	
	NAMESPACE::vector<int>::iterator it3 = it1;
	NAMESPACE::vector<int>::const_iterator it4 = vct.begin();

	std::cout << std::boolalpha;

	std::cout << *(++it2) << std::endl;
	std::cout << *(it2++) << std::endl;
	std::cout << *it2++ << std::endl;
	std::cout << *++it2 << std::endl;

	std::cout << *(++it3) << std::endl;
	std::cout << *(it3++) << std::endl;
	std::cout << *it3++ << std::endl;
	std::cout << *++it3 << std::endl;

	it4 += 6;
	std::cout << *(--it4) << std::endl;
	std::cout << *(it4--) << std::endl;
	std::cout << *--it4 << std::endl;
	std::cout << *it4-- << std::endl;

	*it1 = 5;
	*it2 = 5;
	*it3 = 5;
	//*it4 = 5; //wont compile as it4 is const

	std::cout << *(it3 += 5) << std::endl;
	std::cout << *(it3 -= 6) << std::endl;
	std::cout << *(it3 + 3) << std::endl;
	std::cout << *(it3 - -3) << std::endl;

	std::cout << (++it1-- < --it2++) << std::endl;
	std::cout << (it2 <= it3) << std::endl;
	std::cout << (it4 > it1) << std::endl;
	std::cout << (it3 >= it2) << std::endl;
	
}

void test_vector_comparison(void)
{
	NAMESPACE::vector<int> vct1(70);
	for (unsigned long int i = 0; i < vct1.size(); ++i)
		vct1[i] = (vct1.size() - i);

	NAMESPACE::vector<int> vct2(vct1);
	vct2[4] = 5000; 
	
	std::cout << std::boolalpha;
	
	std::cout << (vct1 < vct2) << std::endl;
	std::cout << (vct1 <= vct2) << std::endl;
	std::cout << (vct1 > vct2) << std::endl;
	std::cout << (vct2 >= vct2) << std::endl;
	std::cout << (vct2 < vct2) << std::endl;
	std::cout << (vct1 <= vct1) << std::endl;
	std::cout << (vct1 > vct1) << std::endl;
	std::cout << (vct2 >= vct1) << std::endl;
	std::cout << (vct2 != vct2) << std::endl;
	std::cout << (vct2 != vct1) << std::endl;
	std::cout << (vct1 == vct2) << std::endl;
	std::cout << (vct2 == vct1) << std::endl;
}

void test_vector_various(void)
{
	NAMESPACE::vector<int> v1(70);
	for (unsigned long int i = 0; i < v1.size(); ++i)
		v1[i] = (v1.size() - i);
	NAMESPACE::vector<int> v2 = v1;
	v2.clear();
	print_vector(v2, "v2");
	print_vector(v1, "v1");
	v2 = v1;
	v2[5] = 999;
	v2.swap(v1);
	print_vector(v2, "v2");
	print_vector(v1, "v1");
	v1.pop_back();
	v1.push_back(76);
	print_vector(v1, "v1");
	std::cout << v1.front() << v1.back() << std::endl;
	std::cout << v1.empty() << std::endl;
	v1.resize(6);
	print_vector(v1, "v1 resized");
	v1.resize(60);
	print_vector(v1, "v1 resized");

	NAMESPACE::vector<int> vtest(70);
	for (unsigned long int i = 0; i < vtest.size(); ++i)
		vtest[i] = (vtest.size() - i);
	NAMESPACE::vector<int>::const_iterator ittest = vtest.begin() + 5;
	NAMESPACE::vector<int>::iterator ittestconst(ittest);
	(void)ittest;
	(void)ittestconst;
	
}

#ifdef TIME_COMPARISON
#include <time.h>
void test_vector_exec_time(void)
{
	const clock_t begin_time = clock();

	NAMESPACE::vector<int> v1(70000);
	for (unsigned long int i = 0; i < v1.size(); ++i)
		v1[i] = (v1.size() - i);
	v1[500] = 999;
	v1.front() = v1.back();
	v1[50] = v1.at(66);
	v1.erase(v1.begin(), v1.begin() + 60);
	v1.erase(v1.begin(), v1.begin() + 60);
	v1.erase(v1.begin(), v1.begin() + 60);
	v1.erase(v1.end() - 60, v1.end());
	v1.erase(v1.end() - 60, v1.end());
	v1.erase(v1.end() - 60, v1.end());
	v1.erase(v1.end() - 60, v1.end());
	v1.resize(70);
	v1.resize(20000);
	std::cout << "elapsed time : " << float( clock () - begin_time ) /  CLOCKS_PER_SEC << "s" << std::endl;
}
#endif

//reverse_it

/*
template <typename T>
void test1(T vector)
{
	//std::vector<int> vector;
	for (int i=0; i<10; i++) vector.push_back(i);

	typedef typename T::iterator					Iter;
	Iter begin = vector.begin();
	Iter end = vector.end();

	for (; begin != end; begin++)
		std::cout << *begin << " ";
	std::cout << std::endl;

	typedef typename T::reverse_iterator			RIter;
	RIter rbegin = vector.rbegin();
	RIter rend = vector.rend();

	for (; rbegin != rend; rbegin++)
		std::cout << *rbegin << " ";
	std::cout << std::endl;
}

template <typename T>
void test2(T vector)
{
	for (int i=0; i<10; i++)
		vector.push_back(i);

	typedef typename T::iterator					Iter;
	Iter begin = vector.begin();
	begin += 3;
	begin--;
	--begin;
	Iter end = vector.end();

	for (; begin != end; begin++)
		std::cout << *begin << " ";
	std::cout << std::endl;

	typedef typename T::reverse_iterator			RIter;
	RIter rbegin = vector.rbegin();
	rbegin += 3;
	rbegin--;
	--rbegin;
	RIter rend = vector.rend();

	for (; rbegin != rend; rbegin++)
		std::cout << *rbegin << " ";
	std::cout << std::endl;
}

template <typename T>
void test3(T vector)
{
	for (int i=0; i<10; i++) vector.push_back(i);

	std::cout << "iteration on vector" << std::endl;
	for (int j = 0; j < 10; j++)
		std::cout << vector[j] << " ";
	std::cout << std::endl;

	std::cout << "iteration on iterator" << std::endl;
	typedef typename T::iterator					Iter;
	Iter begin = vector.begin();
	for (int j = 0; j < 10; j++)
		std::cout << begin[j] << " ";
	std::cout << std::endl;

	std::cout << "iteration on reverse iterator" << std::endl;
	typedef typename T::reverse_iterator			RIter;
	RIter rbegin = vector.rbegin();
	for (int j = 0; j < 10; j++)
		std::cout << rbegin[j] << " ";

	std::cout << std::endl;
}

template <typename T>
void test4(T vector)
{
	for (int i=0; i<10; i++) vector.push_back(i);
	{
		T vector2(vector);
		print_vector(vector2);
	}
	{
		T vector2;
		vector2 = vector;
		print_vector(vector2);
	}
	{
		T vector2(3);
		vector2 = vector;
		print_vector(vector2);
	}
	{
		T vector2(3, 90);
		vector2 = vector;
		print_vector(vector2);
	}
	{
		T vector2(3, 90);
		vector2.assign (7, 100);;
		print_vector(vector2);
	}
	{
		T vector2(3, 90);
		vector2.assign (vector.begin(), vector.end());;
		print_vector(vector2);
	}
}

template <typename T>
void test5(T vector)
{
	(void) vector;
	T vct(7);
	T vct_two(4);
	T vct_three;
	T vct_four;

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = (vct.size() - i) * 3;
	for (unsigned long int i = 0; i < vct_two.size(); ++i)
		vct_two[i] = (vct_two.size() - i) * 5;
	print_size(vct);
	print_size(vct_two);

	vct_three.assign(vct.begin(), vct.end());
	vct.assign(vct_two.begin(), vct_two.end());
	vct_two.assign(2, 42);
	vct_four.assign(4, 21);

	std::cout << "\t### After assign(): ###" << std::endl;

	print_size(vct);
	print_size(vct_two);
	print_size(vct_three);
	print_size(vct_four);

	vct_four.assign(6, 84);
	print_size(vct_four);

	std::cout << "\t### assign() on enough capacity and low size: ###" << std::endl;

	vct.assign(5, 53);
	vct_two.assign(vct_three.begin(), vct_three.begin() + 3);

	print_size(vct);
	print_size(vct_two);
}
*/
