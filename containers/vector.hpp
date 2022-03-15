#ifndef VECTOR_HPP
#define VECTOR_HPP

# include <memory>//std::allocator
# include <stdexcept>//std::out_of_range
# include <iterator>//std::distance


# include "../iterator/vector_iterator.hpp"
# include "../iterator/reverse_iterator.hpp"
# include "../include/lexicographical_compare.hpp"
# include "../include/equal.hpp"
# include "../include/enable_if.hpp"
# include "../include/is_integral.hpp"


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

		typedef typename 	ft::Vector_Iterator<value_type>			iterator;
		typedef	typename	ft::Vector_Iterator<const value_type>	const_iterator;

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

		};
		
		explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
		: _alloc(alloc),
		_size(0),
		_capacity(n)
		{
			this->_ptr = _alloc.allocate(_capacity);
			while (_size < n)
			{
				_alloc.construct(_ptr + _size, val);
				++_size;
			}

		};

		template <class InputIterator>
        vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
		: _alloc(alloc), 
		_size(size_type(std::distance<InputIterator>(first, last))),
		 _capacity(_size)
		{
			size_type i = 0;
			this->_ptr = _alloc.allocate(_capacity);
			
			while (i < _size)
			{
				_alloc.construct(_ptr + i, *first++);
				++i;
			}
		};

		vector(const vector& x)
		: _alloc(x._alloc), 
		_size(x._size),
		 _capacity(x._size)
		{
			
			this->_ptr = this->_alloc.allocate(this->_capacity);
			for (size_type i = 0; i < x._size; ++i)
				_alloc.construct(_ptr + i, *(x._ptr + i));
		};
		
		vector& operator=(const vector& rhs)
		{
			if (&rhs != this)
			{
				this->clear();
				this->reserve(rhs._size);
				_size = rhs._size;
				// std::cerr << "lol" << std::endl;
				for (difference_type i = 0; i < difference_type(_size); ++i)
				{
					// _alloc.destroy(_ptr + i);
					_alloc.construct(_ptr + i, *(rhs.begin() + i));
					// *(_ptr + i) = *(rhs.begin() + i);
				}
			}
			return (*this);
		};


		~vector()
		{			
			for (size_type i = 0; i < _size && _ptr; i++)
				_alloc.destroy(_ptr + i);
			_alloc.deallocate(_ptr, _capacity);
			_ptr = NULL;
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
				throw (std::length_error("vector::reserve"));
			if (n > _capacity)
			{
				pointer		tmp = _alloc.allocate(n);
								
				for (size_type i = 0; i < _size ; ++i)
					_alloc.construct(tmp + i, *(_ptr + i));
				

				for (size_type i = 0; i < _size; ++i)
					_alloc.destroy(_ptr + i);
				_alloc.deallocate(_ptr, _capacity);
				
				_ptr = tmp;
				_capacity = n;
			}
		};

		void resize(size_type n, value_type val = value_type())
		{
			if (n > _alloc.max_size())
					throw (std::length_error("vector::resize"));

			while (n < _size)
				_alloc.destroy(_ptr + --_size);

			if ((n && !_capacity) || n >= _capacity * 2)
				this->reserve(n);
			if (n > _capacity)
				while (n > _capacity)
					this->reserve(_capacity * 2);

			for (size_type i = 0; i < n - _size; ++i)
				_alloc.construct(_ptr + _size + i, val);

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
			pointer			tmp_ptr = _ptr;
			size_type		tmp_size = _size;
			size_type		tmp_capacity = _capacity;

			_ptr = x._ptr;
			_size = x._size;
			_capacity = x._capacity;

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
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
        {
			if (static_cast<size_type>(std::distance<InputIterator>(first, last)) > _alloc.max_size())
				throw (std::length_error("cannot create ft::vector larger than max_size()"));
			this->clear();
			while (first != last)
				this->push_back(*first++);								
        };

		
		iterator insert(iterator position, const value_type &value)
		{
			difference_type pos = position.base() - _ptr;
			
			insert(position, 1, value);
			
			return (_ptr + pos);
		}

		
		void insert(iterator position, size_type count, const value_type &value)
		{
			difference_type pos = position.base() - _ptr;
			
			if (!count)
				return;
			
			if (_size + size_type(count) >= _capacity * 2)
				reserve(_size + size_type(count));
			else if (_size + size_type(count) > _capacity)
				reserve(_size * 2);



			for (difference_type i = difference_type(_size) - 1; i >= pos; i--)
			{
				_alloc.construct(_ptr + i + count, *(_ptr + i));
				_alloc.destroy(_ptr + i);
			}

			for (difference_type i = pos; i < pos + difference_type(count); i++)
				_alloc.construct(_ptr + i, value);

			_size += count;
		}

		template <typename InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last,
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
		{
			difference_type pos = position.base() - _ptr;
			difference_type diff = std::distance(first, last);
			
			if (!diff)
				return;
			
			reserve(_size + size_type(diff));

			for (difference_type i = difference_type(_size) - 1; i >= (difference_type)pos; --i)
			{
				_alloc.construct(_ptr + i + diff, *(_ptr + i));
				_alloc.destroy(_ptr + i);
			}

			for (InputIterator it = first; it != last; ++it)
				_alloc.construct(_ptr + pos++, *it);

			_size += size_type(diff);
		}

		iterator erase(iterator pos)
		{
			return (erase(pos, pos + 1));
		}

		iterator erase(iterator first, iterator last)
		{
			difference_type diff = last - first;
			
			if (diff <= 0)
				return last;

			difference_type pos = first.base() - _ptr;

			for (difference_type i = pos; i < pos + diff; ++i)
				_alloc.destroy(_ptr + i);

			for (difference_type i = pos + diff; i < difference_type(_size); ++i)
			{
				_alloc.construct(_ptr + i - diff, *(_ptr + i));
				_alloc.destroy(_ptr + i);
			}

			_size -= size_type(diff);
			return (first);
		}


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
			return (const_reverse_iterator(this->end()));
		};

		reverse_iterator		rend()
		{
			return (reverse_iterator(this->begin() ));
		};
		const_reverse_iterator	rend() const
		{
			return (const_reverse_iterator( this->begin() ));
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
