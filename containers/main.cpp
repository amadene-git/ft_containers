
#include <iostream>
#include <sys/time.h>


#ifndef NAMESPACE
# define NAMESPACE ft
# include "map.hpp"
# define FT 1

#else


#define FT 0

# include <map>
#endif

using namespace NAMESPACE;





int main()
{
	struct timeval tv1;
	struct timeval tv2;

	gettimeofday(&tv1, NULL);
	
	if (FT)
		std::cout << "ft :\n";
	else
		std::cout << "std :\n";

	map<int, int> mymap;

	int i = 0;
	while( ++i < 100000000)
		mymap.insert(pair<const int, int>(i, i));

	while (i--)
		mymap.erase(i);
		



	gettimeofday(&tv2, NULL);
	std::cout <<  (tv2.tv_sec * 1000000 + tv2.tv_usec) - (tv1.tv_sec * 1000000 + tv1.tv_usec) << std::endl;




}
