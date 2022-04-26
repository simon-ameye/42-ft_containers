/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:40:42 by sameye            #+#    #+#             */
/*   Updated: 2022/04/26 01:27:34 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include "../utils/utils.hpp"
#include <stdlib.h>
#include "../utils/CustomTree.hpp"
#include "../iterators/map_iterator.hpp"


namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator <T> >
	class map
	{
		public:
		typedef Key															key_type;
		typedef T															mapped_type;
		typedef ft::pair<key_type,mapped_type>						value_type;
		typedef Compare														key_compare;
		typedef Alloc														allocator_type;
		typedef typename allocator_type::reference							reference;
		typedef typename allocator_type::const_reference					const_reference;
		typedef typename allocator_type::pointer							pointer;
		typedef typename allocator_type::const_pointer						const_pointer;
		typedef ft::map_iterator<value_type, Key, Compare>											iterator;
		typedef ft::map_iterator<value_type, Key, Compare>											const_iterator;
		//typedef ft::map_reverse_iterator									reverse_iterator;
		//typedef ft::map_reverse_iterator									const_reverse_iterator;

		//typedef typename ft::CustomTree<value_type, key_compare>::iterator iterator;




		typedef std::ptrdiff_t												difference_type;
		typedef std::size_t													size_type;

		private:
		Alloc				_alloc; //copy of allocator
		//pointer				_tree; //pointer on first element
		key_compare			_compare;

		private:
		class value_compare_class
		{
			key_compare _compare;
			public:
				value_compare_class(const key_compare & compare) : _compare(compare) {}

				bool operator()(const value_type & x, const value_type & y) const
				{
					return (_compare(x.first, y.first)); //see std::map::value_comp
				}
		};

		public:
		typedef value_compare_class			value_compare;

		//typedef CustomCompare												value_compare;
		//typedef CustomTree<key_type, mapped_type, value_compare, allocator_type>		tree_type;
		private:
		typedef ft::CustomTree<value_type, Key, value_compare>		tree_type;

		public:
			/* *******************CONSTRUCTORS******************* */
			/* --------------------default constructor-------------------- */
			//when no argument provided
			explicit
			map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
			_alloc(alloc), _compare(comp) {}


			//pair<iterator,bool> insert (const value_type& val)
			//{	return (_tree.insert(val));}

			void insert(const value_type& val)
			{
				_tree.insert(val);
			}

			void erase(Key key)
			{
				_tree.erase(key);
			}

			T &at(Key key)
			{
				return (_tree.at(key)->_val.second);
			}

			void print_tree(void)
			{
				_tree.print_tree();
			}

		public:
			/* *******************ITERATORS******************* */
			iterator				begin()					{ return iterator(_tree.minKeyNode()); }
			const_iterator			begin() const			{ return const_iterator(_tree.minKeyNode()); }
			iterator				end()					{ return iterator(_tree.get_passed_the_end()); }
			const_iterator			end() const				{ return const_iterator(_tree.get_passed_the_end()); }
			//reverse_iterator		rbegin()				{ return reverse_iterator(_vector + _size - 1); }
			//const_reverse_iterator	rbegin() const			{ return const_reverse_iterator(_vector + _size - 1); }
			//reverse_iterator		rend()					{ return reverse_iterator(_vector - 1); }
			//const_reverse_iterator	rend() const			{ return const_reverse_iterator(_vector - 1); }

		private:
			tree_type _tree;
			/* --------------------copy constructor-------------------- */
			//for construction as map<int> foo (copy)

	};
}

#endif