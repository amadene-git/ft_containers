#ifndef IS_INTEGRAL_HPP
#define IS_INTEGRAL_HPP

#include "integral_constant.hpp"

namespace ft
{
    template <class T> struct is_integral				: false_type {};
// bool
	template <> struct is_integral<bool>				: true_type {};	
// char
	template <> struct is_integral<char> 				: true_type {};	
// signed char
	template <> struct is_integral<signed char> 		: true_type {};	 

// char16_t ?
// char32_t ?

// wchar_t
	template <> struct is_integral<wchar_t>				: true_type {};
// short int
	template <> struct is_integral<short int> 			: true_type {};	 
// int
	template <> struct is_integral<int> 				: true_type {};	
// long int
	template <> struct is_integral<long int> 			: true_type {};	 

// long long int ?

// unsigned char
	template <> struct is_integral<unsigned char> 		: true_type {};	 
// unsigned short int
	template <> struct is_integral<unsigned short int> 	: true_type {};	
// unsigned int
	template <> struct is_integral<unsigned int> 		: true_type {};	
// unsigned long int
	template <> struct is_integral<unsigned long int> 	: true_type {};	

// unsigned long long int ?


}

#endif
