/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node_pair.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 10:47:41 by schene            #+#    #+#             */
/*   Updated: 2021/02/18 12:57:56 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_PAIR_HPP
# define NODE_PAIR_HPP

namespace ft
{
	template<class Key, class T>
	class	pair
	{
		public:
			pair(const Key& k = Key(), const T& v = T()): first(k), second(v) {}
			~pair() {}

			pair&	operator=(const pair& p)
			{
				this->first = p.first;
				this->second = p.second;

				return *this;
			}

			Key	first;
			T	second;
	};

	template<class Key, class T>
	class node_pair
	{
		// private:
		// 	ft::pair<Key, T>	member;

		public:
			node_pair(): next(NULL), prev(NULL), parent(NULL) { }
			node_pair(const node_pair& el):
					member(el.member), next(el.next), prev(el.prev), parent(el.parent) { }
			
			node_pair(const pair<Key, T>& pair, node_pair* next = NULL, node_pair* prev = NULL, node_pair* parent = NULL) :
				member(pair), next(next), prev(prev), parent(parent) { }
		
			~node_pair() { }

			ft::pair<Key, T>	member;
			node_pair*			next;
			node_pair*			prev;
			node_pair*			parent;

			node_pair&					operator=(const node_pair& el)
			{
				this->member = el.getMember();
				this->_next = el.next;
				this->_prev = el.prev;
				this->_parent = el.parent;
				return *this;
			}

			ft::pair<Key, T>&			getMember()
			{
				return this->member;
			}

			const ft::pair<Key, T>&	getMember() const
			{
				return this->member;
			}

			node_pair*	getNext(const node_pair* source = NULL) const
			{
				node_pair<Key, T>*	tmp;

				if (!this->next || source == this->next)	//end of branch, looking recursively for next elem
					return this->parent->getNext(this);
				else if (source == this->prev && this->prev)// prev branch ended, return this
					return source->parent;
				else //only case left : return lowest node from next branch
				{
					tmp = this->next;
					while(tmp->prev)
						tmp = tmp->prev;
					return tmp;
				}
			}

			node_pair*	getPrev(const node_pair* source = NULL) const
			{
				node_pair<Key, T>*	tmp;
				
				if (source && source == this->next)
					return source->parent;
				if (source && source == this->prev)
					return this->parent->getPrev(this);
				else
				{
					if (!this->prev)
						return this->parent->getPrev(this);
					tmp = this->prev;
					while(tmp->next)
						tmp = tmp->next;
					return tmp;
				}
			}
	};

	template<class Key, class T>
		bool	operator==(const ft::pair<Key, T>& left, const ft::pair<Key, T>& right)
		{
			return left.first == right.first && left.second == right.second;
		}

	template<class Key, class T>
		bool	operator==(ft::pair<Key, T>& left, ft::pair<Key, T>& right)
		{
			return left.first == right.first && left.second == right.second;
		}
		
	template<class Key, class T>
		bool	operator<(const ft::pair<Key, T>& left, const ft::pair<Key, T>& right)
		{
			return left.first < right.first || (left.first == right.first && left.second < right.second);
		}

	template<class Key, class T>
		bool	operator!=(const ft::pair<Key, T>& left, const ft::pair<Key, T>& right)
		{
			return (!(left == right));
		}

	template<class Key, class T>
		bool	operator>(const ft::pair<Key, T>& left, const ft::pair<Key, T>& right)
		{
			return (right < left);
		}

	template<class Key, class T>
		bool	operator<=(const ft::pair<Key, T>& left, const ft::pair<Key, T>& right)
		{
			return (!(right < left));
		}

	template<class Key, class T>
		bool	operator>=(const ft::pair<Key, T>& left, const ft::pair<Key, T>& right)
		{
			return (!(left < right));
		}
}

#endif