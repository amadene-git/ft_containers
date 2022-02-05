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
		
		Node(T value = T(), Node<T> *p = NULL)
		: data(value), left(NULL), right(NULL), parent(p), red(1), l(0), r(0)
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
				this->r		= rhs.r;
				this->l		= rhs.l;
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
		int		l;
		int		r;
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
		
		void	insert_AVL_post(Node<T> *root)
		{
			if (root->l - root->r > 1)
				insert_AVL_post(root->left);
			if (root->l - root->r < -1)
				insert_AVL_post(root->right);

			if (root->l - root->r > 1)
				right_rotate(root);
			if (root->l - root->r < -1)
				left_rotate(root);

		}

		void	insert_AVL(T value, Node<T> *root = NULL, int lvl = 0)
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
				++root->l;
				if (root->left)
					insert_AVL(value, root->left, lvl + 1);
				else
				{
					root->left = _alloc.allocate(1);
					_alloc.construct(root->left, Node<T>(value, root));
				}


			}
			else
			{
				++root->r;
				if (root->right)
					insert_AVL(value, root->right, lvl + 1);
				else
				{
					root->right = _alloc.allocate(1);
					_alloc.construct(root->right, Node<T>(value, root));
				}
				
		
			}
			if (root->l - root->r > 1)
				this->right_rotate(root);
			else if (root->l - root->r < -1)
				this->left_rotate(root);


			if (!lvl)
				insert_AVL_post(root);

			return;
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
			copy.r = root->l;
			root->parent = copy.parent;

			if (root->right)
				root->right->parent = root;

			copy.right = root->left;
			copy.parent = root;

			*ptr = copy;

			root->left = ptr;	
			
			if (root->left && root->left->left)
				root->left->left->parent = root->left;

			root->l = ptr->l + ptr->r + 1;
	
	
		};
		void	right_rotate(Node<T> *root = NULL)
		{
			if (!root && !_root)
				throw BTreeException("right_rotate error: btree is empty");

			root = (root) ? root : _root;

			if (!root->left)
				throw BTreeException("right_rotate error: left child is empty");
				

			Node<T>	*ptr = root->left;
			Node<T> copy = *root;

			*root = *root->left;
			copy.l = root->r;
			root->parent = copy.parent;

			if (root->left)
				root->left->parent = root;

			copy.left = root->right;
			copy.parent = root;

			*ptr = copy;

			root->right = ptr;	
			
			if (root->right && root->right->right)
				root->right->right->parent = root->right;

			root->r = ptr->l + ptr->r + 1;
	
	
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
