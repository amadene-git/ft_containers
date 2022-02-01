#ifndef BTREE
#define BTREE

#include <iostream>
#include "../vector/utils.hpp"

namespace ft
{
	
	template <class T, class Compare = ft::less<T> >
	class BTree
	{
	public:
		
		BTree(T value = T(), BTree<T> *left = NULL, BTree<T> *right = NULL)
		: _value(value),
		_left(left),
		_right(right),
		_root(this)
		{
			// std::cout << "BTree default constructor called" << std::endl;
		};

		~BTree(void)
		{
			// std::cout << "BTree default destructor called" << std::endl;
		};

		BTree<T>	*getRight(void) const
		{
			return (_right);
		};

		BTree<T>	*getLeft(void) const
		{
			return (_left);
		};

		BTree<T>	*getRoot(void) const
		{
			return (_left);
		};

		T			&getValue(void)
		{
			return (this->_value);
		};

		void		setRight(BTree<T> &node)
		{
			this->_right = &node;
		};

		void		setLeft(BTree<T> &node)
		{
			this->_left = &node;
		};

		void		setValue(T &value)
		{
			this->_value = value;
		};

		void		insert(BTree<T> &to_insert, BTree<T> &root)
		{
		
			if (_comp(to_insert.getValue(), root.getValue()))
			{
				if (root.getLeft() != NULL)
					insert(to_insert, *root.getLeft());
				else
					root.setLeft(to_insert);
				
				return;
			}
			else
			{
				if (root.getRight() != NULL)
					insert(to_insert, *root.getRight());
				else
					root.setRight(to_insert);
				
				return;
			}


		};


	private:
		T			_value;
		BTree<T>	*_left;
		BTree<T>	*_right;
		BTree<T>	*_root;
		Compare		_comp;

	};


}



#endif
