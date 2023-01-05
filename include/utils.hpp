#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <sstream>
#include "pair.hpp"

namespace ft
{
	


	template <class T>
	std::string to_str(T o, typename ft::enable_if<ft::is_pair<T>::value, T>::type* = NULL)
	{
		std::stringstream ss;
		ss << "{" << o.first << ", " << o.second << "}";
		return (ss.str());
	}
	
	template <class T>
	std::string to_str(T o, typename ft::enable_if<!ft::is_pair<T>::value, T>::type* = NULL)
	{
		std::stringstream ss;
		ss << o;
		return (ss.str());
	}



	template <class Arg1, class Arg2, class Result>
	struct	binary_function 
	{
		typedef Arg1 first_argument_type;
		typedef Arg2 second_argument_type;
		typedef Result result_type;
	};

	template <class T>
	struct less : binary_function<T, T, bool> 
	{
		bool operator()(const T& x, const T& y) const 
		{
			return (x < y);
		}
	};

	template <class T> 
	struct greater : binary_function <T, T, bool>
	{
  		bool operator() (const T& x, const T& y) const 
		{
			return (x > y);
		}
	};


	

}
#endif
