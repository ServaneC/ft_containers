/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 12:24:39 by schene            #+#    #+#             */
/*   Updated: 2021/01/12 09:33:18 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vector.hpp"
#include <iostream>

int main()
{
	size_t 				size = 5;
	ft::Vector<int> 	v1(size, 1);

	for (size_t i = 0; i < v1.size(); i++)
		std::cout << i << " -> " << v1[i] << std::endl;
	std::cout << "size = " << v1.size() << std::endl;
	std::cout << "capacity = " << v1.capacity() << std::endl;
	std::cout << "max_size = " << v1.max_size() << std::endl;
	std::cout << "empty ? " << std::boolalpha << v1.empty() << std::endl;

	std::cout << std::endl << "------------------------------------------" << std::endl;

	std::cout << "reserve 10" << std::endl;
	v1.reserve(10);
	std::cout << "size = " << v1.size() << std::endl;
	std::cout << "capacity = " << v1.capacity() << std::endl;
	for (size_t i = 0; i < v1.size(); i++)
		std::cout << i << " -> " << v1[i] << std::endl;
	
	std::cout << std::endl << "------------------------------------------" << std::endl;

	std::cout << "resize 8 (valeur 2)" << std::endl;
	v1.resize(8, 2);
	std::cout << "size = " << v1.size() << std::endl;
	std::cout << "capacity = " << v1.capacity() << std::endl;
	for (size_t i = 0; i < v1.size(); i++)
		std::cout << i << " -> " << v1[i] << std::endl;

	std::cout << std::endl << "------------------------------------------" << std::endl;

	std::cout << "resize 4 (pas de valeur)" << std::endl;
	v1.resize(4);
	std::cout << "size = " << v1.size() << std::endl;
	std::cout << "capacity = " << v1.capacity() << std::endl;
	for (size_t i = 0; i < v1.size(); i++)
		std::cout << i << " -> " << v1[i] << std::endl;
	
	std::cout << std::endl << "------------------------------------------" << std::endl;

	std::cout << "push_back a 42" << std::endl;
	v1.push_back(42);
	std::cout << "size = " << v1.size() << std::endl;
	std::cout << "capacity = " << v1.capacity() << std::endl;
	for (size_t i = 0; i < v1.size(); i++)
		std::cout << i << " -> " << v1[i] << std::endl;
	
	std::cout << std::endl << "------------------------------------------" << std::endl;

	std::cout << "pop_back the 42" << std::endl;
	v1.pop_back();
	std::cout << "size = " << v1.size() << std::endl;
	std::cout << "capacity = " << v1.capacity() << std::endl;
	for (size_t i = 0; i < v1.size(); i++)
		std::cout << i << " -> " << v1[i] << std::endl;
	
	std::cout << std::endl << "------------------------------------------" << std::endl;
	
	std::cout << "call to clear" << std::endl;
	v1.clear();
	std::cout << "size = " << v1.size() << std::endl;
	std::cout << "capacity = " << v1.capacity() << std::endl;
	for (size_t i = 0; i < v1.size(); i++)
		std::cout << i << " -> " << v1[i] << std::endl;
	
	std::cout << std::endl << "------------------------------------------" << std::endl;
	return 0;
}