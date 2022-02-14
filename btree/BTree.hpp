#ifndef BTREE
#define BTREE

#include <iostream>
#include <exception>
#include "../vector/utils.hpp"
#include "BTree_Iterator.hpp"

namespace ft
{

	template <class T>
	class Node
	{
	public:
		
		typedef	 T	value_type;

		Node(T value = T(), Node<T> *p = NULL, Node<T> *pv = NULL, Node<T> *nt = NULL)
		: data(value), left(NULL), right(NULL), parent(p), next(nt), prev(pv), l(0), r(0)
		{};

		Node<T>	&operator=(Node<T> const &rhs)
		{
			if (this != &rhs)
			{
				this->data 	= rhs.data; 
				this->left 	= rhs.left;
				this->right	= rhs.right;
				this->parent = rhs.parent;
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
		Node<T>	*next;
		Node<T>	*prev;
		int		l;
		int		r;
	};

	class BTreeException : public std::exception
	{
	public:
		BTreeException(const std::string msg) : _msg(msg) {};
 		virtual ~BTreeException() throw() {return ;}
	
	private:
		
		virtual	const char * what () const throw () { return _msg.c_str(); };

		const std::string _msg;

	};
	


	template <class T, class Compare, class Alloc = std::allocator< Node<T> >, class AllocN = std::allocator< Node<T>* > >
	class BTree
	{
	public:

		typedef 			T												value_type;	
		typedef typename	ft::Node<value_type>							node_type;
		typedef	typename	Alloc::size_type								size_type;
	
		typedef	typename	ft::BTree_Iterator< node_type, Compare >		iterator;
		typedef	typename	ft::BTree_const_Iterator< node_type, Compare >	const_iterator;
			
		BTree(node_type *root = NULL, Alloc const &alloc = Alloc(), Compare const &comp = Compare())
		: _alloc(alloc), _comp(comp)
		{
			// std::cout << "BTree default constructor called\n";
			this->_root = _allocN.allocate(1);
			*(this->_root) = root;

			this->_end = _alloc.allocate(1);
			this->_begin = this->_end;
			_alloc.construct(this->_end, node_type());
		};

		~BTree(void)
		{
			// std::cout << "BTree default destructor called" << std::endl;
			this->clear();
			_allocN.deallocate(_root, 1);
			_alloc.deallocate(this->_end, 1);

		};

		void	setRoot(node_type *root)
		{
			*_root = root;
		};

		node_type	*getRoot(void) const
		{
			return (*_root);
		};

		void	clear(node_type *root = NULL)
		{
			if (!*_root)
				return;
			if (root == NULL)
				root = *_root;
			
			if (root->left)
				clear(root->left);
			if (root->right)
				clear(root->right);
			_alloc.deallocate(root, 1);
		};

		// void	equilibre(node_type )
		// {

		// }

		ft::pair<iterator, bool>	insert_AVL_1(value_type &value, node_type &root)
		{
			ft::pair<iterator, bool>	pr;

			if (_comp(value.first, root.data.first))
			{
				++root.l;
				if (root.left)
				{

					pr = insert_AVL_1(value, *root.left);
				
				}
				else
				{
					root.left = _alloc.allocate(1);
					_alloc.construct(root.left, node_type(value, &root, root.prev, &root));
					root.prev = root.left;
					if (!root.left->prev)
						_begin = root.left;
			
					return (ft::make_pair<iterator, bool> (root.left, true));
				}

			}
			else if (_comp(root.data.first, value.first))
			{
				++root.r;
				if (root.right && root.next != this->_end)
					pr = insert_AVL_1(value, *root.right);
				else
				{
					root.right = _alloc.allocate(1);
					_alloc.construct(root.right, node_type(value, &root, &root, root.next));
					root.next = root.right;
					return (ft::make_pair<iterator, bool>(root.right, true));
				}

			}
			else
			{
				return (ft::make_pair<iterator, bool>(&root, false));
			}
			if (root.l - root.r > 1)
				this->right_rotate(&root);
			else if (root.l - root.r < -1)
				this->left_rotate(&root);
			
			return pr;
		};

		ft::pair<iterator, bool>	insert_AVL(value_type value, node_type *root = NULL)
		{
			if (*_root == NULL)
			{
				*_root = _alloc.allocate(1);
				_alloc.construct(*_root, node_type(value));
				this->_begin = *_root;
				(*_root)->next = this->_end; 
				return (ft::make_pair<iterator, bool>(root, true));
			}

			if (root == NULL)
				root = *_root;
						
			return ( insert_AVL_1(value, *root) );

		};

		void	left_rotate(node_type *root)
		{
			if (!root)
				return;

			// node_type 	*ptrA = root;
			node_type	*ptrB = root->right;

			if (root == *(this->_root))
				*_root = ptrB;				
			else
			{
				root->parent->right = (root->parent->right == root) ? ptrB : root->parent->right;
				root->parent->left = (root->parent->left == root) ? ptrB : root->parent->left;
			}
			root->right = ptrB->left;
			ptrB->left = root;

			if (root->right)
				root->right->parent = root;
			ptrB->parent = root->parent;
			root->parent = ptrB;

			root->r = ptrB->l;
			ptrB->l = root->l + root->r + 1;

		};
		void	right_rotate(node_type *root)
		{
			if (!root)
				return;

			// node_type 	*ptrA = root;
			node_type	*ptrB = root->left;

			if (root == *(this->_root))
				*_root = ptrB;				
			else
			{
				root->parent->left = (root->parent->left == root) ? ptrB : root->parent->left;
				root->parent->right = (root->parent->right == root) ? ptrB : root->parent->right;
			}
			root->left = ptrB->right;
			ptrB->right = root;

			if (root->left)
				root->left->parent = root;
			ptrB->parent = root->parent;
			root->parent = ptrB;

			root->l = ptrB->r;
			ptrB->r = root->l + root->r + 1;

		};

		void	getHeight(int *size, node_type *root = NULL, int lvl = 1)
		{
			if (!root)
				root = *_root;
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
		unsigned int	getSize(node_type *root = NULL, int lvl = 1)// temporaire hein...
		{
			if (!root)
				root = *_root;
			if (!root)
				return (0);
			
			if (root->left)
				lvl = getSize(root->left, lvl + 1);
			if (root->right)
				lvl = getSize(root->right, lvl + 1);
			return (unsigned(lvl));
		};

		node_type	*get_begin() const
		{
			return (_begin);
		};

		node_type	*get_end() const
		{
			return (_end);
		};


	private:
		node_type	**_root;
		Alloc				_alloc;
		AllocN				_allocN;
		Compare				_comp;
		node_type	*_begin;
		node_type	*_end;

	};


}



#endif
