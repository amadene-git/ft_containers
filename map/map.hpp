#ifndef MAP_HPP
#define MAP_HPP

// #include <utility>//std::pair
#include "../vector/iterator.hpp"
#include "../vector/reverse_iterator.hpp"
#include "../btree/BTree.hpp"
#include "../btree/BTree_Iterator.hpp"
#include <iterator>//bidirectional

namespace ft
{
    template <	class Key,
           		class T,
           		class Compare = ft::less<Key>,
           		class Alloc = std::allocator< ft::pair<const Key,T> > >
    class map
    {
    public:
		
		typedef             Key                         key_type;
        typedef             T                           mapped_type;
		typedef				Compare						key_compare;
	    typedef				Alloc						allocator_type;
		typedef 			std::allocator< int >		allocator_int;// <- chelou A corriger !!!

       
        typedef typename    ft::pair<const key_type, mapped_type>			value_type;// const key_type                                  		
        
   
   
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
		_btree(),
		_size(0)
		{
//			std::cout << "Map default constructor called\n";
		};
	// template <class InputIterator>
	// map (InputIterator first, InputIterator last,
    // const key_compare& comp = key_compare(),
    // const allocator_type& alloc = allocator_type())
	// :_alloc(alloc),
	// _comp(comp),
	// _btree(),
	// _size(0)
	// {
	// 	while (first != last)
	// 	{
	// 		this->insert()
	// 	}
	// };
/*
copy (3)	
map (const map& x);
*/


//	CAPACITY ****************************

	bool		empty() const		{ return (!_size); };
	size_type	size() const		{ return (_size); };
	size_type	max_size() const	{ return (allocator_int().max_size() / 10); };// <- c'est temporaire hein... et surtout degueulasse 

//	MODIFIERS

	ft::pair<iterator, bool>	insert(const value_type& val)
	{
		ft::pair<iterator, bool> pr = _btree.insert_AVL(val);
		_size += pr.second;
		return (ft::make_pair<iterator, bool>(pr.first, pr.second));
	};
	iterator	insert(iterator position, const value_type& val)
	{

		(void)position;

		ft::pair<iterator, bool> pr = _btree.insert_AVL(val);
		_size += pr.second;
		return (pr.first);

	};
	template <class InputIterator>
	void insert (InputIterator first, InputIterator last)
	{
		while (first != last)
		{
			this->insert(ft::make_pair(first->first, first->second));
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
/*
	(1)	
     void erase (iterator position);
(2)	
size_type erase (const key_type& k);
(3)	
     void erase (iterator first, iterator last);
*/

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



// OPERATION
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

//	OBSERVERS ********************************************
	key_compare		key_comp() const
	{
		return (key_compare());
	};

	value_compare	value_comp() const
	{
		return (value_compare(key_compare()));
	};



	Node<value_type>	*get_btree()// A effacer !!!!!!!!!
	{
		return (_btree.getRoot());
	};



	private :
		allocator_type		_alloc;
		key_compare			_comp;
		BTree<value_type, key_compare>	_btree;
		size_type			_size;


    };



}



#endif
