/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:41:34 by sameye            #+#    #+#             */
/*   Updated: 2022/05/04 21:28:22 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include "../utils/CustomTree.hpp"
#include "../utils/trueafalseb.hpp"

#define ADD 1
#define SUBSTRACT -1

namespace ft
{
	template < class value_type, class Key, class Compare, bool Const>
	class map_iterator
	{
			/* *******************ALIASES******************* */
		private:
			typedef ft::Node < value_type >													N;
			typedef ft::CustomTree<value_type, Key, Compare>								tree_type;
			typedef typename TrueAFalseB<Const, const value_type&, value_type&>::type			reference;
			typedef typename TrueAFalseB<Const, const value_type*, value_type*>::type			pointer;

			/* *******************VARIABLES******************* */
		private:
			N* _node;

			/* *******************CONSTRUCTORS & DESTRUCTORS******************* */
		public:
			/* --------------------default constructor-------------------- */
			map_iterator(N* node = NULL) : _node(node) {}

			/* --------------------copy constructor-------------------- */
			map_iterator(const map_iterator< value_type, Key, Compare, false> & copy)
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
			reference operator*() const
			{
				return (_node->_val);
			}

			pointer operator->() const
			{
				return &_node->_val;
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

			bool operator==(const map_iterator& it) const
			{
				return (it._node == _node);
			}

			bool operator!=(const map_iterator& it) const
			{
				return (it._node != _node);
			}

			/* *******************USEFUL FUNCTIONS******************* */
		private:
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
				while (current->left != NULL)
					current = current->left;
				return current;
			}

			N* _maxKeyNode(N* node) const
			{
				N* current = node;
				while (current->right != NULL)
					current = current->right;
				return current;
			}
	};
}
#endif