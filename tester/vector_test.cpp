#include "include.hpp"


void	vector_contain(NAMESPACE::vector<int> &vec)
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
			NAMESPACE::vector<int> first;                                // empty vector of ints
			NAMESPACE::vector<int> second (4,100);                       // four ints with value 100
			NAMESPACE::vector<int> third (second.begin(),second.end());  // iterating through second
			NAMESPACE::vector<int> fourth (third);                       // a copy of third

			// the iterator constructor can also be used to construct from arrays:
			int myints[] = {16,2,77,29};
			NAMESPACE::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

			std::cout << "The contents of fifth are:";
			for (NAMESPACE::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
				std::cout << ' ' << *it;
			std::cout << '\n';
		}
		std::cout << std::endl << "//		OPERATOR =" << std::endl;
		{
			NAMESPACE::vector<int> foo (3,0);
			NAMESPACE::vector<int> bar (5,0);

			bar = foo;
			foo = NAMESPACE::vector<int>();

			std::cout << "Size of foo: " << int(foo.size()) << '\n';
			std::cout << "Size of bar: " << int(bar.size()) << '\n';
		}		
	}


	std::cout << std::endl << std::endl << "//	ITERATOR";
	{
		std::cout << std::endl << "//		BEGIN END" << std::endl;
		{
			NAMESPACE::vector<int> myvector;
			for (int i=1; i<=5; i++) myvector.push_back(i);

			std::cout << "myvector contains:";
			for (NAMESPACE::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
				std::cout << ' ' << *it;
			std::cout << '\n';
		}
		std::cout << std::endl << "//		REVERSE BEGIN END" << std::endl;
		{
			NAMESPACE::vector<int> myvector (5);  // 5 default-constructed ints
			int i = 0;

			NAMESPACE::vector<int>::reverse_iterator rit = myvector.rbegin();
			for (; rit!= myvector.rend(); ++rit)
			{
				*rit = ++i;
			}
			std::cout << "myvector contains:";
			for (NAMESPACE::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
				std::cout << ' ' << *it;
			std::cout << '\n';
		}
	}


	std::cout <<std::endl << std::endl << "//	CAPACITY";
	{

		std::cout << std::endl << "//		SIZE" << std::endl;
		{
			NAMESPACE::vector<int> myints;
			std::cout << "0. size: " << myints.size() << '\n';

			for (int i=0; i<10; i++) myints.push_back(i);
			std::cout << "1. size: " << myints.size() << '\n';

			std::cout << "2. size: " << myints.size() << '\n';

			std::cout << "3. size: " << myints.size() << '\n';
		}
		std::cout << std::endl << "//		MAX_SIZE & CAPACITY" << std::endl;
		{
			NAMESPACE::vector<int> myvector;

			// set some content in the vector:
			for (int i=0; i<100; i++) myvector.push_back(i);

			std::cout << "size: " << myvector.size() << "\n";
			std::cout << "capacity: " << myvector.capacity() << "\n";
			std::cout << "max_size: " << myvector.max_size() << "\n";
		}
		std::cout << std::endl << "//		EMPTY" << std::endl;
		{
			NAMESPACE::vector<int> myvector;
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
			NAMESPACE::vector<int> myvector;
			vector_contain(myvector);

			myvector.resize(2);
			vector_contain(myvector);
			myvector.resize(3);
			vector_contain(myvector);
			myvector.resize(8);
			vector_contain(myvector);
			myvector.resize(12);
			vector_contain(myvector);

			NAMESPACE::vector<int>	bar;
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
			NAMESPACE::vector<int>::size_type sz;

			NAMESPACE::vector<int> foo;
			sz = foo.capacity();
			std::cout << "making foo grow:\n";
			for (int i=0; i<100; ++i) {
				foo.push_back(i);
				if (sz!=foo.capacity()) {
					sz = foo.capacity();
					std::cout << "capacity changed: " << sz << '\n';
				}
			}

			NAMESPACE::vector<int> bar;
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


	std::cout << std::endl << "//	ACCES";
	{
		std::cout << std::endl << "//		OPERATOR []" << std::endl;
		{
			NAMESPACE::vector<int> myvector (10);   // 10 zero-initialized elements
			NAMESPACE::vector<int>::size_type sz = myvector.size();

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
		std::cout << std::endl << "//		AT" << std::endl;
		{
			NAMESPACE::vector<int> myvector (10);   // 10 zero-initialized ints

			for (size_t i = 0; i < myvector.size(); i++)
				myvector.at(i) = static_cast<int>(i);

			std::cout << "myvector contains:";
			for (size_t i = 0; i < myvector.size(); i++)
				std::cout << ' ' << myvector.at(i);
			std::cout << '\n';

		}
		std::cout << std::endl << "//		FRONT" << std::endl;
		{
			NAMESPACE::vector<int> myvector;

			myvector.push_back(78);
			myvector.push_back(16);



			myvector.front() -= myvector.back();

			std::cout << "myvector.front() is now " << myvector.front() << '\n';

		}
		std::cout << std::endl << "//		BACK" << std::endl;
		{
			NAMESPACE::vector<int> myvector;

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
	}


	std::cout << std::endl << std::endl << "//	MODIFIERS";
	{
		std::cout << std::endl << "//		ASSIGN" << std::endl;
		{
			NAMESPACE::vector<int> first;
			NAMESPACE::vector<int> second;
			NAMESPACE::vector<int> third;

			first.assign (7,100);             // 7 ints with a value of 100

			NAMESPACE::vector<int>::iterator it;
			it = first.begin() + 1;

			second.assign (it,first.end()-1); // the 5 central values of first

			int myints[] = {1776,7,4};
			third.assign (myints, myints+3);   // assigning from array.

			std::cout << "Size of first: " << int (first.size()) << '\n';
			std::cout << "Size of second: " << int (second.size()) << '\n';
			std::cout << "Size of third: " << int (third.size()) << '\n';
		}
		std::cout << std::endl << "//		PUSH_BACK" << std::endl;
		{
			NAMESPACE::vector<int> myvector;
			//	int myint;

			//	std::cout << "Please enter some integers (enter 0 to end):\n";

			int i = 1;
			do {
				myvector.push_back (42 % i);
			} while (++i < 100);

			std::cout << "myvector stores " << int(myvector.size()) << " numbers.\n";
		}
		std::cout << std::endl << "//		POP_BACK" << std::endl;
		{
			NAMESPACE::vector<int> myvector;
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
		std::cout << std::endl << "//		INSERT" << std::endl;
		{
			NAMESPACE::vector<int> myvector (3,100);
 			NAMESPACE::vector<int>::iterator it;

 			it = myvector.begin();
 			it = myvector.insert ( it , 200 );

 			myvector.insert (it,2,300);

 			// "it" no longer valid, get a new one:
 			it = myvector.begin();

 			NAMESPACE::vector<int> anothervector (2,400);
 			myvector.insert (it+2,anothervector.begin(),anothervector.end());

 			int myarray [] = { 501,502,503 };
 			myvector.insert (myvector.begin(), myarray, myarray+3);

 			std::cout << "myvector contains:";
 			for (it=myvector.begin(); it<myvector.end(); it++)
 				std::cout << ' ' << *it;
 			std::cout << '\n';

		}
		std::cout << std::endl << "//		ERASE" << std::endl;
		{
			NAMESPACE::vector<int> myvector;

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
		std::cout << std::endl << "//		SWAP" << std::endl;
		{
			NAMESPACE::vector<int> foo (4,100);   // three ints with a value of 100
			NAMESPACE::vector<int> bar (16,200);   // five ints with a value of 200

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
		std::cout << std::endl << "//		CLEAR" << std::endl;
		{
			NAMESPACE::vector<int> myvector;
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
		NAMESPACE::vector<int> myvector;
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
		NAMESPACE::vector<int> foo (3,100);   // three ints with a value of 100
		NAMESPACE::vector<int> bar (2,200);   // two ints with a value of 200

		if (foo==bar) std::cout << "foo and bar are equal\n";
		if (foo!=bar) std::cout << "foo and bar are not equal\n";
		if (foo< bar) std::cout << "foo is less than bar\n";
		if (foo> bar) std::cout << "foo is greater than bar\n";
		if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
		if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
	}


	std::cout << std::endl << std::endl << "//	NON MEMBER SWAP" << std::endl;
	{
		NAMESPACE::vector<int> foo (3,100);   // three ints with a value of 100
		NAMESPACE::vector<int> bar (5,200);   // five ints with a value of 200

		NAMESPACE::swap(foo, bar);

		std::cout << "foo contains:";
		for (NAMESPACE::vector<int>::iterator it = foo.begin(); it!=foo.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';

		std::cout << "bar contains:";
		for (NAMESPACE::vector<int>::iterator it = bar.begin(); it!=bar.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}

}
