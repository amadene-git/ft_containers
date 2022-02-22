#ifndef MAP_HPP
#define MAP_HPP

#include "../iterator/iterator.hpp"
#include "../iterator/reverse_iterator.hpp"
#include "../btree/BTree.hpp"
#include "../iterator/BTree_Iterator.hpp"
#include "../utils/utils.hpp"
#include <memory>

namespace ft
{
    template <	class Key,
           		class T,
           		class Compare = ft::less<Key>,
           		class Alloc = std::allocator< ft::pair<const Key,T> > >
    class map
    {
    public:
	
	//MEMBER TYPE
		typedef             Key                         key_type;
        typedef             T                           mapped_type;
		typedef				Compare						key_compare;
	    typedef				Alloc						allocator_type;
		typedef 			std::allocator< int >		allocator_int;// <- chelou A corriger !!!

       
        typedef typename    ft::pair<const key_type, mapped_type>			value_type;                         		
        
   
   
		class	value_compare : binary_function<value_type, value_type, bool>
		{
			friend class map;
		protected:
			Compare comp;
			value_compare (Compare c) : comp(c) {};

		public:
			bool operator() (const value_type& x, const value_type& y) const
			{
				return comp(x.first, y.first);
			}
		};

        typedef typename    allocator_type::reference                       reference;                                   	
        typedef typename    allocator_type::const_reference                 const_reference;                                 
        typedef typename    allocator_type::pointer                         pointer;                                 	    
        typedef typename    allocator_type::const_pointer                   const_pointer;                                   

        typedef typename    ft::BTree< value_type, key_compare >::iterator					iterator;
        typedef typename    ft::BTree< value_type, key_compare >::const_iterator			const_iterator;

		typedef typename	ft::reverse_iterator<iterator>					reverse_iterator;	
        typedef typename	ft::reverse_iterator<const_iterator>			const_reverse_iterator;	


		typedef typename	ft::iterator_traits<iterator>::difference_type		difference_type;
        typedef    			size_t												size_type;// <- A vérifier !

		~map()
		{
			// std::cout << "Map default destructor called\n";
		};


//	CONSTRUCTOR
		explicit map(const key_compare& comp = key_compare(),
        			const allocator_type& alloc = allocator_type())
		:_alloc(alloc),
		_comp(comp),
		_size(0),
		_btree()
		{
//			std::cout << "Map default constructor called\n";
		};

		template <class InputIterator>
		map (InputIterator first, InputIterator last,
		const key_compare& comp = key_compare(),
		const allocator_type& alloc = allocator_type())
		:_alloc(alloc),
		_comp(comp),
		_btree(),
		_size(0)
		{
			while (first != last)
			{
				this->insert(first);
				++first;
			}
		};

		map (const map& x)
		:_alloc(x.get_allocator()),
		_comp(x.key_comp()),
		_size(0)
		{

			iterator it = x.begin();

			while (it != x.end())
			{
				this->insert(it);
				++it;
			}
		};

	map&	operator=(const map& x)
	{
		this->clear();
		iterator it = x.begin();
		while (it != x.end())
		{
			this->insert(it);
			++it;
		}
	};

//	CAPACITY ****************************

	bool		empty() const		{ return (!_size); };
	size_type	size() const		{ return (_size); };
	size_type	max_size() const	{ return (allocator_int().max_size() / 10); };// <- c'est temporaire hein... et surtout degueulasse 

//	MODIFIERS

	ft::pair<iterator, bool>	insert(const value_type& val)
	{
		ft::pair<iterator, bool> pr = _btree.insert_AVL(val);
		_size += pr.second;
		// this->end()->first = size;
		
		return (ft::make_pair<iterator, bool>(pr.first, pr.second));
	};
	iterator	insert(iterator position, const value_type& val)
	{
		(void)position;

		ft::pair<iterator, bool> pr = this->_btree.insert_AVL(val);
		this->_size += pr.second;
		return (pr.first);
	};
	template <class InputIterator>
	void insert (InputIterator first, InputIterator last)
	{
		ft::pair<iterator, bool> pr;
		while (first != last)
		{
			this->_size  += this->insert(ft::make_pair(first->first, first->second)).second;
			++first;
		}
	};
	
	void	swap(map& x)
	{
		Node<value_type> *tmp = this->_btree.getRoot();
		
		this->_btree.setRoot(x._btree.getRoot());
		x._btree.setRoot(tmp);

		size_t	size = this->_size;
		this->_size = x._size;
		x._size = size;

		tmp = this->_btree.get_begin();
		this->_btree.set_begin(x._btree.get_begin());
		x._btree.set_begin(tmp);

		tmp = this->_btree.get_end();
		this->_btree.set_end(x._btree.get_end());
		x._btree.set_end(tmp);

	};

