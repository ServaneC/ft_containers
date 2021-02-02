/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 10:13:03 by schene            #+#    #+#             */
/*   Updated: 2021/02/01 18:10:23 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iomanip>
#include <vector>
#include <limits>
#include "utils.hpp"
#include "color.h"
#include "../srcs/Vector.hpp"

template <class T>
void	error_diff(ft::vector<T> myv, std::vector<T> vector)
{
	std::cout << _RED << "ERROR - DIFF" << _END << std::endl;
	std::cout << std::setw(30) << "myv.empty(): " << myv.empty() << std::endl;
	std::cout << std::setw(30) << "vector.empty(): " << vector.empty() << std::endl;
	std::cout << std::setw(30) << "myv.size(): " << myv.size() << std::endl;
	std::cout << std::setw(30) << "vector.size(): " << vector.size() << std::endl;
	std::cout << std::setw(30) << "myv : ";
	printContainer(myv);
	std::cout << std::setw(30) << "vector : ";
	printContainer(vector);
}

template <class T>
void	compareVector(std::string function, ft::vector<T> myv, std::vector<T> vector)
{
	std::cout << std::setw(30) << function << ": ";
	if (myv.empty() != vector.empty())
		error_diff(myv, vector);
	else if (myv.size() != vector.size())
		error_diff(myv, vector);
	else
	{
		typename ft::vector<T>::iterator	my_it;
		typename std::vector<T>::iterator	i;
		my_it = myv.begin();
		i = vector.begin();
		while (i != vector.end())
		{
			if (*i != *my_it)
			{
				error_diff(myv, vector);
				return ;
			}
			i++;
			my_it++;
		}
		
		std::cout << _GREEN << "OK " << _END << std::endl;
		std::cout << _YELLOW << "myv   ";
		printContainer(myv);
		std::cout << _YELLOW<< "vector";
		printContainer(vector);
	}
}

void		test_vector(void)
{
	std::cout << _WHITE << "# test_vector" << _END << std::endl;
	std::cout << std::endl << _YELLOW <<  "/* ********************************************************************** */" << std::endl;
	std::cout << "/*                          VECTOR TESTS w/INTS                           */" << std::endl;
	std::cout << "/* ********************************************************************** */" << _END << std::endl;
	std::cout << std::endl;

	ft::vector<int>	myv;
	std::vector<int> vector;

	std::cout << "ft::vector<" << _PURPLE << "int" << _END << "> myv;" << std::endl;
	std::cout << "std::vector<" << _PURPLE << "int" << _END << "> vector;" << std::endl << std::endl;

	std::cout << _BLUE << "# max_size tests" << _END << std::endl;
	std::cout << "myv.max_size():\t\t" << myv.max_size() << std::endl;
	std::cout << "vector.max_size():\t" << vector.max_size() << std::endl;
	std::cout << std::endl;

	std::cout << _BLUE << "# empty and size tests" << _END << std::endl;
	compareVector("vector.empty()", myv, vector);
	compareVector("vector.size()", myv, vector);
	
	std::cout << _BLUE<< "# testing out_of_range exception" << _END << std::endl;
	std::cout << "myv.at(0):" << std::endl;
	try
	{
		myv.at(0);
	}
	catch (std::exception &e)
	{
		std::cerr << "Catching exception myv: " << e.what() << std::endl;
	}
	std::cout << "vector.at(0):" << std::endl;
	try
	{
		vector.at(0);
	}
	catch (std::exception &e)
	{
		std::cerr << "Catching exception vector: " << e.what() << std::endl;
	}
	std::cout << std::endl;

	std::cout << _BLUE << "# testing capacity() and reserve() function" << _END << std::endl;
	std::cout << "myv.capacity(): " << myv.capacity() << std::endl;
	std::cout << "vector.capacity(): " << vector.capacity() << std::endl<< std::endl;
	myv.reserve(0);
	vector.reserve(0);
	std::cout << "myv.reserve(0);" << std::endl;
	std::cout << "vector.reserve(0);" << std::endl<< std::endl;
	std::cout << "myv.capacity(): " << myv.capacity() << std::endl;
	std::cout << "vector.capacity(): " << vector.capacity() << std::endl<< std::endl;
	myv.reserve(1);
	vector.reserve(1);
	std::cout << "myv.reserve(1);" << std::endl;
	std::cout << "vector.reserve(1);" << std::endl<< std::endl;
	std::cout << "myv.capacity(): " << myv.capacity() << std::endl;
	std::cout << "vector.capacity(): " << vector.capacity() << std::endl<< std::endl;
	std::cout << std::endl;

	std::cout << _BLUE << "# testing reserve exception" << _END << std::endl;
	std::cout << "myv.reserve(" << std::numeric_limits<size_t>::max() << ");" << std::endl;
	try
	{
		myv.reserve(std::numeric_limits<size_t>::max());
	}
	catch (std::exception &e)
	{
		std::cerr << "Catching exception myv: " << e.what() << std::endl;
	}
	std::cout << "vector.reserve(" << std::numeric_limits<size_t>::max() << ");" << std::endl;
	try
	{
		vector.reserve(std::numeric_limits<size_t>::max());
	}
	catch (std::exception &e)
	{
		std::cerr << "Catching exception vector: " << e.what() << std::endl;
	}
	std::cout << std::endl;

	std::cout << _BLUE << "# resize tests" << _END << std::endl;
	myv.resize(8);
	vector.resize(8);
	compareVector("vector.resize(8)", myv, vector);
	std::cout << "myv.capacity(): " << myv.capacity() << std::endl;
	std::cout << "vector.capacity(): " << vector.capacity() << std::endl<< std::endl;

	std::cout << _BLUE << "# push_back tests" << _END << std::endl;
	myv.push_back(4);
	vector.push_back(4);
	compareVector("vector.push_back(4)", myv, vector);
	std::cout << "myv.capacity(): " << myv.capacity() << std::endl;
	std::cout << "vector.capacity(): " << vector.capacity() << std::endl << std::endl;
	
	std::cout << _BLUE << "# erase tests" << _END << std::endl;
	myv.erase(myv.begin());
	vector.erase(vector.begin());
	compareVector("vector.erase(vector.begin())", myv, vector);

	std::cout << _BLUE << "# testing front and back function" << _END << std::endl;
	std::cout << "myv.front() => " << myv.front() << std::endl;
	std::cout << "vector.front() => " << vector.front() << std::endl << std::endl;
	
	std::cout << "myv.back() => " << myv.back() << std::endl;
	std::cout << "vector.back() => " << vector.back() << std::endl << std::endl;

	std::cout << _BLUE << "# pop_back tests" << _END << std::endl;
	myv.pop_back();
	vector.pop_back();
	compareVector("vector.pop_back()", myv, vector);
	std::cout << "myv.size(): " << myv.size() << std::endl;
	std::cout << "vector.size(): " << vector.size() << std::endl << std::endl;
	std::cout << "myv.capacity(): " << myv.capacity() << std::endl;
	std::cout << "vector.capacity(): " << vector.capacity() << std::endl << std::endl;

	std::cout << _BLUE << "# launching clear twice" << _END << std::endl;
	myv.clear();
	vector.clear();
	compareVector("vector.clear()", myv, vector);
	myv.clear();
	vector.clear();
	compareVector("vector.clear()", myv, vector);
	std::cout << "myv.capacity(): " << myv.capacity() << std::endl;
	std::cout << "vector.capacity(): " << vector.capacity() << std::endl;

	std::cout << _BLUE << "# assign tests" << _END << std::endl;
	myv.assign((size_t)10, 8);
	vector.assign((size_t)10, 8);
	compareVector("vector.assign(10, 8)", myv, vector);

	myv.assign(myv.begin(), myv.begin() + 4); // wtf that works
	vector.assign(vector.begin(), vector.begin() + 4);
	compareVector("vector.assign(vector.begin(), vector.begin() + 4)", myv, vector);

	std::cout << _BLUE << "# insert tests" << _END << std::endl;
	myv.insert(myv.begin() + 2, 42);
	vector.insert(vector.begin() + 2, 42);
	compareVector("vector.insert(vector.begin() + 2, 42);", myv, vector);

	ft::vector<int> myv2;
	std::vector<int> vector2;
	std::cout << "ft::vector<" << _PURPLE << "int" << _END << "> myv2;" << std::endl;
	std::cout << "std::vector<" << _PURPLE << "int" << _END << "> vector2;" << std::endl << std::endl;
	
	std::cout << _BLUE << "# swap tests" << _END << std::endl;
	myv.swap(myv2);
	vector.swap(vector2);
	compareVector("vector.swap(vector2)", myv, vector);
	compareVector("vector2", myv2, vector2);

	myv.swap(myv2);
	vector.swap(vector2);
	compareVector("vector.swap(vector2)", myv, vector);
	compareVector("vector2", myv2, vector2);

	std::cout << _BLUE << "# erase tests" << _END << std::endl;
	myv.erase(myv.begin() + 2);
	vector.erase(vector.begin() + 2);
	compareVector("vector.erase(this->begin() + 2", myv, vector);

	std::cout << _BLUE << "# operator= tests" << _END << std::endl;
	myv2 = myv;
	vector2 = vector;
	compareVector("vector2 = vector", myv2, vector2);

	myv.at(2) = 1;
	vector.at(2) = 1;
	compareVector("vector.at(2) = 1", myv, vector);

	myv[1] = 0;
	vector[1] = 0;
	compareVector("vector[1] = 0", myv, vector);

	std::cout << std::endl << _BLUE << "# comparaisons tests" << _END << std::endl;
	std::cout << std::setw(30) << "myv < myv2: " << (myv < myv2) << std::endl;
	std::cout << std::setw(30) << "vector < vector2: " << (vector < vector2) << std::endl;
	std::cout << std::endl;
	std::cout << std::setw(30) << "myv > myv2: " << (myv > myv2) << std::endl;
	std::cout << std::setw(30) << "vector > vector2: " << (vector > vector2) << std::endl;
	std::cout << std::endl;
	std::cout << std::setw(30) << "myv == myv2: " << (myv == myv2) << std::endl;
	std::cout << std::setw(30) << "vector == vector2: " << (vector == vector2) << std::endl;
	std::cout << std::endl;
	std::cout << std::setw(30) << "myv != myv2: " << (myv == myv2) << std::endl;
	std::cout << std::setw(30) << "vector != vector2: " << (vector == vector2) << std::endl;
	std::cout << std::endl;
	std::cout << std::setw(30) << "myv <= myv2: " << (myv <= myv2) << std::endl;
	std::cout << std::setw(30) << "vector <= vector2: " << (vector <= vector2) << std::endl;
	std::cout << std::endl;
	std::cout << std::setw(30) << "myv >= myv2: " << (myv >= myv2) << std::endl;
	std::cout << std::setw(30) << "vector >= vector2: " << (vector >= vector2) << std::endl;

	std::cout << std::endl << _YELLOW <<  "/* ********************************************************************** */" << std::endl;
	std::cout << "/*                          VECTOR TESTS w/std::strings                    */" << std::endl;
	std::cout << "/* ********************************************************************** */" << _END << std::endl;
	std::cout << std::endl;

	ft::vector<std::string>	myv_s;
	std::vector<std::string> vector_s;

	std::cout << "ft::vector<" << _PURPLE << "std::string" << _END << "> myv_s;" << std::endl;
	std::cout << "std::vector<" << _PURPLE << "std::string" << _END << "> vector_s;" << std::endl << std::endl;

	std::cout << _BLUE << "# max_size tests" << _END << std::endl;
	std::cout << "myv_s.max_size():\t\t" << myv_s.max_size() << std::endl;
	std::cout << "vector_s.max_size():\t" << vector_s.max_size() << std::endl;
	std::cout << std::endl;

	std::cout << _BLUE << "# empty and size tests" << _END << std::endl;
	compareVector("vector_s.empty()", myv_s, vector_s);
	compareVector("vector_s.size()", myv_s, vector_s);
	
	std::cout << _BLUE<< "# testing out_of_range exception" << _END << std::endl;
	std::cout << "myv_s.at(0):" << std::endl;
	try
	{
		myv_s.at(0);
	}
	catch (std::exception &e)
	{
		std::cerr << "Catching exception myv_s: " << e.what() << std::endl;
	}
	std::cout << "vector_s.at(0):" << std::endl;
	try
	{
		vector_s.at(0);
	}
	catch (std::exception &e)
	{
		std::cerr << "Catching exception vector_s: " << e.what() << std::endl;
	}
	std::cout << std::endl;

	std::cout << _BLUE << "# testing capacity() and reserve() function" << _END << std::endl;
	std::cout << "myv_s.capacity(): " << myv_s.capacity() << std::endl;
	std::cout << "vector_s.capacity(): " << vector_s.capacity() << std::endl<< std::endl;
	myv_s.reserve(0);
	vector_s.reserve(0);
	std::cout << "myv_s.reserve(0);" << std::endl;
	std::cout << "vector_s.reserve(0);" << std::endl<< std::endl;
	std::cout << "myv_s.capacity(): " << myv_s.capacity() << std::endl;
	std::cout << "vector_s.capacity(): " << vector_s.capacity() << std::endl<< std::endl;
	myv_s.reserve(1);
	vector_s.reserve(1);
	std::cout << "myv_s.reserve(1);" << std::endl;
	std::cout << "vector_s.reserve(1);" << std::endl<< std::endl;
	std::cout << "myv_s.capacity(): " << myv_s.capacity() << std::endl;
	std::cout << "vector_s.capacity(): " << vector_s.capacity() << std::endl<< std::endl;
	std::cout << std::endl;

	std::cout << _BLUE << "# testing reserve exception" << _END << std::endl;
	std::cout << "myv_s.reserve(" << std::numeric_limits<size_t>::max() << ");" << std::endl;
	try
	{
		myv_s.reserve(std::numeric_limits<size_t>::max());
	}
	catch (std::exception &e)
	{
		std::cerr << "Catching exception myv_s: " << e.what() << std::endl;
	}
	std::cout << "vector_s.reserve(" << std::numeric_limits<size_t>::max() << ");" << std::endl;
	try
	{
		vector_s.reserve(std::numeric_limits<size_t>::max());
	}
	catch (std::exception &e)
	{
		std::cerr << "Catching exception vector_s: " << e.what() << std::endl;
	}
	std::cout << std::endl;

	std::cout << _BLUE << "# resize tests" << _END << std::endl;
	myv_s.resize(8, "hi");
	vector_s.resize(8, "hi");
	compareVector("vector_s.resize(8, \"hi\")", myv_s, vector_s);
	std::cout << "myv_s.capacity(): " << myv_s.capacity() << std::endl;
	std::cout << "vector_s.capacity(): " << vector_s.capacity() << std::endl<< std::endl;

	std::cout << _BLUE << "# push_back tests" << _END << std::endl;
	myv_s.push_back("hello");
	vector_s.push_back("hello");
	compareVector("vector.push_back(\"hello\")", myv_s, vector_s);
	std::cout << "myv_s.capacity(): " << myv_s.capacity() << std::endl;
	std::cout << "vector_s.capacity(): " << vector_s.capacity() << std::endl << std::endl;
	
	std::cout << _BLUE << "# erase tests" << _END << std::endl;
	myv_s.erase(myv_s.begin());
	vector_s.erase(vector_s.begin());
	compareVector("vector_s.erase(vector_s.begin())", myv_s, vector_s);

	std::cout << _BLUE << "# testing front and back function" << _END << std::endl;
	std::cout << "myv_s.front() => " << myv_s.front() << std::endl;
	std::cout << "vector_s.front() => " << vector_s.front() << std::endl << std::endl;
	
	std::cout << "myv_s.back() => " << myv_s.back() << std::endl;
	std::cout << "vector_s.back() => " << vector_s.back() << std::endl << std::endl;

	std::cout << _BLUE << "# pop_back tests" << _END << std::endl;
	myv_s.pop_back();
	vector_s.pop_back();
	compareVector("vector_s.pop_back()", myv_s, vector_s);
	std::cout << "myv_s.size(): " << myv_s.size() << std::endl;
	std::cout << "vector_s.size(): " << vector_s.size() << std::endl << std::endl;
	std::cout << "myv_s.capacity(): " << myv_s.capacity() << std::endl;
	std::cout << "vector_s.capacity(): " << vector_s.capacity() << std::endl << std::endl;

	std::cout << _BLUE << "# launching clear twice" << _END << std::endl;
	myv_s.clear();
	vector_s.clear();
	compareVector("vector_s.clear()", myv_s, vector_s);
	myv_s.clear();
	vector_s.clear();
	compareVector("vector_s.clear()", myv_s, vector_s);
	std::cout << "myv_s.capacity(): " << myv_s.capacity() << std::endl;
	std::cout << "vector_s.capacity(): " << vector_s.capacity() << std::endl;

	std::cout << _BLUE << "# assign tests" << _END << std::endl;
	myv_s.assign((size_t)10, "code");
	vector_s.assign((size_t)10, "code");
	compareVector("vector_s.assign(10, \"code\")", myv_s, vector_s);

	myv_s.assign(myv_s.begin(), myv_s.begin() + 4); // wtf that works
	vector_s.assign(vector_s.begin(), vector_s.begin() + 4);
	compareVector("vector_s.assign(vector_s.begin(), vector_s.begin() + 4)", myv_s, vector_s);

	std::cout << _BLUE << "# insert tests" << _END << std::endl;
	myv_s.insert(myv_s.begin() + 2, "42born2code");
	vector_s.insert(vector_s.begin() + 2, "42born2code");
	compareVector("vector_s.insert(vector_s.begin() + 2, \"42born2code\");", myv_s, vector_s);

	ft::vector<std::string> myv_s2;
	std::vector<std::string> vector_s2;
	std::cout << "ft::vector<" << _PURPLE << "std::string" << _END << "> myv_s2;" << std::endl;
	std::cout << "std::vector<" << _PURPLE << "std::string" << _END << "> vector_s2;" << std::endl << std::endl;
	
	std::cout << _BLUE << "# swap tests" << _END << std::endl;
	myv_s.swap(myv_s2);
	vector_s.swap(vector_s2);
	compareVector("vector_s.swap(vector_s2)", myv_s, vector_s);
	compareVector("vector_s2", myv_s2, vector_s2);

	myv_s.swap(myv_s2);
	vector_s.swap(vector_s2);
	compareVector("vector_s.swap(vector_s2)", myv_s, vector_s);
	compareVector("vector_s2", myv_s2, vector_s2);

	std::cout << _BLUE << "# erase tests" << _END << std::endl;
	myv_s.erase(myv_s.begin() + 2);
	vector_s.erase(vector_s.begin() + 2);
	compareVector("vector_s.erase(this->begin() + 2", myv_s, vector_s);

	std::cout << _BLUE << "# operator= tests" << _END << std::endl;
	myv_s2 = myv_s;
	vector_s2 = vector_s;
	compareVector("vector_s2 = vector_s", myv_s2, vector_s2);

	myv_s.at(2) = "world";
	vector_s.at(2) = "world";
	compareVector("vector_s.at(2) = \"world\"", myv_s, vector_s);

	myv_s[1] = "hello";
	vector_s[1] = "hello";
	compareVector("vector_s[1] = \"hello\"", myv_s, vector_s);

	std::cout << std::endl << _BLUE << "# comparaisons tests" << _END << std::endl;
	std::cout << std::setw(30) << "myv_s < myv_s2: " << (myv_s < myv_s2) << std::endl;
	std::cout << std::setw(30) << "vector_s < vector_s2: " << (vector_s < vector_s2) << std::endl;
	std::cout << std::endl;
	std::cout << std::setw(30) << "myv_s > myv_s2: " << (myv_s > myv_s2) << std::endl;
	std::cout << std::setw(30) << "vector_s > vector_s2: " << (vector_s > vector_s2) << std::endl;
	std::cout << std::endl;
	std::cout << std::setw(30) << "myv_s == myv_s2: " << (myv_s == myv_s2) << std::endl;
	std::cout << std::setw(30) << "vector_s == vector_s2: " << (vector_s == vector_s2) << std::endl;
	std::cout << std::endl;
	std::cout << std::setw(30) << "myv_s != myv_s2: " << (myv_s == myv_s2) << std::endl;
	std::cout << std::setw(30) << "vector_s != vector_s2: " << (vector_s == vector_s2) << std::endl;
	std::cout << std::endl;
	std::cout << std::setw(30) << "myv_s <= myv_s2: " << (myv_s <= myv_s2) << std::endl;
	std::cout << std::setw(30) << "vector_s <= vector_s2: " << (vector_s <= vector_s2) << std::endl;
	std::cout << std::endl;
	std::cout << std::setw(30) << "myv_s >= myv_s2: " << (myv_s >= myv_s2) << std::endl;
	std::cout << std::setw(30) << "vector_s >= vector_s2: " << (vector_s >= vector_s2) << std::endl;
	
	
	// std::cout << std::endl << _YELLOW <<  "/* ********************************************************************** */" << std::endl;
	// std::cout << "/*                          VECTOR TESTS w/bool                           */" << std::endl;
	// std::cout << "/* ********************************************************************** */" << _END << std::endl;
	// std::cout << std::endl;

	// ft::vector<bool>	myv_b;
	// std::vector<bool> vector_b;

	// std::cout << "ft::vector<" << _PURPLE << "bool" << _END << "> myv_b;" << std::endl;
	// std::cout << "std::vector<" << _PURPLE << "bool" << _END << "> vector_b;" << std::endl << std::endl;

	// std::cout << _BLUE << "# max_size tests" << _END << std::endl;
	// std::cout << "myv_b.max_size():\t\t" << myv_b.max_size() << std::endl;
	// std::cout << "vector_b.max_size():\t" << vector_b.max_size() << std::endl;
	// std::cout << std::endl;

	// std::cout << _BLUE << "# empty and size tests" << _END << std::endl;
	// compareVector("vector_b.empty()", myv_b, vector_b);
	// compareVector("vector_b.size()", myv_b, vector_b);
	
	// std::cout << _BLUE<< "# testing out_of_range exception" << _END << std::endl;
	// std::cout << "myv_b.at(0):" << std::endl;
	// try
	// {
	// 	myv_b.at(0);
	// }
	// catch (std::exception &e)
	// {
	// 	std::cerr << "Catching exception myv_b: " << e.what() << std::endl;
	// }
	// std::cout << "vector_b.at(0):" << std::endl;
	// try
	// {
	// 	vector_b.at(0);
	// }
	// catch (std::exception &e)
	// {
	// 	std::cerr << "Catching exception vector_b: " << e.what() << std::endl;
	// }
	// std::cout << std::endl;

	// std::cout << _BLUE << "# testing capacity() and reserve() function" << _END << std::endl;
	// std::cout << "myv_b.capacity(): " << myv_b.capacity() << std::endl;
	// std::cout << "vector_b.capacity(): " << vector_b.capacity() << std::endl<< std::endl;
	// myv_b.reserve(0);
	// vector_b.reserve(0);
	// std::cout << "myv_b.reserve(0);" << std::endl;
	// std::cout << "vector_b.reserve(0);" << std::endl<< std::endl;
	// std::cout << "myv_b.capacity(): " << myv_b.capacity() << std::endl;
	// std::cout << "vector_b.capacity(): " << vector_b.capacity() << std::endl<< std::endl;
	// myv_b.reserve(1);
	// vector_b.reserve(1);
	// std::cout << "myv_b.reserve(1);" << std::endl;
	// std::cout << "vector_b.reserve(1);" << std::endl<< std::endl;
	// std::cout << "myv_b.capacity(): " << myv_b.capacity() << std::endl;
	// std::cout << "vector_b.capacity(): " << vector_b.capacity() << std::endl<< std::endl;
	// std::cout << std::endl;

	// std::cout << _BLUE << "# testing reserve exception" << _END << std::endl;
	// std::cout << "myv_b.reserve(" << std::numeric_limits<size_t>::max() << ");" << std::endl;
	// try
	// {
	// 	myv_b.reserve(std::numeric_limits<size_t>::max());
	// }
	// catch (std::exception &e)
	// {
	// 	std::cerr << "Catching exception myv_b: " << e.what() << std::endl;
	// }
	// std::cout << "vector_b.reserve(" << std::numeric_limits<size_t>::max() << ");" << std::endl;
	// try
	// {
	// 	vector_b.reserve(std::numeric_limits<size_t>::max());
	// }
	// catch (std::exception &e)
	// {
	// 	std::cerr << "Catching exception vector_b: " << e.what() << std::endl;
	// }
	// std::cout << std::endl;

	// std::cout << _BLUE << "# resize tests" << _END << std::endl;
	// myv_b.resize(8, "hi");
	// vector_b.resize(8, "hi");
	// compareVector("vector_b.resize(8, \"hi\")", myv_b, vector_b);
	// std::cout << "myv_b.capacity(): " << myv_b.capacity() << std::endl;
	// std::cout << "vector_b.capacity(): " << vector_b.capacity() << std::endl<< std::endl;

	// std::cout << _BLUE << "# push_back tests" << _END << std::endl;
	// myv_b.push_back("hello");
	// vector_b.push_back("hello");
	// compareVector("vector.push_back(\"hello\")", myv_b, vector_b);
	// std::cout << "myv_b.capacity(): " << myv_b.capacity() << std::endl;
	// std::cout << "vector_b.capacity(): " << vector_b.capacity() << std::endl << std::endl;
	
	// std::cout << _BLUE << "# erase tests" << _END << std::endl;
	// myv_b.erase(myv_b.begin());
	// vector_b.erase(vector_b.begin());
	// compareVector("vector_b.erase(vector_b.begin())", myv_b, vector_b);

	// std::cout << _BLUE << "# testing front and back function" << _END << std::endl;
	// std::cout << "myv_b.front() => " << myv_b.front() << std::endl;
	// std::cout << "vector_b.front() => " << vector_b.front() << std::endl << std::endl;
	
	// std::cout << "myv_b.back() => " << myv_b.back() << std::endl;
	// std::cout << "vector_b.back() => " << vector_b.back() << std::endl << std::endl;

	// std::cout << _BLUE << "# pop_back tests" << _END << std::endl;
	// myv_b.pop_back();
	// vector_b.pop_back();
	// compareVector("vector_b.pop_back()", myv_b, vector_b);
	// std::cout << "myv_b.size(): " << myv_b.size() << std::endl;
	// std::cout << "vector_b.size(): " << vector_b.size() << std::endl << std::endl;
	// std::cout << "myv_b.capacity(): " << myv_b.capacity() << std::endl;
	// std::cout << "vector_b.capacity(): " << vector_b.capacity() << std::endl << std::endl;

	// std::cout << _BLUE << "# launching clear twice" << _END << std::endl;
	// myv_b.clear();
	// vector_b.clear();
	// compareVector("vector_b.clear()", myv_b, vector_b);
	// myv_b.clear();
	// vector_b.clear();
	// compareVector("vector_b.clear()", myv_b, vector_b);
	// std::cout << "myv_b.capacity(): " << myv_b.capacity() << std::endl;
	// std::cout << "vector_b.capacity(): " << vector_b.capacity() << std::endl;

	// std::cout << _BLUE << "# assign tests" << _END << std::endl;
	// myv_b.assign((size_t)10, "code");
	// vector_b.assign((size_t)10, "code");
	// compareVector("vector_b.assign(10, \"code\")", myv_b, vector_b);

	// myv_b.assign(myv_b.begin(), myv_b.begin() + 4); // wtf that works
	// vector_b.assign(vector_b.begin(), vector_b.begin() + 4);
	// compareVector("vector_b.assign(vector_b.begin(), vector_b.begin() + 4)", myv_b, vector_b);

	// std::cout << _BLUE << "# insert tests" << _END << std::endl;
	// myv_b.insert(myv_b.begin() + 2, "42born2code");
	// vector_b.insert(vector_b.begin() + 2, "42born2code");
	// compareVector("vector_b.insert(vector_b.begin() + 2, \"42born2code\");", myv_b, vector_b);

	// ft::vector<std::string> myv_b2;
	// std::vector<std::string> vector_b2;
	// std::cout << "ft::vector<" << _PURPLE << "std::string" << _END << "> myv_b2;" << std::endl;
	// std::cout << "std::vector<" << _PURPLE << "std::string" << _END << "> vector_b2;" << std::endl << std::endl;
	
	// std::cout << _BLUE << "# swap tests" << _END << std::endl;
	// myv_b.swap(myv_b2);
	// vector_b.swap(vector_b2);
	// compareVector("vector_b.swap(vector_b2)", myv_b, vector_b);
	// compareVector("vector_b2", myv_b2, vector_b2);

	// myv_b.swap(myv_b2);
	// vector_b.swap(vector_b2);
	// compareVector("vector_b.swap(vector_b2)", myv_b, vector_b);
	// compareVector("vector_b2", myv_b2, vector_b2);

	// std::cout << _BLUE << "# erase tests" << _END << std::endl;
	// myv_b.erase(myv_b.begin() + 2);
	// vector_b.erase(vector_b.begin() + 2);
	// compareVector("vector_b.erase(this->begin() + 2", myv_b, vector_b);

	// std::cout << _BLUE << "# operator= tests" << _END << std::endl;
	// myv_b2 = myv_b;
	// vector_b2 = vector_b;
	// compareVector("vector_b2 = vector_b", myv_b2, vector_b2);

	// myv_b.at(2) = "world";
	// vector_b.at(2) = "world";
	// compareVector("vector_b.at(2) = \"world\"", myv_b, vector_b);

	// myv_b[1] = "hello";
	// vector_b[1] = "hello";
	// compareVector("vector_b[1] = \"hello\"", myv_b, vector_b);

	// std::cout << std::endl << _BLUE << "# comparaisons tests" << _END << std::endl;
	// std::cout << std::setw(30) << "myv_b < myv_b2: " << (myv_b < myv_b2) << std::endl;
	// std::cout << std::setw(30) << "vector_b < vector_b2: " << (vector_b < vector_b2) << std::endl;
	// std::cout << std::endl;
	// std::cout << std::setw(30) << "myv_b > myv_b2: " << (myv_b > myv_b2) << std::endl;
	// std::cout << std::setw(30) << "vector_b > vector_b2: " << (vector_b > vector_b2) << std::endl;
	// std::cout << std::endl;
	// std::cout << std::setw(30) << "myv_b == myv_b2: " << (myv_b == myv_b2) << std::endl;
	// std::cout << std::setw(30) << "vector_b == vector_b2: " << (vector_b == vector_b2) << std::endl;
	// std::cout << std::endl;
	// std::cout << std::setw(30) << "myv_b != myv_b2: " << (myv_b == myv_b2) << std::endl;
	// std::cout << std::setw(30) << "vector_b != vector_b2: " << (vector_b == vector_b2) << std::endl;
	// std::cout << std::endl;
	// std::cout << std::setw(30) << "myv_b <= myv_b2: " << (myv_b <= myv_b2) << std::endl;
	// std::cout << std::setw(30) << "vector_b <= vector_b2: " << (vector_b <= vector_b2) << std::endl;
	// std::cout << std::endl;
	// std::cout << std::setw(30) << "myv_b >= myv_b2: " << (myv_b >= myv_b2) << std::endl;
	// std::cout << std::setw(30) << "vector_b >= vector_b2: " << (vector_b >= vector_b2) << std::endl;
}