#ifndef VECTOR_HPP
#define VECTOR_HPP

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



//			MEMBER FUNCTION PUBLIC
//		CONSTRUCTOR

		explicit vector(const allocator_type& alloc = allocator_type())
		{
			std::cout << "Vector Default constructor called ->" << this << std::endl;
			_alloc = alloc;
			_ptr = _alloc.allocate(0);
			_size = 0;
			_capacity = 0;
		};
		
		explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
		{
			std::cout << "Vector Fill constructor called ->" << this << std::endl;			
			_alloc = alloc;
			_ptr = _alloc.allocate(n);
			_size = n;
			_capacity = n;
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
			std::cout << "Vector Default destructor called ->" << this << std::endl;

			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(_ptr + i);
			_alloc.deallocate(_ptr, _size);
		};


//		ACCESS
		//out of range exception throw
		reference at(size_type n)
		{
			if (n >= _size)
				throw std::out_of_range("Exception: vector::at() out of range\n");
			return (*(_ptr + n ));
		};

		const_reference at(size_type n) const
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


//		CAPACITY	
		size_type	size()		const	{ return (_size); };
		size_type	max_size() 	const	{ return (_alloc.max_size()); };
		size_type	capacity() 	const	{ return (_capacity); };
		bool		empty() 	const	{ return ((_size == 0) ? true : false); };

		void resize(size_type n, value_type val = value_type())//if it has to reallocate storage, all iterators, pointers and references related to this container are also invalidated.
		{
			if (n > _alloc.max_size())
					throw (std::length_error("vector::resize"));
			while (n < _size)
				_alloc.destroy(_ptr + --_size);
			if (n > _capacity)
			{
				pointer		tmp;//alloc new obj
				size_type	old_capacity = _capacity;
				std::cout << "1\n" << std::endl;
				_capacity = (!_capacity) ? n : _capacity;
				while (n > _capacity)
					_capacity *= 2;
				std::cout << "capacity :" << _capacity << "|"<< std::endl;
				tmp = _alloc.allocate(_capacity);
				std::cout << "2\n" << std::endl;
				
				//fill it
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(tmp + i, *(_ptr + i));
				for (size_type i = _size; i < n; i++)
					_alloc.construct(tmp + i, val);
				std::cout << "3\n" << std::endl;
				
				//destroy old one
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_ptr + i);
				_alloc.deallocate(_ptr, old_capacity);
				std::cout << "4\n" << std::endl;
				
				_size = n;
				_ptr = tmp;//en vrai je dois pas faire ca, oublie pas de revenir dessus Adrien
			}
			else if (n > _size)
			{
				for (size_type i = _size; i < n; i++)
					_alloc.construct(_ptr + i, val);
				_size = n;
			}
		};

		void	reserve(size_type n)
		{
			if (n > _alloc.max_size())
				throw (std::length_error("vector::reserve"));
			if (n > _capacity)
			{
				pointer		tmp;//alloc new obj
				size_type	old_capacity = _capacity;

				_capacity = n;
				tmp = _alloc.allocate(_capacity);
				
				//fill it
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(tmp + i, *(_ptr + i));
				
				//destroy old one
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_ptr + i);
				_alloc.deallocate(_ptr, old_capacity);
				
				_ptr = tmp;
			}
		};

//		MODIFIERS
		void	push_back(const value_type& val)
		{
			if (_size == _capacity)
				this->reserve(_capacity * 2);
			_alloc.construct(_ptr + _size, val);
			++_size;
		};
		void	pop_back()
		{
			if (_size)
				_alloc.destroy(_ptr + (--_size));
		};


/*assign
Assign vector content (public member function )
pop_back
Delete last element (public member function )
insert
Insert elements (public member function )
erase
Erase elements (public member function )
swap
Swap content (public member function )
clear
Clear content (public member function )*/

//	private:
		allocator_type	_alloc;
		pointer			_ptr;
		size_type		_size;
		size_type		_capacity;

	};
}

#endif
