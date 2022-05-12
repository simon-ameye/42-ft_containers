/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:07:01 by sameye            #+#    #+#             */
/*   Updated: 2022/05/12 14:07:42 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#define ADD 1
#define SUBSTRACT -1

#include "vector_reverse_iterator.hpp"

namespace ft
{
	template<typename T, bool Const>
	class vector_iterator
	{
		public:
			/* *******************ALIASES******************* */
			typedef long int										difference_type;
			typedef T												value_type;
			typedef size_t											size_type;
			typedef T*												elemPtr;
			typedef typename FalseXTrueY<Const, T&, const T&>::type				reference;
			typedef typename FalseXTrueY<Const, T*, const T*>::type				pointer;
			typedef std::random_access_iterator_tag					iterator_category;

			/* *******************ATTRIBUTES******************* */
		protected:
			elemPtr _val;

			/* *******************CONSTRUCTORS & DESTRUCTORS******************* */
		public:
			/* --------------------default constructor-------------------- */
			vector_iterator(elemPtr val = 0) : _val(val) {}

			/* --------------------copy constructor-------------------- */
			vector_iterator(const vector_iterator< T, true>& copy)
			{
				_val = copy.getElemPtr();
			}

			vector_iterator(const vector_iterator< T, false>& copy)
			{
				_val = copy.getElemPtr();
			}

			/* --------------------destructor-------------------- */
			~vector_iterator() {}

			vector_iterator& operator=(const vector_iterator& assign)
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
			reference operator*() const			{ return (*_val); }
			pointer operator->() const			{ return (_val); }
			vector_iterator& operator++()		{ ++_val; return (*this); }
			vector_iterator& operator--()		{ --_val; return (*this); }

			reference operator[](int nb) const
			{
				vector_iterator tmp(*this);
				move(nb, ADD, tmp);
				return (*tmp);
			}

			vector_iterator operator++(int)
			{
				vector_iterator res(*this);
				++(*this);
				return (res);
			}

			vector_iterator operator--(int)
			{
				vector_iterator res(*this);
				--(*this);
				return (res);
			}

			bool operator==(const vector_iterator& it) const	{ return (it._val == _val); }
			bool operator!=(const vector_iterator& it) const	{ return (it._val != _val); }
			bool operator<(const vector_iterator& it) const		{ return (it._val > this->_val); }
			bool operator>(const vector_iterator& it) const		{ return (it._val < this->_val); }
			bool operator<=(const vector_iterator& it) const	{ return (it._val >= this->_val); }
			bool operator>=(const vector_iterator& it) const	{ return (it._val <= this->_val); }

			vector_iterator& operator+=(int nb)
			{
				move(nb, ADD, *this);
				return (*this);
			}

			vector_iterator operator+(int nb) const
			{
				vector_iterator it(*this);
				
				move(nb, ADD, it);
				return (it);
			}

			vector_iterator& operator-=(int nb)
			{
				move(nb, SUBSTRACT, *this);
				return (*this);
			}

			vector_iterator operator-(int nb) const
			{
				vector_iterator it(*this);
				
				move(nb, SUBSTRACT, it);
				return (it);
			}


			difference_type operator-(vector_iterator it) const
			{
				return (this->_val - it._val);
			}

			/* *******************NON MEMBER OPPERATOR OVERLOAD******************* */
			friend vector_iterator operator+(int nb, const vector_iterator& it)
			{
				vector_iterator newIt(it);
				return (newIt += nb);
			}

			friend vector_iterator operator-(int nb, const vector_iterator& it)
			{
				vector_iterator newIt(it);
				return (newIt -= nb);
			}

			/* *******************PRIVATE FUNCTIONS******************* */
		protected :
			/* --------------------useful function-------------------- */
			void move(long nb, int sign, vector_iterator &iterator) const
			{
				long mov = sign * nb;
				if (mov >= 0)
				{
					for (long i = 0; i < mov; i++)
						++iterator;
				}
				else
					for (long i = 0; i > mov; i--)
						--iterator;
			}
	};
}

#endif