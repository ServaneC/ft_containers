/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 15:39:20 by schene            #+#    #+#             */
/*   Updated: 2021/01/26 13:14:31 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
# define NODE_HPP

# include <iostream>
# include <cstdlib>

template <class T>
class node
{
	public:
		T			data;
		node<T>		*prev;
		node<T>		*next;

	public:
		node(void) : prev(NULL), next(NULL) { }
		node(T const &value) : data(value), prev(NULL), next(NULL) { }
		node(node<T> *prev, T const &value, node<T> *next = NULL) : data(value), prev(prev), next(next) { }
		node(const node<T> &other)
		{
			(*this) = other;
		}

		~node(void) { }

		node&		operator=(const node& elem)
		{
			this->data = elem.getData();
			this->prev = elem.prev;
			this->next = elem.next;
		}
		
		T&			getData()
		{
			return this->data;
		}
		const T&	getData() const
		{
			return this->data;
		}
};

# endif