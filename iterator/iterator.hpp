#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "../utils/utils.hpp"
#include <iterator>//std::random_acces_iterator_tag

namespace ft 
{
	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };
	
	template<class T>	struct	is_random_acces_iterator	:	false_type {};
	template<>			struct	is_random_acces_iterator<std::random_access_iterator_tag>	:	true_type {};
	template<>			struct	is_random_acces_iterator<random_access_iterator_tag>	:	true_type {};

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
	public :
		typedef typename	Iterator::difference_type	difference_type;
		typedef typename	Iterator::value_type 		value_type;
		typedef typename	Iterator::pointer 			pointer;
		typedef typename	Iterator::reference 		reference;
		typedef typename	Iterator::iterator_category iterator_category;
	};
	template <class T> 
	class iterator_traits<T*>
	{
	public :
		typedef 			__gnu_cxx::ptrdiff_t		difference_type;
		typedef 			T							value_type;
		typedef 			T*							pointer;
		typedef 			T&							reference;
		typedef 			random_access_iterator_tag	iterator_category;
	};
	template <class T> 
	class iterator_traits<const T*>
	{
	public :
		typedef 			__gnu_cxx::ptrdiff_t		difference_type;
		typedef 			T							value_type;
		typedef 			const T*					pointer;
		typedef 			const T&					reference;
		typedef 			random_access_iterator_tag	iterator_category;
	};
	
	template<class InputIterator>
	typename iterator_traits<InputIterator>::difference_type
    distance(InputIterator first, InputIterator last,
	typename ft::enable_if<!ft::is_random_acces_iterator<typename InputIterator::iterator_category>::value, typename InputIterator::iterator_category>::type* = NULL)
	{
		typename iterator_traits<InputIterator>::difference_type	n = 0;
		
		while (first != last)
		{
			++first;
			++n;
		}
		return (n);	
	}

	template<class InputIterator>
	typename iterator_traits<InputIterator>::difference_type
    distance(InputIterator first, InputIterator last,
	typename ft::enable_if<ft::is_random_acces_iterator<typename InputIterator::iterator_category>::value, typename InputIterator::iterator_category>::type* = NULL)
	{
		return (last - first);		
	}


}
#endif
