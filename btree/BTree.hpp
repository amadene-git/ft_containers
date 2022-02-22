#ifndef BTREE
#define BTREE

#include <iostream>
#include <exception>
#include "../utils/utils.hpp"
#include "../iterator/BTree_Iterator.hpp"

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

		node_type	*get_begin()	const { return (_begin); };
		node_type	*get_end()		const { return (_end); };

		void	set_begin(node_type *begin)	{ this->_begin = begin; };
		void	set_end(node_type *end)		{ this->_end = end; };

		void	clear(void)
		{
			if (!_root || !*_root)
				return;
			clear_rec(*_root);
			*_root = NULL;
		}
		
		void	clear_rec(node_type *root = NULL)
		{			
			if (root->left)
				clear_rec(root->left);
			if (root->right)
				clear_rec(root->right);
			_alloc.deallocate(root, 1);
		};

		ft::pair<iterator, bool>	insert_AVL_1(value_type &value, node_type &root)
		{
			ft::pair<iterator, bool>	pr;

			if (_comp(value.first, root.data.first))
			{
				++root.l;
				if (root.left)
					pr = insert_AVL_1(value, *root.left);
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
				
					if (root.next == this->_end)
						this->_end->prev = root.right;
					
					root.next = root.right;
				
					return (ft::make_pair<iterator, bool>(root.right, true));
				}
			}
			else
				return (ft::make_pair<iterator, bool>(&root, false));
			
			if (root.l - root.r > 1)
				this->right_rotate(&root);
			else if (root.l - root.r < -1)
				this->left_rotate(&root);
			
			return (pr);
		};

		ft::pair<iterator, bool>	insert_AVL(value_type value)
		{
			if (*_root == NULL)
			{
				*_root = _alloc.allocate(1);
				_alloc.construct(*_root, node_type(value));
				this->_begin = *_root;
				(*_root)->next = this->_end;
				this->_end->prev = *_root;
				return (ft::make_pair<iterator, bool>(*_root, true));
			}

			return (insert_AVL_1(value, **_root));
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

		void	erase(node_type *root)
		{
			node_type	*tmp;
			
			if (!root)
				return;
			if (root != this->_begin)
				root->prev->next = root->next;
			else
				this->_begin = root->next;
			
			root->next->prev = root->prev;
			if (!root->left && !root->right)
			{
				if (root == *(this->_root))
				{
					_alloc.deallocate(root, 1);
					*_root = NULL;
					return;
				}
				else
				{
					
					tmp = root;
					while (tmp->parent)
					{
						tmp->parent->l -= (tmp->parent->left == tmp) ? 1 : 0;
						tmp->parent->r -= (tmp->parent->right == tmp) ? 1 : 0;
						
						
						if (tmp->l - tmp->r > 1 || tmp->l - tmp->r < -1)
						{
							if (tmp->l - tmp->r > 1)
								this->right_rotate(tmp);
							else if (tmp->l - tmp->r < -1)
								this->left_rotate(tmp);
							tmp = tmp->parent->parent;
						}
						else
							tmp = tmp->parent;
					}
					root->parent->left 	= (root->parent->left == root) ? NULL : root->parent->left;
					root->parent->right = (root->parent->right == root) ? NULL : root->parent->right;

					_alloc.deallocate(root, 1);
				}
			}
			else if (root->left && !root->right)//a corriger mettre en dessous de root->left && root->right
			{
				tmp = root;
				while (tmp->parent)
				{
					tmp->parent->l -= (tmp->parent->left == tmp) ? 1 : 0;
					tmp->parent->r -= (tmp->parent->right == tmp) ? 1 : 0;
					
					if (tmp->l - tmp->r > 1 || tmp->l - tmp->r < -1)
					{
						if (tmp->l - tmp->r > 1)
							this->right_rotate(tmp);
						else if (tmp->l - tmp->r < -1)
							this->left_rotate(tmp);
						tmp = tmp->parent->parent;
					}
					else
						tmp = tmp->parent;
				}
				if (root->parent)
				{
					root->parent->left 	= (root->parent->left == root) ? root->left : root->parent->left;
					root->parent->right = (root->parent->right == root) ? root->left : root->parent->right;
				}
				else
					*_root = root->left;
				root->left->parent = root->parent;

				_alloc.deallocate(root, 1);

			}
			else if (!root->left && root->right)//a corriger mettre en dessous de root->left && root->right
			{
				tmp = root;
				while (tmp->parent)
				{
					tmp->parent->l -= (tmp->parent->left == tmp) ? 1 : 0;
					tmp->parent->r -= (tmp->parent->right == tmp) ? 1 : 0;
					
					if (tmp->l - tmp->r > 1 || tmp->l - tmp->r < -1)
					{
						if (tmp->l - tmp->r > 1)
							this->right_rotate(tmp);
						else if (tmp->l - tmp->r < -1)
							this->left_rotate(tmp);
						tmp = tmp->parent->parent;
					}
					else
						tmp = tmp->parent;
				}
				if (root->parent)
				{
					root->parent->left 	= (root->parent->left == root) ? root->right : root->parent->left;
					root->parent->right = (root->parent->right == root) ? root->right : root->parent->right;
				}
				else
					*_root = root->right;
				root->right->parent = root->parent;

				_alloc.deallocate(root, 1);

			}
			else if (root->left && root->right)
			{
				tmp = root->right;
				node_type	*elem;


				if (tmp->left)
				{
					while (tmp->left)
						tmp = tmp->left;

					if (tmp->right)
						tmp->right->parent = tmp->parent;
					tmp->parent->left = tmp->right;
					
					if (root->right)
						root->right->parent = tmp;
					tmp->right = root->right;

					elem = tmp->parent;
				}
				else
					elem = tmp;
			
				
				if (root == *_root)
					*_root = tmp;
				else
				{
					root->parent->left 	= (root->parent->left == root) ? tmp : root->parent->left;
					root->parent->right = (root->parent->right == root) ? tmp : root->parent->right;
				}
				tmp->parent = root->parent;

				if (root->left)
					root->left->parent = tmp;

				tmp->left = root->left;

				tmp->l = root->l;
				tmp->r = root->r - 1;

				while (elem->parent)
				{
					elem->parent->l -= (elem->parent->left == elem) ? 1 : 0;
					elem->parent->r -= (elem->parent->right == elem) ? 1 : 0;
					
					if (elem->l - elem->r > 1 || elem->l - elem->r < -1)
					{
						if (elem->l - elem->r > 1)
							this->right_rotate(elem);
						else if (elem->l - elem->r < -1)
							this->left_rotate(elem);
						elem = elem->parent->parent;
					}
					else
						elem = elem->parent;
				}
				// std::cout << "l: " <<  elem->l << " ; r: " << elem->r << std::endl;
				// if (elem->l - elem->r > 1)
				// {
				// 	this->right_rotate(elem);
				// 	std::cout << "yo" << std::endl;
				// }
				// else if (elem->l - elem->r < -1)
				// 	this->left_rotate(elem);
				_alloc.deallocate(root, 1);
				
			}
			else
			{
				std::cout << "other case" << std::endl;
			}
			
			return;
		};
		


	private:
		node_type	**_root;
		Alloc				_alloc;
		AllocN				_allocN;
		Compare				_comp;
		node_type	*_begin;
		node_type	*_end;

	};


//BTREE UTILS *******************************************
#define COUNT 20

template <class T>
void	print_btree(ft::Node<T> *root, int a = 0, int lvl = 0, int max = -1,
typename ft::enable_if< ft::is_pair<T>::value, T >::type* = NULL)
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

}



#endif
