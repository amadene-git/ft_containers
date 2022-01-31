#ifndef BTREE
#define BTREE

#include <iostream>

namespace ft
{
	
	template <typename T>
	class BTree
	{
	public:
		BTree(void);
		~BTree(void);
		
		BTree	&getRight(void) const;
		BTree	&getLeft(void) const;

		void	setRight(BTree &node);
		void	setLeft(BTree &node);

		
	private:
		BTree	*_right;
		BTree	*_left;
	//	BTree	*_node;

		T		_value;

	};


}



#endif
