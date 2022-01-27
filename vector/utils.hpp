#ifndef UTILS_HPP
#define UTILS_HPP
#include <iostream>
#include <stdio.h>
#include <uchar.h>

namespace ft
{
	template	<bool Cond, class T = void>	struct enable_if {};
	template	<class T> 					struct enable_if<true, T> {	typedef T type; };

	template <class T, T v>
	struct integral_constant
	{
  		static const T					value = v;// == static constexpr T value = v;
  		typedef T						value_type;
  		typedef integral_constant<T,v>	type;
		// constexpr operator T() { return v; }
	};

	typedef integral_constant<bool,true> true_type;
	typedef integral_constant<bool,false> false_type;


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




/*				
** enable_if, **
**is_integral**,
iterator_traits, 
reverse_iterator,
equal,
lexicographical compare,
std::pair,
std::make_pair,
*/

}
#endif
