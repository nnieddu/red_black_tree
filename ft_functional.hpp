/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functional.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ninieddu <ninieddu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 11:30:25 by ninieddu          #+#    #+#             */
/*   Updated: 2022/03/31 00:01:24 by ninieddu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

// https://docs.microsoft.com/en-us/cpp/standard-library/function-objects-in-the-stl?view=msvc-170

#pragma once

namespace ft
{
	// https://www.cplusplus.com/reference/functional/binary_function/
	template <class Arg1, class Arg2, class Result>
	struct binary_function
	{
		typedef Arg1 first_argument_type;
		typedef Arg2 second_argument_type;
		typedef Result result_type;
	};
	
	// https://www.cplusplus.com/reference/functional/equal_to/
	template <class T> struct equal_to : binary_function <T,T,bool> 
	{ bool operator() (const T& x, const T& y) const {return x==y;} };
	
	// https://www.cplusplus.com/reference/functional/not_equal_to/
	template <class T> struct not_equal_to : binary_function <T,T,bool> 
	{ bool operator() (const T& x, const T& y) const {return x!=y;} };

	// https://www.cplusplus.com/reference/functional/greater/
	template <class T> struct greater : binary_function <T,T,bool> 
	{ bool operator() (const T& x, const T& y) const {return x>y;} };

	// https://www.cplusplus.com/reference/functional/greater_equal/
	template <class T> struct greater_equal : binary_function <T,T,bool> 
	{ bool operator() (const T& x, const T& y) const {return x>=y;} };

	// https://www.cplusplus.com/reference/functional/less_equal/
	template <class T> struct less_equal : binary_function <T,T,bool> 
	{ bool operator() (const T& x, const T& y) const {return x<=y;} };

	// https://www.cplusplus.com/reference/functional/less/
	template <class T> struct less : ft::binary_function <T,T,bool> 
	{ bool operator() (const T& x, const T& y) const {return x<y;} };

}