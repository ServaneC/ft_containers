/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 13:59:37 by schene            #+#    #+#             */
/*   Updated: 2021/02/23 11:58:54 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_HPP
# define FT_UTILS_HPP

# include <limits>
namespace ft
{	
	template< bool condition, class T = void>
	struct enable_if{}; //nothing defined when not true.

	template<class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};
}

#endif