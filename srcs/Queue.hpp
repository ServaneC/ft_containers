/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 15:34:41 by schene            #+#    #+#             */
/*   Updated: 2021/02/22 18:52:18 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_HPP
# define QUEUE_HPP

# include "List.hpp"

namespace ft
{
	template <class T, class Container = ft::list<T> >
	class queue
	{
		public:
			typedef T			value_type;
			typedef Container	container_type;
			typedef size_t		size_type;
		
		private:
			container_type _container;
		
		public:
			// CONSTRUCTOR
			explicit queue (const container_type& ctnr = container_type()) : _container(ctnr) {}

			// OTHER FUNCTIONS
			bool empty() const
			{
				return this->_container.empty();
			}

			size_type size() const
			{
				return this->_container.size();
			}

			value_type& front()
			{
				return this->_container.front();
			}

			const value_type& front() const
			{
				return this->_container.front();
			}

			value_type& back()
			{
				return this->_container.back();
			}

			const value_type& back() const
			{
				return this->_container.back();
			}

			void push (const value_type& val)
			{
				this->_container.push_back(val);
			}

			void pop()
			{
				this->_container.pop_front();
			}

			//RELATIONAL OPERATOR
			friend bool operator== (const queue<value_type, container_type>& lhs,
			const queue<value_type, container_type>& rhs)
			{
				return lhs._container == rhs._container;
			}

			friend bool operator!= (const queue<value_type, container_type>& lhs,
			const queue<value_type, container_type>& rhs)
			{
				return (lhs._container != rhs._container);
			}

			friend bool operator<  (const queue<value_type, container_type>& lhs,
			const queue<value_type, container_type>& rhs)
			{
				return (lhs._container < rhs._container);
			}

			friend bool operator<= (const queue<value_type, container_type>& lhs,
			const queue<value_type, container_type>& rhs)
			{
				return (lhs._container <= rhs._container);
			}

			friend bool operator>  (const queue<value_type, container_type>& lhs,
			const queue<value_type, container_type>& rhs)
			{
				return (lhs._container > rhs._container);
			}

			friend bool operator>= (const queue<value_type, container_type>& lhs,
			const queue<value_type, container_type>& rhs)
			{
				return (lhs._container >= rhs._container);
			}
	};
}

#endif