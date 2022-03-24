/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_reverse_iterator.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 19:30:26 by sameye            #+#    #+#             */
/*   Updated: 2022/03/24 15:16:20 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_REVERSE_ITERATOR_HPP
#define VECTOR_REVERSE_ITERATOR_HPP

#include "vector_iterator.hpp"

namespace ft
{
	template<typename T>
	class vector_reverse_iterator : public vector_iterator< T >
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
		private:
			elemPtr _val;

			/* *******************CONSTRUCTORS & DESTRUCTORS******************* */
		public:
			/* --------------------default constructor-------------------- */
			vector_reverse_iterator(elemPtr val = 0) : _val(val) {}

			/* --------------------copy constructor-------------------- */
			vector_reverse_iterator(const vector_reverse_iterator< T >& copy)
			{
				_val = copy.getElemPtr();
			}

			/* --------------------destructor-------------------- */
			~vector_reverse_iterator() {}

			vector_reverse_iterator& operator=(const vector_reverse_iterator& assign)
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
			reference operator[](int nb) const	{ return (_val[nb]); }
			vector_reverse_iterator& operator++()		{ ++_val; return (*this); }
			vector_reverse_iterator& operator--()		{ --_val; return (*this); }

			vector_reverse_iterator operator++(int)
			{
				vector_reverse_iterator res(*this);
				--(*this);
				return (res);
			}

			vector_reverse_iterator operator--(int)
			{
				vector_reverse_iterator res(*this);
				++(*this);
				return (res);
			}

			bool operator==(const vector_reverse_iterator& it) const	{ return (it._val == _val); }
			bool operator!=(const vector_reverse_iterator& it) const	{ return (it._val != _val); }
			bool operator<(const vector_reverse_iterator& it) const		{ return (it._val < this->_val); }
			bool operator>(const vector_reverse_iterator& it) const		{ return (it._val > this->_val); }
			bool operator<=(const vector_reverse_iterator& it) const	{ return (it._val <= this->_val); }
			bool operator>=(const vector_reverse_iterator& it) const	{ return (it._val >= this->_val); }

			vector_reverse_iterator& operator+=(int nb)
			{
				move(nb, SUBSTRACT);
				return (*this);
			}

			vector_reverse_iterator operator+(int nb) const
			{
				vector_reverse_iterator it(*this);
				
				move(nb, SUBSTRACT);
				return (it);
			}

			vector_reverse_iterator& operator-=(int nb)
			{
				move(nb, ADD);
				return (*this);
			}

			vector_reverse_iterator operator-(int nb) const
			{
				vector_reverse_iterator it(*this);
				
				move(nb, ADD);
				return (it);
			}


			difference_type operator-(vector_reverse_iterator it) const
			{
				return (- this->_val + it._val);
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

			/* *******************PRIVATE FUNCTIONS******************* */
		private :
			/* --------------------useful function-------------------- */
			void move(long nb, int sign)
			{
				long mov = sign * nb;
				if (mov >= 0)
				{
					for (long i = 0; i < mov; i++)
						++*this;
				}
				else
					for (long i = 0; i > mov; i--)
						--*this;
			}
	};
}

#endif
