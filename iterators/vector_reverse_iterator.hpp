/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_reverse_iterator.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 19:30:26 by sameye            #+#    #+#             */
/*   Updated: 2022/05/06 17:56:10 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_REVERSE_ITERATOR_HPP
#define VECTOR_REVERSE_ITERATOR_HPP

#define ADD 1
#define SUBSTRACT -1

#include "vector_iterator.hpp"

namespace ft
{
	template<typename T, bool Const>
	class vector_reverse_iterator : public vector_iterator<T, Const>
	{
		public:
			/* *******************ALIASES******************* */
			typedef long int										difference_type;
			typedef T												value_type;
			typedef size_t											size_type;
			typedef T*												elemPtr;
			typedef T&												reference;
				typedef T*												pointer;
			typedef std::random_access_iterator_tag					iterator_category;

			/* *******************ATTRIBUTES******************* */

			/* *******************CONSTRUCTORS & DESTRUCTORS******************* */
		public:
			/* --------------------default constructor-------------------- */
			vector_reverse_iterator(elemPtr val = 0)
			{
				this->_val = val;
			}

			/* --------------------copy constructor-------------------- */
			vector_reverse_iterator(const vector_iterator< T, true >& copy)
			{
				this->_val = copy.getElemPtr();
			}

			vector_reverse_iterator(const vector_iterator< T, false >& copy)
			{
				this->_val = copy.getElemPtr();
			}

			/* --------------------destructor-------------------- */
			~vector_reverse_iterator() {}

			/* *******************OPPERATOR OVERLOAD******************* */
		public:
			vector_reverse_iterator& operator++()		{ --this->_val; return (*this); }
			vector_reverse_iterator& operator--()		{ ++this->_val; return (*this); }

			reference operator[](int nb) const
			{
				vector_reverse_iterator tmp(*this);
				this->move(nb, SUBSTRACT, tmp);
				return (*tmp);
			}

			vector_reverse_iterator operator++(int)
			{
				vector_reverse_iterator res(*this);
				++(*this);
				return (res);
			}

			vector_reverse_iterator operator--(int)
			{
				vector_reverse_iterator res(*this);
				--(*this);
				return (res);
			}

			bool operator<(const vector_reverse_iterator& it) const		{ return (it._val < this->_val); }
			bool operator>(const vector_reverse_iterator& it) const		{ return (it._val > this->_val); }
			bool operator<=(const vector_reverse_iterator& it) const	{ return (it._val <= this->_val); }
			bool operator>=(const vector_reverse_iterator& it) const	{ return (it._val >= this->_val); }

			vector_reverse_iterator& operator+=(int nb)
			{
				this->move(nb, SUBSTRACT, *this);
				return (*this);
			}

			vector_reverse_iterator operator+(int nb) const
			{
				vector_reverse_iterator it(*this);
				
				this->move(nb, SUBSTRACT, it);
				return (it);
			}

			vector_reverse_iterator& operator-=(int nb)
			{
				this->move(nb, ADD, *this);
				return (*this);
			}

			vector_reverse_iterator operator-(int nb) const
			{
				vector_reverse_iterator it(*this);
				
				this->move(nb, ADD, it);
				return (it);
			}


			difference_type operator-(vector_reverse_iterator it) const
			{
				return (it._val - this->_val);
			}

			/* *******************NON MEMBER OPPERATOR OVERLOAD******************* */
			friend vector_reverse_iterator operator+(int nb, const vector_reverse_iterator& it)
			{
				vector_reverse_iterator newIt(it);
				return (newIt += nb);
			}

			friend vector_reverse_iterator operator-(int nb, const vector_reverse_iterator& it)
			{
				vector_reverse_iterator newIt(it);
				return (newIt -= nb);
			}
	};
}

#endif