/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 10:09:47 by schene            #+#    #+#             */
/*   Updated: 2021/01/19 15:52:34 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef vector_HPP
# define vector_HPP

# include <memory>
# include <sstream>
# include <cstddef>
# include <stdexcept>
# include <iostream>

# include "Reverse_iterator.hpp"

namespace ft
{
	template <typename T, class Allocator = std::allocator<T> >
	class vector;

	template <typename T>
	class vectorIterator
	{
		public:
			typedef T					value_type;
			typedef value_type*			pointer;
			typedef const value_type*	const_pointer;
			typedef value_type&			reference;
			typedef const value_type&	const_reference;
			typedef std::ptrdiff_t		difference_type;

		protected:
			pointer			it;

		public:
		 	vectorIterator(void) : it(NULL) {}
			vectorIterator(pointer &tab) : it(tab) {}
			vectorIterator(const pointer &tab) : it(tab) {}
			vectorIterator(vectorIterator const &to_copy) : it(to_copy.it) {}
			virtual ~vectorIterator() {}

			vectorIterator			operator=(const vectorIterator &rhs)
			{
				this->it = rhs.it;
				return (*this);
			}

			pointer				getIt()
			{
				return this->it;
			}
			reference			operator*()
			{
				return (*this->it);
			}

			const_reference		operator*() const
			{
				return (*this->it);
			}
			
			pointer operator->()
			{
				return (this->it);
			}
	
			const_pointer operator->() const
			{
				return (this->it);
			}

			reference operator[](int index)
			{
				return (this->it[index]);
			}

			const_reference operator[](int index) const
			{
				return (this->it[index]);
			}

			vectorIterator			operator++()
			{
				++this->it;
				return (*this);
			}
			
			vectorIterator			operator++(int)
			{
				vectorIterator tmp = *this;
   				++*this;
   				return (tmp);
			}

			vectorIterator			&operator--()
			{
				--this->it;
				return (*this);
			}
			
			vectorIterator			operator--(int)
			{
				vectorIterator tmp = *this;
   				--*this;
   				return (tmp);
			}

			difference_type			operator-(vectorIterator const &rhs) const
			{
				vectorIterator tmp(*this);
				return (tmp.it - rhs.it);
			}

			vectorIterator			operator-(int	i) const
			{
				vectorIterator tmp(*this);
				return (tmp.getIt() - i);
			}

			vectorIterator 			operator+(int i) const
			{
				vectorIterator tmp(*this);
				return (tmp.getIt() + i);
			}

			bool				operator==(const vectorIterator &cmp) const
			{
				return (this->it == cmp.it);
			}
			
			bool				operator!=(const vectorIterator &cmp) const
			{
				return (this->it != cmp.it);
			}

			bool				operator<(const vectorIterator &cmp) const
			{
				return (this->it < cmp.it);
			}

			bool				operator<=(const vectorIterator &cmp) const
			{
				return (this->it <= cmp.it);
			}

			bool				operator>(const vectorIterator &cmp) const
			{
				return (this->it > cmp.it);
			}

			bool				operator>=(const vectorIterator &cmp) const
			{
				return (this->it >= cmp.it);
			}
	};

	template <typename T, class Allocator >
	class vector
	{
		public:
			typedef	Allocator							allocator_type;
			typedef	T 									value_type;
			typedef	size_t 								size_type;
			typedef value_type&							reference;
			typedef const value_type&					const_reference;
			typedef value_type*							pointer;
			typedef const value_type*					const_pointer;
			typedef vectorIterator<value_type>			iterator;
			typedef vectorIterator<value_type> const	const_iterator;
			typedef ReverseIterator<iterator>			reverse_iterator;
			typedef ReverseIterator<iterator> const		const_reverse_iterator;
			typedef std::ptrdiff_t						difference_type;

		
		private:
			pointer			_tab;
			size_type		_size;
			size_type		_capacity;
			allocator_type	_alloc;

		public:
			//---------------- CONSTRUCTOR ----------------
			explicit vector (const allocator_type& alloc = allocator_type()) : _size(0), _capacity(0)
			{
				_alloc = static_cast<allocator_type>(alloc);
				_tab = _alloc.allocate(static_cast<size_t>(this->_capacity));
			}

			explicit vector (size_type n, const value_type& val = value_type(),
                const allocator_type& alloc = allocator_type()) : _size(n), _capacity(n)
			{
				_alloc = static_cast<allocator_type>(alloc);
				_tab = _alloc.allocate(static_cast<size_t>(n));
				for (size_t i = 0; i < _size; i++)
					_alloc.construct(_tab + i, val);
			}

			vector (iterator first, iterator last,
			    const allocator_type& alloc = allocator_type()) : _size(0), _capacity(0)
			{
				for (iterator it = first; it != last; it++)
					this->_size++;
				this->_capacity = this->_size;
				this->_alloc = static_cast<allocator_type>(alloc);
				this->_tab = _alloc.allocate(static_cast<size_t>(this->_size));
				size_type i = 0;
				for (iterator it = first; it != last; it++)
				{
					_alloc.construct(_tab + i, *it);
					i++;
				}
			}

			vector (const vector& x) : _size(x.size()), _capacity(x.capacity())
			{
				_tab = _alloc.allocate(static_cast<size_t>(this->_size));
				for (size_t i = 0; i < this->_size; i++)
					_alloc.construct(_tab + i, x[i]);
			}

			//---------------- DESTRUCTOR ----------------
			virtual ~vector()
			{
				if (this->_tab)
				{
					this->clear();	
					this->_alloc.deallocate(this->_tab, this->_capacity);
				}
				this->_tab = NULL;
				this->_size = 0;
				this->_capacity = 0;
			}

			vector& operator= (const vector& x)
			{
				this->erase(this->begin(), this->end());
				this->assign(x.begin(), x.end());
	
				return ((*this));
			}
			//---------------- ITERATOR ----------------

			iterator	begin()
			{
				return (iterator(this->_tab));
			}

			const_iterator begin() const
			{
				return (const_iterator(this->_tab));
			}

			iterator	end()
			{
				pointer 	ptr = &this->_tab[this->_size];
				return (iterator(ptr));
			}

			const_iterator	end() const
			{
				pointer 	ptr = &this->_tab[this->_size];
				return (const_iterator(ptr));
			}

			reverse_iterator rbegin()
			{
				return (reverse_iterator(this->end()));
			}

			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(this->end()));
			}

			reverse_iterator rend()
			{
				return (reverse_iterator(this->begin()));
			}

			const_reverse_iterator rend() const
			{
				return (reverse_iterator(this->begin()));
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
					for (size_t i = n; i < this->_size; i++)
						_alloc.destroy(this->_tab + i);
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
			
			const_reference operator[] (size_type n) const
			{
				return (_tab[n]);
			}

			reference	at(size_type n)
			{
				if (n >= this->_size)
				{
					 std::stringstream stream;

   					stream << "vector::_M_range_check: __n (which is " << n;
					stream << ") >= this->size() (which is " << this->size() << ')';
    				std::string arg = stream.str();
					throw std::out_of_range(arg);
				}
				return (_tab[n]);
			}

			const_reference	at(size_type n) const
			{
				if (n >= this->_size)
				{
					 std::stringstream stream;

   					stream << "vector::_M_range_check: __n (which is " << n;
					stream << ") >= this->size() (which is " << this->size() << ')';
    				std::string arg = stream.str();
					throw std::out_of_range(arg);
				}
				return (_tab[n]);
			}

			reference	front()
			{
				return (_tab[0]);
			}

			const_reference	front() const
			{
				return (_tab[0]);
			}

			reference			back()
			{
				return (_tab[_size - 1]);
			}

			const_reference		back() const
			{
				return (_tab[_size - 1]);
			}
			//---------------- MODIFIER ----------------
			
			void assign (iterator first, iterator last)
			{
				difference_type new_sz = last - first;
				this->resize(new_sz);
				size_type	i = -1;
				for (iterator it = first; it != last; ++it)
					this->_tab[++i] = (*it);
			}
			
			void assign (size_type n, const value_type& val)
			{
				if (this->_size > 0)
					this->clear();
				if (n > this->_capacity)
					this->reserve(n);
				this->resize(n, val);
			}

			void push_back (const value_type& val)
			{
				if (this->_size + 1 > this->capacity())
					this->reserve(this->_size * 2);
				this->resize(this->_size + 1, val);
			}

			void pop_back()
			{
				this->resize(this->_size - 1);
			}

			iterator insert (iterator position, const value_type& val)
			{
				size_type i = 0;
				while ((&this->_tab[i]) && position.getIt() != (&this->_tab[i]))
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
				for (size_type index = i; index < this->_size - n; index++)
					this->_tab[index] = this->_tab[index + n];
				this->resize(this->_size - n);
				pointer		ret = &this->_tab[i];
				return (iterator(ret));
			}
			
			void swap (vector& x)
			{
				vector<value_type> tmp = (*this);
				
				(*this) = x;
				x = tmp;
			}
			
			void clear()
			{
				this->resize(0);
			}
	};

	// template <class Alloc>
	// class vector<bool,Alloc>
	// {
		
	// };

	template <class T, class Alloc>
  	bool		operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		for (size_t i = 0; i < lhs.size() ; i++)
		{
			if (lhs[i] != rhs[i])
				return false;
		}
		return true;
	}

	template <class T, class Alloc>
	bool 	operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Alloc>
	bool	operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		size_t size = lhs.size();
		if (size > rhs.size())
			size = rhs.size();

		for (size_t i = 0; i < size; i++)
		{
			if (lhs[i] < rhs[i])
				return true;
		}
		return false;
	}

	template <class T, class Alloc>
  	bool	operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (lhs < rhs || lhs == rhs);
	}

	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(lhs <= rhs);
	}

	template <class T, class Alloc>
 	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(lhs < rhs);
	}
	
	template <class T, class Alloc>
  	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		x.swap(y);
	}
}

#endif
