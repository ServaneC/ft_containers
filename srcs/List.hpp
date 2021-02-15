/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 14:32:39 by schene            #+#    #+#             */
/*   Updated: 2021/02/15 21:35:19 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
# define LIST_HPP

# include <memory>

# include "Node.hpp"
# include "Reverse_iterator.hpp"
# include "ft_utils.hpp"
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
				return (this->it->getData());
			}

			const_reference		operator*() const
			{
				return (*this->it);
			}
			
			pointer operator->()
			{
				return (this->it->getData());
			}
	
			const_pointer operator->() const
			{
				return (this->it->getData());
			}

			listIterator	&operator++()
			{
				this->it = this->it->getNext();
				return (*this);
			}
			
			listIterator	operator++(int)
			{
				listIterator tmp = *this;
				this->it = this->it->getNext();
				return (tmp);
			}

			listIterator	&operator--()
			{
				this->it = this->it->getPrev();
				return (*this);
			}
			
			listIterator	operator--(int)
			{
				listIterator tmp = *this;
				this->it = this->it->getPrev();
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

			void	starter_node()
			{
				this->_head = this->_alloc.allocate(1);
				this->_head->getNext() = NULL;
				this->_head->getPrev() = NULL;
				this->_tail = this->_head;
			}

			void	push_first_node(node_pointer new_node)
			{
				new_node->getNext() = this->_tail;
				new_node->getPrev() = this->_tail;
				this->_head = new_node;
				this->_tail->getNext() = this->_head;
				this->_tail->getPrev() = this->_head;
			}
		
			void	swap_node(node_pointer a, node_pointer b)
			{
				if (a == this->_head)
				{
					a->getPrev() = b;
					a->getNext() = b->getNext();
					a->getNext()->getPrev() = a;
					b->getPrev() = this->_tail;
					b->getNext() = a;
					this->_head = b;
					this->_tail->getNext() = this->_head;
				}
				else
				{
					node_pointer tmp = a->getPrev();
					tmp->getNext() = b;
					b->getPrev() = tmp;
					tmp = b->getNext();
					tmp->getPrev() = a;
					a->getNext() = tmp;
					b->getNext() = a;
					a->getPrev() = b;
				}
			}

		public:
			//---------------- CONSTRUCTOR ----------------
			explicit list (const allocator_type& alloc = allocator_type()) : _size(0), _alloc(alloc)
			{
				this->starter_node();
			}
			
			explicit list (size_type n, const value_type& val = value_type(),
                const allocator_type& alloc = allocator_type()) : _size(0), _alloc(alloc)
			{
				this->starter_node();
				for (size_type i = 0; i < n; i++)
					this->push_back(val);
			}
			
			template < class InputIter>
			list(typename ft::enable_if<!std::numeric_limits<InputIter>::is_integer, InputIter>::type first,
				InputIter last, const allocator_type& alloc = allocator_type()) : 
			 _size(0), _alloc(alloc)
			{
				this->starter_node();
				this->assign(first, last);
			}
			
			list (const list& x) : _size(0)
			{
				this->starter_node();
				this->assign(x.begin(), x.end());
			}

			//---------------- DESTRUCTOR ----------------

			virtual ~list()
			{
				this->clear();
				if (!this->_size)
					this->_alloc.deallocate(this->_head, 1);
				else
				{
					for (iterator it = this->begin(); it != this->end(); it++)
					{
						this->_alloc.destroy(it.getIt());
						this->_alloc.deallocate(it.getIt(), 1);
					}
				}
				this->_head = NULL;
				this->_tail = NULL;
				this->_size = 0;
			}

			//---------------- OPERATOR = ----------------
			list& 		operator=(const list& x)
			{
				this->assign(x.begin(), x.end());
				return (*this);
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
				return (const_reverse_iterator(this->begin()));
			}

			//---------------- CAPACITY ----------------
			bool		empty() const
			{
				if (this->_size == 0)
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
				return (this->_head->getData());
			}

			const_reference front() const
			{
				return (this->_head->getData());
			}

			reference back()
			{
				return (this->_tail->getPrev()->getData());
			}

			const_reference back() const
			{
				return (this->_tail->getPrev()->getData());
			}

			//---------------- MODIFIER ----------------

			template <class InputIter>
				void	assign(typename ft::enable_if<!std::numeric_limits<InputIter>::is_integer, 
					InputIter>::type first, InputIter last)
			{
				this->clear();
				this->insert(this->begin(), first, last);
			}
	
			void		assign (size_type n, const value_type& val)
			{
				this->clear();
				for (size_type i = 0; i < n; i++)
					this->push_back(val);
			}

			void push_front (const value_type& val)
			{
				this->insert(this->begin(), val);
			}

			void pop_front()
			{
				this->erase(this->begin());
			}

			void		push_back (const value_type& val)
			{
				this->insert(this->end(), val);
			}

			void pop_back()
			{
				this->erase(--this->end());
			}

			iterator insert (iterator position, const value_type& val)
			{
				node_pointer new_node = this->_alloc.allocate(1);
				
				this->_alloc.construct(new_node, val);
				if (!this->_size)
					push_first_node(new_node);
				else if (position == this->_head)
				{
					new_node->getPrev() = this->_tail;
					new_node->getNext() = this->_head;
					this->_head->getPrev() = new_node;
					this->_head = new_node;
					this->_tail->getNext() = this->_head;
				}
				else
				{
					new_node->getPrev() = position.getIt()->getPrev();
					position.getIt()->getPrev()->getNext() = new_node;
					position.getIt()->getPrev() = new_node;
					new_node->getNext() = position.getIt();
				}
				this->_size++;
				return iterator(new_node);
			}
	
   			void insert (iterator position, size_type n, const value_type& val)
			{
				for (size_type i = 0; i < n; i++)
				{
					node_pointer prev = position.getIt()->getPrev();
					node_pointer next = position.getIt();
					node_pointer new_node = this->_alloc.allocate(1);
					new_node->getData() = val;

					if (!this->_size)
						push_first_node(new_node);
					else
					{
						new_node->getPrev() = prev;
						prev->getNext() = new_node;
						new_node->getNext() = next;
						next->getPrev() = new_node;
						if (position.getIt() == this->_head && i == 0)
							this->_head = new_node;
					}
					this->_size++;
				}
			}

			template <class InputIter>
				void insert(iterator position, InputIter first, 
					typename ft::enable_if<!std::numeric_limits<InputIter>::is_integer, InputIter>::type last)
			{
				while (first != last)
					this->insert(position, *first++);
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
					++first;
					to_destroy->getPrev()->getNext() = to_destroy->getNext();
					to_destroy->getNext()->getPrev() = to_destroy->getPrev();
					if (to_destroy == this->_head)
					{
						this->_head = to_destroy->getNext();
						this->_head->getPrev() = this->_tail;
						this->_tail->getNext() = this->_head;
					}
					this->_alloc.destroy(to_destroy);
					this->_alloc.deallocate(to_destroy, 1);
					this->_size--;
				}
				return last;
			}

			void swap (list& x)
			{
				list<value_type> tmp = *this;

				*this = x;
				x = tmp;
			}
			
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
				this->erase(this->begin(), this->end());
			}

			//---------------- OPERATIONS ----------------
			void splice (iterator position, list& x)
			{
				this->splice(position, x, x.begin(), x.end());
			}

			void splice (iterator position, list& x, iterator i)
			{
				this->splice(position, x, i, ++i);
			}

			void splice (iterator position, list& x, iterator first, iterator last)
			{
				this->insert(position, first, last);
				x.erase(first, last);
			}

			void remove (const value_type& val)
			{
				for (iterator it = this->begin(); it != this->end(); ++it)
				{
					if (*it == val)
					{
						this->erase(it);
						it = --this->begin();
					}
				}
			}

			template <class Predicate>
  			void remove_if (Predicate pred)
			{
				for (iterator it = this->begin(); it != this->end(); ++it)
				{
					if (pred(*it))
					{
						this->erase(it);
						it = --this->begin();
					}
				}
			}

			void unique()
			{
				for (iterator it = ++this->begin(); it != this->end(); ++it)
				{
					if (*it == it.getIt()->getPrev()->getData())
						it = this->erase(it);
				}
			}

			template <class BinaryPredicate>
			void unique (BinaryPredicate binary_pred)
			{
				for (iterator it = ++this->begin(); it != this->end(); ++it)
				{
					if (binary_pred(*it, it.getIt()->getPrev()->getData()))
					{
						this->erase(it);
						it = this->begin();
					}
				}
			}

			void merge (list& x)
			{
				for (iterator it = this->begin(); it != this->end(); ++it)
				{
					if (!x.empty() && *it > *(x.begin()))
					{
						this->splice(it, x, x.begin());
						if (it != this->begin())
							--it;
					}
				}
				this->splice(this->end(), x);
			}

			template <class Compare>
			void merge (list& x, Compare comp)
			{
				for (iterator it = this->begin(); it != this->end(); ++it)
				{
					if (!x.empty() && comp(*(x.begin()), *it))
					{
						this->splice(it, x, x.begin());
						if (it != this->begin())
							--it;
					}
				}
				this->splice(this->end(), x);
			}

			void sort()
			{
				node_pointer current = this->_head;
				node_pointer index = this->_head->getNext();

				for (size_type i = 0; i < this->_size; i++)
				{
					while (iterator(index) != this->end())
					{
						if (current->getData() > index->getData())
							swap_node(current, index);
						current = index;
						index = current->getNext();
					}
					current = this->_head;
					index = this->_head->getNext();
				}
			}

			template <class Compare>
			void sort (Compare comp)
			{
				node_pointer current = this->_head;
				node_pointer index = this->_head->getNext();

				for (size_type i = 0; i < this->_size; i++)
				{
					while (iterator(index) != this->end())
					{
						// if (comp(current->getData(), index->getData()))
						if (comp( index->getData(), current->getData()))
							swap_node(current, index);
						current = index;
						index = current->getNext();
					}
					current = this->_head;
					index = this->_head->getNext();
				}
			}

			void reverse()
			{
				if (this->_size)
				{
					node_pointer current = this->_head;
					node_pointer next, tmp;
					node_pointer mem = this->_tail->getPrev();

					do
					{
						next = current->getNext();
						tmp = current->getPrev();
						current->getPrev() = current->getNext();
						current->getNext() = tmp;
						current = next;
					}
					while (current != this->_head);
					this->_head = mem;

				}
			}
	};

	template <class T, class Alloc>
	bool operator== (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		listIterator<T> rhs_it = rhs.begin();
		for (listIterator<T> lhs_it = lhs.begin(); lhs_it != lhs.end();lhs_it++)
		{
			if (lhs_it.getIt() != rhs_it.getIt())
				return false;
			rhs_it++;
		}
		return true;
	}

	template <class T, class Alloc>
	bool operator!= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool operator<  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
	{
		listIterator<T> rhs_it = rhs.begin();
		for (listIterator<T> lhs_it = lhs.begin(); lhs_it != lhs.end();lhs_it++)
		{
			if (lhs_it.getIt() < rhs_it.getIt())
				return true;
		}
		return false;
	}

	template <class T, class Alloc>
	bool operator<= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
	{
		return (lhs < rhs || lhs == rhs);
	}

	template <class T, class Alloc>
	bool operator>  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
	{
		return !(lhs < rhs);
	}

	template <class T, class Alloc>
	bool operator>= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
	{
		return !(lhs <= rhs);
	}

	template <class T, class Alloc>
  	void swap (list<T,Alloc>& x, list<T,Alloc>& y)
	{
		x.swap(y);
	}
}

#endif