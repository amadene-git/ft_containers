#ifndef BTREE_ITERATOR_HPP
#define BTREE_ITERATOR_HPP

#include "iterator.hpp"

namespace ft
{

	template <class T, class Cond>
	class BTree_Iterator : public ft::iterator<bidirectional_iterator_tag, T>
	{
	public :

			typedef	typename	T::value_type value_type;

			typedef	typename	ft::iterator<bidirectional_iterator_tag, value_type>::difference_type	difference_type;
			typedef	typename	ft::iterator<bidirectional_iterator_tag, value_type>::reference			reference;
			typedef	typename	ft::iterator<bidirectional_iterator_tag, value_type>::pointer			pointer;
			typedef	typename	ft::iterator<bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;



			BTree_Iterator(void) {  };

			BTree_Iterator(BTree_Iterator const &src)
			{
				this->_node 	= src._node;
			};
			BTree_Iterator(T* src) 
			{
				this->_node 	= src;
			};
			virtual ~BTree_Iterator(void) {};
			
			//CLASSIC OVERLOAD
			BTree_Iterator 	&operator=(BTree_Iterator const &rhs)
			{
				this->_node = rhs._node;
				return (*this);
			}

			//OVERLOAD POINTER
			reference	operator*(void) const 
			{
				return (this->_node->data); 
			}
			pointer		operator->(void) const { return (&(this->_node->data)); }

			//REALTIONAL OPERATOR
			bool	operator==(const BTree_Iterator &rhs)
			{
				return ( (this->_node == rhs._node) ? true : false );
			};

			bool	operator!=(const BTree_Iterator &rhs)
			{
				return (!(*this == rhs));
			};

			BTree_Iterator	&operator++()
			{
				if (_node)
					this->_node = this->_node->next;
				return (*this);
			};
			BTree_Iterator	operator++(int)
			{
				BTree_Iterator	temp = *this;
				if (_node)
					this->_node = this->_node->next;
				return (temp);
			};

			BTree_Iterator	&operator--()
			{
				if (_node)
					this->_node = this->_node->prev;
				return (*this);
			};
			BTree_Iterator	operator--(int)
			{
				BTree_Iterator	temp = *this;
				if (_node)
					this->_node = this->_node->prev;
				return (temp);
			};

		// private :
			T		*_node;
	};

	template <class T, class Cond>
	class BTree_const_Iterator : public ft::iterator<bidirectional_iterator_tag, T>
	{
	public :

			typedef	typename	T::value_type const value_type;

			typedef	typename	ft::iterator<bidirectional_iterator_tag, value_type>::difference_type	difference_type;
			typedef	typename	ft::iterator<bidirectional_iterator_tag, value_type>::reference			reference;
			typedef	typename	ft::iterator<bidirectional_iterator_tag, value_type>::pointer			pointer;
			typedef	typename	ft::iterator<bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;



			BTree_const_Iterator(void) {  };
			BTree_const_Iterator(BTree_const_Iterator const &src)
			{
				this->_node 	= src._node;
			};

			BTree_const_Iterator(BTree_Iterator<T, Cond> const &src)
			:	_node(src._node)
			{
			};

			BTree_const_Iterator(T* src)
			{
				this->_node 	= src;
			};
			
			
			virtual ~BTree_const_Iterator(void) {};
			
			//CLASSIC OVERLOAD
			BTree_const_Iterator 	&operator=(BTree_const_Iterator const &rhs)
			{
				this->_node = rhs._node;
				return (*this);
			}

			//OVERLOAD POINTER
			reference	operator*(void) const 
			{
				return (this->_node->data); 
			}
			pointer		operator->(void) const { return (&(this->_node->data)); }

			//REALTIONAL OPERATOR
			bool	operator==(const BTree_const_Iterator &rhs)
			{
				return ( (this->_node == rhs._node) ? true : false );
			};

			bool	operator!=(const BTree_const_Iterator &rhs)
			{
				return (!(*this == rhs));
			};

			BTree_const_Iterator	&operator++()
			{
				if (_node)
					this->_node = this->_node->next;
				return (*this);
			};
			BTree_const_Iterator	operator++(int)
			{
				BTree_const_Iterator	temp = *this;
				if (_node)
					this->_node = this->_node->next;
				return (temp);
			};

			BTree_const_Iterator	&operator--()
			{
				if (_node)
					this->_node = this->_node->prev;
				return (*this);
			};
			BTree_const_Iterator	operator--(int)
			{
				BTree_const_Iterator	temp = *this;
				if (_node)
					this->_node = this->_node->prev;
				return (temp);
			};
			

			// operator BTree_const_Iterator<T> () const { return (this->_ptr); };

		// private :
			T		*_node;
	};


	

}

#endif
