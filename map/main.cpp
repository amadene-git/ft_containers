#include "map.hpp"
#include <map>
#include <iostream>
#include <string>

#include <sys/time.h>

int	getrandom(int max)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);


	return ((tv.tv_usec * tv.tv_sec) % max);
}



int main()
{
	std::cout << 			"//MAP" << std::endl;
/*
	std::cout << "\t" << 	"//CAPACITY" << std::endl;
	std::cout << "\t\t" <<	"//EMPTY" << std::endl;
	{
		ft::map<char,int> mymap;

		mymap['a']=10;
		mymap['b']=20;
		mymap['c']=30;

		while (!mymap.empty())
		{
			std::cout << mymap.begin()->first << " => " << mymap.begin()->second << '\n';
			mymap.erase(mymap.begin());
		}

	}
	std::cout << "\t\t" <<	"//SIZE" << std::endl;
	{
		ft::map<char,int> mymap;
		mymap['a']=101;
		mymap['b']=202;
		mymap['c']=302;

		std::cout << "mymap.size() is " << mymap.size() << '\n';

	}
	std::cout << "\t\t" <<	"//MAX_SIZE" << std::endl;
	{
		int i;
		ft::map<int,int> mymap;

		if (mymap.max_size()>1000)
		{
			for (i=0; i<1000; i++) mymap[i]=0;
			std::cout << "The map contains 1000 elements.\n";
		}
		else std::cout << "The map could not hold 1000 elements.\n";
	}	
*/	
	std::cout << "\n\t" <<	"//MODIFIERS" << std::endl;
	std::cout << "\t\t" <<	"//INSERT" << std::endl;
	{
		ft::map<char,int> mymap;

		// first insert function version (single parameter):
		mymap.insert( ft::pair<char,int>('a', 100) );
		mymap.insert( ft::pair<char,int>('z', 200) );

		ft::pair<ft::map<char,int>::iterator,bool> ret;
		ret = mymap.insert( ft::pair<char,int>('z', 500) );
		if (ret.second == false) {
			std::cout << "element 'z' already existed";
			std::cout << " with a value of " << ret.first->second << '\n';
		}

		// second insert function version (with hint position):
		ft::map<char,int>::iterator it = mymap.begin();
		mymap.insert (it, ft::pair<char,int>('b', 300));  // max efficiency inserting
		mymap.insert (it, ft::pair<char,int>('c', 400));  // no max efficiency inserting

		// third insert function version (range insertion):
		ft::map<char,int> anothermap;
		anothermap.insert(mymap.begin(), mymap.find('c'));

		// showing contents:
		std::cout << "mymap contains:\n";
		for (it = mymap.begin(); it != mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';

		std::cout << "anothermap contains:\n";
		for (it = anothermap.begin(); it != anothermap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
	}
	std::cout << "\t\t" <<	"SWAP" << std::endl;
	{
		ft::map<char,int> foo,bar;

		foo['x']=100;
		foo['y']=200;
		
		bar['a']=11;
		bar['b']=22;
		bar['c']=33;
		
		foo.swap(bar);
		
		std::cout << "foo contains:\n";
		for (ft::map<char,int>::iterator it = foo.begin(); it != foo.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
		
		std::cout << "bar contains:\n";
		for (ft::map<char,int>::iterator it = bar.begin(); it != bar.end(); ++it)
    		std::cout << it->first << " => " << it->second << '\n';
	}
	std::cout << "\t\t" << "CLEAR" << std::endl;
	{
		ft::map<char,int> mymap;

		mymap['x'] = 100;
		mymap['y'] = 200;
		mymap['z'] = 300;

		std::cout << "mymap contains:\n";
		for (ft::map<char,int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';

		mymap.clear();
		mymap['a'] = 1101;
		mymap['b'] = 2202;

		std::cout << "mymap contains:\n";
		for (ft::map<char,int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
	}
	

	std::cout << "\n\t" <<	"//ITERATOR" << std::endl;
	std::cout << "\t\t" <<	"//BEGIN & END" << std::endl;
	{
		ft::map<char,int> mymap;

		mymap['b'] = 100;
		mymap['a'] = 200;
		mymap['c'] = 300;

		// show content:
		for (ft::map<char,int>::iterator it = mymap.begin() ; it != mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';

	}
	std::cout << "\t\t" << "//REVERSE BEGIN & END" << std::endl;
	{
		ft::map<char,int> mymap;

		mymap['x'] = 100;
		mymap['y'] = 200;
		mymap['z'] = 300;
	
		// show content:
		ft::map<char,int>::reverse_iterator rit;
		
		for (rit = mymap.rbegin(); rit != mymap.rend(); ++rit)
			std::cout << rit->first << " => " << rit->second << '\n';
	}

	std::cout << "\n\t" <<	"//ELEMENT ACCES" << std::endl;
	std::cout << "\t\t" <<	"//OPERATOR []" << std::endl;
	{
		ft::map<char,std::string> mymap;

		mymap['a'] = "an element";
		mymap['b'] = "another element";
		mymap['c'] = mymap['b'];

		std::cout << "mymap['a'] is " << mymap['a'] << '\n';
		std::cout << "mymap['b'] is " << mymap['b'] << '\n';
		std::cout << "mymap['c'] is " << mymap['c'] << '\n';
		std::cout << "mymap['d'] is " << mymap['d'] << '\n';

		std::cout << "mymap now contains " << mymap.size() << " elements.\n";
	}
	
	std::cout << "\n\t" <<	"//OBSERVERS" << std::endl;
	std::cout << "\t\t" <<	"//KEY_COMP" << std::endl;
	{
		ft::map<char,int> mymap;

		ft::map<char,int>::key_compare mycomp = mymap.key_comp();

		mymap['a'] = 100;
		mymap['b'] = 200;
		mymap['c'] = 300;

		std::cout << "mymap contains:\n";

		char highest = mymap.rbegin()->first;     // key value of last element

		ft::map<char,int>::iterator it = mymap.begin();
		do {
			std::cout << it->first << " => " << it->second << '\n';
		}while( mycomp((*it++).first, highest) );

		std::cout << '\n';

	}
	std::cout << "\t\t" <<	"//VALUE_COMP" << std::endl;
	{
		ft::map<char,int> mymap;

  		mymap['x'] = 1001;
  		mymap['y'] = 2002;
  		mymap['z'] = 3003;

  		std::cout << "mymap contains:\n";

  		ft::pair<char,int> highest = *mymap.rbegin();          // last element

  		ft::map<char,int>::iterator it = mymap.begin();
  		do 
		{
  			std::cout << it->first << " => " << it->second << '\n';
  		} while( mymap.value_comp()(*it++, highest) );
	}

	std::cout << "\n\t" <<	"//OPERATION" << std::endl;
/*
	std::cout << "\t\t" <<	"//FIND" << std::endl;
	{
		std::map<char,int> mymap;
		std::map<char,int>::iterator it;

		mymap['a']=50;
		mymap['b']=100;
		mymap['c']=150;
		mymap['d']=200;

		it = mymap.find('b');
		if (it != mymap.end())
			mymap.erase (it);

		// print content:
		std::cout << "elements in mymap:" << '\n';
		std::cout << "a => " << mymap.find('a')->second << '\n';
		std::cout << "c => " << mymap.find('c')->second << '\n';
		std::cout << "d => " << mymap.find('d')->second << '\n';
	}
*/
	std::cout << "\t\t" <<	"//COUNT" << std::endl;
	{
		std::map<char,int> mymap;
		char c;

		mymap['a'] = 101;
		mymap['c'] = 202;
		mymap['f'] = 303;
	
		for (c = 'a'; c < 'h'; c++)
		{
			std::cout << c;
			if (mymap.count(c) > 0)
				std::cout << " is an element of mymap.\n";
			else 
				std::cout << " is not an element of mymap.\n";
		}
	}
	std::cout << "\t\t" <<	"//LOWER/UPPER BOUND" << std::endl;
	{
		ft::map<char,int> mymap;
		ft::map<char,int>::iterator	itlow, itup;

		mymap['a'] = 20;
		mymap['f'] = 40;
		mymap['m'] = 60;
		mymap['w'] = 80;
		mymap['y'] = 100;

		for (char a = 'a'; a < 'z'; ++a)
		{
			itlow = mymap.lower_bound (a);  // itlow points to b
			itup = mymap.upper_bound (a);   // itup points to e (not d!)

			if (itlow != mymap.end())
				std::cout << "low -> " << itlow->first << std::endl;
			if (itup != mymap.end())
				std::cout << "up -> " << itup->first << std::endl;
		}
		// std::cout << "up  -> " << itup->first << std::endl;
		// mymap.erase(itlow,itup);        // erases [itlow,itup)

		// print content:
		for (ft::map<char,int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
	}
	std::cout << "\t\t" <<	"//EQUAL_RANGE" << std::endl;
	{
		ft::map<char,int> mymap;


		for (char c = 'a'; c < 'z'; c += 3)
			mymap[c] = c * 12;

		ft::pair<ft::map<char,int>::iterator,ft::map<char,int>::iterator> ret;

		for (char c = 'a'; c < 'z'; c++)
		{
			ret = mymap.equal_range('b');

			std::cout << "lower bound points to: ";
			std::cout << ret.first->first << " => " << ret.first->second << '\n';

			std::cout << "upper bound points to: ";
			std::cout << ret.second->first << " => " << ret.second->second << '\n';
		}
	}
	std::cout << "\n\t" <<	"//GET_ALLOCATOR" << std::endl;
	{
		int psize;
  		std::map<char,int> mymap;
  		std::pair<const char,int>* p;
		
  		// allocate an array of 5 elements using mymap's allocator:
  		p=mymap.get_allocator().allocate(5);
		
  		// assign some values to array
  		psize = sizeof(std::map<char,int>::value_type)*5;
		
  		std::cout << "The allocated array has a size of " << psize << " bytes.\n";
		
  		mymap.get_allocator().deallocate(p,5);
	}

	std::cout << "RANDOM" << std::endl;

	std::map<char, int> mymap;

	std::map<char, int>::iterator itend = mymap.end();

	std::map<char, int>::iterator it = mymap.lower_bound('a');

	std::cout << "->" <<  it->first << std::endl;
	std::cout << "end ->" <<  itend->first << std::endl;

	// pr.first = mymap.begin();



	// struct timeval tv1;
	// struct timeval tv2;
	// gettimeofday(&tv1, NULL);	

	// ft::map<int, int > mymap;



	// for (int i = 0; i < 20; ++i)
	// {
	// 	// int a = getrandom(100);
	// 	mymap.insert( ft::pair<const int, int>(i, i) );
	// }


	// gettimeofday(&tv2, NULL);
	// std::cout << (tv2.tv_sec * 1000000 + tv2.tv_usec) - (tv1.tv_sec * 1000000 + tv1.tv_usec) << std::endl;


	// print_btree(mymap.get_btree());

	
	// std::cout << mymap.find(42)->second << std::endl;

	return (0);

}
