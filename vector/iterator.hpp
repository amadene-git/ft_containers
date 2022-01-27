#ifndef ITERATOR_HPP
#define ITERATOR_HPP

namespace ft 
{
	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };

	template <	class Category, class T, class Distance = __gnu_cxx::ptrdiff_t, 
				class Pointer = T*, class Reference = T& >
	class iterator
	{
	public :
		typedef T         value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
		typedef Category  iterator_category;
	};

	template <class Iterator>
	class iterator_traits
	{
		typedef typename	Iterator::difference_type	difference_type;
		typedef typename	Iterator::value_type 		value_type;
		typedef typename	Iterator::pointer 			pointer;
		typedef typename	Iterator::reference 		reference;
		typedef typename	Iterator::iterator_category iterator_category;
	};
	template <class T> 
	class iterator_traits<T*>
	{
		typedef 			__gnu_cxx::ptrdiff_t					difference_type;
		typedef 			T							value_type;
		typedef 			T*							pointer;
		typedef 			T&							reference;
		typedef 			random_access_iterator_tag	iterator_category;
	};
	template <class T> 
	class iterator_traits<const T*>
	{
		typedef 			__gnu_cxx::ptrdiff_t		difference_type;
		typedef 			T							value_type;
		typedef 			const T*					pointer;
		typedef 			const T&					reference;
		typedef 			random_access_iterator_tag	iterator_category;
	};



	template <class Iterator>
	class reverse_iterator
	{
		private	:
		Iterator	_base;
		
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
				_base = rev_it;
			};

			virtual ~reverse_iterator(void) {};

			iterator_type	base(void) const
			{
				return (_base);
			};

			//OVERLOAD POINTER
			reference	operator*(void)		const { return (*_base); }
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
		return (lhs == rhs);
	}	
	template <class Iterator> 
	bool	operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs != rhs);
	}	
	template <class Iterator> 
	bool	operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs > rhs);
	}
	template <class Iterator> 
	bool	operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs >= rhs);
	}
	template <class Iterator> 
	bool	operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs < rhs);
	}
	template <class Iterator> 
	bool	operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs <= rhs);
	}


}
#endif
