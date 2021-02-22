/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 09:46:09 by schene            #+#    #+#             */
/*   Updated: 2021/02/22 10:36:24 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include "./utils/Reverse_iterator.hpp"
# include "./utils/ft_utils.hpp"
# include "../test/color.h"
# include "./utils/Node_pair.hpp"
# include <iostream>
# include <cstdlib>

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>,
           	class Alloc = std::allocator<std::pair<const Key,T> > > 
	class map;

	template<class K, class V>
	class MapIterator
	{
		public:
				typedef ft::pair<K, V>				value_type;
				typedef	node_pair<K, V>				node_type;
				typedef	value_type*					pointer;
				typedef	const value_type*			const_pointer;
				typedef value_type&					reference;
				typedef const value_type&			const_reference;
				typedef	std::ptrdiff_t				difference_type;
				// typedef	const MapIterator			const_iterator;


				static const bool			is_not_const;
		
		protected:
				node_type*			it;

		public:
				MapIterator(): it(NULL) {}
				MapIterator(node_type* ptr) : it(ptr) {}
				MapIterator(const MapIterator& vec): it(vec.getIt()) {}
				~MapIterator() {}
				
				node_type*			getIt() const
				{
					return this->it;
				}

				reference		operator*()
				{
					return this->it->getMember();
				}

				value_type*		operator->()
				{
					return &(this->operator*());
				}

				MapIterator	operator++()
				{
					this->it = this->it->getNext();
					return *this;
				}

				MapIterator	operator++(int)
				{
					MapIterator	tmp(*this);

					this->it = this->it->getNext();
					return tmp;
				}

				MapIterator	operator--()
				{
					this->it = this->it->getPrev();
					return *this;
				}

				MapIterator	operator--(int)
				{
					MapIterator	tmp(*this);

					this->it = this->it->getPrev();
					return tmp;
				}

				bool 			operator==(const MapIterator& right) const 
				{
					return (this->it == right.getIt());
				}

				bool 			operator!=(const MapIterator& right) const 
				{
					bool ret = (*this == right);

					return (!ret);
				}
	};

		template<class K, class V>
		class const_MapIterator
		{
			public:
				typedef	MapIterator<K, V>		iterator_not_const;
				typedef const pair<K, V>		value_type;
				typedef	const node_pair<K, V>	node_type;
				typedef	value_type*				pointer;
				typedef	const value_type*		const_pointer;
				typedef value_type&				reference;
				typedef const value_type&		const_reference;
				typedef	::std::ptrdiff_t		difference_type;

				static const bool			is_not_const;
			
			protected:
				node_type*			it;

			public:
				const_MapIterator(): it(NULL) {}
				const_MapIterator(const node_type* ptr) : it(ptr) {}
				const_MapIterator(const const_MapIterator& vec): it(vec.getIt())
				{
				}
				const_MapIterator(const MapIterator<K, V>& vec): it(vec.getIt())
				{
				}
				~const_MapIterator() {}


				const_MapIterator& operator=(const const_MapIterator& vec)
				{
					this->it = vec.getIt();
					return *this;
				}

				node_type*			getIt() const
				{
					return this->it;
				}

				reference		operator*()
				{
					return this->it->getMember();
				}

				value_type*		operator->()
				{
					return &(this->operator*());
				}

				const_MapIterator	operator++()
				{
					this->it = this->it->getNext();
					return *this;
				}

				const_MapIterator	operator++(int)
				{
					const_MapIterator	tmp(*this);

					this->it = this->it->getNext();
					return tmp;
				}

				const_MapIterator	operator--()
				{
					this->it = this->it->getPrev();
					return *this;
				}

				const_MapIterator	operator--(int)
				{
					const_MapIterator	tmp(*this);

					this->it = this->it->getPrev();
					return tmp;
				}

				bool 			operator==(const const_MapIterator& right) const 
				{
					return (this->it == right.getIt());
				}

				bool 			operator!=(const const_MapIterator& right) const 
				{
					bool ret = (*this == right);

					return (!ret);
				}
		};

	template < class Key, class T, class Compare, class Alloc > 
	class map
	{
		public:
			typedef	Key											key_type;
			typedef	T											mapped_type;
			typedef ft::pair<key_type, mapped_type>				value_type;
			typedef node_pair<key_type, mapped_type>			node_type;
			typedef	Compare										key_compare;
			typedef	std::allocator<node_type>					allocator_type;
			typedef value_type&									reference;
			typedef const value_type&							const_reference;
			typedef value_type*									pointer;
			typedef const value_type*							const_pointer;
			typedef	MapIterator<key_type, mapped_type>			iterator;
			typedef const_MapIterator<key_type, mapped_type>	const_iterator;
			typedef ReverseIterator<iterator>					reverse_iterator;
			typedef const_ReverseIterator<const_iterator>		const_reverse_iterator;
			typedef std::ptrdiff_t								difference_type;
			typedef	size_t										size_type;
			
			class value_compare
			{
				friend class map;

				protected:
					Compare comp;
					value_compare(Compare c): comp(c) {}

				public:
					bool	operator()(const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
			};
			
		private:
			node_type*		_root;
			node_type		_begin;
			node_type		_end;
			key_compare		_comp;
			size_type		_size;
			allocator_type	_alloc;

			void					reset_map()
			{
				this->_size = 0;
				this->_root = &this->_end;
				this->_begin.parent = &this->_end;
				this->_begin.next = NULL;
				this->_begin.prev = NULL;
				this->_end.parent = NULL;
				this->_end.next = NULL;
				this->_end.prev = &this->_begin;
			}

			void					insert_first_elem(const value_type& val)
			{
				this->_root = _alloc.allocate(1);
				_alloc.construct(this->_root, val);
				this->_root->next = &this->_end;
				this->_root->prev = &this->_begin;
				this->_end.parent = this->_root;
				this->_begin.parent = this->_root;
				this->_end.prev = NULL;
				this->_size = 1;
			}

			void cleantree(node_type* root)
			{
				if (root->prev)
					cleantree(root->prev);
				if (root->next)
					cleantree(root->next);
				if (root->getMember().first)
				{
					this->_alloc.destroy(root);
					this->_alloc.deallocate(root, 1);
					this->_size--;
				}
			}

			node_type*				lower_node(const key_type& k)
			{
				node_type*	tmp;
				node_type* lowest;

				tmp = this->_root;
				lowest = (--(this->end())).getIt();
				while(tmp && tmp != &this->_begin && tmp != &this->_end)
				{
					if (!(this->key_comp()(lowest->getMember().first, tmp->getMember().first))
						&& !(this->key_comp()(tmp->getMember().first, k)))
						lowest = tmp;
					if (this->key_comp()(tmp->getMember().first, k))
						tmp = tmp->next;
					else
						tmp = tmp->prev;
				}
				if ((lowest == this->_end.parent)
					&& (this->key_comp()(lowest->getMember().first, k)))
					return &this->_end;
				return (lowest);
			}

		public:

			//---------------- CONSTRUCTROR ----------------

			explicit map (const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()) : _comp(comp), _alloc(alloc) 
			{ 
				this->reset_map();
			}
			
			template <class InputIter>
			map (InputIter first,
					typename ft::enable_if<!std::numeric_limits<InputIter>::is_integer, InputIter>::type last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()) : _comp(comp), _alloc(alloc) 
			{
				this->reset_map();
				this->insert(first, last);
			}
			
			map (const map& x) :  _comp(x._comp)
			{
				this->reset_map();
				this->insert(x.begin(), x.end());
			}

			//---------------- DESTRUCTOR ----------------
			~map()
			{
				this->clear();
			}

			//---------------- OPERATOR = ----------------
			map& operator= (const map& x)
			{
				this->clear();
				this->insert(x.begin(), x.end());
				return *this;
			}

			//---------------- ITERATORS ---------------
			iterator				begin()
			{
				return iterator(this->_begin.parent);
			}

			const_iterator			begin() const
			{
				return const_iterator(this->_begin.parent);
			}

			iterator				end()
			{
				iterator	ret(&this->_end);

				return ret;
			}

			const_iterator			end() const
			{
				const_iterator	ret(&this->_end);

				return ret;
			}

			reverse_iterator rbegin()
			{
				return reverse_iterator(this->end());
			}

			const_reverse_iterator rbegin() const
			{
				return const_reverse_iterator(this->end());
			}

			reverse_iterator rend()
			{
				return reverse_iterator(this->begin());
			}

			const_reverse_iterator rend() const
			{
				return const_reverse_iterator(this->begin());
			}
			//---------------- CAPACITY ----------------
			bool empty() const
			{
				if (this->_size)
					return false;
				return true;
			}

			size_type size() const
			{
				return this->_size;
			}

			size_type max_size() const
			{
				return std::numeric_limits<difference_type>::max() / 20;
				// return this->_alloc.max_size() ;
			}
			//---------------- ELEMENT ACCESS ----------
			mapped_type& operator[] (const key_type& k)
			{
				iterator it = this->find(k);

				if (it != this->end())
					return it->second;
				
				pair<iterator, bool>	ret(this->insert(value_type(k)));
				return ret.first->second;
			}
			
			//---------------- MODIFIER ----------------
			
			pair<iterator,bool> insert (const value_type& val)
			{
				if (!this->_size)
				{
					insert_first_elem(val);
					return pair<iterator, bool>(this->begin(), true);
				}
				node_type*	tmp = this->_root;
				node_type*	beg = &this->_begin;
				node_type*	end = &this->_end;

				while (tmp && tmp != beg && tmp != end)
				{
					if (this->_comp(tmp->getMember().first, val.first))
					{
						if (tmp->next)
							tmp = tmp->next;
						else
							return pair<iterator, bool>(this->insert(iterator(tmp), val), true);
					}
					else if (this->_comp(val.first, tmp->getMember().first))
					{
						if (tmp->prev)
							tmp = tmp->prev;
						else
							return pair<iterator, bool>(this->insert(iterator(tmp), val), true);
					}
					else
						return pair<iterator, bool>(tmp, false);
				}
				if (tmp == beg)
					return pair<iterator, bool>(this->insert(iterator(&this->_begin), val), true);
				else
					return pair<iterator, bool>(this->insert(iterator(this->_end.parent), val), true);
			}

			iterator insert (iterator position, const value_type& val)
			{
				if (!this->size())
				{
					insert_first_elem(val);
					return this->begin();
				}
				iterator	ret = find(val.first);

				if (ret != this->end())
					return ret;
				if (((position == iterator(&this->_begin)) && (this->_comp(val.first, this->begin()->first)))
					|| ((position == iterator(this->_end.parent)) && (this->_comp(position->first, val.first)))
					|| ((this->_comp(position->first, val.first))
							&& (!(position.getIt()->next)))
					|| ((this->_comp(val.first, position->first))
							&& (!(position.getIt()->prev))))
				{
					node_type*	tmp = _alloc.allocate(1);
					_alloc.construct(tmp, val);
					if (position == iterator(&this->_begin))
					{
						tmp->parent = this->_begin.parent;
						tmp->prev =&this->_begin;
						tmp->parent->prev = tmp;
						this->_begin.parent = tmp;
					}
					else if (position == iterator(&this->_end))
					{
						position--;
						delete tmp;
						return(this->insert(position, val));
					}
					else 
					{
						tmp->parent = position.getIt();
						if (this->_comp(val.first, position->first)) 
							tmp->parent->prev = tmp;
						else 
						{
							
							tmp->next = tmp->parent->next;
							if (tmp->next)
								tmp->next->parent = tmp;
							tmp->parent->next = tmp;
						}
					}
					this->_size++;
					return (iterator(tmp));
				}
				pair<iterator, bool>	inserted = this->insert(val);
				return inserted.first;
			}

			template <class InputIter>
				void insert(InputIter first,
					typename ft::enable_if<!std::numeric_limits<InputIter>::is_integer, InputIter>::type last)
			{
				while (first != last && first != this->end())
				{
					this->insert(*first);
					first++;
				}
			}

			void					erase(iterator position)
			{
				if (this->_size == 1) 
				{
					this->clear();
					return ;
				}
				
				node_type*	ptr(position.getIt());
				node_type*	next(ptr->prev);
				node_type*	prev(ptr->prev);
				node_type*	parent(ptr->parent);

				if (prev != &this->_begin) 
				{
					if (parent) 
					{
						if (prev)
						{
							if (parent->next == ptr)
								parent->next = prev;
							else
								parent->prev = prev;
							prev->parent = parent;
							while(next->next)
								next = next->next;
							next->next = ptr->next;
							ptr->next->parent = next;
						}
						else
						{
							if (parent->next == ptr)
								parent->next = ptr->next;
							else
								parent->prev = ptr->next;
							ptr->next->parent = parent;
						}
					}
					else 
					{
						std::cout << "8" << std::endl;
						this->_root = prev;
						while(next->next)
							next = next->next;
						next->next = ptr->next;
						ptr->next->parent = next;
					}
				}
				else
				{
					if (parent) 
					{
						if (ptr->next)
						{
							parent->prev = ptr->next;
							ptr->next->parent = parent;
							next = ptr->next;
							while(next->prev)
								next = next->prev;
							next->prev = &this->_begin;
							this->_begin.parent = next;
						}
						else
						{
							parent->prev = &this->_begin;
							this->_begin.parent = parent;
						}
					}
					else 
					{
						next = ptr->next;
						this->_root = next;
						next->parent = NULL;
						while (next->prev)
							next = next->prev;
						next->prev = &this->_begin;
						this->_begin.parent = next;
					}
				}
				this->_size--;
				this->_alloc.destroy(position.getIt());
				this->_alloc.deallocate(position.getIt(), 1);
				return ;
			}

			size_type erase (const key_type& k)
			{
				iterator to_erase = this->find(k);

				if (to_erase != this->end())
				{
					this->erase(to_erase);
					return 1;
				}
				return 0;
			}

     		void erase (iterator first, iterator last)
			{
				iterator tmp(first);
				
				while (first != last && tmp.getIt()->getNext())
				{
					++tmp;
					erase((*first).first);
					first = tmp;
				}
			}

			void swap (map& x)
			{
				map<key_type, mapped_type> tmp = *this;
				*this = x;
				x = tmp;
			}

			void clear()
			{
				this->cleantree(this->_root);
				this->reset_map();
			}
			//---------------- OBSERVERS ---------------
			key_compare key_comp() const
			{
				return this->_comp;
			}

			value_compare value_comp() const
			{
				return value_compare(this->_comp);
			}
			//---------------- OPERATIONS ---------------
			iterator find (const key_type& k)
			{
				node_type*		ptr(this->_root);

				while(ptr && ptr != &this->_begin && ptr != &this->_end)
				{
					if (this->_comp(k, ptr->getMember().first))
						ptr = ptr->prev;
					else if (this->_comp(ptr->getMember().first, k))
						ptr = ptr->next;
					else
						return iterator(ptr);
				}
				return this->end();
			}

			const_iterator find (const key_type& k) const
			{
				node_type*		ptr(this->_root);

				while(ptr && ptr != &this->_begin && ptr != &this->_end)
				{
					if (this->_comp(k, ptr->getMember().first))
						ptr = ptr->prev;
					else if (this->_comp(ptr->getMember().first, k))
						ptr = ptr->next;
					else
						return const_iterator(ptr);
				}
				return this->end();
			}

			size_type count (const key_type& k) const
			{
				if (this->find(k) != this->end())
					return 1;
				return 0;;
			}

			iterator				lower_bound(const key_type& k)
			{
				return iterator(this->lower_node(k));
			}

			const_iterator			lower_bound(const key_type& k) const
			{
				return const_iterator(this->lower_node(k));
			}

			iterator				upper_bound(const key_type& k)
			{
				iterator	ret(this->lower_bound(k));

				if (ret->first == k)
					++ret;
				return ret;
			}

			const_iterator			upper_bound(const key_type& k) const
			{
				const_iterator	ret(lower_bound(k));

				if (ret->first == k)
					return ++ret;
				return ret;
			}

			pair<const_iterator,const_iterator> equal_range (const key_type& k) const
			{
				return pair<const_iterator, const_iterator>(this->lower_bound(k), this->upper_bound(k));
			}
	
			pair<iterator,iterator>             equal_range (const key_type& k)
			{
				return pair<iterator, iterator>(this->lower_bound(k), this->upper_bound(k));
			}
	};

	template < class Key, class T, class Compare, class Alloc >
	bool	operator==( const ft::map<Key,T,Compare,Alloc>& lhs,
    	const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		if (lhs.size() != rhs.size())
			return false;
		typename map<Key, T>::const_iterator rhsit = rhs.begin();
		for (typename map<Key, T>::const_iterator lhsit = lhs.begin(); lhsit != lhs.end();lhsit++)
		{
			if (*lhsit != *rhsit)
				return false;
			rhsit++;
		}
		return true;
	}

	template< class Key, class T, class Compare, class Alloc >
	bool	operator!=( const ft::map<Key,T,Compare,Alloc>& lhs,
		const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return !(lhs == rhs);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs,
         const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		typename map<Key, T, Compare>::const_iterator	it = rhs.begin();
		typename map<Key, T, Compare>::const_iterator	i = lhs.begin();
		
		while (it != rhs.end() && i != lhs.end() && *it == *i)
		{
			it++;
			i++;
		}
		if (it == rhs.end() && i != lhs.end())
			return false;
		if (i == lhs.end() && it != rhs.end())
			return true;
		return (*i < *it);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs,
        const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return (lhs == rhs || lhs < rhs);
	}
	
	template< class Key, class T, class Compare, class Alloc >
	bool operator>(const ft::map<Key,T,Compare,Alloc>& lhs,
    const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return (rhs < lhs);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs,
        const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return (lhs == rhs || lhs > rhs);
	}
	
	template< class Key, class T, class Compare, class Alloc >
	void swap( ft::map<Key,T,Compare,Alloc>& lhs, 
        ft::map<Key,T,Compare,Alloc>& rhs )
	{
		lhs.swap(rhs);
	}
}

#endif