/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_tests.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:38:23 by sameye            #+#    #+#             */
/*   Updated: 2022/03/28 18:46:26 by sameye           ###   ########.fr       */
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

void test_vector_assign(void)
{
	NAMESPACE::vector<int>v1(10);
	print_vector(v1, "v1");
}


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
