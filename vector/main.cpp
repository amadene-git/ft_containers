#include "vector.hpp"
#include <vector>
#include <memory>

int main()
{
	ft::vector<int> foo;
	
	std::cout << foo._ptr << std::endl;

	ft::vector<float> foo1;

	ft::vector<int> bar(12, 42);
	for (size_t i = 0; i < 12; i++)
		std::cout << i << ": " << bar.at(i) << std::endl;
	
	int &ref = bar.at(11);

	ref = 43;

	for (size_t i = 0; i < 12; i++)
		std::cout << i << ": " << bar.at(i) << std::endl;
	
	std::cout << foo.front() << std::endl;
}
