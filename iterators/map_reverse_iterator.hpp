/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reverse_iterator.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 12:06:03 by sameye            #+#    #+#             */
/*   Updated: 2022/05/05 14:47:27 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_REVERSE_ITERATOR_HPP
#define MAP_REVERSE_ITERATOR_HPP

#include "map_iterator.hpp"

namespace ft
{
	template < class value_type, class Key, class Compare, bool Const>
	class map_reverse_iterator : map_iterator<value_type, Key, Compare, Const>
	{
		//using vector<T>::vector; 
	};
	
}


#endif