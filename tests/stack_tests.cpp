/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_tests.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:47:46 by sameye            #+#    #+#             */
/*   Updated: 2022/05/19 13:22:01 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stack>
#include <list>
#include <vector>
#include <deque>
#include <iterator> 
#include <time.h>
#include <iomanip>

#include "../stack.hpp"
#include "../vector_iterator.hpp"

#include "test_utils.hpp"
#include "stack_tests.hpp"

void test_stack_assign(void)
{
	#ifdef TIME_COMPARISON
	const clock_t begin_time = clock();
	#endif
	
	NAMESPACE::stack<int> s1;
	std::cout << "s1.empty(): " <<  s1.empty() << std::endl;
	std::cout << "s1.size(): " << s1.size() << std::endl;
	s1.push(1);
	s1.push(2);
	std::cout << "s1.push()" << std::endl;
	std::cout << "s1.push()" << std::endl;
	std::cout << "s1.empty(): " <<  s1.empty() << std::endl;
	std::cout << "s1.size(): " << s1.size() << std::endl;
	std::cout << "s1.top(): " << s1.top() << std::endl;
	std::cout << "s1.size(): " << s1.size() << std::endl;
	s1.pop();
	std::cout << "s1.pop()" << std::endl;
	std::cout << "s1.size(): " << s1.size() << std::endl;
	std::cout << "s1.top(): " << s1.top() << std::endl;
	std::cout << std::endl;

	NAMESPACE::stack<int, ft::vector<int> > s2;
	std::cout << "s2.empty(): " <<  s2.empty() << std::endl;
	s2.push(42);
	std::cout << "s2.push()" << std::endl;
	s2.push(2);
	std::cout << "s2.push()" << std::endl;
	std::cout << "s2.size(): " << s2.size() << std::endl;
	std::cout << "s2.top(): " << s2.top() << std::endl;
	std::cout << "s2.empty(): " <<  s2.empty() << std::endl;
	std::cout << "s2.top(): " << s2.top() << std::endl;
	s2.pop();
	std::cout << "s2.pop()" << std::endl;
	std::cout << "s2.size(): " << s2.size() << std::endl;
	std::cout << std::endl;

	NAMESPACE::stack<int>	s3 = s1;
	s1.push(55);
	s1.push(2);
	std::cout << std::boolalpha;
	std::cout << (s1 < s3) << std::endl;
	std::cout << (s1 > s3) << std::endl;
	std::cout << (s1 <= s3) << std::endl;
	std::cout << (s1 >= s3) << std::endl;
	std::cout << (s1 == s3) << std::endl;
	std::cout << (s1 != s3) << std::endl;

	NAMESPACE::stack<int, std::vector<int> > t1;
	t1.push(55);
	NAMESPACE::stack<int, std::deque<int> > t2;
	t2.push(55);
	NAMESPACE::stack<int, std::list<int> > t3;
	t3.push(55);

	#ifdef TIME_COMPARISON
	std::cout << "STACK elapsed time : " << float( clock () - begin_time ) /  CLOCKS_PER_SEC << "s" << std::endl;
	#endif
}