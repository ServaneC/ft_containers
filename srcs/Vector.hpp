/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 10:09:47 by schene            #+#    #+#             */
/*   Updated: 2021/01/15 14:03:30 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <cstddef>
# include <stdexcept>
# include <iostream>

namespace ft
{
	template <typename T, class Allocator = std::allocator<T> >
	class Vector;

	template <typename T>
	class VectorIterator
	{
		public:
			typedef T					value_type;
			typedef value_type*			pointer;
			typedef value_type&			reference;
			typedef std::ptrdiff_t		difference_type;

		protected:
			pointer			it;

		public:
		 	VectorIterator(void) : it(NULL) {}
			VectorIterator(pointer &tab) : it(tab) {}
			VectorIterator(VectorIterator const &to_copy) : it(to_copy.it) {}
			virtual ~VectorIterator() {}

			VectorIterator			operator=(VectorIterator &rhs)
			{
				this->it = rhs.it;
				return (*this);
			}

			bool				operator==(VectorIterator &cmp)
			{
				return (this->it == cmp.it);
			}
			
			bool				operator!=(VectorIterator &cmp)
			{
				return (this->it != cmp.it);
			}

			pointer				getIt()
			{
				return this->it;
			}
			reference			operator*()
			{
				return (*this->it);
			}

			VectorIterator			operator++()
			{
				++this->it;
				return (*this);
			}
			
			VectorIterator			operator++(int)
			{
				VectorIterator tmp = *this;
   				++*this;
   				return (tmp);
			}

			VectorIterator			operator--()
			{
				--this->it;
				return (*this);
			}
			
			VectorIterator			operator--(int)
			{
				VectorIterator tmp = *this;
   				--*this;
   				return (tmp);
			}

			difference_type			operator-(VectorIterator const &rhs) const
			{
				VectorIterator tmp(*this);
				return (tmp.it - rhs.it);
			}

			VectorIterator			operator-(int	i) const
			{
				VectorIterator tmp(*this);
				return (tmp - i);
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
			typedef std::ptrdiff_t					difference_type;

		
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
			virtual ~Vector()
			{
				if (this->_tab)
				{
					this->clear();	
					this->_alloc.deallocate(this->_tab, this->_capacity);
				}
			}
			//---------------- ITERATOR ----------------

			iterator	begin()
			{
				return (iterator(this->_tab));
			}

			iterator	end()
			{
				pointer 	ptr = &this->_tab[this->_size];
				return (iterator(ptr));
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
			
			void assign (iterator first, iterator last)
			{
				if (this->_size > 0)
				{
					for (size_t i = 0; i < _size; i++)
						_alloc.destroy(_tab + i);
					this->_size = 0;
				}
				difference_type new_sz = last - first;
				this->reserve(new_sz);
				this->resize(new_sz);
				size_type	i = -1;
				for (iterator it = first; it != last; ++it)
					this->_tab[++i] = (*it);
			}
			
			void assign (size_type n, const value_type& val)
			{
				if (this->_size > 0)
				{
					for (size_t i = 0; i < _size; i++)
						_alloc.destroy(_tab + i);
					this->_size = 0;
				}
				if (n > this->_capacity)
					this->reserve(n);
				this->resize(n, val);
			}

			void push_back (const value_type& val)
			{
				this->resize(this->_size + 1, val);
			}

			void pop_back()
			{
				this->resize(this->_size - 1);
			}

			iterator insert (iterator position, const value_type& val)
			{
				size_type i = 0;
				while (position.getIt() != (&this->_tab[i]) && this->_tab[i])
					i++;
				this->insert(position, 1, val);
				pointer		ret = &this->_tab[i];
				return (iterator(ret));
			}

			void insert (iterator position, size_type n, const value_type& val)
			{
				size_type first = this->_size;
				while (position.getIt() != (&this->_tab[first]) && first >= 0)
					first--;
				if (this->_size + n > this->_capacity)
					this->reserve(this->_size + n);
				size_type	old_size = this->_size;
				this->resize(this->_size + n);
				size_type	last = first + n;
				for (size_type j = old_size; j >= first; --j)
					this->_tab[j + n] = this->_tab[j];
				while (last-- != first)
					this->_tab[last] = val;
			}
			
			void insert (iterator position, iterator first, iterator last)
			{
				size_type n = 0;
				for (iterator it = first; it != last; it++)
					n++;
				size_type i = this->_size;
				while (position.getIt() != (&this->_tab[i]) && i >= 0)
					i--;
				if (this->_size + n > this->_capacity)
					this->reserve(this->_size + n);
				size_type	old_size = this->_size;
				this->resize(this->_size + n);
				for (size_type j = old_size; j >= i; --j)
					this->_tab[j + n] = this->_tab[j];
				size_type index = i;
				while (first++ != last)
				{
					this->_tab[index] = *first.getIt();
					index++;
				}	
			}

			iterator erase (iterator position)
			{
				return (this->erase(position, ++position));
			}

			iterator erase (iterator first, iterator last)
			{
				size_type n = 0;
				for (iterator it = first; it != last; it++)
					n++;
				size_type i = 0;
				while (first.getIt() != (&this->_tab[i]) && i <= this->_size)
					i++;
				for (size_type index = i; this->_tab[index + n]; index++)
					this->_tab[index] = this->_tab[index + n];
				this->resize(this->_size - n);
				pointer		ret = &this->_tab[i];
				return (iterator(ret));
			}
			
			void swap (Vector& x)
			{
				Vector<value_type> tmp = (*this);
				
				(*this) = x;
				x = tmp;
			}
			
			void clear()
			{
				this->resize(0);
			}
	};
}

#endif
