/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 17:05:19 by sameye            #+#    #+#             */
/*   Updated: 2022/03/22 11:51:00 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "../utils/utils.hpp"
#include "../iterators/vector_reverse_iterator.hpp"
#include "../iterators/vector_iterator.hpp"
#include <cmath>

namespace ft
{
	template < class T, class Alloc = std::allocator <T> >
	class vector
	{
		public :
			/* *******************TYPES DEFINITION******************* */
			typedef T											value_type;
			typedef Alloc										allocator_type;
			typedef long int									difference_type;
			typedef size_t										size_type;

			typedef T&											reference;
			typedef const T&									const_reference;
			typedef T*											pointer;
			typedef const T*									const_pointer;
			
			typedef typename ft::vector_iterator<T, false>		iterator;
			typedef typename ft::vector_iterator<T, true>		const_iterator;

			typedef typename ft::vector_reverse_iterator<T, false>	reverse_iterator;
			typedef typename ft::vector_reverse_iterator<T, true>	const_reverse_iterator;

			/* *******************CONSTRUCTORS******************* */
			/* --------------------default constructor-------------------- */
			explicit
			vector (const allocator_type& alloc = allocator_type()) :
			_alloc(alloc), _size(0), _capacity(0)
			{
				_vector = _alloc.allocate(_capacity);
				//std::cout << "Vector default constructor call" << std::endl;
			}

			/* --------------------fill constructor-------------------- */
			explicit
			vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) :
			_alloc(alloc), _size(n), _capacity(n)
			{
				//std::cout << "Vector constructor call with n=" << n << " val=" << val << std::endl;
				_vector = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; ++i)
					_alloc.construct(&_vector[i], val);
			}

			/* --------------------range constructor-------------------- */
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
			vector(const vector& x) :
					_alloc(x._alloc), _size(x._size), _capacity(x._capacity)
			{
				_vector = _alloc.allocate(_capacity);
				
				for (ft::pair<int, const_iterator> i(0, x.begin());
						i.second != x.end(); ++i.first, ++i.second)
					_alloc.construct(&_vector[i.first], *i.second);
			}

		private:
			/* *******************VARIABLES******************* */
			Alloc				_alloc;
			pointer				_vector;
			size_type			_size;
			size_type			_capacity;

		public:
			/* *******************ITERATORS******************* */
			iterator				begin()					{ return iterator(_vector); }
			const_iterator			begin() const			{ return const_iterator(_vector); }
			iterator				end()					{ return iterator(_vector + _size); }
			const_iterator			end() const				{ return const_iterator(_vector + _size); }
			reverse_iterator		rbegin()				{ return reverse_iterator(_vector + _size - 1); }
			const_reverse_iterator	rbegin() const			{ return const_reverse_iterator(_vector + _size - 1); }
			reverse_iterator		rend()					{ return reverse_iterator(_vector - 1); }
			const_reverse_iterator	rend() const			{ return const_reverse_iterator(_vector - 1); }

		public:
			/* *******************CAPACITY******************* */
			/* --------------------get size-------------------- */
			size_type		size() const					{ return _size; }

			/* --------------------get max size-------------------- */
			size_type		max_size() const				{ return static_cast<size_type>(pow(2.0, 64.0) / static_cast<double>(sizeof(value_type)) - 1.0); }

			/* --------------------resize-------------------- */
			void resize (size_type n, value_type val = value_type())
			{
				if (n > _capacity)
					reallocateVec(n);
				while (n > _size)
					push_back(val);
				while (n < _size)
					pop_back();
			}

			/* --------------------get capacity-------------------- */
			size_type		capacity() const				{ return _capacity; }

			/* --------------------get is empty-------------------- */
			bool			empty() const					{ return _size == 0; }

			/* --------------------reserve-------------------- */
			void			reserve (size_type n)
			{
				if (n > max_size())
					throw std::length_error("vector");
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
			reference at(size_type n)
			{
				if (!(n < _size))
					throw std::out_of_range("vector");
				return _vector[n];
			}

			/* --------------------const at-------------------- */
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
			template <class InputIterator>
			void assign (InputIterator first, InputIterator last,
						typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0)
			{
				clear();

				// Reallocating only if new capacity exceeds previous
				size_type n = static_cast<size_type>(last - first);
				if (n > _capacity)
				{
					_alloc.deallocate(_vector, _capacity);
					_vector = _alloc.allocate(n);
				}
				
				size_type i = 0;
				for (; first != last; ++i, ++first)
					_alloc.construct(&_vector[i], *first);
				_size = i;
			}

			void assign (size_type n, const value_type& val)
			{
				clear();

				// Reallocating only if new capacity exceeds previous
				if (n > _capacity)
				{
					_alloc.deallocate(_vector, _capacity);
					_vector = _alloc.allocate(n);
				}
				
				for (size_type i = 0; i < n; ++i)
					_alloc.construct(&_vector[i], val);
				_size = n;
			}

			void push_back (const value_type& val)
			{
				if (_size + 1 > _capacity)
					reallocateVec(!_capacity ? 1 : _capacity * 2);
				_alloc.construct(&_vector[_size++], val);
			}

			void pop_back()
			{
				if (_size)
					_alloc.destroy(&_vector[_size-- - 1]);
			}

			iterator insert (iterator position, const value_type& val)
			{
				// In case of a realloc, position will be invalited because _vector
				// points to another allocated area so we need to save the index array
				// where position iterator is pointing to create a new one after the reallocation
				difference_type index = position - begin();
				
				insert(position, 1, val);
				return iterator(&_vector[index]);
			}

			void insert (iterator position, size_type n, const value_type& val)
			{
				// In case of a realloc, position will be invalited because _vector
				// points to another allocated area so we need to save the index array
				// where position iterator is pointing to create a new one after the reallocation
				difference_type index = position - begin();
				
				if (_size + n > _capacity)
					reallocateVec(_capacity + n);
				
				// Creating a new iterator pointing to the correct allocated are (case a realloc occured previously)
				iterator newPosition(&_vector[index]);
				
				// Moving at newPosition + n all elements after newPosition
				if (newPosition != end())
					moveElementsToTheRight(newPosition, n);
				
				// Constructing n new elements from val
				for (size_type i = 0; i < n; ++i)
					_alloc.construct(&(*newPosition++), val);
				_size += n;
			}

			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last, 
						typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0)
			{
				// Counting number of elements to add
				size_type n = 0;
				InputIterator tmp(first);
				while (tmp++ != last)
					++n;
				
				// In case of a realloc, position will be invalited because _vector
				// points to another allocated area so we need to save the index array
				// where position iterator is pointing to create a new one after the reallocation
				difference_type index = position - begin();
				
				if (_size + n > _capacity)
					reallocateVec(_capacity + n);

				// Creating a new iterator pointing to the correct allocated are (case a realloc occured previously)
				iterator newPosition(&_vector[index]);
				
				// Moving at newPosition + n all elements after newPosition
				if (newPosition != end())
					moveElementsToTheRight(newPosition, n);

				// Constructing n new elements from the iterator's range
				for (size_type i = 0; i < n; ++i)
					_alloc.construct(&(*newPosition++), *first++);
				_size += n;
			}

			iterator erase (iterator position)
			{
				return erase(position, position + 1);
			}

			iterator erase (iterator first, iterator last)
			{
				if (first == end() || first == last)
					return first;
				
				// In case of a realloc, iterators will be invalited because _vector
				// points to another allocated area so we need to save the index array
				// where first is pointing to create a new iterator after the reallocation
				difference_type index = first - begin();
				
				// If there is elements after the iterators range, we need to move them at first position
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


			/* ----------------------------------------------------------------------------------------- */
			/* ---------------------- NON-MEMBER FUNCTION OVERLOADS ---------------------- */

			friend bool operator==(const vector& lhs, const vector& rhs)
			{
				if (lhs.size() != rhs.size())
					return false;

				for (ft::pair<const_iterator, const_iterator> it(lhs.begin(), rhs.begin());
						it.first != lhs.end(); ++it.first, ++it.second)
					if (*(it.first) != *(it.second))
						return false;
				return true;
			}

			friend bool operator!=(const vector& lhs, const vector& rhs)    { return !(lhs == rhs); }

			friend bool operator<(const vector& lhs, const vector& rhs)
			{
				for (ft::pair<const_iterator, const_iterator> it(lhs.begin(), rhs.begin());
						it.first != lhs.end() && it.second != rhs.end(); ++it.first, ++it.second)
					if (*(it.first) < *(it.second))
						return true;
				return (lhs.size() < rhs.size());
			}

			friend bool operator>(const vector& lhs, const vector& rhs)     { return rhs < lhs; }

			friend bool operator<=(const vector& lhs, const vector& rhs)    { return !(rhs < lhs); }

			friend bool operator>=(const vector& lhs, const vector& rhs)    { return !(lhs < rhs); }

			friend void swap (vector& x, vector& y)                         { x.swap(y); }
			
			
			/* ----------------------------------------------------------------------------------------- */
			/* ------------------------- PRIVATE MEMBER FUNCTIONS ------------------------ */

		private:

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
				// Starting from the end, until it meets pos iterator
				for (ft::pair<iterator, iterator> it(end() - 1, end());
					it.second != pos; --it.first, --it.second)
				{
					_alloc.construct(&(*(it.first + lenMov)), *it.first);
					_alloc.destroy(&(*it.first));
				}
			}

			void moveElementsToTheLeft(iterator first, iterator last)
			{
				for (; first != end(); ++first, ++last)
				{
					// Destructing the previous element to replace it by a new one.
					// First will destroy all the element until the end.
					_alloc.destroy(&(*first));
					
					// Moving a new element to the left at first position, only if there is
					// still element to move
					if (last < end())
						_alloc.construct(&(*(first)), *last);
				}
			}
























	};
}

#endif