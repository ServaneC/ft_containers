/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 15:33:29 by schene            #+#    #+#             */
/*   Updated: 2021/02/19 10:54:31 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

// namespace ft
// {
// 	struct IteratorTrait {};

// 	template<typename It>
// 	class ReverseIterator: public It
// 	{
// 		public:
// 			using typename It::value_type;
// 		    using typename It::pointer;
// 		    using typename It::const_pointer;
// 		    using typename It::reference;
// 		    using typename It::const_reference;
// 		    using typename It::difference_type;

// 		public:
// 			ReverseIterator(): It() {}
// 			ReverseIterator(It const &it): It(it) {}
// 			ReverseIterator(ReverseIterator const &other): It(other.it) {}
// 			ReverseIterator &operator=(ReverseIterator const &other) 
// 			{
// 				this->it = other.it;
// 				return (*this);
// 			}

// 			reference operator*() 
// 			{
// 				It tmp(*this);
// 				return (*--tmp);
// 			}

// 			const_reference operator*() const 
// 			{
// 				It tmp(*this);
// 				return (*--tmp);
// 			}

// 			pointer operator->() {
// 				It tmp(*this);
// 				return (&*--tmp);
// 			}

// 			const_pointer operator->() const 
// 			{
// 				It tmp(*this);
// 				return (&*--tmp);
// 			}

// 			ReverseIterator operator++(int) 
// 			{
// 				ReverseIterator tmp(*this);
// 				operator++();
// 				return (tmp);
// 			}

// 			It &operator++() 
// 			{
// 				return (this->It::operator--());
// 			}

// 			ReverseIterator operator--(int) 
// 			{
// 				ReverseIterator tmp(*this);
// 				operator--();
// 				return (tmp);
// 			}

// 			It &operator--() 
// 			{
// 				return (this->It::operator++());
// 			}
// 	};

// 	template<typename It>
// 	class const_ReverseIterator: public It
// 	{
// 		public:
// 			using typename It::value_type;
// 		    using typename It::pointer;
// 		    using typename It::const_pointer;
// 		    using typename It::reference;
// 		    using typename It::const_reference;
// 		    using typename It::difference_type;

// 		public:
// 			const_ReverseIterator(): It() {}
// 			const_ReverseIterator(It const &it): It(it) {}
// 			const_ReverseIterator(const_ReverseIterator const &other): It(other.it) {}
// 			const_ReverseIterator &operator=(const_ReverseIterator const &other) 
// 			{
// 				this->it = other.it;
// 				return (*this);
// 			}

// 			reference operator*() 
// 			{
// 				It tmp(*this);
// 				return (*--tmp);
// 			}

// 			const_reference operator*() const 
// 			{
// 				It tmp(*this);
// 				return (*--tmp);
// 			}

// 			pointer operator->() {
// 				It tmp(*this);
// 				return (&*--tmp);
// 			}

// 			const_pointer operator->() const 
// 			{
// 				It tmp(*this);
// 				return (&*--tmp);
// 			}

// 			const_ReverseIterator operator++(int) 
// 			{
// 				const_ReverseIterator tmp(*this);
// 				operator++();
// 				return (tmp);
// 			}

// 			It &operator++() 
// 			{
// 				return (this->It::operator--());
// 			}

// 			const_ReverseIterator operator--(int) 
// 			{
// 				const_ReverseIterator tmp(*this);
// 				operator--();
// 				return (tmp);
// 			}

// 			It &operator--() 
// 			{
// 				return (this->It::operator++());
// 			}
// 	};

	
// }

namespace ft
{
	template <class Iterator>
		class ReverseIterator
		{
			public:
				typedef Iterator							iterator_type;
				typedef typename Iterator::value_type		value_type;
				typedef	typename Iterator::difference_type	difference_type;
				typedef typename Iterator::pointer			pointer;
				typedef typename Iterator::reference		reference;

				ReverseIterator(): _base(NULL) {}
				ReverseIterator(const ReverseIterator<iterator_type>& rev):
					_base(rev._base) {}
				ReverseIterator(iterator_type it): _base(it) {}
				~ReverseIterator() {}

				iterator_type	_base;

				iterator_type		base() const
				{
					return this->_base;
				}

				reference			operator*() const
				{
					iterator_type	tmp(this->_base);

					return (*(--tmp));
				}

				pointer				operator->() const
				{
					iterator_type	tmp(this->_base);
					tmp--;

					pointer		ret = tmp.operator->();
					
					return ret;
				}

				ReverseIterator		operator+(difference_type n) const
				{
					ReverseIterator	ret(this->_base - n);

					return ret;
				}

				ReverseIterator&	operator++()
				{
					--this->_base;

					return (*this);
				}

				ReverseIterator		operator++(int)
				{
					ReverseIterator	ret = *this;

					++(*this);
					return ret;
				}

				ReverseIterator&	operator+=(difference_type n)
				{
					this->_base -= n;
					return *this;
				}

				ReverseIterator		operator-(difference_type n) const
				{
					ReverseIterator	ret(this->_base + n);

					return ret;
				}

				ReverseIterator&	operator--()
				{
					++this->_base;

					return (*this);
				}

				ReverseIterator		operator--(int)
				{
					ReverseIterator	ret = *this;

					--(*this);
					return ret;
				}

				ReverseIterator&	operator-=(difference_type n)
				{
					this->_base += n;
					return *this;
				}

				reference			operator[](difference_type n) const
				{
					return this->_base[-n - 1];
				}

				ReverseIterator&	operator=(const ReverseIterator& vec)
				{
					this->_base = vec.base();
					return *this;
				}
		};

	template < class Iterator>
		bool	operator==(const ReverseIterator<Iterator>& l, const ReverseIterator<Iterator>& r)
		{
			return l.base() == r.base();
		}

	template < class Iterator>
		bool	operator!=(const ReverseIterator<Iterator>& l, const ReverseIterator<Iterator>& r)
		{
			return l.base() != r.base();
		}

	template < class Iterator>
		bool	operator<(const ReverseIterator<Iterator>& l, const ReverseIterator<Iterator>& r)
		{
			return l.base() < r.base();
		}

	template < class Iterator>
		bool	operator<=(const ReverseIterator<Iterator>& l, const ReverseIterator<Iterator>& r)
		{
			return l.base() <= r.base();
		}

	template < class Iterator>
		bool	operator>(const ReverseIterator<Iterator>& l, const ReverseIterator<Iterator>& r)
		{
			return l.base() > r.base();
		}

	template < class Iterator>
		bool	operator>=(const ReverseIterator<Iterator>& l, const ReverseIterator<Iterator>& r)
		{
			return l.base() >= r.base();
		}
	
	template < class Iterator>
  		ReverseIterator<Iterator> operator+
			(typename ReverseIterator<Iterator>::difference_type n,
             	const ReverseIterator<Iterator>& rev_it)
		{
			return rev_it + n;
		}

	template < class Iterator>
  		typename ReverseIterator<Iterator>::difference_type operator-
			(const ReverseIterator<Iterator>& lhs,
				const ReverseIterator<Iterator>& rhs)
		{
			return rhs.base() - lhs.base();
		}

	template <class Iterator>
		class const_ReverseIterator
		{
			public:
				typedef	typename Iterator::iterator_not_const	iterator_not_const;
				typedef Iterator								iterator_type;
				typedef typename Iterator::value_type			value_type;
				typedef	typename Iterator::difference_type		difference_type;
				typedef typename Iterator::pointer				pointer;
				typedef typename Iterator::reference			reference;

				const_ReverseIterator(): _base(NULL) {}
				const_ReverseIterator(const const_ReverseIterator<iterator_type>& rev):
					_base(rev._base) {}
				const_ReverseIterator(const ReverseIterator<iterator_not_const>& rev):
					_base(rev._base) {}
				const_ReverseIterator(iterator_type it): _base(it) {}
				const_ReverseIterator(iterator_not_const it):  _base(iterator_type(it)) {}
				~const_ReverseIterator() {}
				
				iterator_type								_base;

				iterator_type		base() const
				{
					return this->_base;
				}

				reference			operator*() const
				{
					iterator_type	tmp(this->_base);

					return (*(--tmp));
				}

				pointer				operator->() const
				{
					iterator_type	tmp(this->_base);
					tmp--;

					pointer		ret = tmp.operator->();
					
					return ret;
				}

				const_ReverseIterator		operator+(difference_type n) const
				{
					const_ReverseIterator	ret(this->_base - n);

					return ret;
				}

				const_ReverseIterator&	operator++()
				{
					--this->_base;

					return (*this);
				}

				const_ReverseIterator		operator++(int)
				{
					const_ReverseIterator	ret = *this;

					++(*this);
					return ret;
				}

				const_ReverseIterator&	operator+=(difference_type n)
				{
					this->_base -= n;
					return *this;
				}

				const_ReverseIterator		operator-(difference_type n) const
				{
					const_ReverseIterator	ret(this->_base + n);

					return ret;
				}

				const_ReverseIterator&	operator--()
				{
					++this->_base;

					return (*this);
				}

				const_ReverseIterator		operator--(int)
				{
					const_ReverseIterator	ret = *this;

					--(*this);
					return ret;
				}

				const_ReverseIterator&	operator-=(difference_type n)
				{
					this->_base += n;
					return *this;
				}

				reference			operator[](difference_type n) const
				{
					return this->_base[-n - 1];
				}

				const_ReverseIterator&	operator=(const const_ReverseIterator& vec)
				{
					this->_base = vec.base();
					return *this;
				}

		};

	template < class Iterator>
		bool	operator==(const const_ReverseIterator<Iterator>& l, const const_ReverseIterator<Iterator>& r)
		{
			return l.base() == r.base();
		}

	template < class Iterator>
		bool	operator!=(const const_ReverseIterator<Iterator>& l, const const_ReverseIterator<Iterator>& r)
		{
			return l.base() != r.base();
		}

	template < class Iterator>
		bool	operator<(const const_ReverseIterator<Iterator>& l, const const_ReverseIterator<Iterator>& r)
		{
			return l.base() < r.base();
		}

	template < class Iterator>
		bool	operator<=(const const_ReverseIterator<Iterator>& l, const const_ReverseIterator<Iterator>& r)
		{
			return l.base() <= r.base();
		}

	template < class Iterator>
		bool	operator>(const const_ReverseIterator<Iterator>& l, const const_ReverseIterator<Iterator>& r)
		{
			return l.base() > r.base();
		}

	template < class Iterator>
		bool	operator>=(const const_ReverseIterator<Iterator>& l, const const_ReverseIterator<Iterator>& r)
		{
			return l.base() >= r.base();
		}
	
	template < class Iterator>
  		const_ReverseIterator<Iterator> operator+
			(typename const_ReverseIterator<Iterator>::difference_type n,
             	const const_ReverseIterator<Iterator>& rev_it)
		{
			return rev_it + n;
		}

	template < class Iterator>
  		typename const_ReverseIterator<Iterator>::difference_type operator-
			(const const_ReverseIterator<Iterator>& lhs,
				const const_ReverseIterator<Iterator>& rhs)
		{
			return rhs.base() - lhs.base();
		}


		//left const right not const

	template < class Iterator>
		bool	operator==(const const_ReverseIterator<Iterator>& l, const ReverseIterator<typename Iterator::iterator_not_const>& r)
		{
			return l.base() == r.base();
		}

	template < class Iterator>
		bool	operator!=(const const_ReverseIterator<Iterator>& l, const ReverseIterator<typename Iterator::iterator_not_const>& r)
		{
			return l.base() != r.base();
		}

	template < class Iterator>
		bool	operator<(const const_ReverseIterator<Iterator>& l, const ReverseIterator<typename Iterator::iterator_not_const>& r)
		{
			return l.base() < r.base();
		}

	template < class Iterator>
		bool	operator<=(const const_ReverseIterator<Iterator>& l, const ReverseIterator<typename Iterator::iterator_not_const>& r)
		{
			return l.base() <= r.base();
		}

	template < class Iterator>
		bool	operator>(const const_ReverseIterator<Iterator>& l, const ReverseIterator<typename Iterator::iterator_not_const>& r)
		{
			return l.base() > r.base();
		}

	template < class Iterator>
		bool	operator>=(const const_ReverseIterator<Iterator>& l, const ReverseIterator<typename Iterator::iterator_not_const>& r)
		{
			return l.base() >= r.base();
		}
	
	template < class Iterator>
  		const_ReverseIterator<Iterator> operator+
			(typename const_ReverseIterator<Iterator>::difference_type n,
             	const ReverseIterator<typename Iterator::iterator_not_const>& rev_it)
		{
			return rev_it + n;
		}

	template < class Iterator>
  		typename const_ReverseIterator<Iterator>::difference_type operator-
			(const const_ReverseIterator<Iterator>& lhs,
				const ReverseIterator<typename Iterator::iterator_not_const>& rhs)
		{
			return rhs.base() - lhs.base();
		}

	// left not const, right const
	template < class Iterator>
		bool	operator==(const ReverseIterator<typename Iterator::iterator_not_const>& l, const const_ReverseIterator<Iterator>& r)
		{
			return l.base() == r.base();
		}

	template < class Iterator>
		bool	operator!=(const ReverseIterator<typename Iterator::iterator_not_const>& l, const const_ReverseIterator<Iterator>& r)
		{
			return l.base() != r.base();
		}

	template < class Iterator>
		bool	operator<(const ReverseIterator<typename Iterator::iterator_not_const>& l, const const_ReverseIterator<Iterator>& r)
		{
			return l.base() < r.base();
		}

	template < class Iterator>
		bool	operator<=(const ReverseIterator<typename Iterator::iterator_not_const>& l, const const_ReverseIterator<Iterator>& r)
		{
			return l.base() <= r.base();
		}

	template < class Iterator>
		bool	operator>(const ReverseIterator<typename Iterator::iterator_not_const>& l, const const_ReverseIterator<Iterator>& r)
		{
			return l.base() > r.base();
		}

	template < class Iterator>
		bool	operator>=(const ReverseIterator<typename Iterator::iterator_not_const>& l, const const_ReverseIterator<Iterator>& r)
		{
			return l.base() >= r.base();
		}

	template < class Iterator>
  		typename const_ReverseIterator<Iterator>::difference_type operator-
			(const ReverseIterator<typename Iterator::iterator_not_const>& lhs,
				const const_ReverseIterator<Iterator>& rhs)
		{
			return rhs.base() - lhs.base();
		}
}

#endif
