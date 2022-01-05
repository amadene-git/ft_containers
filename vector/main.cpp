#include "vector.hpp"
#include <vector>
#include <memory>

class A
{
	public:
		int		i;
		char	c;
		float	f;
		double	d;
		char	*str;
};

void    vector_contain(std::vector<int> &myvector)
{
	std::cout << "myvector contains:";
	for (size_t i = 0; i < myvector.size(); i++)
		std::cout << ' ' << myvector[i];

	std::cout << '\n';
	std::cout << "size: " << myvector.size() << "\n";
	std::cout << "capacity: " << myvector.capacity() << "\n";
	std::cout << "max_size: " << myvector.max_size() << "\n\n";    
}
void    vector_contain(ft::vector<int> &myvector)
{
	std::cout << "myvector contains:";
	for (size_t i=0;i<myvector.size();i++)
		std::cout << ' ' << myvector[i];

	std::cout << '\n';
	std::cout << "size: " << myvector.size() << "\n";
	std::cout << "capacity: " << myvector.capacity() << "\n";
	std::cout << "max_size: " << myvector.max_size() << "\n\n";    
}
int main()
{
	// Vector
	std::cout << std::endl << "//	ACCES";
	{
		{
			std::cout << std::endl << "//		AT" << std::endl;
			std::vector<int> myvector (10);   // 10 zero-initialized ints

			// assign some values:
			for (size_t i = 0; i < myvector.size(); i++)
				myvector.at(i) = static_cast<int>(i);

			std::cout << "myvector contains:";
			for (size_t i = 0; i < myvector.size(); i++)
				std::cout << ' ' << myvector.at(i);
			std::cout << '\n';

			/*Output:
			  myvector contains: 0 1 2 3 4 5 6 7 8 9*/
		}
		{
			std::cout << std::endl << "//		FRONT" << std::endl;
			std::vector<int> myvector;

			myvector.push_back(78);
			myvector.push_back(16);

			// now front equals 78, and back 16

			myvector.front() -= myvector.back();

			std::cout << "myvector.front() is now " << myvector.front() << '\n';

			/*Output:
			  myvector.front() is now 62*/
		}
		{
			std::cout << std::endl << "//		BACK" << std::endl;
			std::vector<int> myvector;

			myvector.push_back(10);

			while (myvector.back() != 0)
			{
				myvector.push_back ( myvector.back() -1 );
			}

			std::cout << "myvector contains:";
			for (size_t i=0; i<myvector.size() ; i++)
				std::cout << ' ' << myvector[i];
			std::cout << '\n';
			/*Output:
			  myvector contains: 10 9 8 7 6 5 4 3 2 1 0*/
		}
		{
			std::cout << std::endl << "//		OPERATOR []" << std::endl;
			std::vector<int> myvector (10);   // 10 zero-initialized elements
			std::vector<int>::size_type sz = myvector.size();

			// assign some values:
			for (size_t i = 0; i < sz; i++) myvector[i] = static_cast<int>(i);

			// reverse vector using operator[]:
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
			/*Output:
			  myvector contains: 9 8 7 6 5 4 3 2 1 0*/
		}

	}
	std::cout <<std::endl << std::endl << "//	CAPACITY";
	{
		{
			std::cout << std::endl << "//		SIZE" << std::endl;
			std::vector<int> myints;
			std::cout << "0. size: " << myints.size() << '\n';

			for (int i=0; i<10; i++) myints.push_back(i);
			std::cout << "1. size: " << myints.size() << '\n';

			myints.insert (myints.end(),10,100);
			std::cout << "2. size: " << myints.size() << '\n';

			myints.pop_back();
			std::cout << "3. size: " << myints.size() << '\n';

			/*Output:
			  0. size: 0
			  1. size: 10
			  2. size: 20
			  3. size: 19*/

		}
		{
			std::cout << std::endl << "//		MAX_SIZE & CAPACITY" << std::endl;

			std::vector<int> myvector;

			// set some content in the vector:
			for (int i=0; i<100; i++) myvector.push_back(i);

			std::cout << "size: " << myvector.size() << "\n";
			std::cout << "capacity: " << myvector.capacity() << "\n";
			std::cout << "max_size: " << myvector.max_size() << "\n";

			/*Output:
size: 100
capacity: 128
max_size: 1073741823*/
		}
		{
			std::cout << std::endl << "//		EMPTY" << std::endl;
			std::vector<int> myvector;
			int sum (0);

			for (size_t i = 1; i <= 10; i++) myvector.push_back(static_cast<int>(i));

			while (!myvector.empty())
			{
				sum += myvector.back();
				myvector.pop_back();
			}

			std::cout << "total: " << sum << '\n';
			/*Output:
total: 55*/

		}
		{
			std::cout << std::endl << "//		RESIZE" << std::endl;
			std::vector<int> myvector;
			vector_contain(myvector);
			// set some initial content:
		//	for (int i=1;i<10;i++) myvector.push_back(i);

			myvector.resize(2);
			vector_contain(myvector);
			myvector.resize(5);
			vector_contain(myvector);
			myvector.resize(8);
			vector_contain(myvector);
			myvector.resize(12);
			vector_contain(myvector);

		}
		{
			std::cout << std::endl << "//		RESIZE" << std::endl;
			ft::vector<int> myvector;
			vector_contain(myvector);
			// set some initial content:
			//for (int i=1;i<10;i++) myvector.push_back(i);
			
			myvector.resize(1);
			myvector.resize(5);
			vector_contain(myvector);
			myvector.resize(8,100);
			vector_contain(myvector);
			myvector.resize(12);
			vector_contain(myvector);
		}
	}

}
