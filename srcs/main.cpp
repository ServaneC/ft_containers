/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 12:24:39 by schene            #+#    #+#             */
/*   Updated: 2021/02/01 10:34:10 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "List.hpp"

// template <typename T>
// void	print_vector(ft::vector<T> vec)
// {
// 	for (size_t i = 0; i < vec.size(); i++)
// 		std::cout << i << " [" << vec[i] << ']' << std::endl;
// }

template <typename T>
void	print_list(ft::list<T> lst)
{
	for (ft::listIterator<T> it = lst.begin(); it != lst.end(); it++)
		std::cout << it.getIt()->data << " ";
	std::cout << std::endl;
}

int main()
{
	ft::list<int>	lst1;
	// ft::list<int>	lst2(5, 42);
	
	for (int i = 0; i < 10; ++i)
		lst1.push_back(i);
	std::cout << "lst1 = "; print_list(lst1);
	std::cout << "size = " << lst1.size() << std::endl;
	// std::cout << "lst2 = "; print_list(lst2);
	// std::cout << "size = " << lst2.size() << std::endl;

	// ft::listIterator<int>	pos = lst2.begin();
	// pos++;
	// pos++;

	// lst2.insert(pos, 3, 2);

	// pos++;
	// lst2.insert(pos, 1);

	// std::cout << "lst1 = "; print_list(lst1);
	// std::cout << "size = " << lst1.size() << std::endl;
	// std::cout << "lst2 = "; print_list(lst2);
	// std::cout << "size = " << lst2.size() << std::endl;

	// std::cout << "lst2.assign(lst1.begin(), pos);" << std::endl;
	// pos = lst1.begin();
	// pos++;
	// pos++;
	// pos++;
	// lst2.assign(lst1.begin(), pos);

	// std::cout << "lst1 = "; print_list(lst1);
	// std::cout << "size = " << lst1.size() << std::endl;
	// std::cout << "lst2 = "; print_list(lst2);
	// std::cout << "size = " << lst2.size() << std::endl;

	ft::listIterator<int>	first = lst1.begin();
	first++;
	first++;
	first++;

	ft::listIterator<int>	last = lst1.end();
	last--;
	last--;
	last--;	
	std::cout << "lst1.erase(lst1.begin(), first);" << std::endl;
	lst1.erase(lst1.begin(), first);
	
	std::cout << "lst1 = "; print_list(lst1);
	std::cout << "size = " << lst1.size() << std::endl;
	// std::cout << "lst2 = "; print_list(lst2);
	// std::cout << "size = " << lst2.size() << std::endl;

	return 0;
}