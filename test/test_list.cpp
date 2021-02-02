/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_list.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 18:03:28 by schene            #+#    #+#             */
/*   Updated: 2021/02/02 11:25:48 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iomanip>
#include <list>
#include <limits>
#include "utils.hpp"
#include "color.h"
#include "../srcs/List.hpp"

template <class T>
void	error_diff(ft::list<T> mylst, std::list<T> list)
{
	std::cout << _RED << "ERROR - DIFF" << _END << std::endl;
	std::cout << std::setw(30) << "mylst.empty(): " << mylst.empty() << std::endl;
	std::cout << std::setw(30) << "list.empty(): " << list.empty() << std::endl;
	std::cout << std::setw(30) << "mylst.size(): " << mylst.size() << std::endl;
	std::cout << std::setw(30) << "list.size(): " << list.size() << std::endl;
	std::cout << std::setw(30) << "mylst : ";
	printContainer(mylst);
	std::cout << std::setw(30) << "list : ";
	printContainer(list);
}

template <class T>
void	compareList(std::string function, ft::list<T> mylst, std::list<T> list)
{
	std::cout << std::setw(30) << function << ": ";
	if (mylst.empty() != list.empty())
		error_diff(mylst, list);
	else if (mylst.size() != list.size())
		error_diff(mylst, list);
	else
	{
		typename ft::list<T>::iterator	my_it;
		typename std::list<T>::iterator	i;
		my_it = mylst.begin();
		i = list.begin();
		while (i != list.end())
		{
			if (*i != *my_it)
			{
				error_diff(mylst, list);
				return ;
			}
			i++;
			my_it++;
		}
		
		std::cout << _GREEN << "OK " << _END << std::endl;
		std::cout << _YELLOW << "mylst   ";
		printContainer(mylst);
		std::cout << _YELLOW<< "list";
		printContainer(list);
	}
}

void		test_list(void)
{
	std::cout << _WHITE << "# test_list" << _END << std::endl;
	std::cout << std::endl << _YELLOW <<  "/* ********************************************************************** */" << std::endl;
	std::cout << "/*                          LIST TESTS w/INTS                           */" << std::endl;
	std::cout << "/* ********************************************************************** */" << _END << std::endl;
	std::cout << std::endl;

	std::cout << _BLUE << "# default constructor" << _END << std::endl;
	ft::list<int>	mylst;
	std::list<int>  list;

	std::cout << "ft::list<" << _PURPLE << "int" << _END << "> mylst;" << std::endl;
	std::cout << "std::list<" << _PURPLE << "int" << _END << "> list;" << std::endl << std::endl;

	std::cout << _BLUE << "# max_size tests" << _END << std::endl;
	std::cout << "mylst.max_size():\t" << mylst.max_size() << std::endl;
	std::cout << "list.max_size():\t" << list.max_size() << std::endl;
	std::cout << std::endl;

	std::cout << _BLUE << "# empty and size tests" << _END << std::endl;
	compareList("list.empty()", mylst, list);
	compareList("list.size()", mylst, list);

	std::cout << _BLUE << "# push front test" << _END << std::endl;
	for (int i = 5; i > 0; --i)
	{
		mylst.push_front(i);
		list.push_front(i);
	}
	compareList("list.push_front(i)", mylst, list);

	std::cout << _BLUE << "# push back test" << _END << std::endl;
	for (int i = 6; i <= 10; ++i)
	{
		mylst.push_back(i);
		list.push_back(i);
	}
	compareList("list.push_back(i)", mylst, list);

	std::cout << _BLUE << "# pop front test" << _END << std::endl;

	mylst.pop_front();
	list.pop_front();	

	compareList("list.pop_front()", mylst, list);

	std::cout << _BLUE << "# pop back test" << _END << std::endl;

	mylst.pop_back();
	list.pop_back();	

	compareList("list.pop_back()", mylst, list);

	std::cout << _YELLOW << "mylst.front() -> " << _GREEN << mylst.front() << std::endl;
	std::cout <<_YELLOW <<  "list.front()  -> " << _GREEN << list.front() << std::endl;
	std::cout << _YELLOW << "mylst.back() -> " << _GREEN << mylst.back() << std::endl;
	std::cout <<_YELLOW <<  "list.back()  -> " << _GREEN << list.back() << std::endl;

	std::cout << _BLUE << "# fill constructor" << _END << std::endl;
	ft::list<int>	myfill(5, 21);
	std::list<int>  fill(5, 21);

	std::cout << "ft::list<" << _PURPLE << "int" << _END << "> mylst(5, 21);" << std::endl;
	std::cout << "std::list<" << _PURPLE << "int" << _END << "> list(5, 21);" << std::endl << std::endl;

	compareList("new list from fill constructor ", myfill, fill);

	std::cout << _BLUE << "# insert test" << _END << std::endl;

	ft::list<int>::iterator		mypos = mylst.begin();
	std::list<int>::iterator	pos = list.begin();

	std::cout << _BLUE << "-> at the beginning (one value)" << _END << std::endl;
	mylst.insert(mypos, 42);
	list.insert(pos, 42);	

	compareList("list.insert(pos, 42)", mylst, list);

	std::cout << _BLUE << "-> somewhere in the list (three of the same value)" << _END << std::endl;

	for (int i = 0; i < 5; ++i)
	{
		++mypos;
		++pos;
	}

	mylst.insert(mypos, 3, 10);
	list.insert(pos, 3, 10);	

	compareList("list.insert(pos, 3, 10)", mylst, list);

	std::cout << _BLUE << "-> at the end (with iterator)" << _END << std::endl;
	
	mylst.insert(mylst.end(), myfill.begin(), myfill.end());
	list.insert(list.end(), fill.begin(), fill.end());	

	compareList("list.insert(list.end(), fill.begin(), fill.end())", mylst, list);

	std::cout << _BLUE << "# assign test (with iterator)" << _END << std::endl;

	myfill.assign(mylst.begin(), mypos);
	fill.assign(list.begin(), pos);	

	compareList("fill.assign(list.begin(), pos)", myfill, fill);

	std::cout << _BLUE << "# assign test (range)" << _END << std::endl;

	myfill.assign(mylst.begin(), mypos);
	fill.assign(list.begin(), pos);	

	compareList("fill.assign(list.begin(), pos)", myfill, fill);

	std::cout << _BLUE << "# assign test (fill)" << _END << std::endl;

	mylst.assign(10, 5);
	list.assign(10, 5);

	compareList("list.assign(10, 5)", mylst, list);

	std::cout << _BLUE << "# operator =" << _END << std::endl;

	mylst = myfill;
	list = fill;

	compareList("list = fill", mylst, list);

	std::cout << _BLUE << "# erase test (the first elem)" << _END << std::endl;

	mylst.erase(mylst.begin());
	list.erase(list.begin());

	compareList("list.erase(list.begin())", mylst, list);

	std::cout << _BLUE << "# erase test (the three last elem)" << _END << std::endl;

	mypos = mylst.end();
	pos = list.end();

	for (int i = 3; i > 0; i--)
	{
		--mypos;
		--pos;
	}

	mylst.erase(mypos, mylst.end());
	list.erase(pos, list.end());

	compareList("list.erase(pos, list.end())", mylst, list);

	std::cout << _BLUE << "# resize test" << _END << std::endl;

	mylst.resize(8, 7);
	list.resize(8, 7);

	compareList("list.resize(8, 7)", mylst, list);

	std::cout << _BLUE << "# clear test" << _END << std::endl;

	mylst.clear();
	list.clear();

	compareList("list.clear()", mylst, list);
	
}