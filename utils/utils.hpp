#ifndef UTILS_HPP
#define UTILS_HPP
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
		operator T() { return v; }// constexpr operator T() { return v; }
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


	template <class InputIterator1, class InputIterator2>
	bool	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1)
		{
	    	if (!(*first1 == *first2))
	      		return false;
	    	++first1; ++first2;
	  	}
		return true;
	}
	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
	{
		while (first1 != last1)
		{
		    if (!pred(*first1, *first2))
	      		return false;
	    	++first1; ++first2;
	  	}
		return true;
	}

	template <class InputIterator1, class InputIterator2>
	bool	lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
									InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1) 
				return (false);
			else if (*first1 < *first2) 
				return (true);

			++first1;
			++first2;
		}
		return (first2 != last2);
	}

	template <class InputIterator1, class InputIterator2, class Compare>
	bool	lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
	                                InputIterator2 first2, InputIterator2 last2,
	                                Compare comp)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || comp(*first2, *first1)) 
				return (false);
			else if (comp(*first1, *first2)) 
				return (true);

			++first1;
			++first2;
		}
		return (first2 != last2);
	}


	template <class T1, class T2> // <- A completer !!!
	struct	pair
	{
	public:
		typedef	T1	first_type;
		typedef	T2	second_type;

		pair() : first(first_type()), second(second_type()) {};

		template<class U, class V>
		pair(const pair<U,V>& pr)
		: first(T1(pr.first)),
		second(T2(pr.second))
		{};

		pair(const first_type& a, const second_type& b)
		: first(a),
		second(b)
		{};

		pair& operator=(const pair& pr)
		{
			this->first = first_type(pr.first);
			this->second = second_type(pr.second);
			return (*this);
		};

	public:
		first_type	first;
		second_type	second;
	};

	template <class T> 			struct is_pair						: false_type {};
	template <class T, class K> struct is_pair< ft::pair<T, K> >	: true_type {};

	template <class T1,class T2>
	ft::pair<T1,T2> make_pair(T1 x, T2 y)
	{
	  return (ft::pair<T1,T2>(x,y));
	}

	template <class T1, class T2>
	  bool operator== (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{ return lhs.first==rhs.first && lhs.second==rhs.second; }

	template <class T1, class T2>
	  bool operator!= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{ return !(lhs==rhs); }

	template <class T1, class T2>
	  bool operator<  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{ return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

	template <class T1, class T2>
	  bool operator<= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{ return !(rhs<lhs); }

	template <class T1, class T2>
	  bool operator>  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{ return rhs<lhs; }

	template <class T1, class T2>
	  bool operator>= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{ return !(lhs<rhs); }



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


	// template <typename T>
	// std::string	to_str(T pouet)
	// {
	// 	std::stringstream ss;

	// 	ss << pouet;
	// 	return (ss.str());
	// }

}
#endif
