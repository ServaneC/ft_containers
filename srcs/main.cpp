/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 12:24:39 by schene            #+#    #+#             */
/*   Updated: 2021/01/19 10:11:44 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vector.hpp"

template <typename T>
void	print_vector(ft::vector<T> vec)
{
	for (size_t i = 0; i < vec.size(); i++)
		std::cout << i << " [" << vec[i] << ']' << std::endl;
}


int main()
{
	ft::vector<int> 	v1(5, 1);

	return 0;
}