/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 11:04:11 by schene            #+#    #+#             */
/*   Updated: 2021/02/23 12:32:17 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "List.hpp"

namespace ft
{
	template <class T, class Container = ft::list<T> >
	class stack
	{
		public:
			typedef T			value_type;
			typedef Container	container_type;
			typedef size_t		size_type;
		
		private:
			container_type _container;

		public:
			// CONSTRUCTOR
			explicit	stack(const container_type& ctnr = container_type()) : _container(ctnr) {}

			// OTHER FUNCTIONS
			bool empty() const
			{
				return this->_container.empty();
			}

			size_type size() const
			{
				return this->_container.size();
			}

			value_type& top()
			{
				return this->_container.back();
			}

			const value_type& top() const
			{
				return this->_container.back();
			}

			void push (const value_type& val)
			{
				this->_container.push_back(val);
			}

			void pop()
			{
				this->_container.pop_back();
			}

			//RELATIONAL OPERATOR
			friend bool operator== (const stack<value_type, container_type>& lhs,
			const stack<value_type, container_type>& rhs)
			{
				return lhs._container == rhs._container;
			}

			friend bool operator!= (const stack<value_type, container_type>& lhs,
			const stack<value_type, container_type>& rhs)
			{
				return (lhs._container != rhs._container);
			}

			friend bool operator<  (const stack<value_type, container_type>& lhs,
			const stack<value_type, container_type>& rhs)
			{
				return (lhs._container < rhs._container);
			}

			friend bool operator<= (const stack<value_type, container_type>& lhs,
			const stack<value_type, container_type>& rhs)
			{
				return (lhs._container <= rhs._container);
			}

			friend bool operator>  (const stack<value_type, container_type>& lhs,
			const stack<value_type, container_type>& rhs)
			{
				return (lhs._container > rhs._container);
			}

			friend bool operator>= (const stack<value_type, container_type>& lhs,
			const stack<value_type, container_type>& rhs)
			{
				return (lhs._container >= rhs._container);
			}
	};
}

#endif