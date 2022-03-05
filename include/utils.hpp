#ifndef UTILS_HPP
#define UTILS_HPP

// #include <stdio.h>
// #include <uchar.h>

namespace ft
{
	
	

	// template <class T> 			struct is_pair						: false_type {};
	// template <class T, class K> struct is_pair< ft::pair<T, K> >	: true_type {};

	

	static class nullptr_t
	{
    public:
        template<class T>
        operator T*() const { return (0); };

        template<class C, class T>
        operator T C::*() const { return (0); };

    private:
        void operator&() const;

	} u_nullptr = {};

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
