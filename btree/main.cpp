#include <iostream>
#include "BTree.hpp"
#include <cstdlib>
#include "../vector/utils.hpp"

using namespace ft;
using namespace std;

#define COUNT 10

template <class T>
void	print_btree(Node<T> *root, int a = 0, int lvl = 0)
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
			std::cout << "<" << root->parent->data;
		else
			std::cout << "<nil";
		std::cout << "---<" << lvl << ">";

	if (root->red)
		std::cout << "\033[31m";
	else
		std::cout << "\033[32m";
	std::cout << "[" <<root->data << "]";
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

template<class T>
void	print_data(T data)
{
	std::cout << data << std::endl;
}


#include <chrono>
using namespace std::chrono;
auto start = high_resolution_clock::now();

#include <map>


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

#include "AVL.hpp"

int main()
{
	AVL_tree<int> tree;

	tree.add(1);

	std::cout << tree.data << std::endl;
}
