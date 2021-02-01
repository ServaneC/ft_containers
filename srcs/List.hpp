/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 14:32:39 by schene            #+#    #+#             */
/*   Updated: 2021/02/01 10:36:20 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
# define LIST_HPP

# include <memory>

#include "Node.hpp"
#include "Reverse_iterator.hpp"
# include <iostream>

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class list;

	template <typename T>
	class listIterator
	{
		public:
			typedef T					value_type;
			typedef value_type*			pointer;
			typedef const value_type*	const_pointer;
			typedef value_type&			reference;
			typedef const value_type&	const_reference;
			typedef node<T>				node_type;
			typedef node_type*			node_pointer;
			typedef node_type&			node_reference;
			typedef std::ptrdiff_t		difference_type;
		
		protected:
			node_pointer	it;

		public:
			listIterator(void) : it(NULL) {}
			listIterator(node_pointer &node) : it(node) {}
			listIterator(const node_pointer &node) : it(node) {}
			listIterator(listIterator const &to_copy) : it(to_copy.it) {}
			virtual ~listIterator() {}

			listIterator	operator=(const listIterator &rhs)
			{
				this->it = rhs.it;
				return (*this);
			}

			node_pointer	getIt()
			{
				return this->it;
			}
			
			reference			operator*()
			{
				return (this->it->data);
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

			listIterator	operator++()
			{
				this->it = this->it->next;
				return (*this);
			}
			
			listIterator	operator++(int)
			{
				listIterator tmp = *this;
				this->it = this->it->next;
				return (tmp);
			}

			listIterator	operator--()
			{
				this->it = this->it->prev;
				return (*this);
			}
			
			listIterator	operator--(int)
			{
				listIterator tmp = *this;
				this->it = this->it->prev;
				return (tmp);
			}

			bool				operator==(const listIterator &cmp) const
			{
				return (this->it == cmp.it);
			}
			
			bool				operator!=(const listIterator &cmp) const
			{
				return ((this->it) != cmp.it);
			}
			
	};

	template < class T, class Alloc >
	class list
	{
		public:
			typedef	T 									value_type;
			typedef	std::allocator<node<T> >			allocator_type;
			typedef value_type&							reference;
			typedef const value_type&					const_reference;
			typedef value_type*							pointer;
			typedef const value_type*					const_pointer;
			typedef node<T>								node_type;
			typedef node_type*							node_pointer;
			typedef listIterator<value_type>			iterator;
			typedef listIterator<value_type> const		const_iterator;
			typedef ReverseIterator<iterator>			reverse_iterator;
			typedef ReverseIterator<iterator> const		const_reverse_iterator;
			typedef std::ptrdiff_t						difference_type;
			typedef	size_t								size_type;

		private:
			node_pointer	_head;
			node_pointer	_tail;
			size_type		_size;
			allocator_type	_alloc;

			void			deep_clean()
			{
				this->clear();
				for (iterator it(this->_head); it != this->_tail; it++)
					_alloc.deallocate(it.getIt(), 1);
				this->_head = _alloc.allocate(1);
				this->_tail = _alloc.allocate(1);
				this->_head->data = 0;
				this->_head->next = this->_tail;
				this->_head->prev = this->_tail;
				this->_tail->prev = this->_head;
				this->_tail->next = this->_head;
			}

		public:
			//---------------- CONSTRUCTOR ----------------
			explicit list (const allocator_type& alloc = allocator_type()) : _size(0)
			{
				this->_alloc = static_cast<allocator_type>(alloc);
				this->_head = _alloc.allocate(1);
				this->_tail = _alloc.allocate(1);
				this->_head->next = this->_tail;
				this->_head->prev = this->_tail;
				// this->_head->data = NULL;
				this->_tail->prev = this->_head;
				this->_tail->next = this->_head;

			}
			
			explicit list (size_type n, const value_type& val = value_type(),
                const allocator_type& alloc = allocator_type()) : _size(0)
			{
				_alloc = static_cast<allocator_type>(alloc);
				this->_head = _alloc.allocate(1);
				this->_tail = _alloc.allocate(1);
				this->_head->next = this->_tail;
				this->_head->prev = this->_tail;
				this->_tail->prev = this->_head;
				this->_tail->next = this->_head;
				for (size_type i = 0; i < n; i++)
					this->push_back(val);
			}
			
  			// list (listIterator first, listIterator last,
         	// 		const allocator_type& alloc = allocator_type());
			
			// list (const list& x);

			//---------------- DESTRUCTOR ----------------

			virtual ~list()
			{
				this->clear();
				// for (iterator it = this->begin(); it != this->end(); it++)
				// 		_alloc.deallocate(it.getIt(), 1);
				this->_head = NULL;
				this->_tail = NULL;
				this->_size = 0;
			}
			//---------------- ITERATOR ----------------
			iterator begin()
			{
				return (iterator(this->_head));
			}

			const_iterator begin() const
			{
				return (const_iterator(this->_head));
			}

			iterator end()
			{
				return (iterator(this->_tail));
			}

			const_iterator end() const
			{
				return (const_iterator(this->_tail));
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
			bool		empty() const
			{
				if (_size == 0)
					return true;
				return false;
			}

			size_type	size() const
			{
				return this->_size;
			}

			size_type max_size() const
			{
				return _alloc.max_size();
			}
			//---------------- ELEMENT ACCESS ----------
			reference front()
			{
				return (this->_head->data);
			}

			const_reference front() const
			{
				return (this->_head->data);
			}

			reference back()
			{
				return (this->_tail->prev->data);
			}

			const_reference back() const
			{
				return (this->_tail->prev->data);
			}

			//---------------- MODIFIER ----------------

  			void		assign(iterator first, iterator last)
			{
				this->deep_clean();
				while (first != last)
				{
					this->push_back(first.getIt()->data);
					first++;
				}
			}
	
			void		assign (size_type n, const value_type& val)
			{
				this->deep_clean();
				for (size_type i = 0; i < n; i++)
					this->push_back(val);
			}

			void push_front (const value_type& val)
			{
				if (!this->_head->data)
				{
					this->_head->data = val;
				}
				else
				{
					node_pointer new_node = _alloc.allocate(1);
					new_node->data = val;
					new_node->prev = this->_head->prev;
					new_node->next = this->_head;
					this->_head->prev = new_node;
					this->_head = new_node;
				}
				this->_size++;
			}

			void pop_front()
			{
				node_pointer to_destroy = this->_head;
				this->_head = to_destroy->next;
				this->_head->prev = to_destroy->prev;
				this->_tail->next = this->_head;
				_alloc.destroy(to_destroy);
				_alloc.deallocate(to_destroy, 1);
				this->_size--;
			}

			void		push_back (const value_type& val)
			{
				if (!this->_size)
				{
					this->_head->data = val;
				}
				else
				{
					node_pointer new_node = this->_alloc.allocate(1);
					new_node->data = val;
					this->_tail->prev->next = new_node;
					new_node->prev = this->_tail->prev;
					new_node->next = this->_tail;
					this->_tail->prev = new_node;
				}
				this->_size++;
			}

			void pop_back()
			{
				node_pointer to_destroy = this->_tail->prev;
				to_destroy->prev->next = this->_tail;
				this->_tail->prev = to_destroy->prev;
				_alloc.destroy(to_destroy);
				_alloc.deallocate(to_destroy, 1);
				this->_size--;
			}

			iterator insert (iterator position, const value_type& val)
			{
				insert(position, 1, val);
				return iterator(position.getIt()->prev);
			}
	
   			void insert (iterator position, size_type n, const value_type& val)
			{
				for (size_type i = 0; i < n; i++)
				{
					node_pointer prev = position.getIt()->prev;
					node_pointer next = position.getIt();
					node_pointer new_node = this->_alloc.allocate(1);

					new_node->data = val;
					new_node->prev = prev;
					prev->next = new_node;
					new_node->next = next;
					next->prev = new_node;
					this->_size++;
				}
			}

    		void insert (iterator position, iterator first, iterator last)
			{
				while (first != last)
				{
					
					first++;
				}
			}
		
			iterator erase (iterator position)
			{
				this->erase(position, ++position);
				return (position);
			}

			iterator erase (iterator first, iterator last)
			{
				while (first != last)
				{
					node_pointer to_destroy = first.getIt();
					to_destroy->prev->next = to_destroy->next;
					to_destroy->next->prev = to_destroy->prev;
					if (to_destroy != this->_head)
					{
						_alloc.destroy(to_destroy);
						_alloc.deallocate(to_destroy, 1);
					}
					else
					{
						this->_head = to_destroy->next;
					}
					this->_size--;
					first++;
				}
				return last;
			}

			// void swap (list& x);
			
			void resize (size_type n, value_type val = value_type())
			{
				if (n < this->_size)
				{
					size_type diff = this->_size - n;
					for (size_type i = 0; i < diff; i++)
						pop_back();
				}
				else
				{
					size_type diff = n - this->_size;
					for (size_type i = 0; i < diff; i++)
						push_back(val);
				}
			}

			void		clear()
			{
				if (this->_size > 0)
				{
					for (iterator it(this->_head); it != this->_tail; it++)
						this->_alloc.destroy(it.getIt());
				}
				this->_size = 0;
			}

			//---------------- OPERATIONS ----------------
			// void splice (iterator position, list& x);
			// void splice (iterator position, list& x, iterator i);
			// void splice (iterator position, list& x, iterator first, iterator last);

			// void remove (const value_type& val);

			// template <class Predicate>
  			// void remove_if (Predicate pred);

			// void unique();
			// template <class BinaryPredicate>
			//   void unique (BinaryPredicate binary_pred);

			// void merge (list& x);
			// template <class Compare>
			//   void merge (list& x, Compare comp);

			// void sort();
			// template <class Compare>
			//   void sort (Compare comp);

			// void reverse();
	};
}

#endif