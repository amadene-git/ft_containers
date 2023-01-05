#include "include.hpp"
#include <sys/time.h>




int main()
{


	// vector_test();
	// std::cout << std::endl << std::endl;
	// map_test();
	// std::cout << std::endl << std::endl;
	// stack_test();
	// std::cout << std::endl << std::endl;
	// utils_test();


	// if (IS_FT)
	// 	std::cout << "ft :" << std::endl;
	// else if (!IS_FT) 
	// 	std::cout << "std :" << std::endl;

	// struct timeval tv1;
	// struct timeval tv2;

	// gettimeofday(&tv1, NULL);

	ft::map<unsigned int, unsigned int>	mymap;

	for(unsigned int i = 0; i < 500 ; ++i)
		mymap.insert(NAMESPACE::make_pair(i, i));

	// for(unsigned int i = 0; i < 5000000 ; ++i)
	// 	mymap.erase(--mymap.end());

	// gettimeofday(&tv2, NULL);
	
	// std::cout << (tv2.tv_sec * 1000000 + tv2.tv_usec) - (tv1.tv_sec * 1000000 + tv1.tv_usec) << std::endl;

	return (0);
}

