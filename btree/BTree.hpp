#ifndef BTREE_HPP
#define BTREE_HPP

#include "../iterator/BTree_Iterator.hpp"
#include "../include/pair.hpp"
#include "../include/enable_if.hpp"


#include <iostream>
#define COUNT 20


namespace ft
{

	enum _Rb_tree_color { _S_red = false, _S_black = true };

	template <class T>
	class Alloc_Node
	{
	public:
		
		typedef	 T	value_type;

		Alloc_Node()
		{};
		
		~Alloc_Node(void)
		{};
		
		T				data;
		Alloc_Node<T>	*left;
		Alloc_Node<T>	*right;
		Alloc_Node<T>	*parent;
		_Rb_tree_color	color;
	};

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

	template <class T, class Compare, class Alloc = std::allocator< Node<T> >, class AllocN = std::allocator< Node<T>* > >
	class BTree
	{
	public:

		void	print_btree(ft::Node<T> *root = NULL, int a = 0, int lvl = 0, int max = -1)
		{
			if (!root)
			{
				root = getRoot();
				if (!root)
					return;
			std::cerr << "******************************************************************************************************************" << std::endl;

			}

			if (root->right && (lvl <= max || max == -1))
				print_btree(root->right, 0, lvl + 1, max);

			for (int k = 1	; k < lvl; k++)
				for (int i = 0; i < COUNT; i++)
					std::cerr << " ";
			if (lvl)
			{
				for (int i = 0; i < COUNT - 5; i++)
					std::cerr << " ";
				if (a)
					std::cerr << "\\";
				else
					std::cerr << "/";
			}
			if (root->parent)
				std::cerr << "<" << root->parent->data.first;
			else
				std::cerr << "<nil";
			std::cerr << "---<" << lvl << ">";
			std::cerr << root->l << "-" << root->r;
			std::cerr << "[" << root->data.first << ", " << root->data.second << "]";
			// std::cerr << "\033[0m";


			if (root->right && root->left)
				std::cerr << " <";
			else
			{
				if (root->right)
					std::cerr << " /";
				if (root->left)
					std::cerr << " \\";
			}
			std::cerr << std::endl;

			if (root->left && (lvl <= max || max == -1))
				print_btree(root->left, 1, lvl + 1, max);
			if (root == getRoot())
			std::cerr << "******************************************************************************************************************" << std::endl << std::endl;


		}


		typedef 			T												value_type;	
		typedef typename	ft::Node<value_type>							node_type;
		typedef				size_t											size_type;
	
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
			_alloc.destroy(root);
			_alloc.deallocate(root, 1);
		};

		ft::pair<iterator, bool>	insert_AVL_ite(value_type &value, node_type *root)
		{
			ft::pair<iterator, bool>	pr;

			while (root)
			{
				if (_comp(value.first, root->data.first))
				{
					if (root->left)
					{
						root = root->left;
						continue;
					}
					else
					{
						root->left = _alloc.allocate(1);
						_alloc.construct(root->left, node_type(value, root, root->prev, root));
						
						root->prev = root->left;
						if (!root->left->prev)
							_begin = root->left;
						else
							root->left->prev->next = root->left;
						
						root = root->left;
						pr = ft::make_pair(root, true);
						break;
					}
				}
				else if (_comp(root->data.first, value.first))
				{
					if (root->right)
					{
						root = root->right;
						continue;
					}
					else
					{
						root->right = _alloc.allocate(1);
						_alloc.construct(root->right, node_type(value, root, root, root->next));
					
						if (root->next == this->_end)
							this->_end->prev = root->right;
						else
							root->next->prev = root->right;
						root->next = root->right;
						
						root = root->right;
						pr = ft::make_pair(root, true);
						break;
					}
				}
				else
				{
					pr = ft::make_pair(root, false);
					break;
				}
			}
			while (root != *_root)
			{
			
				if (root->parent->left == root && pr.second == true)
					++root->parent->l;
				else if (root->parent->right == root && pr.second == true)
					++root->parent->r;
		
				if (root->l - root->r > 1)
				{
					this->right_rotate(root);
					if (root->parent && root->parent->parent)
						root = root->parent->parent;
				}
				else if (root->l - root->r < -1)
				{
					this->left_rotate(root);
					if (root->parent && root->parent->parent)
						root = root->parent->parent;
				}
				else
					root = root->parent;
			}
			if (root->left)
				root->l = root->left->l + root->left->r + 1;
			if (root->right)
				root->r = root->right->l + root->right->r + 1;
	
			if (root->l - root->r > 1)
				this->right_rotate(root);
			else if (root->l - root->r < -1)
				this->left_rotate(root);
	
			return (pr);
		}
		
