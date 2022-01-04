#include <iostream>
#include <memory>

namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
	public:


//		MEMBER_TYPE

		typedef 			T								value_type;	

		typedef 			Allocator						allocator_type;	
		
		typedef	typename	allocator_type::reference		reference;

		typedef	typename	allocator_type::const_reference	const_reference;	

		typedef	typename	allocator_type::pointer			pointer;

		typedef typename	allocator_type::const_pointer	const_pointer;

		typedef	typename	allocator_type::size_type		size_type;

/*
iterator	a random access iterator to value_type	convertible to const_iterator
const_iterator	a random access iterator to const value_type	
reverse_iterator	reverse_iterator<iterator>	
const_reverse_iterator	reverse_iterator<const_iterator>	
difference_type	a signed integral type, identical to: iterator_traits<iterator>::difference_type	usually the same as ptrdiff_t
*/	





//		CONSTRUCTOR

		explicit vector (const allocator_type& alloc = allocator_type())
		{
			std::cout << "Default constructor called ->" << this << std::endl;
			_alloc = alloc;
			_ptr = _alloc.allocate(0);
			_size = 0;
		};
		
		explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
		{
			std::cout << "Fill constructor called ->" << this << std::endl;			
			_alloc = alloc;
			_ptr = _alloc.allocate(n);
			_size = n;
			for (size_type i = 0; i < n; i++)
				_alloc.construct(_ptr + i, val); 

		};
/*
range (3)	
template <class InputIterator>
         vector (InputIterator first, InputIterator last,
                 const allocator_type& alloc = allocator_type());
copy (4)	
vector (const vector& x);
*/
		~vector()
		{
			std::cout << "Default destructor called ->" << this << std::endl;

			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(_ptr + i);
			_alloc.deallocate(_ptr, _size);
		};




//			MEMBER FUNCTION PUBLIC
//		ACCESS
		//out of range exception throw
		reference at (size_type n)
		{
			if (n >= _size)
				throw std::out_of_range("Exception: vector::at() out of range\n");
			return (*(_ptr + n ));
		};

		const_reference at (size_type n) const
		{
			if (n >= _size)
				throw std::out_of_range("Exception: const vector::at() out of range\n");
			return (*(_ptr + n ));	
		};

		//out of range undefined behavior
		reference		front()			{ return (*_ptr); };
		const_reference	front() const	{ return (*_ptr); };

		reference		back()			{ return (*(_ptr + _size)); };
		const_reference	back() const	{ return (*(_ptr + _size)); };
	
		reference		operator[] (size_type n)		{ return (*(_ptr + n)); };
		const_reference	operator[] (size_type n) const	{ return (*(_ptr + n)); };

	
//	private:
		allocator_type	_alloc;
		pointer			_ptr;
		size_type		_size;

	};
}


