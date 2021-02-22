/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 12:24:39 by schene            #+#    #+#             */
/*   Updated: 2021/02/18 12:19:36 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Map.hpp"
#include <list>
#include <iterator>
#include <map>
#include <iostream>
#include <unordered_map>

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

template<typename K, typename V>
void print_map(std::map<K,V> const &m)
{
	for (typename std::map<K,V>::const_iterator it = m.begin(); it != m.end(); ++it)
        std::cout << "{" << (*it).first << ": " << (*it).second << "} ";
	std::cout << std::endl;
}

template<typename K, typename V>
void print_mymap(ft::map<K,V> const &m)
{
	for (typename ft::map<K,V>::const_iterator it = m.begin(); it != m.end(); it++)
        std::cout << "{" << (*it).first << ": " << (*it).second << "} ";
	std::cout << std::endl;
	
}

int main()
{
	return 0;
}