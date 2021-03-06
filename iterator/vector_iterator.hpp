#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP


#include <iterator>//std::random_access_iterator_tag
// #include "../include/iterator.hpp"//std::iterator

namespace ft
{

	template <class T>
	class Vector_Iterator : public std::iterator<std::random_access_iterator_tag, T>
	{
	public :
			typedef typename	std::iterator<std::random_access_iterator_tag, T>::reference			reference;
			typedef typename	std::iterator<std::random_access_iterator_tag, T>::pointer			pointer;

			typedef	typename	std::iterator<std::random_access_iterator_tag, T>::difference_type	difference_type;
			typedef	typename	std::iterator<std::random_access_iterator_tag, T>::value_type		value_type;
			typedef	typename	std::iterator<std::random_access_iterator_tag, T>::iterator_category	iterator_category;

			Vector_Iterator(void) { _ptr = NULL; };
			Vector_Iterator(pointer	src) { _ptr = src; };
			Vector_Iterator(Vector_Iterator const &src) { *this = src; };
			virtual ~Vector_Iterator(void) {};
			
			//CLASSIC OVERLOAD
			Vector_Iterator 	&operator=(Vector_Iterator const &rhs)
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
			pointer		operator->(void) const { return &(this->operator*()); }

			//OVERLOAD COMPARISON
			bool	operator>(Vector_Iterator const &rhs)	const	{ return (_ptr >  rhs._ptr); };
			bool	operator>=(Vector_Iterator const &rhs)	const	{ return (_ptr >= rhs._ptr); };
			bool	operator<(Vector_Iterator const &rhs)	const	{ return (_ptr <  rhs._ptr); };
			bool	operator<=(Vector_Iterator const &rhs) 	const	{ return (_ptr <= rhs._ptr); };
			bool	operator==(Vector_Iterator const &rhs) 	const	{ return (_ptr == rhs._ptr); };
			bool	operator!=(Vector_Iterator const &rhs) 	const	{ return (_ptr != rhs._ptr); };
	
			
			//INCREMENT & DECREMENT
			Vector_Iterator	&operator++()
			{
				_ptr++;
				return (*this);
			};
			Vector_Iterator	operator++(int)
			{
				Vector_Iterator	temp = *this;
				++_ptr;
				return (temp);
			};

			Vector_Iterator	&operator--()
			{
				_ptr--;
				return (*this);
			};
			Vector_Iterator	operator--(int)
			{
				Vector_Iterator	temp = *this;
				--_ptr;
				return (temp);
			};		

			Vector_Iterator	&operator+=(difference_type n)
			{ 
				_ptr += n;
				return (*this);
			};
			Vector_Iterator	&operator-=(difference_type n)
			{ 
				_ptr -= n;
				return (*this);
			};
			
			//OVERLOAD ARITHMETIC
			Vector_Iterator	operator+(difference_type n) const	{ return (_ptr + n); };
			Vector_Iterator	operator-(difference_type n) const	{ return (_ptr - n); };
			
			difference_type		operator-(Vector_Iterator rhs)	const	
			{ return (_ptr - rhs._ptr); };

			//OVERLOAD CONST
			operator Vector_Iterator<const T> () const { return (Vector_Iterator<const T>(this->_ptr)); };
		
			pointer base() const
            { return (this->_ptr); }

		private :
			pointer	_ptr;
	};
//	OVERLOAD  n + it
template <typename T>
	Vector_Iterator<T> operator+(int i, const Vector_Iterator<T> &rhs) { return (rhs + i); }

template <typename T, typename P>
	Vector_Iterator<T> operator+(int i, const Vector_Iterator<P> &rhs) { return (rhs + i); }


//**************** != *************************

			template <typename T>
    		bool	operator!=(const ft::Vector_Iterator<T> lhs,
    		          const ft::Vector_Iterator<T> rhs)
    		{
    		    return (lhs.base() != rhs.base());
    		}
    		template<typename T_L, typename T_R>
    		bool	operator!=(const ft::Vector_Iterator<T_L> lhs,
    		          const ft::Vector_Iterator<T_R> rhs)
    		{
    		    return (lhs.base() != rhs.base());
    		}

//*************** == *****************************
			template <typename T>
    		bool	operator==(const ft::Vector_Iterator<T> lhs,
    		          const ft::Vector_Iterator<T> rhs)
    		{
    		    return (lhs.base() == rhs.base());
    		}
    		template<typename T_L, typename T_R>
    		bool	operator==(const ft::Vector_Iterator<T_L> lhs,
    		          const ft::Vector_Iterator<T_R> rhs)
    		{
    		    return (lhs.base() == rhs.base());
    		}

//************* > *******************************			
			template <typename T>
    		bool	operator>(const ft::Vector_Iterator<T> lhs,
    		          const ft::Vector_Iterator<T> rhs)
    		{
    		    return (lhs.base() > rhs.base());
    		}
    		template<typename T_L, typename T_R>
    		bool	operator>(const ft::Vector_Iterator<T_L> lhs,
    		          const ft::Vector_Iterator<T_R> rhs)
    		{
    		    return (lhs.base() > rhs.base());
    		}

//***************** >= ******************************
			template <typename T>
    		bool	operator>=(const ft::Vector_Iterator<T> lhs,
    		          const ft::Vector_Iterator<T> rhs)
    		{
    		    return (lhs.base() >= rhs.base());
    		}
    		template<typename T_L, typename T_R>
    		bool	operator>=(const ft::Vector_Iterator<T_L> lhs,
    		          const ft::Vector_Iterator<T_R> rhs)
    		{
    		    return (lhs.base() >= rhs.base());
    		}

//**************** < *********************************
			template <typename T>
    		bool	operator<(const ft::Vector_Iterator<T> lhs,
    		          const ft::Vector_Iterator<T> rhs)
    		{
    		    return (lhs.base() < rhs.base());
    		}
    		template<typename T_L, typename T_R>
    		bool	operator<(const ft::Vector_Iterator<T_L> lhs,
    		          const ft::Vector_Iterator<T_R> rhs)
    		{
    		    return (lhs.base() < rhs.base());
    		}

//********************** <= **************************
			template <typename T>
    		bool	operator<=(const ft::Vector_Iterator<T> lhs,
    		          const ft::Vector_Iterator<T> rhs)
    		{
    		    return (lhs.base() <= rhs.base());
    		}
    		template<typename T_L, typename T_R>
    		bool	operator<=(const ft::Vector_Iterator<T_L> lhs,
    		          const ft::Vector_Iterator<T_R> rhs)
    		{
    		    return (lhs.base() <= rhs.base());
    		}


}

#endif
