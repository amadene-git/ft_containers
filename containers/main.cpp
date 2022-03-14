/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 12:40:31 by hbaudet           #+#    #+#             */
/*   Updated: 2022/03/14 10:19:59 by admadene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <memory>

#ifndef NAMESPACE
# define NAMESPACE ft
#include "map.hpp"

#else
#include <map>

#endif

template <class T>
class myalloc : public  std::allocator<T>
{
	public:
	virtual typename std::allocator<T>::size_type	maxe_size()
	{
		std::cout << "wesh" << std::endl; 
		return (123456);
	}
};


using namespace NAMESPACE;

#include <sys/time.h>

using namespace std;




int main()
{
	NAMESPACE::map<char, char, myalloc<NAMESPACE::pair<const char,char> > >mymap;
	
	std::cout << mymap.max_size() << std::endl;
	return (0);
}
