#ifndef MAP_HPP
#define MAP_HPP

#include <utility>//std::pair
#include "iterator.hpp"
#include "reverse_iterator.hpp"
#include <iterator>//bidirectional

namespace ft
{
    template < class Key,                                     // map::key_type
           class T,                                       // map::mapped_type
           class Compare = ft::less<Key>,                     // map::key_compare
           class Alloc = std::allocator< std::pair<const Key,T> > >   // map::allocator_type SERIEUX MEC OUBLIE PAS D'IMPLEMENTER PAIR !!!!!!
    class map
    {
    public:
		
		typedef             Key                         key_type;                                    		
        typedef             T                           mapped_type;                                 		
       
        typedef typename    std::pair<const key_type, mapped_type>			value_type;// <- A corriger !                                  		
        
		typedef				Compare						key_compare;                                 	
       
	    typedef     Alloc											allocator_type;                                  
    //   template <class Key, class T, class Compare, class Alloc>
		class	value_compare : binary_function<value_type, value_type, bool>// class map<Key,T,Compare,Alloc>::value_compare
		{   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
			friend class map;
		protected:
			Compare comp;
			value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object

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
        
        typedef typename    std::iterator<std::bidirectional_iterator_tag, value_type>				iterator;// <- A corriger !
        typedef typename	std::iterator<std::bidirectional_iterator_tag, const value_type>		const_iterator;// <- A corriger !
        
		typedef typename	ft::reverse_iterator<iterator>					reverse_iterator;	
        typedef typename	ft::reverse_iterator<const_iterator>			const_reverse_iterator;	
        
		
		typedef typename	ft::iterator_traits<iterator>::difference_type		difference_type;
        typedef    			size_t												size_type;// <- A vérifier !

		~map()
		{
			std::cout << "Map default destructor called\n";
		};


//	CONSTRUCTOR
		explicit map(const key_compare& comp = key_compare(),
        			const allocator_type& alloc = allocator_type())
		:_alloc(alloc),
		_comp(comp)
		{
//			std::cout << "Map default constructor called\n";
		};
/*
range (2)	
template <class InputIterator>
  map (InputIterator first, InputIterator last,
       const key_compare& comp = key_compare(),
       const allocator_type& alloc = allocator_type());
copy (3)	
map (const map& x);
*/


//	OBSERVERS
	key_compare		key_comp() const
	{
		return (key_compare());
	};

	value_compare	value_comp() const
	{
		return (value_compare(key_compare()));
	};



	private :
		allocator_type	_alloc;
		key_compare		_comp;


    };



}



#endif
