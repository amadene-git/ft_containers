#ifndef VECTOR_HPP
#define VECTOR_HPP

//A SUPPRIMER
// #include <vector>
// #include <type_traits>
//

#include <iostream>
#include <memory>
#include <algorithm>
#include "vector_iterator.hpp"
#include "reverse_iterator.hpp"

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

		typedef typename 	ft::Vector_Iterator<T>					iterator;
		typedef	typename	ft::Vector_Iterator<const T>			const_iterator;

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
		_ptr(_alloc.allocate(n)),
		_size(n),
		_capacity(n)
		{
			// std::cout << "Vector Fill constructor called ->" << this << std::endl;			
			std::fill_n(_ptr, n, val);
		};

		template <class InputIterator>
        vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = NULL)//A CORRIGER !!!
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
								
				std::copy(this->begin(), this->end(), tmp);

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
			iterator		it = this->begin();
			size_type		n = 0;
			difference_type	k = 0;

			while (it != position)
			{
				++it;
				++n;
			}				

			if (_capacity == _size)
				this->reserve(_capacity * 2);
			k = static_cast<difference_type>(_size);
			it = this->begin();
			
			while (k > static_cast<difference_type>(n))
			{
				it[k + 1] = it[k];
				--k;
			}
			it[k] = val;
			++_size;
			return (it + k);
		};
		void	insert(iterator position, size_type n, const value_type& val)
		{
			if (n > _alloc.max_size())
				throw (std::length_error("ft::vector::fill_insert"));
		
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
			iterator		it = this->begin();
			difference_type	i = 0;
			difference_type	k = 0;

			while (it != position)
			{
				++it;
				++i;
			}				

			while (_size + static_cast<size_type>(diff) > _capacity)
				this->reserve(_size *2);
			k = static_cast<difference_type>(_size) + diff;
			it = this->begin();
			while (k > i)
			{
				_ptr[k] = _ptr[k - diff];
				--k;
			}

			_size += static_cast<size_type>(diff);
			i = -1;
			while (diff--)
				it[k + diff] = first[++i];
		};

		iterator	erase(iterator position)
		{
			iterator		it = this->begin();
			difference_type	n = 0;
			difference_type	k = 0;

			while (it != position)
			{
				++it;
				++n;
			}				

			k = static_cast<difference_type>(_size);
			it = this->begin();

			while (k > n)
			{
				it[n] = it[n + 1];
				++n;
			}
			--_size;
			_alloc.destroy(_ptr + _size);
			return (position);	
		};
		iterator	erase(iterator first, iterator last)
		{
			difference_type	diff = last - first;	
			iterator		it = this->begin();
			difference_type	i = 0;
			difference_type	k = 0;

			while (it != first)
			{
				++it;
				++i;
			}				

			k = static_cast<difference_type>(_size) - diff;
			it = this->begin();
			while (k > i)
			{
				it[i] = it[i + diff];
				++i;
			}
			while (i < static_cast<difference_type>(_size))
				_alloc.destroy(_ptr + i++ - 1);
			_size -= static_cast<size_type>(diff);
			return (first);
		};



//		ITERATOR
		iterator 		begin() 		{ return (_ptr); };
		const_iterator	begin() const	{ return (_ptr); };
		
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
