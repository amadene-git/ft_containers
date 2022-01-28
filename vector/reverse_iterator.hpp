#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator.hpp"

namespace ft
{
	template <class Iterator>
	class reverse_iterator
	{
		public :

			typedef 			Iterator										iterator_type;	

			typedef typename	ft::iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename 	ft::iterator_traits<Iterator>::value_type			value_type;
			typedef typename	ft::iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename	ft::iterator_traits<Iterator>::pointer				pointer;
			typedef typename	ft::iterator_traits<Iterator>::reference			reference;


			reverse_iterator(void){};
			explicit reverse_iterator(iterator_type it)
			{
				_base = it;
			};

			template <class Iter>
  			reverse_iterator (const reverse_iterator<Iter>& rev_it)
			{
				_base = rev_it._base;
			};

			virtual ~reverse_iterator(void) {};

			iterator_type	base(void) const
			{
				return (_base);
			};

			//OVERLOAD POINTER
			reference	operator*(void)		const 
			{ 
				iterator_type tmp = _base;
				--tmp;
                return (*tmp);
			}
			pointer		operator->(void)	const { return &(operator*()); }

	

			//OVERLOAD ARITHMETIC
			reverse_iterator	operator+(difference_type n) const	{ return (_base - n); };
			reverse_iterator	operator-(difference_type n) const	{ return (_base + n); };

			//INCREMENT & DECREMENT
			reverse_iterator	&operator++()
			{
				_base--;
				return (*this);
			};
			reverse_iterator	operator++(int)
			{
				reverse_iterator	temp = *this;
				++(*this);
				return (temp);
			};

			reverse_iterator	&operator--()
			{
				_base++;
				return (*this);
			};
			reverse_iterator	operator--(int)
			{
				reverse_iterator	temp = *this;
				--(*this);
				return (temp);
			};		

			reverse_iterator	&operator+=(difference_type n)
			{ 
				_base -= n;
				return (*this);
			};
			reverse_iterator	&operator-=(difference_type n)
			{ 
				_base += n;
				return (*this);
			};

			//CLASSIC OVERLOAD
			// reverse_iterator 	&operator=(reverse_iterator const &rhs)
			// {
			// 	this->_base = rhs._base;
			// 	return (*this);
			// }

			reference	operator[](difference_type n) { return (this->base()[-n -1]); }	
			
			//OVERLOAD CONST
			operator reverse_iterator<const Iterator> () const { return (reverse_iterator<const Iterator>(*this)); };

	
		private	:
		iterator_type	_base;
	};
	//OVERLOAD + -
	template <class Iterator>
	reverse_iterator<Iterator> operator+(	typename reverse_iterator<Iterator>::difference_type n,
											const reverse_iterator<Iterator>& rev_it)
	{
		return (rev_it + n);
	}
	
	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(	const reverse_iterator<Iterator>& lhs, 
																	const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() - rhs.base());
	}
	
	//RELATIONAL OPERATORS
	template <class Iterator> 
	bool operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() == rhs.base());
	}	
	template <class Iterator> 
	bool	operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() != rhs.base());
	}	
	template <class Iterator> 
	bool	operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() > rhs.base());
	}
	template <class Iterator> 
	bool	operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}
	template <class Iterator> 
	bool	operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() < rhs.base());
	}
	template <class Iterator> 
	bool	operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() <= rhs.base());
	}

}


#endif
