/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reverse_iterator.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 12:06:03 by sameye            #+#    #+#             */
/*   Updated: 2022/05/12 13:58:57 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_REVERSE_ITERATOR_HPP
#define MAP_REVERSE_ITERATOR_HPP

#include "map_iterator.hpp"
#include "CustomTree.hpp"

namespace ft
{
	template < class value_type, class Key, class Compare, bool Const>
	class map_reverse_iterator : public map_iterator<value_type, Key, Compare, Const>
	{
			/* *******************ALIASES******************* */
		private:
			//typedef ft::Node < value_type >														N;
			typedef ft::CustomTree<value_type, Key, Compare>									tree_type;
			typedef typename tree_type::Node													N;

			
			typedef typename FalseXTrueY<Const, value_type&, const value_type&>::type								reference;
			typedef typename FalseXTrueY<Const, value_type*, const value_type*>::type								pointer;
		public:
			/* --------------------default constructor-------------------- */
			map_reverse_iterator(N* node = NULL)
			{
				this->_node = node;
			}

			/* --------------------copy constructor-------------------- */
			map_reverse_iterator(const map_iterator< value_type, Key, Compare, false> & copy)
			{
				this->_node = copy.getElemPtr();
			}

			map_reverse_iterator(const map_iterator< value_type, Key, Compare, true> & copy)
			{
				this->_node = copy.getElemPtr();
			}

			/* --------------------destructor-------------------- */
			~map_reverse_iterator() {}

			/* *******************OPPERATOR OVERLOAD******************* */
		public:

			map_reverse_iterator& operator++()
			{
				this->_node = this->_previous(this->_node);
				return (*this);
			}

			map_reverse_iterator& operator--()
			{
				this->_node = this->_next(this->_node); //TO CHANGE
				return (*this);
			}

			map_reverse_iterator operator++(int)
			{
				map_reverse_iterator res(*this);
				--(*this);
				return (res);
			}

			map_reverse_iterator operator--(int)
			{
				map_reverse_iterator res(*this);
				++(*this);
				return (res);
			}
	};
	
}

#endif