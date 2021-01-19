/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 15:33:29 by schene            #+#    #+#             */
/*   Updated: 2021/01/18 16:00:33 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

namespace ft
{
	struct IteratorTrait {};

	template<typename It>
	class ReverseIterator: public It
	{
		public:
			using typename It::value_type;
		    using typename It::pointer;
		    using typename It::const_pointer;
		    using typename It::reference;
		    using typename It::const_reference;
		    using typename It::difference_type;

		public:
			ReverseIterator(): It() {}
			ReverseIterator(It const &it): It(it) {}
			ReverseIterator(ReverseIterator const &other): It(other.it) {}
			ReverseIterator &operator=(ReverseIterator const &other) 
			{
				this->it = other.it;
				return (*this);
			}

			reference operator*() 
			{
				It tmp(*this);
				return (*--tmp);
			}

			const_reference operator*() const 
			{
				It tmp(*this);
				return (*--tmp);
			}

			pointer operator->() {
				It tmp(*this);
				return (&*--tmp);
			}

			const_pointer operator->() const 
			{
				It tmp(*this);
				return (&*--tmp);
			}

			ReverseIterator operator++(int) 
			{
				ReverseIterator tmp(*this);
				operator++();
				return (tmp);
			}

			It &operator++() 
			{
				return (this->It::operator--());
			}

			ReverseIterator operator--(int) 
			{
				ReverseIterator tmp(*this);
				operator--();
				return (tmp);
			}

			It &operator--() 
			{
				return (this->It::operator++());
			}
	};
}

#endif
