/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_tests.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:40:02 by sameye            #+#    #+#             */
/*   Updated: 2022/05/13 17:59:43 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_TESTS_HPP
#define VECTOR_TESTS_HPP

//#define TIME_COMPARISON

#ifndef NAMESPACE
#define NAMESPACE ft
#endif

void test_vector_assign(void);
void test_vector_at_const(void);
void test_vector_copy(void);
void test_vector_insert(void);
void test_vector_erase(void);
void test_vector_iterators(void);
void test_vector_comparison(void);
void test_vector_various(void);
#ifdef TIME_COMPARISON
void test_vector_exec_time(void);
#endif
void test_vector_sandbox(void);
#endif