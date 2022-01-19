#ifndef UTILS_HPP
#define UTILS_HPP
#include <iostream>
#include <stdio.h>
//#include <cuchar>

namespace ft
{


	template	<bool Cond, class T = void>	struct enable_if {};
	template	<class T> 					struct enable_if<true, T> 
											{	
												typedef T type; 
											};

	template <bool b, typename T>
	struct stock_type 
	{
  		typedef	bool		value_type;
		static	const bool	value = b;

	};

	template <class T> struct is_integral : public stock_type<false, T> {};


	template <> struct is_integral<bool>						: public stock_type<true, bool> {};
	template <> struct is_integral<char> 					: public stock_type<true, char> {};
	// template <> struct is_integral<char16_t> 				: public stock_type<true, char16_t> {};
	// template <> struct is_integral<char32_t> 				: public stock_type<true, char32_t> {};
	// template <> struct is_integral<wchar_t> 					: public stock_type<true, wchar_t> {};
	template <> struct is_integral<signed char> 				: public stock_type<true, signed char> {};
	template <> struct is_integral<short int> 				: public stock_type<true, short int> {};
	template <> struct is_integral<int> 						: public stock_type<true, int> {};
	template <> struct is_integral<long int> 				: public stock_type<true, long int> {};
//	template <> struct is_integral<long long int> 			: public stock_type<true, long long int> {};
	template <> struct is_integral<unsigned char> 			: public stock_type<true, unsigned char> {};
	template <> struct is_integral<unsigned short int> 		: public stock_type<true, unsigned short int> {};
	template <> struct is_integral<unsigned int> 			: public stock_type<true, unsigned int> {};
	template <> struct is_integral<unsigned long int> 		: public stock_type<true, unsigned long int> {};
//	template <> struct is_integral<unsigned long long int>	: public stock_type<true, unsigned long long int> {};

// bool
// char
// char16_t
// char32_t
// wchar_t
// signed char
// short int
// int
// long int
// long long int
// unsigned char
// unsigned short int
// unsigned int
// unsigned long int
// unsigned long long int




/*				
** enable_if, **
iterator_traits, 
reverse_iterator,
is_integral,
equal,
lexicographical compare,
std::pair,
std::make_pair,
*/

}
#endif
