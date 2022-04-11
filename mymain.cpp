/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mymain.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ninieddu <ninieddu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 09:43:42 by ninieddu          #+#    #+#             */
/*   Updated: 2022/04/05 16:51:17 by ninieddu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rb_tree.hpp"

/*
#define DUMPSTR_WNAME(os, name, a) \
    do { (os) << (name) << " = " << (a) << std::endl; } while(false)
	
#define DUMPSTR_WNAME_NO_STDENDL(os, name, a) \
    do { (os) << (name) << " = " << "[" << (a) << "]"; } while(false)
	
#define DUMPSTR(os, a) DUMPSTR_WNAME((os), #a, (a))
#define DUMP(a)        DUMPSTR_WNAME(std::cout, #a, (a))
#define DUMPN(a)        DUMPSTR_WNAME_NO_STDENDL(std::cout, #a, (a))

#define COUT_I(os, name, i) \
    do { (os) << " " << (name) << " = " << (i++) << std::endl; } while(false)
	
#define COUNT(i)       COUT_I(std::cout, #i, (i)) 
*/



int main() 
{
	ft::rbtree<int> tr;
	for (int i = 1; i <= 6; i++)
		tr.insert(i);


	int x = 6;
	ft::rbtree<int>::node* test;
	for (int i = 2; i > 0; i--)
	{
		test = tr.search(x);
		if (test == NULL)
			std::cout << x << " Not found" << std::endl;
		else 
			std::cout << test->value << " Found" << std::endl;
		x++;
	}

	tr.insert(886);
	tr.insert(2777);
	tr.insert(6915);
	tr.insert(7793);
	tr.insert(9383);
	tr.insert(888);
	tr.insert(876);
	tr.insert(881);

	std::cout << std::endl <<  "Size = " << tr.size() << std::endl; 
	tr.erase(6915);
	std::cout << "Erase";
	std::cout << std::endl <<  "Size = " << tr.size() << std::endl; 

	std::cout << std::endl;
	tr.display();
	std::cout << std::endl;

	return 0;
}