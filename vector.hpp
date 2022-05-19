/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 17:05:19 by sameye            #+#    #+#             */
/*   Updated: 2022/05/19 13:36:13 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "utils.hpp"
#include "reverse_iterator.hpp"
#include "vector_iterator.hpp"
#include <cmath>
# include <limits>

namespace ft
{
	template < class T, class Alloc = std::allocator <T> >
	class vector
	{
		public :
			/* *******************TYPES DEFINITION******************* */
			typedef T												value_type; //class of elements to store
			typedef Alloc											allocator_type; //allocator
			typedef long int										difference_type; //difference between two iterators
			typedef size_t											size_type; //size
			typedef T&												reference; //reference on element (for returned values)
			typedef const T&										const_reference; //const reference on element (for returned values)
			typedef T*												pointer; //pointer on element
			typedef const T*										const_pointer; //const pointer on element
			typedef typename ft::vector_iterator< T, false>			iterator;
			typedef typename ft::vector_iterator< T, true >			const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

			/* *******************CONSTRUCTORS******************* */
			/* --------------------default constructor-------------------- */
			//when no argument provided, optional allocator
			explicit
			vector (const allocator_type& alloc = allocator_type()) :
			_alloc(alloc), _size(0), _capacity(0)
			{
				_vector = _alloc.allocate(_capacity);
			}

			/* --------------------fill constructor-------------------- */
			//for construction as vector<int> foo (10) or vector<int> foo (10, 42)
			//optional allocator
			explicit //deny implicit conversion when calling constructor
			vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) :
			_alloc(alloc), _size(n), _capacity(n)
			{
				_vector = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; ++i)
					_alloc.construct(&_vector[i], val);
			}

			/* --------------------range constructor-------------------- */
			//for construction as vector<int> foo (first, last)
			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
			typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0) :
			_alloc(alloc), _size(0)
			{
				InputIterator tmp(first);
				while (tmp++ != last)
					_size++;
				_capacity = _size;
				_vector = _alloc.allocate(_capacity);
				for (int i = 0; first != last; ++first, ++i)
					_alloc.construct(&_vector[i], *first);
			}

			/* --------------------copy constructor-------------------- */
			//for construction as vector<int> foo (copy)
			
			vector(const vector& x) :
			_alloc(x._alloc), _size(x._size), _capacity(x._capacity)
			{
				_vector = _alloc.allocate(_capacity);
				for (ft::pair<int, const_iterator> i(0, x.begin());
						i.second != x.end(); ++i.first, ++i.second)
					_alloc.construct(&_vector[i.first], *i.second);
			}
			
			~vector()
			{
				for (iterator it = begin(); it != end(); ++it)
					_alloc.destroy(&(*it));
				_alloc.deallocate(_vector, _capacity);
			}

			vector& operator= (const vector& x)
			{
				vector tmp(x);
				swap(tmp);
				return *this;
			}

		public:
			/* *******************ITERATORS******************* */
			iterator				begin()					{ return iterator(_vector); }
			const_iterator			begin() const			{ return const_iterator(_vector); }
			iterator				end()					{ return iterator(_vector + _size); }
			const_iterator			end() const				{ return const_iterator(_vector + _size); }
			reverse_iterator		rbegin()				{ return reverse_iterator(_vector + _size); }
			const_reverse_iterator	rbegin() const			{ return const_reverse_iterator(_vector + _size); }
			reverse_iterator		rend()					{ return reverse_iterator(_vector); }
			const_reverse_iterator	rend() const			{ return const_reverse_iterator(_vector); }

		public:
			/* *******************CAPACITY******************* */
			/* --------------------get size-------------------- */
			size_type		size() const					{ return _size; }

			/* --------------------get max size-------------------- */
			size_type		max_size() const				{return std::numeric_limits<difference_type>::max() / 2 / (sizeof(value_type) / 2 ?: 1);}
			
			void	resize (size_type n, value_type val = value_type())
			{
				if (n > this->max_size())
					throw (std::length_error("vector::resize"));
				else if (n < _size)
				{
					while (_size > n)
					{
						--_size;
						_alloc.destroy(_vector + _size);
					}
				}
				else
					this->insert(iterator(_vector + _size), n - _size, val);
			}

			/* --------------------get capacity-------------------- */
			size_type		capacity() const				{ return _capacity; }

			/* --------------------get is empty-------------------- */
			bool			empty() const					{ return _size == 0; }

			/* --------------------get is allocator-------------------- */
			allocator_type	get_allocator() const			{ return _alloc; }

			/* --------------------reserve-------------------- */
			void			reserve (size_type n)
			{
				if (n > max_size())
					throw std::length_error("vector::reserve");
				if (n > _capacity)
					reallocateVec(n);
			}

		public:
			/* *******************ACCESS ELEMENTS******************* */
			/* --------------------access-------------------- */
			reference operator[] (size_type n)				{ return _vector[n]; }

			/* --------------------const access-------------------- */
			const_reference operator[] (size_type n) const	{ return _vector[n]; }

			/* --------------------at-------------------- */
			//same as [] but with overflow protection
			reference at(size_type n)
			{
				if (n >= _size)
					throw std::out_of_range("vector");
				return _vector[n];
			}

			/* --------------------const at-------------------- */
			//same as [] const but with overflow protection
			const_reference at(size_type n) const
			{
				if (!(n < _size))
					throw std::out_of_range("vector");
				return _vector[n];
			}

			/* --------------------front & back-------------------- */
			reference front()								{ return _vector[0]; }
			reference back()								{ return _vector[_size - 1]; }
			const_reference front() const					{ return _vector[0]; }
			const_reference back() const					{ return _vector[_size - 1]; }

			/* *******************MODIFIERS******************* */
			/* --------------------range assign-------------------- */
			//Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.
			template <class InputIterator>
			void assign (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0)
			{
				clear();
				InputIterator tmp = first;
				size_type n = 0;
				while (tmp++ != last)
					n++;
				_alloc.deallocate(_vector, _capacity);
				_capacity = n;
				_vector = _alloc.allocate(n);
				size_type i = 0;
				for (; first != last; first++)
				{
					_alloc.construct(&_vector[i], *first);
					 i++;
				}
				_size = i;
			}
			/* --------------------fill assign-------------------- */
			void assign (size_type n, const value_type& val)
			{
				clear();
				_alloc.deallocate(_vector, _capacity);
				_capacity = n;
				_vector = _alloc.allocate(_capacity);
				for (size_type i = 0; i < n; ++i)
					_alloc.construct(&_vector[i], val);
				_size = n;
			}

			void push_back (const value_type& val)
			{
				if (_size + 1 > _capacity)
					reallocateVec(!_capacity ? 1 : _capacity * 2); //if capacity is reached, multiply it by 2
				_alloc.construct(&_vector[_size++], val);
			}

			void pop_back()
			{
				if (_size)
				{
					_alloc.destroy(&_vector[_size - 1]);
					_size--;
				}
			}

			/* --------------------val insert-------------------- */
			iterator insert (iterator position, const value_type& val)
			{
				difference_type index = position - begin();
				insert(position, 1, val);
				return iterator(&_vector[index]);
			}

			/* --------------------range insert-------------------- */
			
			void insert (iterator position, size_type n, const value_type& val)
			{
				if (!n)
					return;
				difference_type index = position - begin();
				if (_size + n > _capacity)
					reallocateVec(_capacity + n);
				iterator newPosition(&_vector[index]);
				if (newPosition != end())
					moveElementsToTheRight(newPosition, n);
				for (size_type i = 0; i < n; ++i)
					_alloc.construct(&(*newPosition++), val);
				_size += n;
			}

			/* --------------------iterator range insert-------------------- */
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last, 
						typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0)
			{
				size_type n = 0;
				InputIterator tmp(first);
				while (tmp++ != last)
					++n;
				difference_type index = position - begin();
				if (_size + n > _capacity)
					reallocateVec(_capacity + n);
				iterator newPosition(&_vector[index]);
				if (newPosition != end())
					moveElementsToTheRight(newPosition, n);
				for (size_type i = 0; i < n; ++i)
					_alloc.construct(&(*newPosition++), *first++);
				_size += n;
			}

			/* --------------------erase one element-------------------- */
			iterator erase (iterator position)
			{
				return erase(position, position + 1);
			}

			/* --------------------erase range-------------------- */
			iterator erase (iterator first, iterator last)
			{
				if (first == end() || first == last)
					return first;
				difference_type index = first - begin();
				if (last < end())
				{
					moveElementsToTheLeft(first, last);
					_size -= static_cast<size_type>(last - first);
				}
				else
				{
					size_type newSize = _size - static_cast<size_type>(last - first);
					while (_size != newSize)
						pop_back();
				}
				
				return iterator(&_vector[index]);
			}

			/* --------------------swap vectors content-------------------- */
			void swap (vector& x)
			{
				swap(_alloc, x._alloc);
				swap(_vector, x._vector);
				swap(_size, x._size);
				swap(_capacity, x._capacity);
			}

			void clear()
			{
				while (_size)
					pop_back();
			}

			/* *******************NON MEMBER FUNCTIONS OVERLOAD******************* */
			friend bool operator==(const vector& lhs, const vector& rhs)
			{
				if (lhs.size() != rhs.size())
					return false;
				const_iterator lit;
				const_iterator rit;
				lit = lhs.begin();
				rit = rhs.begin();
				while (lit != lhs.end())
				{
					if (*lit != *rit)
						return false;
					++lit;
					++rit;
				}
				return true;
			}

			friend bool operator<(const vector& lhs, const vector& rhs)		{return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());}
			friend bool operator!=(const vector& lhs, const vector& rhs)	{ return !(lhs == rhs); }
			friend bool operator>(const vector& lhs, const vector& rhs)		{ return rhs < lhs; }
			friend bool operator<=(const vector& lhs, const vector& rhs)	{ return !(rhs < lhs); }
			friend bool operator>=(const vector& lhs, const vector& rhs)	{ return !(lhs < rhs); }

		private:
			/* *******************NON MEMBER FUNCTIONS OVERLOAD******************* */
			void reallocateVec(size_type newCapacity)
			{
				pointer tmp = _alloc.allocate(newCapacity);
				for (size_type i = 0; i < _size; ++i)
					_alloc.construct(&tmp[i], _vector[i]);
				this->~vector();
				_capacity = newCapacity;
				_vector = tmp;
			}

			template <typename U>
			void swap(U& a, U&b)
			{
				U tmp = a;
				a = b;
				b = tmp;
			}

			void moveElementsToTheRight(iterator pos, size_type lenMov)
			{
				for (ft::pair<iterator, iterator> it(end() - 1, end()); it.second != pos; --it.first, --it.second)
				{
					_alloc.construct(&(*(it.first + lenMov)), *it.first);
					_alloc.destroy(&(*it.first));
				}
			}

			void moveElementsToTheLeft(iterator first, iterator last)
			{
				for (; first != end(); ++first, ++last)
				{
					_alloc.destroy(&(*first));
					if (last < end())
						_alloc.construct(&(*(first)), *last);
				}
			}

		private:
			/* *******************VARIABLES******************* */
			Alloc				_alloc; //copy of allocator
			pointer				_vector; //pointer on first element
			size_type			_size; //actual size
			size_type			_capacity; //capacity, max size available
	};
}
#endif