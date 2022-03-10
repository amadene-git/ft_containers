#include <iostream>
#include "BTree.hpp"
#include <cstdlib>

using namespace ft;
using namespace std;


template<class T>
void	print_data(T data)
{
	std::cout << data << std::endl;
}

template <class T>
void	check_parent(Node<T> *root)
{
	if (root->left && root->left->parent != root)
	{
		std::cout << "oh no !!!" << root->left->data << std::endl;
		return;
	}
	if (root->right && root->right->parent != root)
	{
		std::cout << "oh no !!!" << root->right->data << std::endl;
		return;
	}

}


#include <map>


#include "../iterator/BTree_Iterator.hpp"
#define N 20

#include <sys/time.h>

int	getrandom(int max)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);


	return ((tv.tv_usec * tv.tv_sec) % max);
}

int main()
{

	BTree<ft::pair<const int,int>, std::less<const int> > btree;

	ft::pair<BTree< ft::pair<const int, int>, std::less<const int> >::iterator, bool> pr;

	
	for (int i = 0; i < 30; i++)
	{

		btree.insert_AVL(ft::pair<const int, int>(i, i));
	}

	btree.print_btree();


	// btree.erase(btree.getRoot()->right);
	// std::cout << "***********************************************************************************************" << std::endl;
	// ft::print_btree(btree.getRoot(), 0, 0, 3);
	
	// std::cout << btree.getRoot()->right->data.first << std::endl;
	// std::cout << btree.getRoot()->right->left->data.first << std::endl;
	
	// std::cout << btree.getRoot()->right->data.first << std::endl;


	// BTree<ft::pair<const int,int>, ft::less<const int> >::iterator it = btree.get_begin();

	// while (it != btree.get_end())
	// 	std::cout << (it++)->first << std::endl;


}
