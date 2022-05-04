/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:40:42 by sameye            #+#    #+#             */
/*   Updated: 2022/05/04 18:55:08 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include "../utils/utils.hpp"
#include <stdlib.h>
#include "../utils/CustomTree.hpp"
#include "../iterators/map_iterator.hpp"
#include <math.h>

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator <T> >
	class map
	{
		public:
		typedef Key															key_type;
		typedef T															mapped_type;
		typedef ft::pair<key_type,mapped_type>								value_type; //UNABLE TO MAKE IT CONST AS REQUIRED
		typedef Compare														key_compare;
		typedef Alloc														allocator_type;
		typedef typename allocator_type::reference							reference;
		typedef typename allocator_type::const_reference					const_reference;
		typedef typename allocator_type::pointer							pointer;
		typedef typename allocator_type::const_pointer						const_pointer;
		typedef ft::map_iterator<value_type, Key, Compare, false>					iterator;
		typedef ft::map_iterator<value_type, Key, Compare, true>					const_iterator; //TO SET AS CONST
		//typedef ft::map_reverse_iterator									reverse_iterator; //TO DO
		//typedef ft::map_reverse_iterator									const_reverse_iterator; //TO DO
		typedef std::ptrdiff_t												difference_type;
		typedef std::size_t													size_type;

		private:
		class value_compare_class
		{
			friend class map<key_type, mapped_type, key_compare, Alloc>;

			protected:
				Compare comp;
				value_compare_class (Compare c) : comp(c) {}
			public:

				bool operator()(const value_type & x, const value_type & y) const
				{
					return (comp(x.first, y.first)); //see std::map::value_comp
				}
		};

		public:
		typedef value_compare_class			value_compare;

		private:
		typedef ft::CustomTree<value_type, Key, value_compare>		tree_type;
		typedef ft::Node<value_type>								node_type;

			/* *******************CONSTRUCTORS******************* */
		public:
			/* --------------------default-------------------- */
			explicit
			map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
			_compare(comp), _alloc(alloc) {}

			/* --------------------copy-------------------- */
			map(const map& copy) : _compare(copy._compare), _alloc(copy._alloc)
			{
				insert(copy.begin(), copy.end());
			}

			/* --------------------range-------------------- */
			map(iterator first, iterator last)
			{
				insert(first, last);
			}

			/* --------------------destructor-------------------- */
		public:
			~map() {}

			/* *******************OPERATOR******************* */
			/* --------------------=-------------------- */
		public:
			map& operator= (const map& rhs)
			{
				clear();
				insert(rhs.begin(), rhs.end());
			}

			/* *******************ITERATORS******************* */
		public:
			iterator				begin()					{ return ++iterator(_tree.minKeyNode()); } //++ because of passed the begining
			//const_iterator			begin() const			{ return (const_iterator(_bst._last_node->left, _bst._last_node)); } //need to create a const iterator to allow copy construction
			iterator				end()					{ return iterator(_tree.maxKeyNode()); }
			//reverse_iterator		rbegin()				{ return reverse_iterator(_vector + _size - 1); }
			//reverse_iterator		rend()					{ return reverse_iterator(_vector - 1); }

			/* *******************CAPACITY******************* */
		public:
			bool empty() const
			{
				return (++iterator(_tree.minKeyNode()) == iterator(_tree.maxKeyNode()));
			}

			size_type size() const
			{
				return (_tree.getSize());
			}

			size_type		max_size() const
			{
				return static_cast<size_type>(pow(2.0, 64.0) / static_cast<double>(sizeof(value_type))) - 1;
			}

			/* *******************ELEMENT ACCESS******************* */
		public:
			mapped_type& operator[] (const key_type& k)
			{
				node_type* tmp;
				tmp = _tree.at(k);
				if (!tmp)
				{
					_tree.insert(ft::make_pair(k, mapped_type()));
					tmp = _tree.at(k);
				}
				return (tmp->_val.second);
			}

			/* *******************MODIFIERS******************* */
		public:
			ft::pair<iterator,bool> insert (const value_type& val) //single element
			{
				node_type *tmp = _tree.at(val.first);
				if (tmp)
					return (ft::pair<iterator, bool>(iterator(tmp), false));
				_tree.insert(val);
				return (ft::pair<iterator, bool>(iterator(_tree.at(val.first)), false));
			}
			
			iterator insert (iterator position, const value_type& val) //with hint
			{
				(void) position;
				return (insert(val).first);
			}

			template <class InputIterator>
			void insert (InputIterator first, InputIterator last) //range
			{
				while (first != last)
				{
					insert(*first);
					++first;
				}
			}

			void erase (iterator position)
			{
				_tree.erase(position->first);
			}

			size_type erase (const key_type& k)
			{
				node_type *tmp = _tree.at(k);
				if (tmp)
				{
					_tree.erase(k);
					return (1);
				}
				return (0);
			}

			void erase (iterator first, iterator last)
			{
				while (first != last)
				{
					erase(first);
					++first;
				}
			}

			void swap (map& x)
			{
				node_type *tmproot = x._get_root();
				size_t tmpsize = x._get_size();
				x._set_root(_get_root());
				x._set_size(_get_size());
				_set_root(tmproot);
				_set_size(tmpsize);
			}

			void clear(void)
			{
				_tree.clear();
			}

			/* *******************OBSERVERS******************* */
		public:
			key_compare key_comp() const
			{
				return (key_compare());
			}

			value_compare value_comp() const
			{
				return (value_compare(key_compare()));
			}

			/* *******************OPERATIONS******************* */
		public:
			iterator find (const key_type& k)
			{
				node_type* tmp;
				tmp = _tree.at(k);
				if (tmp)
					return (iterator(tmp));
				else
					return (iterator(_tree.maxKeyNode()));
			}

			const_iterator find (const key_type& k) const
			{
				node_type* tmp;
				tmp = _tree.at(k);
				if (tmp)
					return (iterator(tmp));
				else
					return (iterator(_tree.maxKeyNode()));
			}

			size_type count (const key_type& k) const
			{
				return (_tree.at(k) != NULL);
			}

			iterator lower_bound (const key_type& k)
			{
				iterator beg = this->begin();
				iterator end = this->end();

				while (beg != end)
				{
					if (_compare((*beg).first, k) == false)
						break;
					beg++;
				}
				return (beg);
			}

			const_iterator lower_bound (const key_type& k) const
			{
				return (const_iterator(this->lower_bound(k))); 
			}

			iterator upper_bound (const key_type& k)
			{
				iterator beg = this->begin();
				iterator end = this->end();

				while (beg != end)
				{
					if (_compare(k, (*beg).first))
						break;
					beg++;
				}
				return (beg);
			}

			const_iterator upper_bound (const key_type& k) const
			{
				return (const_iterator(this->upper_bound(k)));
			}

			pair<iterator,iterator> equal_range (const key_type& k)
			{
				return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
			}

			pair<const_iterator,const_iterator> equal_range (const key_type& k) const
			{
				return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
			}

			/* *******************ALLOCATOR******************* */
		public:
			allocator_type get_allocator() const
			{
				return (allocator_type());
			}

			/* *******************DEV******************* */ //TO REMOVE
		public:
			void print_tree(void) //TO DELETE
			{
				_tree.print_tree();
			}

			void pre0rder(void) //TO DELETE
			{
				_tree.pre0rder();
			}

			/* *******************PRIVATE VARIABLES******************* */
		private:
			tree_type _tree;
			Compare _compare;
			Alloc _alloc; //copy of allocator

			/* *******************PRIVATE FUNCTIONS******************* */
		private:
			void _set_root(node_type* root) {_tree._root = root;}
			node_type* _get_root(void) {return (_tree._root);}
			void _set_size(size_t size) {_tree._size = size;}
			size_t _get_size(void) {return (_tree._size);}

	};
}

#endif