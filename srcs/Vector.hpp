/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 10:09:47 by schene            #+#    #+#             */
/*   Updated: 2021/02/23 11:56:34 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef vector_HPP
# define vector_HPP

# include <memory>
# include <sstream>
# include <cstddef>
# include <stdexcept>
# include <iostream>

# include "./utils/ft_utils.hpp"
# include "./utils/Reverse_iterator.hpp"

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
			typedef const pointer		const_pointer;
			typedef value_type&			reference;
			typedef const value_type&	const_reference;
			typedef std::ptrdiff_t		difference_type;

			static const bool			input_iter;

		protected:
			pointer			it;

		public:
		 	vectorIterator(void) : it(NULL) {}
			vectorIterator(pointer &tab) : it(tab) {}
			vectorIterator(const_pointer &tab) : it(tab) {}
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
			explicit vector (const allocator_type& alloc = allocator_type()) : 
				_tab(NULL), _size(0), _capacity(0), _alloc(alloc) {}

			explicit vector (size_type n, const value_type& val = value_type(),
                const allocator_type& alloc = allocator_type()) :  _tab(NULL), _size(n), _capacity(n), _alloc(alloc)
			{
				_tab = _alloc.allocate(static_cast<size_t>(n));
				for (size_t i = 0; i < _size; i++)
					_alloc.construct(_tab + i, val);
			}

			template < class InputIter>
			vector(typename ft::enable_if<!std::numeric_limits<InputIter>::is_integer, InputIter>::type first,
				InputIter last, const allocator_type& alloc = allocator_type()) :
				  _tab(NULL), _size(0), _capacity(0), _alloc(alloc)
			{
				this->assign(first, last);
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
					if (this->_size)
						this->_alloc.destroy(this->_tab);
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
					erase(this->begin() + n, this->end());
				else if (n > this->_size)
				{
					if (n > this->_capacity)
					{
						if (n <= (this->_capacity * 2 ) && this->_capacity)
							this->reserve(this->_capacity * 2);
						else
							this->reserve(n);
					}
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
				return (!this->_size);
			}

			void reserve (size_type n)
			{
				if (n > this->_capacity)
				{
					allocator_type	tmp_alloc;
					pointer			tmp_tab = tmp_alloc.allocate(n);

					for (size_t i = 0; i < this->_size; i++)
						tmp_alloc.construct(&tmp_tab[i], _tab[i]);
					if (this->_size)
						_alloc.destroy(_tab);
					_alloc.deallocate(_tab, _capacity);
					this->_capacity = n;
					this->_alloc = tmp_alloc;
					this->_tab = tmp_tab;
				}
			}

			//---------------- ELEMENT ACCESS ----------------
			reference operator[] (size_type n)
			{
				return (this->_tab[n]);
			}
			
			const_reference operator[] (size_type n) const
			{
				return (this->_tab[n]);
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
				return (this->_tab[n]);
			}

			reference	front()
			{
				return (this->_tab[0]);
			}

			const_reference	front() const
			{
				return (this->_tab[0]);
			}

			reference			back()
			{
				return (this->_tab[this->_size - 1]);
			}

			const_reference		back() const
			{
				return (this->_tab[this->_size - 1]);
			}
			//---------------- MODIFIER ----------------
			
			template <class InputIter>
			void	assign(typename ft::enable_if<!std::numeric_limits<InputIter>::is_integer, 
				InputIter>::type first, InputIter last)
			{
				this->clear();
				this->insert(this->begin(), first, last);
			}
			
			void assign (size_type n, const value_type& val)
			{
				this->clear();
				this->resize(n, val);
			}

			void push_back (const value_type& val)
			{
				this->insert(this->end(), val);
			}

			void pop_back()
			{
				this->erase(--this->end());
			}

			iterator insert (iterator position, const value_type& val)
			{
				difference_type idx = position - this->begin();

				this->insert(position, 1, val);
				return (iterator(this->begin() + idx));
			}

			void insert (iterator position, size_type n, const value_type& val)
			{
				difference_type const	idx = position - this->begin();
				difference_type const	old_end_idx = this->end() - this->begin();
				iterator				old_end, end;

				this->resize(this->_size + n);

				end = this->end();
				position = this->begin() + idx;
				old_end = this->begin() + old_end_idx;
				while (old_end != position)
					*--end = *--old_end;
				while (n-- > 0)
					*position++ = val;
			}
			
			template <class InputIter>
			void insert(iterator position, InputIter first, 
				typename ft::enable_if<!std::numeric_limits<InputIter>::is_integer, InputIter>::type last)
			{
				difference_type const	idx = position - this->begin();
				difference_type const	old_end_idx = this->end() - this->begin();
				iterator				old_end, end;

				this->resize(this->_size + (last - first));

				end = this->end();
				position = this->begin() + idx;
				old_end = this->begin() + old_end_idx;
				while (old_end != position)
					*--end = *--old_end;
				while (first != last)
					*position++ = *first++;
			}

			iterator erase (iterator position)
			{
					iterator	ret;

					ret = position;
					while (position + 1 != this->end())
					{
						*position = *(position + 1);
						position++;
					}
					this->_size--;
					return ret;
			}

			iterator erase (iterator first, iterator last)
			{
					while (first != last)
					{
						erase(first);
						last--;
					}
					return first;
			}
			
			void swap (vector& x)
			{
				
				pointer			tmp_tab = this->_tab;
				size_type		tmp_size = this->_size ;
				size_type		tmp_capacity = this->_capacity;
				allocator_type	tmp_alloc = this->_alloc;

				this->_tab = x._tab;
				this->_alloc = x._alloc;
				this->_size = x._size;
				this->_capacity = x._capacity;

				x._tab = tmp_tab;
				x._alloc = tmp_alloc;
				x._size = tmp_size;
				x._capacity = tmp_capacity;
			}
			
			void clear()
			{
				this->erase(this->begin(), this->end());
			}
	};

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
