/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 17:01:54 by sameye            #+#    #+#             */
/*   Updated: 2022/05/16 18:46:27 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_tests.hpp"
#include "map_tests.hpp"
#include "map_tests2.hpp"
#include "default_tests.hpp"
#include "test_utils/test_utils.hpp"

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
	std::cout << "------------------sandbox------------------" << std::endl;
	test_vector_sandbox();
	std::cout << "------------------exec time------------------" << std::endl;
	test_vector_exec_time();
}

void test_map(void)
{
	std::cout << "##########################################MAP##########################################" << std::endl;
	std::cout << "------------------assign------------------" << std::endl;
	test_map_assign();
	//map_custom_2();
	
}

void test_default(void)
{
	std::cout << "##########################################DEFAULT##########################################" << std::endl;
	char str[] = "10";
	char *ptr = &str[0];
	char **av = &ptr;
	default_tests(2, av);
}

int main (void)
{
	//test_default();
	test_vector();
	test_map();
}
