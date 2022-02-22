#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <algorithm>
#include <stdexcept>
#include "../iterator/vector_iterator.hpp"
#include "../iterator/reverse_iterator.hpp"

namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
	public:

//		MEMBER_TYPE
		typedef 			T										value_type;	

		typedef 			Allocator								allocator_type;	
		
		typedef	typename	allocator_type::reference				reference;
		typedef	typename	allocator_type::const_reference			const_reference;	

		typedef	typename	allocator_type::pointer					pointer;
		typedef typename	allocator_type::const_pointer			const_pointer;

		typedef typename 	ft::Vector_Iterator<value_type>					iterator;
		typedef	typename	ft::Vector_Iterator<const value_type>			const_iterator;

		typedef typename	ft::reverse_iterator<iterator>			reverse_iterator;
		typedef typename	ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		typedef	typename	allocator_type::size_type						size_type;
		typedef typename 	ft::iterator_traits<iterator>::difference_type	difference_type;

		
		

//			MEMBER FUNCTION PUBLIC
//		CONSTRUCTOR
		explicit vector(const allocator_type& alloc = allocator_type()) 
		: _alloc(alloc),
		_ptr(NULL),
		_size(0),
		_capacity(0)
		{
			// std::cout << "Vector Default constructor called ->" << this << std::endl;
		};
		
		explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
		: _alloc(alloc),
		// _ptr(_alloc.allocate(n)),
		_size(0),
		_capacity(n)
		{
			// std::cout << "Vector Fill constructor called ->" << this << std::endl;			
			this->_ptr = _alloc.allocate(n);
			
			while (_size < n)
			{
				_alloc.construct(_ptr + _size, val);
				++_size;
			}

		};

		template <class InputIterator>
        vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)//A CORRIGER !!!
		: _alloc(alloc), 
		_ptr(_alloc.allocate(size_type(last - first))),
		_size(size_type(last - first)),
		 _capacity(_size)
		{
			std::copy(first, last, _ptr);
		};

		vector(const vector& x)
		: _alloc(x._alloc), 
		_ptr(NULL),
		_size(0),
		 _capacity(0)
		{
			*this = x;
		};
		
		vector& operator=(const vector& rhs)
		{
			if (&rhs != this)
			{
				this->clear();
				this->resize(rhs._size);
				std::copy(rhs.begin(), rhs.end(), _ptr);
			}
			return (*this);
		};


		~vector()
		{
			// std::cout << "Vector Default destructor called ->" << this << std::endl;			
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(_ptr + i);
			_alloc.deallocate(_ptr, _size);
		};


//		ACCESS
		//out of range exception throw
		reference		at(size_type n)
		{
			if (n >= _size)
				throw std::out_of_range("Exception: vector::at() out of range\n");
			return (*(_ptr + n ));
		};
		const_reference	at(size_type n) const
		{
			if (n >= _size)
				throw std::out_of_range("Exception: const vector::at() out of range\n");
			return (*(_ptr + n ));	
		};

		//out of range undefined behavior
		reference		front()			{ return (*_ptr); };
		const_reference	front() const	{ return (*_ptr); };

		reference		back()			{ return (*(_ptr + _size - 1)); };
		const_reference	back() const	{ return (*(_ptr + _size - 1)); };
	
		reference		operator[] (size_type n)		{ return (*(_ptr + n)); };
		const_reference	operator[] (size_type n) const	{ return (*(_ptr + n)); };


//		CAPACITY	
		size_type	size()		const	{ return (_size); };
		size_type	max_size() 	const	{ return (_alloc.max_size()); };
		size_type	capacity() 	const	{ return (_capacity); };
		bool		empty() 	const	{ return ((_size == 0) ? true : false); };

		void	reserve(size_type n)
		{
			if (n > _alloc.max_size())
				throw (std::length_error("cannot create ft::vector larger than max_size()"));
			if (n > _capacity)
			{
				pointer		tmp = _alloc.allocate(n);
								
				for (size_type i = 0; i < _size ; i++)
					_alloc.construct(tmp + i, *(_ptr + i));
				

				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_ptr + i);
				_alloc.deallocate(_ptr, _capacity);
				
				_ptr = tmp;
				_capacity = n;
			}
		};

		void resize(size_type n, value_type val = value_type())//if it has to reallocate storage, all iterators, pointers and references related to this container are also invalidated.
		{
			if (n > _alloc.max_size())
					throw (std::length_error("cannot create ft::vector larger than max_size()"));
		
			while (n < _size)
				_alloc.destroy(_ptr + --_size);
			
			if (n && !_capacity)
				this->reserve(n);
			if (n > _capacity)
				while (n > _capacity)
					this->reserve(_capacity * 2);

			std::fill_n(_ptr + _size, n - _size, val);

			_size = n;
		};

