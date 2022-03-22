/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:07:01 by sameye            #+#    #+#             */
/*   Updated: 2022/03/21 18:32:20 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#define ADD 1
#define SUBSTRACT 0

namespace ft
{
	template<typename T, bool B>
	class vector_iterator
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
//            typedef typename chooseConst<B, T&, const T&>::type     reference;
//            typedef typename chooseConst<B, T*, const T*>::type     pointer;

			/* *******************ATTRIBUTES******************* */
		private:
			elemPtr _val;

			/* *******************CONSTRUCTORS & DESTRUCTORS******************* */
		public:
			vector_iterator(elemPtr val = 0) :
			_val(val)
			{}

			vector_iterator(const vector_iterator<T, false>& copy)
			{
				_val = copy.getElemPtr();
			}

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
				movePtr(this->_val, nb, ADD);
				return (*this);
			}

			vector_iterator operator+(int nb) const
			{
				vector_iterator it(*this);
				
				movePtr(it._val, nb, ADD);
				return (it);
			}

			vector_iterator& operator-=(int nb)
			{
				movePtr(this->_val, nb, SUBSTRACT);
				return (*this);
			}

			vector_iterator operator-(int nb) const
			{
				vector_iterator it(*this);
				
				movePtr(it._val, nb, SUBSTRACT);
				return (it);
			}

			reference operator[](int nb) const
			{
				value_type* tmp;
				tmp = this->_val;

				movePtr(tmp, nb, ADD);
				return (*tmp);
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
		private :
			void movePtr(elemPtr& val, long nb, bool sign) const
			{
				int mov;

				if (sign == ADD)
					mov = nb > 0 ? mov = 1: mov = -1;
				else
					mov = nb > 0 ? mov = -1: mov = 1;

				if (nb < 0)
					nb *= -1;
				for (; nb > 0; --nb)
					val += mov;
			}
	};
}

#endif