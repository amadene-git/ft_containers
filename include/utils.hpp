#ifndef UTILS_HPP
#define UTILS_HPP

// #include <stdio.h>
// #include <uchar.h>
#include "iterator.hpp"

namespace ft
{
	
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


	

}
#endif
