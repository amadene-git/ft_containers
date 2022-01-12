#ifndef ITERATOR_HPP
#define ITERATOR_HPP
namespace ft 
{

	struct input_iterator_tag { };

	struct output_iterator_tag { };

	struct forward_iterator_tag : public input_iterator_tag { };

	struct bidirectional_iterator_tag : public forward_iterator_tag { };

	struct random_access_iterator_tag : public bidirectional_iterator_tag { };



	template <	class Category,              // iterator::iterator_category
			 class T,                     // iterator::value_type
			 class Distance = __gnu_cxx::ptrdiff_t,  // iterator::difference_type
			 class Pointer = T*,          // iterator::pointer
			 class Reference = T& >         // iterator::reference
				 class iterator
				 {
					 public :
						 typedef T         value_type;
						 typedef Distance  difference_type;
						 typedef Pointer   pointer;
						 typedef Reference reference;
						 typedef Category  iterator_category;
				 };

	template <class T>
		class random_access_iterator : public ft::iterator<random_access_iterator_tag, T>
	{
		public :
			typedef	T&	reference;
			typedef	T*	pointer;

			typedef	typename	ft::iterator<random_access_iterator_tag, T>::difference_type	difference_type;
			typedef	typename	ft::iterator<random_access_iterator_tag, T>::value_type			value_type;
			typedef	typename	ft::iterator<random_access_iterator_tag, T>::iterator_category	iterator_category;

			random_access_iterator(void) { _ptr = NULL; };
			random_access_iterator(pointer	src) { _ptr = src; };
			random_access_iterator(random_access_iterator const &src) { *this = src; };
			virtual ~random_access_iterator(void) {};
			
			//CLASSIC OVERLOAD
			random_access_iterator 	&operator=(random_access_iterator const &rhs)
			{
				this->_ptr = rhs._ptr;
				return (*this);
			}

			reference				operator[](difference_type n)
			{
				return (*(_ptr + n));
			}

			//OVERLOAD POINTER
			reference	operator*(void) const { return (*_ptr); }

			//OVERLOAD COMPARISON
			bool	operator>(random_access_iterator const &rhs)	const	{ return (_ptr >  rhs._ptr); };
			bool	operator>=(random_access_iterator const &rhs)	const	{ return (_ptr >= rhs._ptr); };
			bool	operator<(random_access_iterator const &rhs)	const	{ return (_ptr <  rhs._ptr); };
			bool	operator<=(random_access_iterator const &rhs) 	const	{ return (_ptr <= rhs._ptr); };
			bool	operator==(random_access_iterator const &rhs) 	const	{ return (_ptr == rhs._ptr); };
			bool	operator!=(random_access_iterator const &rhs) 	const	{ return (_ptr != rhs._ptr); };
	
			//INCREMENT & DECREMENT
			random_access_iterator	&operator++()
			{
				_ptr++;
				return (*this);
			};
			random_access_iterator	operator++(int)
			{
				random_access_iterator	temp = *this;
				++_ptr;
				return (temp);
			};

			random_access_iterator	&operator--()
			{
				_ptr--;
				return (*this);
			};
			random_access_iterator	operator--(int)
			{
				random_access_iterator	temp = *this;
				--_ptr;
				return (temp);
			};		

			random_access_iterator	&operator+=(difference_type n)
			{ 
				_ptr += n;
				return (*this);
			};
			random_access_iterator	&operator-=(difference_type n)
			{ 
				_ptr -= n;
				return (*this);
			};
			
			//OVERLOAD ARITHMETIC
			random_access_iterator	operator+(difference_type n) const	{ return (_ptr + n); };
			random_access_iterator	operator-(difference_type n) const	{ return (_ptr - n); };
			
			difference_type		operator-(random_access_iterator rhs)	const	
			{ return (_ptr - rhs._ptr); };

			//OVERLOAD CONST
			operator random_access_iterator<const T> () const { return (random_access_iterator<const T>(this->_elem)); }
		
		private :
			pointer	_ptr;
	};

//	OVERLOAD  n + it
template <typename T>
	random_access_iterator<T> operator+(int i, const random_access_iterator<T> &rhs) { return (rhs + i); }
}

#endif
