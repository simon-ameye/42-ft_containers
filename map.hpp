/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:40:42 by sameye            #+#    #+#             */
/*   Updated: 2022/05/17 17:12:02 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include "utils.hpp"
#include <stdlib.h>
#include "CustomTree.hpp"
#include "map_iterator.hpp"
#include "reverse_iterator.hpp"
#include <math.h>
#include <list>

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator <T> >
	class map
	{
		public:
		typedef Key																		key_type;
		typedef T																		mapped_type;
		typedef ft::pair<key_type, mapped_type>											value_type; //UNABLE TO MAKE IT CONST AS REQUIRED
		typedef Compare																	key_compare;
		typedef Alloc																	allocator_type;
		typedef typename allocator_type::reference										reference;
		typedef typename allocator_type::const_reference								const_reference;
		typedef typename allocator_type::pointer										pointer;
		typedef typename allocator_type::const_pointer									const_pointer;
		typedef ft::map_iterator< value_type, Key, Compare, Alloc, false>				iterator;
		typedef ft::map_iterator< value_type, Key, Compare, Alloc, true>				const_iterator;
		typedef ft::reverse_iterator<iterator>											reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>									const_reverse_iterator;
		typedef typename allocator_type::difference_type								difference_type;
		typedef std::size_t																size_type;

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
		typedef value_compare_class														value_compare;

		private:
		typedef ft::CustomTree<value_type, Key, Compare>								tree_type;
		typedef typename tree_type::Node												node_type;

			/* *******************CONSTRUCTORS******************* */
		public:
			/* --------------------default-------------------- */
			explicit
			map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
			_compare(comp), _alloc(alloc)
			{}

			/* --------------------copy-------------------- */
			map(const map& copy) : _compare(copy._compare), _alloc(copy._alloc)
			{
				insert(copy.begin(), copy.end());
			}

			/* --------------------range-------------------- */
			template <class InputIterator>
			map(InputIterator first, InputIterator last)
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
				if (this == &rhs)
					return (*this);
				clear();
				insert(rhs.begin(), rhs.end());
				return (*this);
			}

			/* *******************ITERATORS******************* */
		public:
			iterator					begin()					{ return ++iterator				(_tree.minKeyNode()); }
			iterator					end()					{ return iterator				(_tree.maxKeyNode()); }
			reverse_iterator			rbegin()				{ return reverse_iterator		(_tree.maxKeyNode()); }
			reverse_iterator			rend()					{ return --reverse_iterator		(_tree.minKeyNode()); }
			const_iterator				begin()		const		{ return ++iterator				(_tree.minKeyNode()); }
			const_iterator				end()		const		{ return iterator				(_tree.maxKeyNode()); }
			const_reverse_iterator		rbegin()	const		{ return reverse_iterator		(_tree.maxKeyNode()); }
			const_reverse_iterator		rend()		const		{ return reverse_iterator		(_tree.minKeyNode()); }

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
				//return static_cast<size_type>(pow(2.0, 64.0) / static_cast<double>(sizeof(value_type))) - 1;
				return (this->_alloc.max_size());
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
				return (ft::pair<iterator, bool>(iterator(_tree.at(val.first)), true));
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
				iterator	tmp;
				while (first != last)
				{
					tmp = first++;
					erase(tmp);
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
				const_iterator beg = this->begin();
				const_iterator end = this->end();

				while (beg != end)
				{
					if (_compare((*beg).first, k) == false)
						break;
					beg++;
				}
				return (const_iterator(beg));
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
				const_iterator beg = this->begin();
				const_iterator end = this->end();

				while (beg != end)
				{
					if (_compare(k, (*beg).first))
						break;
					beg++;
				}
				return (const_iterator(beg));
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
			void		_set_root(node_type* root)	{_tree._root = root;}
			void		_set_size(size_t size)		{_tree._size = size;}
			node_type*	_get_root(void)				{return (_tree._root);}
			size_t		_get_size(void)				{return (_tree._size);}
	};

		/* *******************RELATIONAL OPERATORS******************* */
	template <class Key, class T, class Compare, class Alloc>
	bool operator<  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator== ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (!(lhs < rhs) && !(rhs < lhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{	return (!(lhs == rhs));	}


	template <class Key, class T, class Compare, class Alloc>
	bool operator<= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{	return (!(rhs < lhs));	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{	return (rhs < lhs);	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{	return (!(lhs < rhs));	}

}
#endif