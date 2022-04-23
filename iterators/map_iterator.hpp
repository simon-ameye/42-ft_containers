/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:41:34 by sameye            #+#    #+#             */
/*   Updated: 2022/04/23 19:50:23 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include "../utils/CustomTree.hpp"

#define ADD 1
#define SUBSTRACT -1

namespace ft
{
	template < class Key, class T, class Compare>
	class map_iterator
	{
		public:
			/* *******************ALIASES******************* */
			typedef Key												key_type;
			typedef T												mapped_type;

		private:
			typedef ft::Node < key_type, mapped_type >				N;
			typedef ft::CustomTree<Key, T, Compare>					tree_type;

		public:
			typedef N*												elemPtr;
			typedef N&												reference;
			typedef ft::pair<Key, T>							pair;
			//typedef T*												pointer;

			/* *******************ATTRIBUTES******************* */
		private:
			elemPtr _val;

			/* *******************CONSTRUCTORS & DESTRUCTORS******************* */
		public:
			/* --------------------default constructor-------------------- */
			map_iterator(elemPtr val = 0) : _val(val) {}

			/* --------------------copy constructor-------------------- */
			map_iterator(const map_iterator< Key, T , Compare>& copy)
			{
				_val = copy.getElemPtr();
			}

			/* --------------------destructor-------------------- */
			~map_iterator() {}

			map_iterator& operator=(const map_iterator& assign)
			{
				if (this != &assign)
					_val = assign._val;
				return (*this);
			}

			/* *******************GETTER******************* */
		public:
			elemPtr getElemPtr() const			{ return _val; }

			/* *******************OPPERATOR OVERLOAD******************* */
		public:
			pair& operator*() const
			{
				return (ft::make_pair<Key, T>(_val->_key, _val->_map));
			}
			pair* operator->() const
			{
				return &(ft::make_pair<Key, T>(_val->_key, _val->_map)); //obligé de stocker une paire malocee dans node !
			}
			map_iterator& operator++()
			{
				_val = _tree.next(_val);
				return (*this);
			}
			map_iterator& operator--()
			{
				_val = _tree.next(_val); //TO CHANGE
				return (*this);
			}

			map_iterator operator++(int)
			{
				map_iterator res(*this);
				++(*this);
				return (res);
			}

			map_iterator operator--(int)
			{
				map_iterator res(*this);
				--(*this);
				return (res);
			}

			bool operator==(const map_iterator& it) const	{ return (it._val == _val); }
			bool operator!=(const map_iterator& it) const	{ return (it._val != _val); }

		private:
			tree_type _tree;

	};
}
#endif