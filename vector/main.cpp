#include "vector.hpp"
#include <vector>

#include "utils.hpp"
#include "reverse_iterator.hpp"
#include <iterator>//iterator_traits, reverse_iterator


#include <typeinfo>
#include <memory>

//#include <chrono>
//using namespace std::chrono;
//auto start = high_resolution_clock::now();

void	vector_contain(ft::vector<int> &vec)
{
	std::cout << "vector (" << vec.size() << ", " << vec.capacity() << ")\n";
	for (size_t i = 0; i < vec.size(); i++)
		std::cout << ' ' << vec.at(i);
	std::cout << '\n';

}


void    vector_test(void)
{
	// Vector
	std::cout << std::endl << "//VECTOR";
	{
		std::cout << std::endl << std::endl << "//		CONSTRUCTOR" << std::endl;
		{
			// constructors used in the same order as described above:
			ft::vector<int> first;                                // empty vector of ints
			ft::vector<int> second (4,100);                       // four ints with value 100
			ft::vector<int> third (second.begin(),second.end());  // iterating through second
			ft::vector<int> fourth (third);                       // a copy of third

			// the iterator constructor can also be used to construct from arrays:
			int myints[] = {16,2,77,29};
			ft::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

			std::cout << "The contents of fifth are:";
			for (ft::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
				std::cout << ' ' << *it;
			std::cout << '\n';
		}
		std::cout << std::endl << "//		OPERATOR =" << std::endl;
		{
			ft::vector<int> foo (3,0);
			ft::vector<int> bar (5,0);

			bar = foo;
			foo = ft::vector<int>();

			std::cout << "Size of foo: " << int(foo.size()) << '\n';
			std::cout << "Size of bar: " << int(bar.size()) << '\n';
		}		
	}


	std::cout << std::endl << std::endl << "//	ITERATOR";
	{
		std::cout << std::endl << "//		BEGIN END" << std::endl;
		{
			ft::vector<int> myvector;
			for (int i=1; i<=5; i++) myvector.push_back(i);

			std::cout << "myvector contains:";
			for (ft::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
				std::cout << ' ' << *it;
			std::cout << '\n';
		}
		std::cout << std::endl << "//		REVERSE BEGIN END" << std::endl;
		{
			ft::vector<int> myvector (5);  // 5 default-constructed ints
			int i = 0;

			ft::vector<int>::reverse_iterator rit = myvector.rbegin();
			for (; rit!= myvector.rend(); ++rit)
			{
				*rit = ++i;
			}
			std::cout << "myvector contains:";
			for (ft::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
				std::cout << ' ' << *it;
			std::cout << '\n';
		}
	}


	std::cout <<std::endl << std::endl << "//	CAPACITY";
	{

		std::cout << std::endl << "//		SIZE" << std::endl;
		{
			ft::vector<int> myints;
			std::cout << "0. size: " << myints.size() << '\n';

			for (int i=0; i<10; i++) myints.push_back(i);
			std::cout << "1. size: " << myints.size() << '\n';

			std::cout << "2. size: " << myints.size() << '\n';

			std::cout << "3. size: " << myints.size() << '\n';
		}
		std::cout << std::endl << "//		MAX_SIZE & CAPACITY" << std::endl;
		{
			ft::vector<int> myvector;

			// set some content in the vector:
			for (int i=0; i<100; i++) myvector.push_back(i);

			std::cout << "size: " << myvector.size() << "\n";
			std::cout << "capacity: " << myvector.capacity() << "\n";
			std::cout << "max_size: " << myvector.max_size() << "\n";
		}
		std::cout << std::endl << "//		EMPTY" << std::endl;
		{
			ft::vector<int> myvector;
			int sum (0);

			for (size_t i = 1; i <= 10; i++) myvector.push_back(static_cast<int>(i));

			while (!myvector.empty())
			{
				sum += myvector.back();
				myvector.pop_back();
			}

			std::cout << "total: " << sum << '\n';
		}
		std::cout << std::endl << "//		RESIZE" << std::endl;
		{
			ft::vector<int> myvector;
			vector_contain(myvector);

			myvector.resize(2);
			vector_contain(myvector);
			myvector.resize(3);
			vector_contain(myvector);
			myvector.resize(8);
			vector_contain(myvector);
			myvector.resize(12);
			vector_contain(myvector);

			ft::vector<int>	bar;
			size_t sz = bar.capacity();
			for (size_t i = 0; i < 300; i += 5)
			{
				bar.resize(i);
				if (sz != bar.capacity())
				{
					std::cout << "capacity change " << bar.capacity() << "; at " << i << std::endl;
					sz = bar.capacity();
				}
			}
		}
		std::cout << std::endl << "//		RESERVE" << std::endl;
		{
			ft::vector<int>::size_type sz;

			ft::vector<int> foo;
			sz = foo.capacity();
			std::cout << "making foo grow:\n";
			for (int i=0; i<100; ++i) {
				foo.push_back(i);
				if (sz!=foo.capacity()) {
					sz = foo.capacity();
					std::cout << "capacity changed: " << sz << '\n';
				}
			}

			ft::vector<int> bar;
			sz = bar.capacity();
			bar.reserve(100);   // this is the only difference with foo above
			std::cout << "making bar grow:\n";
			for (int i=0; i<300; ++i) {
				bar.push_back(i);
				if (sz!=bar.capacity())
				{
					sz = bar.capacity();
					std::cout << "capacity changed: " << sz << '\n';
				}
			}
		}
	}


	std::cout << std::endl << std::endl << "//	ACCES";
	{
		std::cout << std::endl << "//		AT" << std::endl;
		{
			ft::vector<int> myvector (10);   // 10 zero-initialized ints

			for (size_t i = 0; i < myvector.size(); i++)
				myvector.at(i) = static_cast<int>(i);

			std::cout << "myvector contains:";
			for (size_t i = 0; i < myvector.size(); i++)
				std::cout << ' ' << myvector.at(i);
			std::cout << '\n';

		}
		std::cout << std::endl << "//		FRONT" << std::endl;
		{
			ft::vector<int> myvector;

			myvector.push_back(78);
			myvector.push_back(16);



			myvector.front() -= myvector.back();

			std::cout << "myvector.front() is now " << myvector.front() << '\n';

		}
		std::cout << std::endl << "//		BACK" << std::endl;
		{
			ft::vector<int> myvector;

			myvector.push_back(10);

			while (myvector.back() != 0)
			{
				myvector.push_back ( myvector.back() -1 );
			}

			std::cout << "myvector contains:";
			for (size_t i=0; i<myvector.size() ; i++)
				std::cout << ' ' << myvector[i];
			std::cout << '\n';
		}
		std::cout << std::endl << "//		OPERATOR []" << std::endl;
		{
			ft::vector<int> myvector (10);   // 10 zero-initialized elements
			ft::vector<int>::size_type sz = myvector.size();

			for (size_t i = 0; i < sz; i++) myvector[i] = static_cast<int>(i);

			for (size_t i = 0; i < sz / 2; i++)
			{
				int temp;
				temp = myvector[sz-1-i];
				myvector[sz-1-i]=myvector[i];
				myvector[i]=temp;
			}

			std::cout << "myvector contains:";
			for (size_t i = 0; i < sz; i++)
				std::cout << ' ' << myvector[i];
			std::cout << '\n';
		}
	}


	std::cout << std::endl << std::endl << "//	MODIFIERS";
	{
		std::cout << std::endl << "//		PUSH_BACK" << std::endl;
		{
			ft::vector<int> myvector;
			//	int myint;

			//	std::cout << "Please enter some integers (enter 0 to end):\n";

			int i = 0;
			do {
				myvector.push_back (42);
			} while (++i < 100);

			std::cout << "myvector stores " << int(myvector.size()) << " numbers.\n";
		}
		std::cout << std::endl << "//		POP_BACK" << std::endl;
		{
			ft::vector<int> myvector;
			int sum (0);
			myvector.push_back (100);
			myvector.push_back (200);
			myvector.push_back (300);

			while (!myvector.empty())
			{
				sum+=myvector.back();
				myvector.pop_back();
			}

			std::cout << "The elements of myvector add up to " << sum << '\n';
		}
		std::cout << std::endl << "//		SWAP" << std::endl;
		{
			ft::vector<int> foo (4,100);   // three ints with a value of 100
			ft::vector<int> bar (16,200);   // five ints with a value of 200

			std::cout << "foo " << foo.capacity()<<  "; bar " << bar.capacity() << std::endl; 

			foo.swap(bar);

			std::cout << "foo contains:";
			for (unsigned i=0; i<foo.size(); i++)
				std::cout << ' ' << foo[i];
			std::cout << '\n';

			std::cout << "bar contains:";
			for (unsigned i=0; i<bar.size(); i++)
				std::cout << ' ' << bar[i];
			std::cout << '\n';
			std::cout << "foo " << foo.capacity()<<  "; bar " << bar.capacity() << std::endl; 

		}
		std::cout << std::endl << "//		ASSIGN" << std::endl;
		{
			ft::vector<int> first;
			ft::vector<int> second;
			//ft::vector<int> third;

			first.assign (7,100);             // 7 ints with a value of 100

			ft::vector<int>::iterator it;
			it = first.begin() + 1;

			//	second.assign (it,first.end()-1); // the 5 central values of first

			//			int myints[] = {1776,7,4};
			//			third.assign (myints,myints+3);   // assigning from array.

			std::cout << "Size of first: " << int (first.size()) << '\n';
			std::cout << "Size of second: " << int (second.size()) << '\n';
			//			std::cout << "Size of third: " << int (third.size()) << '\n';
		}
		std::cout << std::endl << "//		INSERT" << std::endl;
		{
			ft::vector<int> myvector (8,100);
			ft::vector<int>::iterator it;

			it = myvector.begin();
			it += 3;
			it = myvector.insert ( it , 200 );


			myvector.insert (it,42,300);

			// "it" no longer valid, get a new one:
			it = myvector.begin();

			ft::vector<int> anothervector (2,400);
			myvector.insert (it+2,anothervector.begin(),anothervector.end());

			//			int myarray [] = { 501,502,503 };
			//			myvector.insert (myvector.begin(), myarray, myarray+3);

			std::cout << "myvector contains:";
			for (it=myvector.begin(); it<myvector.end(); it++)
				std::cout << ' ' << *it;
			std::cout << '\n';

			std::cout << myvector.size() << " " << myvector.capacity() << std::endl;

		}
		std::cout << std::endl << "//		ERASE" << std::endl;
		{
			ft::vector<int> myvector;

			// set some values (from 1 to 10)
			for (int i=1; i<=10; i++) myvector.push_back(i);

			// erase the 6th element
			myvector.erase (myvector.begin()+5);

			// erase the first 3 elements:
			myvector.erase (myvector.begin(),myvector.begin()+3);

			std::cout << "myvector contains:";
			for (unsigned i=0; i<myvector.size(); ++i)
				std::cout << ' ' << myvector[i];
			std::cout << '\n';
			std::cout << myvector.size() << " " << myvector.capacity() << std::endl;
		}
		std::cout << std::endl << "//		CLEAR" << std::endl;
		{
			ft::vector<int> myvector;
			myvector.push_back (100);
			myvector.push_back (200);
			myvector.push_back (300);

			std::cout << "myvector contains:";
			for (unsigned i=0; i<myvector.size(); i++)
				std::cout << ' ' << myvector[i];
			std::cout << '\n';

			myvector.clear();
			myvector.push_back (1101);
			myvector.push_back (2202);

			std::cout << "myvector contains:";
			for (unsigned i=0; i<myvector.size(); i++)
				std::cout << ' ' << myvector[i];
			std::cout << '\n';
		}
	}


	std::cout << std::endl << std::endl << "//	ALLOCATOR" << std::endl;
	{
		ft::vector<int> myvector;
		int * p;
		unsigned int i;

		// allocate an array with space for 5 elements using vector's allocator:
		p = myvector.get_allocator().allocate(5);

		// construct values in-place on the array:
		for (i=0; i<5; i++) myvector.get_allocator().construct(&p[i],static_cast<const int>(i));

		std::cout << "The allocated array contains:";
		for (i=0; i<5; i++) std::cout << ' ' << p[i];
		std::cout << '\n';

		// destroy and deallocate:
		for (i=0; i<5; i++) myvector.get_allocator().destroy(&p[i]);
		myvector.get_allocator().deallocate(p,5);
	}


	std::cout << std::endl << std::endl << "//	RELATIONAL OPERATORS" << std::endl;
	{
		ft::vector<int> foo (3,100);   // three ints with a value of 100
		ft::vector<int> bar (2,200);   // two ints with a value of 200

		if (foo==bar) std::cout << "foo and bar are equal\n";
		if (foo!=bar) std::cout << "foo and bar are not equal\n";
		if (foo< bar) std::cout << "foo is less than bar\n";
		if (foo> bar) std::cout << "foo is greater than bar\n";
		if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
		if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
	}


	std::cout << std::endl << std::endl << "//	NON MEMBER SWAP" << std::endl;
	{
		ft::vector<int> foo (3,100);   // three ints with a value of 100
		ft::vector<int> bar (5,200);   // five ints with a value of 200

		ft::swap(foo, bar);

		std::cout << "foo contains:";
		for (ft::vector<int>::iterator it = foo.begin(); it!=foo.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';

		std::cout << "bar contains:";
		for (ft::vector<int>::iterator it = bar.begin(); it!=bar.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}

}


/*
//-std=c++11
#include <type_traits>//enable_if is_integral


// 1. the return type (bool) is only valid if T is an integral type:
template <class T>
typename ft::enable_if<ft::is_integral<T>::value,bool>::type
is_odd (T i) {return bool(i%2);}
// 2. the second template argument is only valid if T is an integral type:
template < class T,
class = typename ft::enable_if<ft::is_integral<T>::value>::type>
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
typedef ft::iterator_traits<int*> traits;
if (typeid(traits::iterator_category)==typeid(ft::random_access_iterator_tag))
std::cout << "int* is a random-access iterator\n";

typedef ft::iterator_traits<ft::vector<int>::iterator> vectraits;
if (typeid(vectraits::iterator_category)==typeid(ft::random_access_iterator_tag))
std::cout << "vector<int> is a random-access iterator\n";
}
std::cout << std::endl << "//	REVERSE_ITERATOR" << std::endl;
{
ft::vector<int> myvector;

for (int i=0; i<10; i++)
myvector.push_back(i);

typedef ft::vector<int>::iterator iter_type;
// ? 0 1 2 3 4 5 6 7 8 9 ?
iter_type from (myvector.begin());                     //   ^
//         ------>
iter_type until (myvector.end());                      //                       ^
//
ft::reverse_iterator<iter_type> rev_until (from);     // ^
//         <------
ft::reverse_iterator<iter_type> rev_from (until);     //                     ^

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
	std::cout << "char: " << ft::is_integral<char>::value << std::endl;
	std::cout << "int: " << ft::is_integral<int>::value << std::endl;
	std::cout << "float: " << ft::is_integral<float>::value << std::endl;
	std::cout << "iterator: " << ft::is_integral<ft::vector<int>::iterator>::value << std::endl;

}
std::cout << std::endl << "//	EQUAL" << std::endl;
{
	int myints[] = {20,40,60,80,100};               //   myints: 20 40 60 80 100
	ft::vector<int>myvector (myints,myints+5);     // myvector: 20 40 60 80 100

	// using default comparison:
	if ( ft::equal (myvector.begin(), myvector.end(), myints) )
		std::cout << "The contents of both sequences are equal.\n";
	else
		std::cout << "The contents of both sequences differ.\n";

	myvector[3]=81;                                 // myvector: 20 40 60 81 100

	// using predicate comparison:
	if ( ft::equal (myvector.begin(), myvector.end(), myints, mypredicate) )
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
	std::cout << ft::lexicographical_compare(foo,foo+5,bar,bar+9);
	std::cout << '\n';

	std::cout << "Using mycomp as comparison object: ";
	std::cout << ft::lexicographical_compare(foo,foo+5,bar,bar+9,mycomp);
	std::cout << '\n';


}

}

}
*/


#include "map.hpp"
#include <map>
#include <string>


void	map_test()
{
	ft::map<std::string, int> mymap;



	std::cout << "//" <<			"MAP" << std::endl;
	/*	std::cout << "//\t" <<			"CONSTRUCTOR" << std::endl;
		{
		bool fncomp (char lhs, char rhs) {return lhs<rhs;}

		struct classcomp {
		bool operator() (const char& lhs, const char& rhs) const
		{return lhs<rhs;}
		};

		std::map<char,int> first;

		first['a']=10;
		first['b']=30;
		first['c']=50;
		first['d']=70;

		std::map<char,int> second (first.begin(),first.end());

		std::map<char,int> third (second);

		std::map<char,int,classcomp> fourth;                 // class as Compare

		bool(*fn_pt)(char,char) = fncomp;
		std::map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare
		}

		std::cout << "//\t" <<			"OBSERVERS" << std::endl;
		{
		std::cout << "//\t\t" <<	"VALUE_COMP" << std::endl;
		{
		std::map<char,int> mymap;

		mymap['x']=1001;
		mymap['y']=2002;
		mymap['z']=3003;

		std::cout << "mymap contains:\n";

		std::pair<char,int> highest = *mymap.rbegin();          // last element

		std::map<char,int>::iterator it = mymap.begin();
		do {
		std::cout << it->first << " => " << it->second << '\n';
		} while ( mymap.value_comp()(*it++, highest) );
		}
		std::cout << "//\t\t" <<	"KEY_COMP" << std::endl;
		{
		std::map<char,int> mymap;

		std::map<char,int>::key_compare mycomp = mymap.key_comp();

		mymap['a']=100;
		mymap['b']=200;
		mymap['c']=300;

		std::cout << "mymap contains:\n";

		char highest = mymap.rbegin()->first;     // key value of last element

		std::map<char,int>::iterator it = mymap.begin();
		do {
		std::cout << it->first << " => " << it->second << '\n';
		} while ( mycomp((*it++).first, highest) );

		std::cout << '\n';

		}
		}
	 */




}



int main()
{

	//	vector_test();

	//	utils_test();

	map_test();




	//	auto stop = high_resolution_clock::now();
	//	auto duration = duration_cast<microseconds>(stop - start);
	//	std::cout << duration.count() << std::endl;

	return (0);
}

