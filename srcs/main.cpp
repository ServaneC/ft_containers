/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 12:24:39 by schene            #+#    #+#             */
/*   Updated: 2021/01/15 13:27:17 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vector.hpp"

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
	ft::VectorIterator<int>		end = v1.end();
	for (ft::VectorIterator<int> it = v1.begin(); it != end; ++it)
		std::cout  << *it << std::endl;
	
	std::cout << std::endl << "------------------------------------------" << std::endl;
	std::cout << "pop_back the 42" << std::endl;
	v1.pop_back();
	std::cout << "size = " << v1.size() << std::endl;
	std::cout << "capacity = " << v1.capacity() << std::endl;
	for (size_t i = 0; i < v1.size(); i++)
		std::cout << i << " -> " << v1[i] << std::endl;
	
	std::cout << std::endl << "------------------------------------------" << std::endl;
	
	// std::cout << "call to clear" << std::endl;
	// v1.clear();
	// std::cout << "size = " << v1.size() << std::endl;
	// std::cout << "capacity = " << v1.capacity() << std::endl;
	// for (size_t i = 0; i < v1.size(); i++)
	// 	std::cout << i << " -> " << v1[i] << std::endl;
	
	// std::cout << std::endl << "------------------------------------------" << std::endl;
	
	ft::VectorIterator<int>			end2 = v1.end();
	for (ft::VectorIterator<int>	it = v1.begin(); it != end2; ++it)
		std::cout  << *it << std::endl;
	
	std::cout << std::endl << "------------------------------------------" << std::endl;
	
	std::cout << "call to assign(15, 5)" << std::endl;
	v1.assign(15, 5);
	std::cout << "size = " << v1.size() << std::endl;
	std::cout << "capacity = " << v1.capacity() << std::endl;
	for (size_t i = 0; i < v1.size(); i++)
		std::cout << i << " -> " << v1[i] << std::endl;
	
	std::cout << std::endl << "------------------------------------------" << std::endl;
	
	// std::cout << "call to assign with iterator" << std::endl;
	// ft::Vector<int> 	v2;
	// v2.assign(v1.begin(), v1.end());
	// std::cout << "size = " << v2.size() << std::endl;
	// std::cout << "capacity = " << v2.capacity() << std::endl;
	// for (size_t i = 0; i < v2.size(); i++)
	// 	std::cout << i << " -> " << v2[i] << std::endl;
	
	// std::cout << std::endl << "------------------------------------------" << std::endl;
	
	std::cout << "call to insert (one 42 at second)" << std::endl;

	v1.insert(++v1.begin(), 42);
	std::cout << "size = " << v1.size() << std::endl;
	std::cout << "capacity = " << v1.capacity() << std::endl;
	for (size_t i = 0; i < v1.size(); i++)
		std::cout << i << " -> " << v1[i] << std::endl;

	std::cout << std::endl << "------------------------------------------" << std::endl;
	
	std::cout << "call to insert " << std::endl;
	ft::VectorIterator<int>  pos = v1.end();

	--pos;
	--pos;
	--pos;

	v1.insert(pos, 5, 21);
	std::cout << "size = " << v1.size() << std::endl;
	std::cout << "capacity = " << v1.capacity() << std::endl;
	for (size_t i = 0; i < v1.size(); i++)
		std::cout << i << " -> " << v1[i] << std::endl;

	std::cout << std::endl << "------------------------------------------" << std::endl;

	size = 10;
	ft::Vector<int> 	to_insert(size, 1);
	std::cout << "call to insert " << std::endl;
	ft::VectorIterator<int>  pos2 = v1.begin();

	++pos2;
	++pos2;
	++pos2;
	
	v1.insert(pos2, to_insert.begin(), to_insert.end());
	std::cout << "size = " << v1.size() << std::endl;
	std::cout << "capacity = " << v1.capacity() << std::endl;
	for (size_t i = 0; i < v1.size(); i++)
		std::cout << i << " -> " << v1[i] << std::endl;

	std::cout << std::endl << "------------------------------------------" << std::endl;
	
	std::cout << "reassigning the vector values" << std::endl;

	for (size_t i = 0; i < v1.size(); i++)
		v1[i] = i;

	std::cout << "size = " << v1.size() << std::endl;
	std::cout << "capacity = " << v1.capacity() << std::endl;
	for (size_t i = 0; i < v1.size(); i++)
		std::cout << i << " -> " << v1[i] << std::endl;
	
	std::cout << std::endl << "------------------------------------------" << std::endl;
	
	std::cout << "call to erase" << std::endl;
	ft::VectorIterator<int>  first = v1.begin();
	ft::VectorIterator<int>  last = v1.end();

	for (int i = 0; i < 7; i++)
	{
		first++;
		last--;
	}

	v1.erase(first, last);
	std::cout << "size = " << v1.size() << std::endl;
	std::cout << "capacity = " << v1.capacity() << std::endl;
	for (size_t i = 0; i < v1.size(); i++)
		std::cout << i << " -> " << v1[i] << std::endl;
	
	std::cout << std::endl << "------------------------------------------" << std::endl;
		std::cout << "call to erase" << std::endl;

	v1.erase(++v1.begin());
	std::cout << "size = " << v1.size() << std::endl;
	std::cout << "capacity = " << v1.capacity() << std::endl;
	for (size_t i = 0; i < v1.size(); i++)
		std::cout << i << " -> " << v1[i] << std::endl;
	
	std::cout << std::endl << "------------------------------------------" << std::endl;
	ft::Vector<int> foo (3,100);   // three ints with a value of 100
 	ft::Vector<int> bar (5,200);   // five ints with a value of 200

  	std::cout << "foo contains:";
  	for (unsigned i=0; i<foo.size(); i++)
   		std::cout << ' ' << foo[i];
	std::cout << '\n';
  	std::cout << "size = "<< foo.size() << " capacity = " << foo.capacity() <<'\n';
	

	std::cout << "bar contains:";
  	for (unsigned i=0; i<bar.size(); i++)
    	std::cout << ' ' << bar[i];
  	std::cout << '\n';
  	std::cout << "size = "<< bar.size() << " capacity = " << bar.capacity() <<'\n';

  	foo.swap(bar);
	std::cout << '\n'<< "------------- SWAP -----------" << std::endl;

  	std::cout << "foo contains:";
  	for (unsigned i=0; i<foo.size(); i++)
   		std::cout << ' ' << foo[i];
  	std::cout << '\n';
  	std::cout << " size = "<< foo.size() << " capacity = " << foo.capacity() <<'\n';

	  std::cout << "bar contains:";
  	for (unsigned i=0; i<bar.size(); i++)
    	std::cout << ' ' << bar[i];
  	std::cout << '\n';
  	std::cout << " size = "<< bar.size() << " capacity = " << bar.capacity() <<'\n';
  	
	// bar.swap(foo);
	// std::cout << '\n' << "------------- SWAP -----------" << std::endl;

  	// std::cout << "foo contains:";
  	// for (unsigned i=0; i<foo.size(); i++)
   	// 	std::cout << ' ' << foo[i];
  	// std::cout << '\n';
  	// std::cout << " size = "<< foo.size() << " capacity = " << foo.capacity() <<'\n';

	//   std::cout << "bar contains:";
  	// for (unsigned i=0; i<bar.size(); i++)
    // 	std::cout << ' ' << bar[i];
  	// std::cout << '\n';
  	// std::cout << " size = "<< bar.size() << " capacity = " << bar.capacity() <<'\n';

	// while (1)
	// 	;
	return 0;
}