		ft::pair<iterator, bool>	insert_AVL_rec(value_type &value, node_type &root)
		{
			ft::pair<iterator, bool>	pr;

		


			if (_comp(value.first, root.data.first))
			{
				++root.l;
				if (root.left)
					pr = insert_AVL_rec(value, *root.left);
				else
				{
					root.left = _alloc.allocate(1);
					_alloc.construct(root.left, node_type(value, &root, root.prev, &root));
					
					root.prev = root.left;
					if (!root.left->prev)
						_begin = root.left;
					else
						root.left->prev->next = root.left;					
					
					return (ft::make_pair<iterator, bool> (root.left, true));
				}

			}
			else if (_comp(root.data.first, value.first))
			{
				++root.r;
				if (root.right && root.next != this->_end)
					pr = insert_AVL_rec(value, *root.right);
				else
				{
					root.right = _alloc.allocate(1);
					_alloc.construct(root.right, node_type(value, &root, &root, root.next));
				
					if (root.next == this->_end)
						this->_end->prev = root.right;
					else
						root.next->prev = root.right;
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

		node_type	*find(value_type& k)
		{
			Node<value_type>	*root = getRoot();

			while (root)
			{
				if (_comp(k.first, root->data.first))
					root = root->left;
				else if (_comp(root->data.first, k.first))
					root = root->right;
				else
					break;
			}
			if (root)
				return (root);
			return (NULL);
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

			ft::pair<iterator, bool> pr;
			node_type *root = find(value);
			
			if (!root)
				pr = insert_AVL_rec(value, **_root);
			else
				pr = ft::make_pair(root, false);

			return (pr);
			
			return (insert_AVL_ite(value, *_root));
		};

		void	left_rotate(node_type *root)
		{
			if (!root || !root->right)
				return;

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

			if (!root || !root->left)
				return;

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
					while (tmp && tmp->parent)
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

					
					tmp = getRoot();
				
					if (tmp->right)
						tmp->r = (!tmp->right->l && !tmp->right->r) ? 1 : tmp->right->l + tmp->right->r + 1;
					if (tmp->left)
						tmp->l = (!tmp->left->l && !tmp->left->r) ? 1 : tmp->left->l + tmp->left->r + 1;


				}
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
				else//l'element a supprimer est le parent de tmp					
					elem = tmp;

				if (root == *_root)
				{

					*_root = tmp;
					if (tmp->parent)
						--tmp->parent->l;

				}
				else if (elem != tmp)//cas generique
				{

					if (root->parent->left == root)
						root->parent->left 	= tmp;

					if (root->parent->right == root)
						root->parent->right = tmp;

					tmp->l = root->l;
					tmp->r = root->r - 1;
					--tmp->parent->l;
				
				}
				else//l'element a supprimer est le parent de tmp
				{
					
					if (root->parent->left == root)
						root->parent->left 	= tmp;

					if (root->parent->right == root)
						root->parent->right = tmp;

					tmp->l = root->l;
					tmp->r = root->r - 1;
				
				}

				tmp->parent = root->parent;

				if (root->left)
					root->left->parent = tmp;

				tmp->left = root->left;

				
				while (elem && elem->parent)
				{

					if (elem->parent->left == elem)
						elem->parent->l = elem->l + elem->r + 1;
					if (elem->parent->right == elem)
						elem->parent->r = elem->l + elem->r + 1;
					
					
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

				elem = getRoot();
				if (elem->right)
					elem->r = (!elem->right->l && !elem->right->r) ? 1 : elem->right->l + elem->right->r + 1;
				if (elem->left)
					elem->l = (!elem->left->l && !elem->left->r) ? 1 : elem->left->l + elem->left->r + 1;

				
			}
			else if (root->left)
			{

				tmp = root;
				while (tmp && tmp->parent)
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
				if (root && root->left)
				    root->left->parent = root->parent;

	
				tmp = getRoot();
				
				if (tmp->right)
					tmp->r = (!tmp->right->l && !tmp->right->r) ? 1 : tmp->right->l + tmp->right->r + 1;
				if (tmp->left)
					tmp->l = (!tmp->left->l && !tmp->left->r) ? 1 : tmp->left->l + tmp->left->r + 1;
			

			}
			else if (root->right)
			{

				tmp = root;
				while (tmp && tmp->parent)
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
				
				if (root && root->right)
				root->right->parent = root->parent;
		
				
				tmp = getRoot();
				
				if (tmp->right)
					tmp->r = (!tmp->right->l && !tmp->right->r) ? 1 : tmp->right->l + tmp->right->r + 1;
				if (tmp->left)
					tmp->l = (!tmp->left->l && !tmp->left->r) ? 1 : tmp->left->l + tmp->left->r + 1;

			}

			
			_alloc.deallocate(root, 1);
			
			return;
		};
		

			typedef typename std::allocator< ft::Node<T> >  node_alloc;

			size_type max_size() const
			{ 
				return (node_alloc().max_size());
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
