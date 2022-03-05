#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft
{
    template <class T1, class T2>
	struct	pair
	{
	public:
		typedef	T1	first_type;
		typedef	T2	second_type;

		pair() : first(first_type()), second(second_type()) {};

		template<class U, class V>
		pair(const pair<U,V>& pr)
		: first(T1(pr.first)),
		second(T2(pr.second))
		{};

		pair(const first_type& a, const second_type& b)
		: first(a),
		second(b)
		{};

		pair& operator=(const pair& pr)
		{
			this->first = first_type(pr.first);
			this->second = second_type(pr.second);
			return (*this);
		};

	public:
		first_type	first;
		second_type	second;
	};

    template <class T1,class T2>
	ft::pair<T1,T2> make_pair(T1 x, T2 y)
	{
	  return (ft::pair<T1,T2>(x,y));
	}

	template <class T1, class T2>
	  bool operator== (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{ return lhs.first==rhs.first && lhs.second==rhs.second; }

	template <class T1, class T2>
	  bool operator!= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{ return !(lhs==rhs); }

	template <class T1, class T2>
	  bool operator<  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{ return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

	template <class T1, class T2>
	  bool operator<= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{ return !(rhs<lhs); }

	template <class T1, class T2>
	  bool operator>  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{ return rhs<lhs; }

	template <class T1, class T2>
	  bool operator>= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{ return !(lhs<rhs); }


}


#endif
