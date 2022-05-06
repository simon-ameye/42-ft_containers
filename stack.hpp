/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:29:51 by sameye            #+#    #+#             */
/*   Updated: 2022/05/06 19:50:55 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "utils.hpp"
#include "vector_reverse_iterator.hpp"
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
		explicit stack (const Container& container = Container()) : _container(container) {}

		~stack() {}

		/* *******************MEMBER FUNCTIONS******************* */
		public :
		bool empty() const { return (this->_container.empty()); }
		size_type size() const { return (this->_container.size()); }
		value_type& top() { return (this->_container.back()); }
		const value_type& top() const { return (this->_container.back()); }
		void push (const value_type& val) { this->_container.push_back(val); }
		void pop() { this->_container.pop_back(); }

		/* *******************VARIABLES******************* */
		private:
		Container _container;
	};

	/* *******************NON-MEMBER FUNCTIONS OVERLOAD******************* */
	template <class T, class Container>
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
	template <class T, class Container>
	bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
	template <class T, class Container>
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
}
#endif