/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 17:01:54 by sameye            #+#    #+#             */
/*   Updated: 2022/03/24 15:05:15 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "../containers/vector.hpp"
#include <vector>
#include "../iterators/vector_iterator.hpp"
#include <iterator> 

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
	for (int i=0; i<10; i++) vector.push_back(i);

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

int main (void)
{
	{
		std::cout << "\n################## test 1 ##################" << std::endl;

		std::cout << "std::vector<int>" << std::endl;
		std::vector<int> std1;
		test1(std1);

		std::cout << "ft::vector<int>" << std::endl;
		ft::vector<int> ft1;
		test1(ft1);
	}
	{
		std::cout << "\n################## test 2 ##################" << std::endl;

		std::cout << "std::vector<int>" << std::endl;
		std::vector<int> std1;
		test2(std1);

		std::cout << "ft::vector<int>" << std::endl;
		ft::vector<int> ft1;
		test2(ft1);
	}
	{
		std::cout << "\n################## test 3 ##################" << std::endl;

		std::cout << "std::vector<int>" << std::endl;
		std::vector<int> std1;
		test3(std1);

		std::cout << "ft::vector<int>" << std::endl;
		ft::vector<int> ft1;
		test3(ft1);
	}
}