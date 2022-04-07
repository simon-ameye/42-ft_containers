/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:40:42 by sameye            #+#    #+#             */
/*   Updated: 2022/04/05 15:28:37 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include "../utils/utils.hpp"
#include <stdlib.h>
#include "../utils/CustomTree.hpp"


namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator <T> >
	class map
	{
		public:
		typedef Key															key_type;
		typedef T															mapped_type;
		typedef ft::pair<const key_type,mapped_type>						value_type;
		typedef Compare														key_compare;
		typedef Alloc														allocator_type;
		typedef typename allocator_type::reference							reference;
		typedef typename allocator_type::const_reference					const_reference;
		typedef typename allocator_type::pointer							pointer;
		typedef typename allocator_type::const_pointer						const_pointer;
		//typedef ft::map_iterator<T>										iterator;
		//typedef ft::map_iterator<T>										const_iterator;
		//typedef ft::map_reverse_iterator									reverse_iterator;
		//typedef ft::map_reverse_iterator									const_reverse_iterator;
		typedef std::ptrdiff_t												difference_type;
		typedef std::size_t													size_type;

		private:
		Alloc				_alloc; //copy of allocator
		pointer				_tree; //pointer on first element
		key_compare			_compare;

		private:
		class CustomCompare
		{
			key_compare _compare;
			public:
				CustomCompare(const key_compare & compare) : _compare(compare) {}

				bool operator()(const value_type & x, const value_type & y) const
				{
					return (_compare(x.first, y.first)); //see std::map::value_comp
				}
		};

		typedef CustomCompare												value_compare;
		typedef CustomTree<value_type, value_compare, allocator_type>		tree_type;

		public:
			/* *******************CONSTRUCTORS******************* */
			/* --------------------default constructor-------------------- */
			//when no argument provided
			explicit
			map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
			_alloc(alloc), _tree(NULL), _compare(comp)
			{
				std::cout << "default constructor called" << std::endl;
			}

			/* --------------------copy constructor-------------------- */
			//for construction as map<int> foo (copy)

	};
}

#endif