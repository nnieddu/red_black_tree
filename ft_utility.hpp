/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utility.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ninieddu <ninieddu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 11:30:25 by ninieddu          #+#    #+#             */
/*   Updated: 2022/03/30 23:36:00 by ninieddu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

// https://www.cplusplus.com/reference/utility/pair/?kw=pair
// https://www.cplusplus.com/reference/utility/pair/operators/

namespace ft
{
	template <class T1, class T2> 
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		first_type  first;
		second_type second;

		pair() : first(), second() { }

		template<class U, class V>
		pair(const pair<U, V> &pr) : first(pr.first), second(pr.second) { }

		pair(const first_type &a, const second_type &b) : first(a), second(b) { }

		~pair() {}
		
		pair& operator=(const pair& pr)
		{
			if (&pr == this)
				return *this;
			first = pr.first;
			second = pr.second;
			return *this;
		}

	};

	template <class T1, class T2>
	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return lhs.first==rhs.first && lhs.second==rhs.second; }

	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(lhs==rhs); }

	template <class T1, class T2>
	bool operator< (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(rhs<lhs); }

	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return rhs<lhs; }

	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(lhs<rhs); }


	//	----------[ make_pair ]----------
	// https://www.cplusplus.com/reference/utility/make_pair/

	template <class T1,class T2>
	pair<T1,T2> make_pair (T1 x, T2 y)
	{ return (pair<T1,T2>(x,y)); }
}