/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 17:01:54 by sameye            #+#    #+#             */
/*   Updated: 2022/03/31 19:18:53 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_tests.hpp"
#include <iostream>

void test_vector(void)
{
	std::cout << "##########################################VECTOR##########################################" << std::endl;
	std::cout << "------------------assign------------------" << std::endl;
	test_vector_assign();
	std::cout << "------------------at------------------" << std::endl;
	test_vector_at_const();
	std::cout << "------------------copy------------------" << std::endl;
	test_vector_copy();
	std::cout << "------------------insert------------------" << std::endl;
	test_vector_insert();
	std::cout << "------------------erase------------------" << std::endl;
	test_vector_erase();
	std::cout << "------------------iterators------------------" << std::endl;
	test_vector_iterators();
	std::cout << "------------------comparison------------------" << std::endl;
	test_vector_comparison();
	std::cout << "------------------various------------------" << std::endl;
	test_vector_various();
	#ifdef TIME_COMPARISON
	std::cout << "------------------exec time------------------" << std::endl;
	test_vector_exec_time();
	#endif

}

int main (void)
{
	test_vector();
/*
	{	std::cout << "\n################## test 1 ##################" << std::endl;

		std::cout << "-----std::vector<int>" << std::endl;
		std::vector<int> std1;
		test1(std1);

		std::cout << "-----ft::vector<int>" << std::endl;
		ft::vector<int> ft1;
		test1(ft1);
	}
	{	std::cout << "\n################## test 2 ##################" << std::endl;

		std::cout << "-----std::vector<int>" << std::endl;
		std::vector<int> std1;
		test2(std1);

		std::cout << "-----ft::vector<int>" << std::endl;
		ft::vector<int> ft1;
		test2(ft1);
	}
	{	std::cout << "\n################## test 3 ##################" << std::endl;

		std::cout << "-----std::vector<int>" << std::endl;
		std::vector<int> std1;
		test3(std1);

		std::cout << "-----ft::vector<int>" << std::endl;
		ft::vector<int> ft1;
		test3(ft1);
	}
	{	std::cout << "\n################## test 4 ##################" << std::endl;
		std::cout << "-----std::vector<int>" << std::endl;
		std::vector<int> std1;
		test4(std1);

		std::cout << "-----ft::vector<int>" << std::endl;
		ft::vector<int> ft1;
		test4(ft1);
	}
	{	std::cout << "\n################## test 5 ##################" << std::endl;
		std::cout << "-----std::vector<int>" << std::endl;
		std::vector<int> std1;
		test5(std1);

		std::cout << "-----ft::vector<int>" << std::endl;
		ft::vector<int> ft1;
		test5(ft1);
	}
	*/
}
