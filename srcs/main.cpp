/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 12:24:39 by schene            #+#    #+#             */
/*   Updated: 2021/02/01 18:02:47 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "List.hpp"
#include <list>
#include <iterator>

// template <typename T>
// void	print_vector(ft::vector<T> vec)
// {
// 	for (size_t i = 0; i < vec.size(); i++)
// 		std::cout << i << " [" << vec[i] << ']' << std::endl;
// }

template <class Container>
void	printContainer(Container c)
{
	int								n;
	typename Container::iterator	i;
	
	i = c.begin();
	n = 0;
	std::cout << "[";
	while (i != c.end())
	{
		if (n != 0)
			std::cout << ", ";
		std::cout << *i;
		i++;
		n++;
	}
	std::cout << "]" << std::endl;
	std::cout << std::endl;
}

int main()
{
	
	
	return 0;
}