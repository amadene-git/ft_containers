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
		
		Node(T value = T(), Node<T> *p = NULL, Node<T> *l = NULL, Node<T> *r = NULL, bool b = true)
		: data(value), left(l), right(r), parent(p), red(b)
		{};

		Node<T>	&operator=(Node<T> const &rhs)
		{
			if (this != &rhs)
			{
				this->data 	= rhs.data; 
				this->left 	= rhs.left;
				this->right	= rhs.right;
				this->parent = rhs.parent;
				this->red   = rhs.red;
			}
			return (*this);
		};
		
		~Node(void)
		{};
		
		T		data;
		Node<T>	*left;
		Node<T>	*right;
		Node<T> *parent;
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
			// this->clear();
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
					_alloc.construct(root->left, Node<T>(value, root));
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
					_alloc.construct(root->right, Node<T>(value, root));
				}
				return;
			}
			return;
		};
		void	insert_BST(Node<T> &to_insert, Node<T> *root = NULL)
		{
			if (_root == NULL)
			{
				_root = &to_insert;
				return;
			}

			if (root == NULL)
				root = _root;
						
			if (_comp(to_insert.data, root->data))
			{
				if (root->left)
					insert_BST(to_insert, root->left);
				else
				{
					root->left = &to_insert;
					to_insert.parent = root;
				}
				return;
			}
			else
			{
				if (root->right)
					insert_BST(to_insert, root->right);
				else
				{
					root->right = &to_insert;
					to_insert.parent = root;
				}
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
					if (root->red)
						root->left->red = false;
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
					if (root->red)
						root->right->red = false;

					
				}
				return false;
			}

			return false;
		};

		class BTreeException : public std::exception
		{
		public:
			BTreeException(const std::string& msg) : m_msg(msg)
		    {};

			~BTreeException()
		   	{};

		   const std::string m_msg;

		   virtual const char* what() const throw () { return m_msg.c_str(); };
		};

		void	left_rotate(Node<T> *root = NULL)
		{
			if (!root && !_root)
				throw BTreeException("left_rotate error: btree is empty");

			root = (root) ? root : _root;

			if (!root->right)
				throw BTreeException("left_rotate error: right child is empty");
				

			Node<T>	*ptr = root->right;
			Node<T> copy = *root;


			*root = *root->right;
			root->parent = copy.parent;

			if (root->right)
				root->right->parent = root;

			copy.right = root->left;
			copy.parent = root;

			*ptr = copy;

			root->left = ptr;	
			
			if (root->left && root->left->left)
				root->left->left->parent = root->left;
		};
		void	right_rotate(Node<T> *root = NULL)
		{
			if (!root && !_root)
				throw BTreeException("left_rotate error: btree is empty");

			root = (root) ? root : _root;

			if (!root->left)
				throw BTreeException("left_rotate error: left child is empty");
				

			Node<T>	*ptr = root->left;
			Node<T> copy = *root;


			*root = *root->left;
			root->parent = copy.parent;

			if (root->left)
				root->left->parent = root;

			copy.left = root->right;
			copy.parent = root;

			*ptr = copy;

			root->right = ptr;	
			
			if (root->right && root->right->right)
				root->right->right->parent = root->right;		
		};

		void	getHeight(int *size, Node<T> *root = NULL, int lvl = 1)
		{
			if (!root)
				root = _root;
			if (!root)
				return;
			if (!lvl)
				*size = 0;
			if (root->left)
				getHeight(size, root->left, lvl + 1);
			if (root->right)
				getHeight(size, root->right, lvl + 1);
			*size = (lvl > *size) ? lvl : *size;
		};
		unsigned int	getSize(Node<T> *root = NULL, int lvl = 1)// temporaire hein...
		{
			if (!root)
				root = _root;
			if (!root)
				return (0);
			
			if (root->left)
				lvl = getSize(root->left, lvl + 1);
			if (root->right)
				lvl = getSize(root->right, lvl + 1);
			return (lvl);
		};


//		APPLY FUNCTIONS		
		void	prefix(void (*fct)(Node<T> *), Node<T> *root = NULL)
		{
			if (_root == NULL)
				return;
			if (root == NULL)
				root = _root;
			
			fct(root);

			if (root->left)
				prefix(fct, root->left);
			if (root->right)
				prefix(fct, root->right);
		};
		void	infix(void (*fct)(Node<T> *) = NULL, Node<T> *root = NULL)
		{
			if (_root == NULL)
				return;

			if (root == NULL)
				root = _root;
			
			if (root->left)
				infix(fct, root->left);
			
			fct(root);
			
			if (root->right)
				infix(fct, root->right);
		};
		void	postfix(void (*fct)(Node<T> *) = NULL, Node<T> *root = NULL)
		{
			if (_root == NULL)
				return;

			if (root == NULL)
				root = _root;
			
			if (root->left)
				postfix(fct, root->left);
			if (root->right)
				postfix(fct, root->right);
			
			fct(root);
		};
		void	rev_prefix(void (*fct)(Node<T> *), Node<T> *root = NULL)
		{
			if (_root == NULL)
				return;
			if (root == NULL)
				root = _root;
			
			fct(root);

			if (root->right)
				prefix(fct, root->right);
			if (root->left)
				prefix(fct, root->left);
		};
		void	rev_infix(void (*fct)(Node<T>) = NULL, Node<T> *root = NULL)
		{
			if (_root == NULL)
				return;

			if (root == NULL)
				root = _root;
			
			if (root->right)
				infix(fct, root->right);
			
			fct(root);
			
			if (root->left)
				infix(fct, root->left);
		};
		void	rev_postfix(void (*fct)(Node<T> *) = NULL, Node<T> *root = NULL)
		{
			if (_root == NULL)
				return;

			if (root == NULL)
				root = _root;
			
			if (root->right)
				postfix(fct, root->right);
			if (root->left)
				postfix(fct, root->left);
			
			fct(root);
		};

	private:
		Node<T>		*_root;
		Alloc		_alloc;
		Compare		_comp;

	};


}



#endif
