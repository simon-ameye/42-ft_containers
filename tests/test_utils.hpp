/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:50:37 by sameye            #+#    #+#             */
/*   Updated: 2022/05/18 17:33:23 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#ifndef TEST_UTILS_HPP
#define TEST_UTILS_HPP

//COMMENT IF YOU DONT WANT TO TEST SPEED
//#define TIME_COMPARISON

template <typename T>
void	print_data(T const &vct)
{
	std::cout << "size: "		<< vct.size();
	std::cout << " capacity: "	<< (vct.capacity() >= vct.size() ? "OK" : "KO");
	//std::cout << " max_size: "	<< vct.max_size();
	std::cout << std::endl;
}

template <typename T>
void print_content(T vector)
{
	std::cout << "content : ";
	typename T::iterator begin = vector.begin();
	typename T::iterator end = vector.end();
	while (begin != end)
	{
		std::cout << *begin << " ";
		begin++;
	}
	std::cout << std::endl;
}

template <typename T>
void print_vector(T vector, std::string str)
{
	std::cout << "----- vector " << str << " -----"<< std::endl;
	print_data(vector);
	print_content(vector);
}

#endif