#ifndef STACK_HPP
# define STACK_HPP
# include "vector.hpp"

namespace ft 
{

	template <typename T, typename Container = ft::vector<T> >
	class stack 
	{

	public:
		typedef	typename	Container::value_type	value_type;
		typedef	typename	Container::size_type	size_type;
		typedef				Container				container_type;

		template <typename _T, typename _Container>
		friend bool	ft::operator==(stack<_T, _Container> const &lhs,
		stack<_T, _Container> const &rhs);
		template <typename _T, typename _Container>
		friend bool	ft::operator<(stack<_T, _Container> const &lhs,
		stack<_T, _Container> const &rhs);

		explicit stack(Container const &c = Container())
		: _container(c) 
		{
		};

		bool		empty(void)	const	{ return (_container.empty()); };
		size_type	size(void)	const	{ return (_container.size()); };
		
		value_type			&top(void)			{ return (_container.back()); };
		value_type	const	&top(void) const	{ return (_container.back()); };

		void	push(value_type const &val) { _container.push_back(val); };
		void	pop(void) 					{ _container.pop_back(); };

	protected:
		Container _container;
	};

	template <typename T, typename Container>
	bool	operator==(	stack<T, Container> const &lhs,
						stack<T, Container> const &rhs) 
	{
		return (lhs._container == rhs._container);
	}

	template <typename T, typename Container>
	bool	operator<(	stack<T, Container>const &lhs,
						stack<T, Container> const &rhs) 
	{
		return (lhs._container < rhs._container);
	}

	template <typename T, typename Container>
	bool	operator!=(	stack<T, Container> const &lhs,
						stack<T, Container> const &rhs) 
	{
		return (!(lhs == rhs));
	}

	template <typename T, typename Container>
	bool	operator>(	stack<T, Container> const & lhs,
						stack<T, Container> const& rhs)
	{
		return (rhs < lhs);
	}

	template <typename T, typename Container>
	bool	operator>=(	stack<T, Container> const & lhs,
						stack<T, Container> const & rhs)
	{
		return (rhs < lhs || lhs == rhs);
	}

	template <typename T, typename Container>
	bool	operator<=(	stack<T, Container> const & lhs,
						stack<T, Container> const & rhs)
	{
		return (lhs < rhs || lhs == rhs);
	}

}

#endif

