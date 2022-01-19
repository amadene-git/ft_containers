#ifndef VECTOR_HPP
#define VECTOR_HPP

//A SUPPRIMER
// #include <vector>
// #include <type_traits>
//

#include <iostream>
#include <memory>
#include "iterator.hpp"
#include "utils.hpp"

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

		
		typedef typename 	ft::random_access_iterator<T>		iterator;
		typedef	typename	ft::random_access_iterator<const T>	const_iterator;
		
		
		typedef typename 	ft::random_access_iterator<T>::difference_type	difference_type;// a corriger -> iterator_trait<iterator>::difference_type


/*
reverse_iterator	reverse_iterator<iterator>	
const_reverse_iterator	reverse_iterator<const_iterator>	
*/	



//			MEMBER FUNCTION PUBLIC
//		CONSTRUCTOR
		explicit vector(const allocator_type& alloc = allocator_type())
		{
			// std::cout << "Vector Default constructor called ->" << this << std::endl;
			_alloc = alloc;
			_ptr = NULL;
			_size = 0;
			_capacity = 0;
		};
		
		explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
		{
			// std::cout << "Vector Fill constructor called ->" << this << std::endl;			
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
				pointer		tmp;//alloc new obj

				tmp = _alloc.allocate(n);
				
				//fill it
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(tmp + i, *(_ptr + i));
				
				//destroy old one
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
			
			//gestion de _capacity == 0
			if (n && !_capacity)
				this->reserve(n);
			if (n > _capacity)
				while (n > _capacity)
					this->reserve(_capacity * 2);

			for (size_type i = _size; i < n; i++)
				_alloc.construct(_ptr + i, val);
								
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
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)//A CORRIGER !!!
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
			iterator		it = this->begin();
			size_type		i = 0;
			difference_type	k = 0;

			while (it != position)
			{
				++it;
				++i;
			}				

			if (_size + n > _capacity)
				this->reserve(_size + n);
			k = static_cast<difference_type>(_size + n);
			it = this->begin();
			while (k > static_cast<difference_type>(i))
			{
				it[k] = it[k - static_cast<difference_type>(n)];
				--k;
			}
			_size += n;
			while (n--)
				it[k + static_cast<difference_type>(n)] = val;
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
				it[k] = it[k - diff];
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
				return (_ptr);
			return (_ptr + _size);
		};

/*
rbegin
Return reverse iterator to reverse beginning (public member function )
rend
Return reverse iterator to reverse end (public member function )*/


//		ALLOCATOR
		allocator_type	get_allocator(void) const { return (_alloc); };


	private:
		allocator_type	_alloc;
		pointer			_ptr;
		size_type		_size;
		size_type		_capacity;

	};
}

#endif
