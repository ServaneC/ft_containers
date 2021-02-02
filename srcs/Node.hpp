/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 15:39:20 by schene            #+#    #+#             */
/*   Updated: 2021/02/02 11:30:07 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
# define NODE_HPP

# include <iostream>
# include <cstdlib>

template <class T>
class node
{
	private:
		T			_data;
		node<T>		*_prev;
		node<T>		*_next;

	public:
		node(void) : _prev(NULL), _next(NULL) { }
		// node(T const &value) : _data(value), _prev(NULL), _next(NULL) { }
		// node(node<T> *prev, T const &value, node<T> *next = NULL) : data(value), prev(prev), next(next) { }
		node(const node<T> &other)
		{
			(*this) = other;
		}

		~node(void) { }

		node&		operator=(const node& elem)
		{
			this->_data = elem.getData();
			this->_prev = elem.getPrev();
			this->_next = elem.getNext();
		}
		
		T&			getData()
		{
			return this->_data;
		}
		const T&	getData() const
		{
			return this->_data;
		}

		node	*&getNext(void)
		{
			return (this->_next);
		}

		node	*&getPrev(void)
		{
			return (this->_prev);
		}

		node	*getNext(void) const
		{
			return (this->_next);
		}

		node	*getPrev(void) const
		{
			return (this->_prev);
		}
	
};

# endif