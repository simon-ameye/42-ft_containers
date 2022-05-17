/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:07:01 by sameye            #+#    #+#             */
/*   Updated: 2022/05/17 11:31:52 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#define ADD 1
#define SUBSTRACT -1

#include "utils.hpp"
#include "reverse_iterator.hpp"

namespace ft
{
	template<typename T, bool Const = false>
	class vector_iterator
	{
		public:
			/* *******************ALIASES******************* */
			typedef long int													difference_type;
			typedef T															value_type;
			typedef size_t														size_type;
			typedef T*															elemPtr;
			typedef typename FalseXTrueY<Const, T&, const T&>::type				reference;
			typedef typename FalseXTrueY<Const, T*, const T*>::type				pointer;
			typedef ft::random_access_iterator_tag								iterator_category;


			/* *******************CONSTRUCTORS & DESTRUCTORS******************* */
		public:
			/* --------------------default constructor-------------------- */
			vector_iterator(elemPtr val = 0) : _val(val) {}

			/* --------------------copy constructor-------------------- */

			vector_iterator(const vector_iterator< T, false >& copy)
			{
				this->_val = copy.getElemPtr();
			}

			vector_iterator(const vector_iterator< ft::enable_if< Const, T >, true >& copy)
			{
				this->_val = copy.getElemPtr();
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
			elemPtr getElemPtr() const
			{
				return _val;
			}

			vector_iterator base(void) //NOT SURE
			{
				return (_val);
			}

			/* *******************OPPERATOR OVERLOAD******************* */
		public:
			reference operator*() const			{ return (*_val); }
			pointer operator->() const			{ return (_val); }
			vector_iterator& operator++()		{ ++_val; return (*this); }
			vector_iterator& operator--()		{ --_val; return (*this); }

			reference operator[](int nb) const
			{
				vector_iterator tmp(*this);
				tmp += nb;
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

			bool operator==(const vector_iterator<T, true> & it) const	{ return (it.getElemPtr() == this->_val); }
			bool operator!=(const vector_iterator<T, true> & it) const	{ return (it.getElemPtr() != this->_val); }
			bool operator< (const vector_iterator<T, true> & it) const	{ return (it.getElemPtr() >  this->_val); }
			bool operator> (const vector_iterator<T, true> & it) const	{ return (it.getElemPtr() <  this->_val); }
			bool operator<=(const vector_iterator<T, true> & it) const	{ return (it.getElemPtr() >= this->_val); }
			bool operator>=(const vector_iterator<T, true> & it) const	{ return (it.getElemPtr() <= this->_val); }

			vector_iterator& operator+=(int nb)
			{
				_val += nb;
				return (*this);
			}

			vector_iterator operator+(int nb) const
			{
				vector_iterator it(*this);
				
				it._val += nb;
				return (it);
			}

			vector_iterator& operator-=(int nb)
			{
				_val -= nb;
				return (*this);
			}

			vector_iterator operator-(int nb) const
			{
				vector_iterator it(*this);
				
				it._val -= nb;
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

			/* *******************ATTRIBUTES******************* */
		protected:
			elemPtr _val;
	};

}

#endif