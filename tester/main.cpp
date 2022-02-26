#include "include.hpp"



/*
//-std=c++11
#include <type_traits>//enable_if is_integral


// 1. the return type (bool) is only valid if T is an integral type:
template <class T>
typename NAMESPACE::enable_if<NAMESPACE::is_integral<T>::value,bool>::type
is_odd (T i) {return bool(i%2);}
// 2. the second template argument is only valid if T is an integral type:
template < class T,
class = typename NAMESPACE::enable_if<NAMESPACE::is_integral<T>::value>::type>
bool is_even (T i) {return !bool(i%2);}



#include <algorithm>//equal lexicographical_compare
bool mypredicate (int i, int j) {
return (i==j);
}

#include <cctype>       // std::tolower

// a case-insensitive comparison function:
bool mycomp (char c1, char c2)
{ return std::tolower(c1)<std::tolower(c2); }



void	utils_test()
{
//UTILS
std::cout << std::endl << std::endl << std::endl << "//UTILS";
{
std::cout << std::endl << "//	ITERATOR_TRAITS" << std::endl;
{
typedef NAMESPACE::iterator_traits<int*> traits;
if (typeid(traits::iterator_category)==typeid(NAMESPACE::random_access_iterator_tag))
std::cout << "int* is a random-access iterator\n";

typedef NAMESPACE::iterator_traits<NAMESPACE::vector<int>::iterator> vectraits;
if (typeid(vectraits::iterator_category)==typeid(NAMESPACE::random_access_iterator_tag))
std::cout << "vector<int> is a random-access iterator\n";
}
std::cout << std::endl << "//	REVERSE_ITERATOR" << std::endl;
{
NAMESPACE::vector<int> myvector;

for (int i=0; i<10; i++)
myvector.push_back(i);

typedef NAMESPACE::vector<int>::iterator iter_type;
// ? 0 1 2 3 4 5 6 7 8 9 ?
iter_type from (myvector.begin());                     //   ^
//         ------>
iter_type until (myvector.end());                      //                       ^
//
NAMESPACE::reverse_iterator<iter_type> rev_until (from);     // ^
//         <------
NAMESPACE::reverse_iterator<iter_type> rev_from (until);     //                     ^

std::cout << "myvector:";
while (rev_from != rev_until)
std::cout << ' ' << *rev_from++;
std::cout << '\n';
}
std::cout << std::endl << "//	ENABLE_IF" << std::endl;
{


short int i = 1;    // code does not compile if type of i is not integral

std::cout << std::boolalpha;
std::cout << "i is odd: " << is_odd(i) << std::endl;
std::cout << "i is even: " << is_even(i) << std::endl;


}
std::cout << std::endl << "//	IS_INTEGRAL" << std::endl;
{
	std::cout << std::boolalpha;
	std::cout << "is_integral:" << std::endl;
	std::cout << "char: " << NAMESPACE::is_integral<char>::value << std::endl;
	std::cout << "int: " << NAMESPACE::is_integral<int>::value << std::endl;
	std::cout << "float: " << NAMESPACE::is_integral<float>::value << std::endl;
	std::cout << "iterator: " << NAMESPACE::is_integral<NAMESPACE::vector<int>::iterator>::value << std::endl;

}
std::cout << std::endl << "//	EQUAL" << std::endl;
{
	int myints[] = {20,40,60,80,100};               //   myints: 20 40 60 80 100
	NAMESPACE::vector<int>myvector (myints,myints+5);     // myvector: 20 40 60 80 100

	// using default comparison:
	if ( NAMESPACE::equal (myvector.begin(), myvector.end(), myints) )
		std::cout << "The contents of both sequences are equal.\n";
	else
		std::cout << "The contents of both sequences differ.\n";

	myvector[3]=81;                                 // myvector: 20 40 60 81 100

	// using predicate comparison:
	if ( NAMESPACE::equal (myvector.begin(), myvector.end(), myints, mypredicate) )
		std::cout << "The contents of both sequences are equal.\n";
	else
		std::cout << "The contents of both sequences differ.\n";

}
std::cout << std::endl << "//	LEXICOGRAPHICAL COMPARE" << std::endl;
{
	char foo[]="Apple";
	char bar[]="apartment";

	std::cout << std::boolalpha;

	std::cout << "Comparing foo and bar lexicographically (foo<bar):\n";

	std::cout << "Using default comparison (operator<): ";
	std::cout << NAMESPACE::lexicographical_compare(foo,foo+5,bar,bar+9);
	std::cout << '\n';

	std::cout << "Using mycomp as comparison object: ";
	std::cout << NAMESPACE::lexicographical_compare(foo,foo+5,bar,bar+9,mycomp);
	std::cout << '\n';


}

}

}
*/




// #include <sys/time.h>

int main()
{

	// struct timeval tv1;
	// struct timeval tv2;
	// gettimeofday(&tv1, NULL);
	// gettimeofday(&tv2, NULL);
	// std::cout << (tv2.tv_sec * 1000000 + tv2.tv_usec) - (tv1.tv_sec * 1000000 + tv1.tv_usec) << std::endl;;


	vector_test();


	return (0);
}