//		MODIFIERS
		void	push_back(const value_type& val)
		{
			this->resize(_size + 1, val);
		};
		void	pop_back(void)
		{
			if (_size)
				_alloc.destroy(_ptr + (--_size));
		};

		void	swap(vector& x)
		{
			allocator_type	tmp_alloc = _alloc;
			pointer			tmp_ptr = _ptr;
			size_type		tmp_size = _size;
			size_type		tmp_capacity = _capacity;

			_alloc = x._alloc;
			_ptr = x._ptr;
			_size = x._size;
			_capacity = x._capacity;

			x._alloc = tmp_alloc;
			x._ptr = tmp_ptr;
			x._size = tmp_size;
			x._capacity = tmp_capacity;
		};

		void	clear(void)
		{
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(_ptr + i);
			_size = 0;
		};

		void	assign(size_type n, const value_type& val)
		{
			this->clear();
			this->resize(n, val);
		};
		
		template<typename InputIterator>
        void assign(InputIterator first, InputIterator last,
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = NULL)//A CORRIGER !!!
        {
			if (static_cast<size_type>(last - first) > _alloc.max_size())
				throw (std::length_error("cannot create ft::vector larger than max_size()"));
			this->clear();
			while (first != last)
				this->push_back(*first++);								
        };

		iterator	insert(iterator position, const value_type& val)
		{
			difference_type	pos = position - this->begin();
			
			if (_capacity == _size)
			{
				if (_capacity)
					this->reserve(_capacity * 2);
				else
					this->reserve(1);
				position = _ptr + pos;
			}
		
			for (difference_type i = _size; i > pos; i--)
				*(_ptr + i) = *(_ptr + (i - 1));
			
			this->_alloc.construct(this->_ptr + pos, val);
			++_size;

			return (this->begin() + pos);
		};
		void	insert(iterator position, size_type n, const value_type& val)
		{
			if (n > _alloc.max_size())
				throw (std::length_error("cannot create ft::vector larger than max_size()"));
		
			difference_type	i = position - this->begin();
			difference_type	j = difference_type(_size);

			if (_size + n > _capacity)
				this->reserve(_size + n);
			
			while (i <= --j)
				_alloc.construct(_ptr + j + n, *(_ptr + j));
			for (difference_type a = 0; a < difference_type(n); a++)
				_alloc.construct(_ptr + i + a, val);
			_size += n;
		};
		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last,
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)//A CORRIGER !!!
		{
			if (static_cast<size_type>(last - first) > _alloc.max_size())
				throw (std::length_error("cannot create ft::vector larger than max_size()"));

			difference_type	diff = last - first;	
			difference_type	pos = position - this->begin();
			
			if (!_size)
				this->reserve(size_type(diff));
			else
				while (_size + static_cast<size_type>(diff) > _capacity)
					this->reserve(_capacity * 2);
			
			position = _ptr + pos; 
			iterator	it = this->end() - 1;
		
			while (it >= position)
			{
				*(it + diff) = *it;
				--it;
			}

			while (first != last)
			{
				this->_alloc.construct(this->_ptr + pos, *first);
				++first;
				++pos;
			}
			_size += static_cast<size_type>(diff);
		};

		iterator	erase(iterator position)
		{
			if (position == this->end())
				return (this->end());
			
			difference_type	pos = position - this->begin();			

			while (++position != this->end())
				*(position - 1) = *(position);
			
			--this->_size;
			this->_alloc.destroy(_ptr + this->_size);
			
			return (this->_ptr + pos);	
		};
		iterator	erase(iterator first, iterator last)
		{
			difference_type	diff = (last - first);

			while (++last != this->end())
				*(last - diff) = *last;

			while (--diff)
			{
				this->_alloc.destroy(_ptr + this->_size - 1);
				--this->_size;
			}
			return (first);
		};



//		ITERATOR
		iterator 		begin() 		{ return (this->_ptr); };
		const_iterator	begin() const	{ return (this->_ptr); };
		
		iterator		end()
		{
			if (this->empty())
				return (_ptr);
			return (_ptr + _size);
		};
		const_iterator	end() const
		{
			if (this->empty())
				return ( _ptr);
			return (_ptr + _size);
		};
		
		reverse_iterator		rbegin()
		{
			return (reverse_iterator(this->end()));
		};
		const_reverse_iterator	rbegin() const
		{
			return (reverse_iterator(this->end()));
		};

		reverse_iterator		rend()
		{
			return (reverse_iterator(this->begin() ));
		};
		const_reverse_iterator	rend() const
		{
			return (reverse_iterator( this->begin() ));
		};


//		ALLOCATOR
		allocator_type	get_allocator(void) const { return (_alloc); };


	private:
		allocator_type	_alloc;
		pointer			_ptr;
		size_type		_size;
		size_type		_capacity;

	};

//	RELATIONAL OPERATORS
	template <class T, class Alloc>
	bool	operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}
	template <class T, class Alloc>
	bool	operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}
	template <class T, class Alloc>
	bool	operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	template <class T, class Alloc>
	bool	operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(rhs < lhs));
	}
	template <class T, class Alloc>
	bool	operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool	operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(rhs > lhs));
	}

//	NON MEMBER SWAP
	template <class T, class Alloc>
	void	swap(vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		x.swap(y);
	}

}

#endif
