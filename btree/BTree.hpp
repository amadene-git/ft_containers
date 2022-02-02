#ifndef BTREE
#define BTREE

#include <iostream>
#include "../vector/utils.hpp"

namespace ft
{

	template <class T>
	class Node
	{
	public:
		
		Node(T value = T(), Node<T> *l = NULL, Node<T> *r = NULL)
		: data(value), left(l), right(r), red(true)
		{};
		
		~Node(void)
		{};
		
		T		data;
		Node<T>	*left;
		Node<T>	*right;
		bool	red;
	};

	template <class T, class Compare = ft::less<T>, class Alloc = std::allocator< Node<T> > >
	class BTree
	{
	public:

		BTree(Node<T> *root = NULL, Alloc const &alloc = Alloc(), Compare const &comp = Compare())
		: _root(root), _alloc(alloc), _comp(comp)
		{
			// std::cout << "BTree default constructor called\n";
		};

		BTree(Node<T> &root, Alloc const &alloc = Alloc(), Compare const &comp = Compare())
		: _root(&root), _alloc(alloc), _comp(comp)
		{
			// std::cout << "BTree reference constructor called\n";
		};

		~BTree(void)
		{
			// std::cout << "BTree default destructor called" << std::endl;
			this->clear();
		};

		void	setRoot(Node<T> *root)
		{
			_root = root;
		};

		Node<T>	*getRoot(void) const
		{
			return (_root);
		};

		void	clear(Node<T> *root = NULL)
		{
			if (_root == NULL)
				return;
			if (root == NULL)
				root = _root;
			
			if (root->left)
				clear(root->left);
			if (root->right)
				clear(root->right);
			_alloc.deallocate(root, 1);
		};

		void	insert_BST(T value, Node<T> *root = NULL)
		{
			if (_root == NULL)
			{
				_root = _alloc.allocate(1);
				_alloc.construct(_root, Node<T>(value));
				return;
			}

			if (root == NULL)
				root = _root;
						
			if (_comp(value, root->data))
			{
				if (root->left)
					insert_BST(value, root->left);
				else
				{
					root->left = _alloc.allocate(1);
					_alloc.construct(root->left, Node<T>(value));
				}
				return;
			}
			else
			{
				if (root->right)
					insert_BST(value, root->right);
				else
				{
					root->right = _alloc.allocate(1);
					_alloc.construct(root->right, Node<T>(value));
				}
				return;
			}
			return;
		};
		void	insert_BST(Node<T> to_insert, Node<T> *root = NULL)
		{
			if (_root == NULL)
			{
				_root = to_insert;
				return;
			}

			if (root == NULL)
				root = _root;
						
			if (_comp(to_insert->data, root->data))
			{
				if (root->left)
					insert_BST(to_insert, root->left);
				else
					root->left = to_insert;

				return;
			}
			else
			{
				if (root->right)
					insert_BST(to_insert, root->right);
				else
					root->right = to_insert;

				return;
			}
			return;
		};
		
		bool	insert_RBT(T value, bool red = false, Node<T> *root = NULL)
		{
			if (_root == NULL)
			{
				_root = _alloc.allocate(1);
				_alloc.construct(_root, Node<T>(value));
				return false;
			}

			if (root == NULL)
				root = _root;
						
			if (_comp(value, root->data))
			{
				if (root->left)
					insert_RBT(value, root->red, root->left);
				else
				{
					root->left = _alloc.allocate(1);
					_alloc.construct(root->left, Node<T>(value));
					// std::cout << "\n\n\n\nHERE \n\n" << red << std::endl;
				}
					if (red)
						root->red = false;
				return false;
			}
			else
			{
				if (root->right)
					insert_RBT(value, root->red, root->right);
				else
				{
					root->right = _alloc.allocate(1);
					_alloc.construct(root->right, Node<T>(value));
					// std::cout << "\n\n\n\nHERE \n\n" << red << std::endl;

					
				}
					if (red)
						root->red = false;
				return false;
			}
			if (red)
					root->red = false;

			return false;
		};

//		APPLY FUNCTIONS		
		void	prefix(void (*fct)(T), Node<T> *root = NULL)
		{
			if (_root == NULL)
				return;
			if (root == NULL)
				root = _root;
			
			fct(root->data);

			if (root->left)
				prefix(fct, root->left);
			if (root->right)
				prefix(fct, root->right);
		};
		void	infix(void (*fct)(T) = NULL, Node<T> *root = NULL)
		{
			if (_root == NULL)
				return;

			if (root == NULL)
				root = _root;
			
			if (root->left)
				infix(fct, root->left);
			
			fct(root->data);
			
			if (root->right)
				infix(fct, root->right);
		};
		void	postfix(void (*fct)(T) = NULL, Node<T> *root = NULL)
		{
			if (_root == NULL)
				return;

			if (root == NULL)
				root = _root;
			
			if (root->left)
				postfix(fct, root->left);
			if (root->right)
				postfix(fct, root->right);
			
			fct(root->data);
		};

	private:
		Node<T>		*_root;
		Alloc		_alloc;
		Compare		_comp;

	};


}



#endif
