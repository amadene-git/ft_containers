#include <iostream>
#include "BTree.hpp"
#include <cstdlib>
#include "../vector/utils.hpp"

using namespace ft;
using namespace std;

// #define COUNT 10

// template <class T>
// void	print_btree(Node<T> *root, int a = 0, int lvl = 0, 
// typename ft::enable_if<ft::is_integral<T>::value, T>::type* = NULL)
// {
// 	if (!root)
// 	{
// 		std::cout << "Oh NO !" << std::endl;
// 		return;
// 	}
	
// 	if (root->right)
// 		print_btree(root->right, 0, lvl + 1);
// 	// else
// 	// 	std::cout << std::endl;

// 	for (int k = 1	; k < lvl; k++)
// 		for (int i = 0; i < COUNT; i++)
// 			std::cout << " ";
// 	if (lvl)
// 	{
// 		for (int i = 0; i < COUNT - 5; i++)
// 			std::cout << " ";
// 		if (a)
// 			std::cout << "\\";
// 		else
// 			std::cout << "/";
// 	}
// 	if (root->parent)
// 		std::cout << "<" << root->parent->data;
// 	else
// 		std::cout << "<nil";
// 	std::cout << "---<" << lvl << ">";
// 	std::cout << root->l << "-" << root->r;
// 	std::cout << "[" <<root->data << "]";
// 	std::cout << "\033[0m";
	
	
// 	if (root->right && root->left)
// 		std::cout << " <";
// 	else
// 	{
// 		if (root->right)
// 			std::cout << " /";
// 		if (root->left)
// 			std::cout << " \\";
// 	}
// 	std::cout << std::endl;

// 	if (root->left)
// 		print_btree(root->left, 1, lvl + 1);
// 	// else
// 	// 	std::cout << std::endl;


// }

// template <class T>
// void	print_btree(Node<T> *root, int a = 0, int lvl = 0,
// typename ft::enable_if< ft::is_pair<T>::value, T >::type* = NULL)
// {
// 	if (!root)
// 	{
// 		std::cout << "Oh NO !" << std::endl;
// 		return;
// 	}
	
// 	if (root->right)
// 		print_btree(root->right, 0, lvl + 1);
// 	// else
// 	// 	std::cout << std::endl;

// 	for (int k = 1	; k < lvl; k++)
// 		for (int i = 0; i < COUNT; i++)
// 			std::cout << " ";
// 	if (lvl)
// 	{
// 		for (int i = 0; i < COUNT - 5; i++)
// 			std::cout << " ";
// 		if (a)
// 			std::cout << "\\";
// 		else
// 			std::cout << "/";
// 	}
// 	if (root->parent)
// 		std::cout << "<" << root->parent->data.first;
// 	else
// 		std::cout << "<nil";
// 	std::cout << "---<" << lvl << ">";
// //	std::cout << root->l << "-" << root->r;
// 	std::cout << "[" << root->data.first << ", " << root->data.second << "]";
// 	std::cout << "\033[0m";
	
	
// 	if (root->right && root->left)
// 		std::cout << " <";
// 	else
// 	{
// 		if (root->right)
// 			std::cout << " /";
// 		if (root->left)
// 			std::cout << " \\";
// 	}
// 	std::cout << std::endl;

// 	if (root->left)
// 		print_btree(root->left, 1, lvl + 1);
// 	// else
// 	// 	std::cout << std::endl;


// }

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




#include "../vector/utils.hpp"
#include "BTree_Iterator.hpp"
#define N 10

#include <sys/time.h>

int	getrandom(int max)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);


	return ((tv.tv_usec * tv.tv_sec) % max);
}

int main()
{

	BTree<ft::pair<const int,int>, ft::less<const int> > btree;

	ft::pair<BTree< ft::pair<const int, int>, ft::less<const int> >::iterator, bool> pr;

	
	for (int i = 0; i < N; i++)
	{

		btree.insert_AVL(ft::pair<const int, int>(i, i));
	}
	// std::map<int, int> mymap;
	// for (int i = 0; i < N; i++)
	// 	mymap.insert(std::pair<int, int>(i, rand() % 1000));


	


	ft::print_btree(btree.getRoot());


	// btree.erase(btree.getRoot()->right->right->right);
	std::cout << "***********************************************************************************************" << std::endl;
	ft::print_btree(btree.getRoot());
	
	// std::cout << std::endl << btree.getRoot()->data.first << std::endl;
	// std::cout << btree.getRoot()->right->data.first << std::endl;

	// ft::print_btree(btree.getRoot());


}
