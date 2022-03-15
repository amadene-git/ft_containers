#ifndef INCLUDE_HPP
# define INCLUDE_HPP

# include <iostream>
# include <string>
# include <deque>//for stack test
# include <typeinfo>//for iterator_traits test

# ifndef NAMESPACE

//containers
#  include  "../containers/vector.hpp"
#  include  "../containers/map.hpp"
#  include  "../containers/stack.hpp"

//utils
#  include  "../include/iterator_traits.hpp"
#  include  "../iterator/reverse_iterator.hpp"
#  include  "../include/enable_if.hpp"
#  include  "../include/equal.hpp"
#  include  "../include/lexicographical_compare.hpp"
#  include  "../include/pair.hpp"


#  define   NAMESPACE ft
 
# else

//containers
#  include  <vector>
#  include  <map>
#  include  <stack>

//utils
#  include  <iterator>
// #  include  <type_traits>//enable_if
#  include <cctype>//lexicographical_compare
#  include <utility>//pair


# endif



void    vector_test(void);
void    map_test(void);
void    stack_test(void);
void    utils_test(void);



#endif
