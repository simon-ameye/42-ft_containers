/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 16:55:07 by sameye            #+#    #+#             */
/*   Updated: 2022/05/14 19:34:56 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "utils.hpp"

namespace ft
{
	template <class Iterator>
	class reverse_iterator
	{
		public:

			typedef Iterator														iterator_type;
			typedef typename ft::iterator_traits<Iterator>::iterator_category		iterator_category;
			typedef typename ft::iterator_traits<Iterator>::value_type				value_type;
			typedef typename ft::iterator_traits<Iterator>::difference_type			difference_type;
			typedef typename ft::iterator_traits<Iterator>::pointer					pointer;
			typedef typename ft::iterator_traits<Iterator>::reference				reference;

			reverse_iterator() : _iterator() {}

			explicit reverse_iterator (iterator_type it) : _iterator(it) {}

			template <class Iter>
			reverse_iterator (const reverse_iterator<Iter>& rev_it) : _iterator(rev_it.base()) {}

			virtual ~reverse_iterator() {}

			iterator_type base() const
			{ return (_iterator); }

			reference operator*() const
			{
				iterator_type tmp = _iterator;
				return (*(--tmp));
			}

			reverse_iterator operator+ (difference_type n) const
			{
				return (reverse_iterator(_iterator - n));
			}

			reverse_iterator& operator++()
			{
				--_iterator;
				return (*this);
			}

			reverse_iterator operator++(int)
			{
				reverse_iterator tmp = *this;
				++(*this);
				return (tmp);
			}

			reverse_iterator& operator+= (difference_type n)
			{
				_iterator -= n;
				return (*this);
			}

			reverse_iterator operator- (difference_type n) const { return (reverse_iterator(_iterator + n)); }

			reverse_iterator& operator--()
			{
				++_iterator;
				return (*this);
			}

			reverse_iterator operator--(int)
			{
				reverse_iterator tmp = *this;
				--(*this);
				return (tmp);
			}

			reverse_iterator& operator-= (difference_type n)
			{
				_iterator += n;
				return (*this);
			}

			pointer operator->() const { return &(operator*()); }

			reference operator[] (difference_type n) const { return (this->base()[-n - 1]); }

		private:
			iterator_type	_iterator;
	};

	template <class Iterator>
	bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class Iterator_L, class Iterator_R>
	bool operator== (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class Iterator>
	bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class Iterator_L, class Iterator_R>
	bool operator!= (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class Iterator>
	bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class Iterator_L, class Iterator_R>
	bool operator< (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class Iterator>
	bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator_L, class Iterator_R>
	bool operator<= (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator>
	bool operator> (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class Iterator_L, class Iterator_R>
	bool operator> (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class Iterator>
	bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <class Iterator_L, class Iterator_R>
	bool operator>= (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <class Iterator>
	reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
	{
		return (rev_it + n);
	}

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base().getElemPtr() - rhs.base().getElemPtr());
	}

	template <class Iterator_L, class Iterator_R>
	typename reverse_iterator<Iterator_L>::difference_type operator- (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs)
	{
		return (rhs.base().getElemPtr() - lhs.base().getElemPtr());
	}
}
#endif