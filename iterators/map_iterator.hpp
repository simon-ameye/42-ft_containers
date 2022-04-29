/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:41:34 by sameye            #+#    #+#             */
/*   Updated: 2022/04/29 17:04:36 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include "../utils/CustomTree.hpp"

#define ADD 1
#define SUBSTRACT -1

namespace ft
{
	template < class value_type, class Key, class Compare>
	class map_iterator
	{
		public:
			/* *******************ALIASES******************* */
			//typedef value_type.first											key_type;
			//typedef value_type.second												mapped_type;

		private:
			typedef ft::Node < value_type >				N;
			typedef ft::CustomTree<value_type, Key, Compare>					tree_type;

		public:
			//typedef N*												elemPtr;
			//typedef N&												reference;
			//typedef ft::pair<Key, T>							pair;
			//typedef T*												pointer;

			/* *******************ATTRIBUTES******************* */
		private:
			N* _node;

			/* *******************CONSTRUCTORS & DESTRUCTORS******************* */
		public:
			/* --------------------default constructor-------------------- */
			map_iterator(N* node = NULL) : _node(node) {}

			/* --------------------copy constructor-------------------- */
			map_iterator(const map_iterator< value_type, Key, Compare> & copy)
			{
				_node = copy.getElemPtr();
			}

			/* --------------------destructor-------------------- */
			~map_iterator() {}

			map_iterator& operator=(const map_iterator& assign)
			{
				if (this != &assign)
					_node = assign._node;
				return (*this);
			}

			/* *******************GETTER******************* */
		public:
			N* getElemPtr() const			{ return _node; }

			/* *******************OPPERATOR OVERLOAD******************* */
		public:
			value_type& operator*() const
			{
				return (_node->_val);
			}
			value_type* operator->() const
			{
				return &_node->_val; //obligé de stocker une paire malocee dans node !
			}
			map_iterator& operator++()
			{
				_node = _next(_node);
				return (*this);
			}
			map_iterator& operator--()
			{
				_node = _previous(_node); //TO CHANGE
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

			bool operator==(const map_iterator& it) const	{ return (it._node == _node); }
			bool operator!=(const map_iterator& it) const	{ return (it._node != _node); }

		private:
			//tree_type _tree;
			N* _next(N *node) const
			{
				if (node->right)
					return (_minKeyNode(node->right));
				else
					while (node->parent)
					{
						if (node->parent->left == node)
							return (node->parent);
						node = node->parent;
					}
				return (NULL); // TO CHANGE
			}

			N* _previous(N *node) const
			{
				if (node->right)
					return (_maxKeyNode(node->left));
				else
					while (node->parent)
					{
						if (node->parent->right == node)
							return (node->parent);
						node = node->parent;
					}
				return (NULL); // TO CHANGE
			}

			N* _minKeyNode(N* node) const
			{
				N* current = node;

				/* loop down to find the leftmost leaf */

				while (current->left != NULL)
					current = current->left;
				return current;
			}

			N * _maxKeyNode(N* node) const
			{
				N* current = node;

				/* loop down to find the leftmost leaf */
				while (current->right != NULL)
					current = current->right;

				return current;
			}
	};
}
#endif