	void	clear()
	{
		this->_btree.clear();
		this->_size = 0;
	};
	
	void	erase(iterator position)
	{
		if (position == this->end())
			return;
		
		Node<value_type>	*root = this->_btree.getRoot();
		
		while (position->first != root->data.first)
		{
			if (_comp(position->first, root->data.first))
				root = root->left;
			else if (_comp(root->data.first, position->first))
				root = root->right;
			else
				break;
		}

		this->_btree.erase(root);
		--this->_size;
	};
	size_type	erase(const key_type& k)
	{
		iterator	it = this->find(k);

		if (it != this->end())
		{
			this->erase(it);
			return (1);
		}
		return (0);
	};
    void	erase(iterator first, iterator last)
	{
		while (first != last)
		{
			this->erase(first);
			++first;
		}
	};

//	ITERATOR	*****************************
	iterator		begin()			{ return(_btree.get_begin()); };
	const_iterator	begin()	const	{ return(const_iterator(_btree.get_begin())); };

	iterator		end()			{ return(_btree.get_end()); };
	const_iterator	end() const		{ return (const_iterator(_btree.get_end())); };

	reverse_iterator		rbegin()			{ return(reverse_iterator(this->end())); };
	const_reverse_iterator	rbegin()	const	{ return(reverse_iterator(this->end())); };

	reverse_iterator		rend() 				{ return(reverse_iterator(this->begin())); };
	const_reverse_iterator	rend() 		const	{ return(reverse_iterator(this->begin())); };


//	ACCES *************************************
	mapped_type	&operator[](const key_type& k)
	{
		return ((*((this->insert(ft::make_pair(k,mapped_type()))).first)).second);
	};



// OPERATION ***************************************
	iterator	find(const key_type& k)
	{
		Node<value_type>	*root = _btree.getRoot();

		while (root)
		{
			if (_comp(k, root->data.first))
				root = root->left;
			else if (_comp(root->data.first, k))
				root = root->right;
			else
				break;
		}
		if (root)
			return (root);
		return (this->end());
	};
	const_iterator	find(const key_type& k) const
	{
		Node<value_type>	*root = _btree.getRoot();

		while (root)
		{
			if (_comp(k, root->data.first))
				root = root->left;
			else if (_comp(root->data.first, k))
				root = root->right;
			else
				break;
		}
		if (root)
			return (root);
		return (this->end());
	};

	size_type	count(const key_type& k) const
	{
		if (this->find(k) == this->end())
			return (0);
		return (1);
	};

	iterator	lower_bound(const key_type& k)
	{
		if (_comp((--this->end())->first, k))
			return (this->end());
		
		Node<value_type> *root = this->_btree.getRoot();

		while (root)
		{
			if (_comp(root->data.first, k) && root->right)
				root = root->right;
			else if (_comp(k, root->data.first) && root->left)
				root = root->left;
			else if (root->data.first == k)
				return (root);
			else
				break;
		}
		while (_comp(root->data.first, k))
			root = root->parent;
		
		return (root);

	};
	const_iterator	lower_bound(const key_type& k) const
	{
		if (_comp((--this->end())->first, k))
			return (this->end());
		
		Node<value_type> *root = this->_btree.getRoot();

		while (root)
		{
			if (_comp(root->data.first, k) && root->right)
				root = root->right;
			else if (_comp(k, root->data.first) && root->left)
				root = root->left;
			else if (root->data.first == k)
				return (root);
			else
				break;
		}
		while (_comp(root->data.first, k))
			root = root->parent;
		
		return (root);	
	};

	iterator	upper_bound(const key_type& k)
	{
		iterator	it = lower_bound(k);

		if (it == this->end() || _comp(k, it->first))
			return (it);
		return (++it);
	};
	const_iterator	upper_bound(const key_type& k) const
	{
		iterator	it = lower_bound(k);

		if (it == this->end() || _comp(k, it->first))
			return (it);
		return (++it);
	};

	pair<const_iterator,const_iterator>	equal_range(const key_type& k) const
	{
		return (ft::make_pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k)));
	};
	pair<iterator,iterator> equal_range (const key_type& k)
	{
		return (ft::make_pair<iterator, iterator>(lower_bound(k), upper_bound(k)));
	};

//	OBSERVERS ********************************************
	key_compare		key_comp() const
	{
		return (key_compare());
	};

	value_compare	value_comp() const
	{
		return (value_compare(key_compare()));
	};

//	ALLOCATOR

	allocator_type	get_allocator() const
	{
		return (allocator_type(_alloc));
	};

	private :
		allocator_type		_alloc;
		key_compare			_comp;
		size_type			_size;
		BTree<value_type, key_compare>	_btree;


    };



}



#endif
