/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:29:51 by sameye            #+#    #+#             */
/*   Updated: 2022/05/19 13:37:28 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "utils.hpp"
#include "vector_iterator.hpp"
#include "vector.hpp"

namespace ft
{
	template <class T, class Container = vector<T> >
	class stack
	{
		/* *******************MEMBER TYPES******************* */
		public :
		typedef T							value_type;
		typedef Container					container_type;
		typedef size_t						size_type;
		
		/* *******************CONSTRUCTOR******************* */
		public :
		explicit stack (const Container& container = Container()) : c(container) {}

		~stack() {}

		/* *******************MEMBER FUNCTIONS******************* */
		public :
		bool empty() const { return (this->c.empty()); }
		size_type size() const { return (this->c.size()); }
		value_type& top() { return (this->c.back()); }
		const value_type& top() const { return (this->c.back()); }
		void push (const value_type& val) { this->c.push_back(val); }
		void pop() { this->c.pop_back(); }

		/* *******************ALLOWING NON MEMBER FUNCTIONS TO ACCESS _CONTAINER******************* */
		template <class Tn, class ContainerN>
			friend bool operator== (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs);
		template <class Tn, class ContainerN>
			friend bool operator!= (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs);
		template <class Tn, class ContainerN>
			friend bool operator< (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs);
		template <class Tn, class ContainerN>
			friend bool operator<= (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs);
		template <class Tn, class ContainerN>
			friend bool operator> (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs);
		template <class Tn, class ContainerN>
			friend bool operator>= (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs);

		/* *******************VARIABLES******************* */
		protected:
		Container c; // name imposed in 42 example
	};

	/* *******************NON-MEMBER FUNCTIONS OVERLOAD******************* */
	template <class T, class Container>
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c == rhs.c);
	}
	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c != rhs.c);
	}
	template <class T, class Container>
	bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c < rhs.c);
	}
	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c <= rhs.c);
	}
	template <class T, class Container>
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c > rhs.c);
	}
	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c >= rhs.c);
	}
}
#endif