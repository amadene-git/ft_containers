#include "BTree.hpp"

template <typename T>
ft::BTree::BTree(T value = T())
: _value(value)
{
	std::cout << "BTree default constructor called" << std::endl;
}

ft::BTree::~BTree(void)
{
	std::cout << "BTree default destructor called" << std::endl;
}

ft::BTree	&ft::BTree::getRight(void) const
{
	return (*_right);
}

ft::BTree	&ft::BTree::getLeft(void) const
{
	return (*_left);
}

void		ft::BTree::setRight(ft::BTree &node)
{
	this->_right = &node;
}

void		ft::BTree::setLeft(ft::BTree &node)
{
	this->_left = &node;
}



