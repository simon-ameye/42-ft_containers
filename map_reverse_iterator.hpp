/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reverse_iterator.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 12:06:03 by sameye            #+#    #+#             */
/*   Updated: 2022/05/12 20:59:59 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_REVERSE_ITERATOR_HPP
#define MAP_REVERSE_ITERATOR_HPP

#include "map_iterator.hpp"
#include "CustomTree.hpp"

namespace ft
{
	template < class Value_type, class Key, class Compare, class Alloc, bool Const>
	class map_reverse_iterator : public map_iterator< Value_type, Key, Compare, Alloc, Const>
	{
			/* *******************ALIASES******************* */
		public:
			typedef typename Alloc::difference_type		difference_type;
			typedef Value_type			value_type;
			//typedef typename Alloc::pointer				pointer;
			//typedef typename Alloc::reference			reference;

		private:
			typedef ft::CustomTree<value_type, Key, Compare>									tree_type;
			typedef typename tree_type::Node													N;

		public:
			typedef std::bidirectional_iterator_tag		iterator_category;
			typedef typename FalseXTrueY<Const, value_type&, const value_type&>::type								reference;
			typedef typename FalseXTrueY<Const, value_type*, const value_type*>::type								pointer;
			/* --------------------default constructor-------------------- */
		public:
			map_reverse_iterator(N* node = NULL)
			{
				this->_node = node;
			}

			/* --------------------copy constructor-------------------- */
			map_reverse_iterator(const map_iterator< value_type, Key, Compare, Alloc, false> & copy)
			{
				this->_node = copy.getElemPtr();
			}

			map_reverse_iterator(const map_iterator< value_type, Key, Compare, Alloc, true> & copy)
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
				++(*this);
				return (res);
			}

			map_reverse_iterator operator--(int)
			{
				map_reverse_iterator res(*this);
				--(*this);
				return (res);
			}
	};
	
}

#endif