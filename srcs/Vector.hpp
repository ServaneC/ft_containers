/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:44:43 by schene            #+#    #+#             */
/*   Updated: 2021/01/12 10:00:10 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <cstddef>
# include <stdexcept>

namespace ft
{
	template <typename T, class Allocator = std::allocator<T> >
	class Vector;

	template <typename T>
	class VectorIterator
	{
		public:
			typedef T				value_type;
			typedef value_type*		pointer;
			typedef value_type&		reference;
			typedef ptrdiff_t		difference_type;

		protected:
			pointer			it;

		public:
		 	VectorIterator() : it(NULL) {} ;
			VectorIterator(VectorIterator &to_copy) : it(to_copy->it) {};
			~VectorIterator() {};

			reference			operator=(VectorIterator &rhs)
			{
				this->it = rhs->it;
				return (*this);
			}

			bool				operator==(VectorIterator &cmp)
			{
				return (this->it == cmp->it);
			}
			
			bool				operator!=(VectorIterator &cmp)
			{
				return (this->it != cmp->it);
			}

			reference			operator++()
			{
				++this->it;
				return (this->it);
			}
			reference			operator--()
			{
				--this->it;
				return (this->it);
			}
	};

	template <typename T, class Allocator >
	class Vector
	{
		public:
			typedef	Allocator						allocator_type;
			typedef	T 								value_type;
			typedef	size_t 							size_type;
			typedef value_type&						reference;
			typedef const value_type&				const_reference;
			typedef value_type*						pointer;
			typedef const value_type*				const_pointer;
			typedef VectorIterator<value_type>		iterator;	
			typedef ptrdiff_t						difference_type;

		
		private:
			pointer			_tab;
			size_type		_size;
			size_type		_capacity;
			allocator_type	_alloc;

		public:
			//---------------- CONSTRUCTOR ----------------
			explicit Vector (const allocator_type& alloc = allocator_type()) : _size(0), _capacity(0)
			{
				_alloc = static_cast<allocator_type>(alloc);
				_tab = _alloc.allocate(static_cast<size_t>(this->_capacity));
			}
			explicit Vector (size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type())
			{
				_size = n;
				_capacity = n;
				_alloc = static_cast<allocator_type>(alloc);
				_tab = _alloc.allocate(static_cast<size_t>(n));
				for (size_t i = 0; i < _size; i++)
					_alloc.construct(_tab + i, val);
			}

			//---------------- DESTRUCTOR ----------------
			~Vector()
			{
				for (size_t i = 0; i < _size; i++)
					_alloc.destroy(_tab + i);
				_alloc.deallocate(_tab, _size);
			}
			
			//---------------- ITERATOR ----------------

			iterator	begin()
			{
				return (iterator(this->_tab));
			}

			//---------------- CAPACITY ----------------
			size_type 	size() const
			{
				return this->_size;
			}

			size_type max_size() const
			{
				return _alloc.max_size();
			}

			void		resize (size_type n, value_type val = value_type())
			{
				
				if (n < this->_size)
				{
					for (size_t i = n; i < _size; i++)
						_alloc.destroy(_tab + i);
				}
				else if (n > this->_size)
				{
					if (n > this->_capacity)
						this->reserve(n);
					for (size_type i = this->_size; i < n; i++)
						_alloc.construct(_tab + i, val);
				}
				this->_size = n;
			}

			size_type	capacity() const
			{
				return this->_capacity;
			}
			
			bool 		empty() const
			{
				if (this->_size == 0)
					return true;
				else
					return false;
			}

			void reserve (size_type n)
			{
				if (n > this->_capacity)
				{
					allocator_type tmp_alloc;
					tmp_alloc = static_cast<allocator_type>(this->_alloc);
					pointer			tmp_tab;
					tmp_tab = tmp_alloc.allocate(static_cast<size_t>(n));
					for (size_t i = 0; i < _size; i++)
						tmp_alloc.construct(tmp_tab + i, _tab[i]);
					_alloc.deallocate(_tab, _capacity);
					this->_capacity = n;
					this->_alloc = tmp_alloc;
					this->_tab = tmp_tab;
				}
			}

			//---------------- ELEMENT ACCESS ----------------
			reference operator[] (size_type n)
			{
				return (_tab[n]);
			}
			
			reference	at(size_type n)
			{
				if (n >= this->_size)
					throw std::out_of_range("n is out of range !");
				return (_tab[n]);
			}

			reference	front()
			{
				return (_tab[0]);
			}

			reference	back()
			{
				return (_tab[_size - 1]);
			}
			//---------------- MODIFIER ----------------
			void push_back (const value_type& val)
			{
				this->resize(this->_size + 1, val);
			}

			void pop_back()
			{
				this->resize(this->_size - 1);
			}

			void clear()
			{
				this->resize(0);
			}
	};
}

#endif