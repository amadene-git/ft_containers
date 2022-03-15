#include "include.hpp"


/* ******************* ENABLE_IF ************************************



// 1. the return type (bool) is only valid if T is an integral type:
template <class T>
typename std::enable_if<std::is_integral<T>::value,bool>::type
  is_odd (T i) {return bool(i%2);}

// 2. the second template argument is only valid if T is an integral type:
template < class T,
           class = typename std::enable_if<std::is_integral<T>::value>::type>
bool is_even (T i) {return !bool(i%2);}

void	enable_if_test()
{
	short int i = 1;    // code does not compile if type of i is not integral

	std::cout << std::boolalpha;
	std::cout << "i is odd: " << is_odd(i) << std::endl;
	std::cout << "i is even: " << is_even(i) << std::endl;
}

*/

//for equal test
bool mypredicate (int i, int j) {
  return (i==j);
}

//for lexicographical_compare
bool mycomp (char c1, char c2)
{ return std::tolower(c1)<std::tolower(c2); }

void	utils_test()
{
	std::cout << 			"//UTILS" << std::endl;
	std::cout << "\n\t\t"		"//ITERATOR_TRAITS" << std::endl;
	{
		typedef NAMESPACE::iterator_traits<int*> traits;
		if (typeid(traits::iterator_category)==typeid(std::random_access_iterator_tag))
			std::cout << "int* is a random-access iterator";
	}
	std::cout << "\n\t\t"		"//REVERSE_ITERATOR" << std::endl;
	std::cout << "\n\t\t\t" <<	"//CONSTRUCTOR && OPERATOR * ++ " << std::endl;
	{
		NAMESPACE::vector<int> myvector;
 		for (int i=0; i<10; i++) myvector.push_back(i);

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
	std::cout << "\n\t\t\t" <<	"//BASE" << std::endl;
	{
		NAMESPACE::vector<int> myvector;
  		for (int i=0; i<10; i++) myvector.push_back(i);

  		typedef NAMESPACE::vector<int>::iterator iter_type;

  		NAMESPACE::reverse_iterator<iter_type> rev_end (myvector.begin());
  		NAMESPACE::reverse_iterator<iter_type> rev_begin (myvector.end());

  		std::cout << "myvector:";
  		for (iter_type it = rev_end.base(); it != rev_begin.base(); ++it)
  		  std::cout << ' ' << *it;
  		std::cout << '\n';
	}
	std::cout << "\n\t\t\t" <<	"//OPERATOR +" << std::endl;
	{
		NAMESPACE::vector<int> myvector;
  		for (int i=0; i<10; i++) myvector.push_back(i);	// myvector: 0 1 2 3 4 5 6 7 8 9

  		typedef NAMESPACE::vector<int>::iterator iter_type;

  		NAMESPACE::reverse_iterator<iter_type> rev_it;

  		rev_it = myvector.rbegin() +3;

  		std::cout << "The fourth element from the end is: " << *rev_it << '\n';
	}
	std::cout << "\n\t\t\t" <<	"//OPERATOR +=" << std::endl;
	{
		NAMESPACE::vector<int> myvector;
		for (int i=0; i<10; i++) myvector.push_back(i);	// myvector: 0 1 2 3 4 5 6 7 8 9

		typedef NAMESPACE::vector<int>::iterator iter_type;

		NAMESPACE::reverse_iterator<iter_type> rev_iterator = myvector.rbegin();

		rev_iterator += 2;

		std::cout << "The third element from the end is: " << *rev_iterator << '\n';
	}
	std::cout << "\n\t\t\t" <<	"//OPERATOR -" << std::endl;
	{
		NAMESPACE::vector<int> myvector;
		for (int i=0; i<10; i++) myvector.push_back(i);	// myvector: 0 1 2 3 4 5 6 7 8 9

		typedef NAMESPACE::vector<int>::iterator iter_type;

		NAMESPACE::reverse_iterator<iter_type> rev_iterator;

		rev_iterator = myvector.rend() - 3;

		std::cout << "myvector.rend()-3 points to: " << *rev_iterator << '\n';
	}
	std::cout << "\n\t\t\t" <<	"//OPERATOR --" << std::endl;
	{
		NAMESPACE::vector<int> myvector;
		for (int i=0; i<10; i++) myvector.push_back(i);

		typedef NAMESPACE::vector<int>::iterator iter_type;

		NAMESPACE::reverse_iterator<iter_type> rev_begin (myvector.end());
		NAMESPACE::reverse_iterator<iter_type> rev_end (myvector.begin());

		NAMESPACE::reverse_iterator<iter_type> rev_iterator = rev_begin;
		while ( rev_iterator != rev_end )
		  std::cout << *rev_iterator++ << ' ';
		std::cout << '\n';

		while ( rev_iterator != rev_begin )
		  std::cout << *(--rev_iterator) << ' ';
		std::cout << '\n';
	}
	std::cout << "\n\t\t\t" <<	"//OPERATOR -=" << std::endl;
	{
		NAMESPACE::vector<int> myvector;
		for (int i=0; i<10; i++) myvector.push_back(i);	// myvector: 0 1 2 3 4 5 6 7 8 9

		typedef NAMESPACE::vector<int>::iterator iter_type;

		NAMESPACE::reverse_iterator<iter_type> rev_iterator = myvector.rend();

		rev_iterator -= 4;

		std::cout << "rev_iterator now points to: " << *rev_iterator << '\n';
	}
	std::cout << "\n\t\t\t" <<	"//OPERATOR ->" << std::endl;
	{
		NAMESPACE::map<int,std::string> numbers;
		numbers.insert (NAMESPACE::make_pair(1,"one"));
		numbers.insert (NAMESPACE::make_pair(2,"two"));
		numbers.insert (NAMESPACE::make_pair(3,"three"));

		typedef NAMESPACE::map<int,std::string>::iterator map_iter;

		NAMESPACE::reverse_iterator<map_iter> rev_end (numbers.begin());

		NAMESPACE::reverse_iterator<map_iter> rev_iterator (numbers.end());

		for ( ; rev_iterator != rev_end ; ++rev_iterator )
    	std::cout << rev_iterator->first << ' ' << rev_iterator->second << '\n';
	}
	std::cout << "\n\t\t\t" <<	"//OPERATOR []" << std::endl;
	{
		NAMESPACE::vector<int> myvector;
		for (int i=0; i<10; i++) myvector.push_back(i);  // myvector: 0 1 2 3 4 5 6 7 8 9

		typedef NAMESPACE::vector<int>::iterator iter_type;

		NAMESPACE::reverse_iterator<iter_type> rev_iterator = myvector.rbegin();

		std::cout << "The fourth element from the end is: " << rev_iterator[3] << '\n';
	}
	std::cout << "\n\t\t" <<	"//NON MEMBER " << std::endl;
	std::cout << "\n\t\t\t" <<	"//RELATIONAL OPERATORS" << std::endl;
	{
		NAMESPACE::vector<int> myvector(20, 12);
		
		NAMESPACE::vector<int>::reverse_iterator rbe = myvector.rbegin();
		NAMESPACE::vector<int>::reverse_iterator ren = myvector.rend();

		if (rbe==ren) std::cout << "rbe and ren are equal\n";
		if (rbe!=ren) std::cout << "rbe and ren are not equal\n";
		if (rbe< ren) std::cout << "rbe is less than ren\n";
		if (rbe> ren) std::cout << "rbe is greater than ren\n";
		if (rbe<=ren) std::cout << "rbe is less than or equal to ren\n";
		if (rbe>=ren) std::cout << "rbe is greater than or equal to ren\n";

		rbe += 3;
		ren = rbe;

		if (rbe==ren) std::cout << "rbe and ren are equal\n";
		if (rbe!=ren) std::cout << "rbe and ren are not equal\n";
		if (rbe< ren) std::cout << "rbe is less than ren\n";
		if (rbe> ren) std::cout << "rbe is greater than ren\n";
		if (rbe<=ren) std::cout << "rbe is less than or equal to ren\n";
		if (rbe>=ren) std::cout << "rbe is greater than or equal to ren\n";

	}
	std::cout << "\n\t\t\t" <<	"//OPERATOR +" << std::endl;
	{

		NAMESPACE::vector<int> myvector;
  		for (int i=0; i<10; i++) myvector.push_back(i);	// myvector: 0 1 2 3 4 5 6 7 8 9

  		typedef NAMESPACE::vector<int>::iterator iter_type;

  		NAMESPACE::reverse_iterator<iter_type> rev_it;

  		rev_it = 3 + myvector.rbegin();

  		std::cout << "The fourth element from the end is: " << *rev_it << '\n';

	}
	std::cout << "\n\t\t\t" <<	"//OPERATOR -" << std::endl;
	{
		NAMESPACE::vector<int> myvector;
		for (int i=0; i<10; i++) myvector.push_back(i);

		NAMESPACE::reverse_iterator<NAMESPACE::vector<int>::iterator> from,until;

		from = myvector.rbegin();
		until = myvector.rend();

		std::cout << "myvector has " << (until-from) << " elements.\n";
	}


	// std::cout << "\n\t" <<	"//ENABLE_IF" << std::endl;
	// {
	// 	enable_if_test();
	// }

	std::cout << "\n\t" <<	"//EQUAL" << std::endl;
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
	std::cout << "\n\t" <<	"//LEXICOGRIPHICAL_COMPARE" << std::endl;
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
	}
	
	std::cout << "\n\t" <<		"//PAIR" << std::endl;
	std::cout << "\n\t\t" <<	"//CONSTRUCTOR" << std::endl;
	{
		NAMESPACE::pair <std::string,double> product1;                     // default constructor
  		NAMESPACE::pair <std::string,double> product2 ("tomatoes",2.30);   // value init
  		NAMESPACE::pair <std::string,double> product3 (product2);          // copy constructor
		
  		product1 = NAMESPACE::make_pair(std::string("lightbulbs"),0.99);   // using make_pair (move)
		
  		product2.first = "shoes";                  // the type of first is string
  		product2.second = 39.90;                   // the type of second is double
		
  		std::cout << "The price of " << product1.first << " is $" << product1.second << '\n';
  		std::cout << "The price of " << product2.first << " is $" << product2.second << '\n';
  		std::cout << "The price of " << product3.first << " is $" << product3.second << '\n';
	}
	std::cout << "\n\t\t" <<	"//OPERATOR =" << std::endl;
	{
		NAMESPACE::pair <std::string,int> planet, homeplanet;

		planet = NAMESPACE::make_pair("Earth",6371);

		homeplanet = planet;

		std::cout << "Home planet: " << homeplanet.first << '\n';
		std::cout << "Planet size: " << homeplanet.second << '\n';
	}
	std::cout << "\n\t\t" <<	"//RELATIONAL OPERATOR" << std::endl;
	{
		NAMESPACE::pair<int,char> foo (10,'z');
  		NAMESPACE::pair<int,char> bar (90,'a');

  		if (foo==bar) std::cout << "foo and bar are equal\n";
  		if (foo!=bar) std::cout << "foo and bar are not equal\n";
  		if (foo< bar) std::cout << "foo is less than bar\n";
  		if (foo> bar) std::cout << "foo is greater than bar\n";
  		if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
  		if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
	}


	std::cout << "\n\t" <<		"//MAKE_PAIR" << std::endl;
	{
		NAMESPACE::pair <int,int> foo;
		NAMESPACE::pair <int,int> bar;

		foo = NAMESPACE::make_pair (10,20);
		bar = NAMESPACE::make_pair (10.5,'A'); // ok: implicit conversion from pair<double,char>

		std::cout << "foo: " << foo.first << ", " << foo.second << '\n';
		std::cout << "bar: " << bar.first << ", " << bar.second << '\n';
	}

}
