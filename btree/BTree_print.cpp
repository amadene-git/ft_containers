#include "BTree.hpp"

//BTREE UTILS *******************************************
#define COUNT 20

template <class T>
void	print_btree(ft::Node<T> *root, int a = 0, int lvl = 0, int max = -1)
{
	if (!root)
	{
		std::cout << "Oh NO !" << std::endl;
		return;
	}
	
	if (root->right && (lvl <= max || max == -1))
		print_btree(root->right, 0, lvl + 1, max);
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
	// std::cout << "\033[0m";
	
	
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

	if (root->left && (lvl <= max || max == -1))
		print_btree(root->left, 1, lvl + 1, max);
	// else
	// 	std::cout << std::endl;


}
