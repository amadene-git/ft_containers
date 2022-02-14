#include "map.hpp"
#include <map>
#include <iostream>

#include <sys/time.h>

int	getrandom(int max)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);


	return ((tv.tv_usec * tv.tv_sec) % max);
}


#define COUNT 20

template <class T>
void	print_btree(ft::Node<T> *root, int a = 0, int lvl = 0,
typename ft::enable_if< ft::is_pair<T>::value, T >::type* = NULL)
{
	if (!root)
	{
		std::cout << "Oh NO !" << std::endl;
		return;
	}
	
	if (root->right)
		print_btree(root->right, 0, lvl + 1);
	// else
	// 	std::cout << std::endl;

	for (int k = 1	; k < lvl; k++)
		for (int i = 0; i < COUNT; i++)
			std::cout << " ";
	if (lvl)
	{
		for (int i = 0; i < COUNT - 5; i++)
			std::cout << " ";
		if (a)
			std::cout << "\\";
		else
			std::cout << "/";
	}
	if (root->parent)
		std::cout << "<" << root->parent->data.first;
	else
		std::cout << "<nil";
	std::cout << "---<" << lvl << ">";
	std::cout << root->l << "-" << root->r;
	std::cout << "[" << root->data.first << ", " << root->data.second << "]";
	std::cout << "\033[0m";
	
	
	if (root->right && root->left)
		std::cout << " <";
	else
	{
		if (root->right)
			std::cout << " /";
		if (root->left)
			std::cout << " \\";
	}
	std::cout << std::endl;

	if (root->left)
		print_btree(root->left, 1, lvl + 1);
	// else
	// 	std::cout << std::endl;


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
	std::cout << "\t" <<	"//MODIFIERS" << std::endl;
	std::cout << "\t\t" <<	"//INSERT" << std::endl;
	{
		ft::map<char,int> mymap;

		// first insert function version (single parameter):
		mymap.insert ( ft::pair<char,int>('a',100) );
		mymap.insert ( ft::pair<char,int>('z',200) );

		ft::pair<ft::map<char,int>::iterator,bool> ret;
		ret = mymap.insert ( ft::pair<char,int>('z',500) );
		if (ret.second==false) {
			std::cout << "element 'z' already existed";
			std::cout << " with a value of " << ret.first->second << '\n';
		}

		// second insert function version (with hint position):
		ft::map<char,int>::iterator it = mymap.begin();
		mymap.insert (it, ft::pair<char,int>('b',300));  // max efficiency inserting
		mymap.insert (it, ft::pair<char,int>('c',400));  // no max efficiency inserting

		// third insert function version (range insertion):
		ft::map<char,int> anothermap;
		anothermap.insert(mymap.begin(),mymap.find('c'));

		// showing contents:
		std::cout << "mymap contains:\n";
		for (it=mymap.begin(); it!=mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';

		std::cout << "anothermap contains:\n";
		for (it=anothermap.begin(); it!=anothermap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
	}
*/	
	std::cout << "\t" <<	"//ITERATOR" << std::endl;
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
