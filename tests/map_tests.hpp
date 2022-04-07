/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:33:01 by sameye            #+#    #+#             */
/*   Updated: 2022/04/04 19:34:09 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_TESTS_HPP
#define MAP_TESTS_HPP

//#define TIME_COMPARISON

#ifndef NAMESPACE
#define NAMESPACE ft
#endif

void test_map_assign(void);

#ifdef TIME_COMPARISON
void test_vector_exec_time(void);
#endif

#endif