/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_algorithm.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ninieddu <ninieddu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 11:19:47 by ninieddu          #+#    #+#             */
/*   Updated: 2022/03/30 11:24:28 by ninieddu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft {

	//		----------[ ft_equal ]----------
	// https://www.cplusplus.com/reference/algorithm/equal/?kw=equal
	// https://en.cppreference.com/w/cpp/algorithm/equal

	// Test whether the elements in two ranges are equal
	// Compares the elements in the range [first1,last1) with those in the range beginning at first2,
	// and returns true if all of the elements in both ranges match.

	// equality (1)	
	template<class InputIt1, class InputIt2>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
	{
		for (; first1 != last1; ++first1, ++first2) 
		{
			if (!(*first1 == *first2)) 
				return false;
		}
		return true;
	}

	// predicate (2)
	template<class InputIt1, class InputIt2, class BinaryPredicate>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p)
	{
		for (; first1 != last1; ++first1, ++first2) 
		{
			if (!p(*first1, *first2))
				return false;
		}
		return true;
	}


	//		----------[ ft_lexicographical_compare ]----------
	// https://www.cplusplus.com/reference/algorithm/lexicographical_compare/
	// https://en.cppreference.com/w/cpp/algorithm/lexicographical_compare

	// Lexicographical less-than comparison
	// 
	// Returns true if the range [first1,last1) compares lexicographically less than the range [first2,last2).
	// 
	// A lexicographical comparison is the kind of comparison generally used to sort 
	// words alphabetically in dictionaries; It involves comparing sequentially 
	// the elements that have the same position in both ranges against each other 
	// until one element is not equivalent to the other. The result of comparing 
	// these first non-matching elements is the result of the lexicographical comparison.
	// 
	// If both sequences compare equal until one of them ends, the shorter sequence is lexicographically
	// less than the longer one.
	// 
	// The elements are compared using operator< for the first version, and comp for the second.
	// Two elements, a and b are considered equivalent if (!(a<b) && !(b<a)) or if (!comp(a,b) && !comp(b,a)).

	// default (1)	
	template<class InputIt1, class InputIt2>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
		InputIt2 first2, InputIt2 last2)
	{
		for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
		{
			if (*first1 < *first2) return true;
			if (*first2 < *first1) return false;
		}
		return (first1 == last1) && (first2 != last2);
	}

	// custom (2)	
	template<class InputIt1, class InputIt2, class Compare>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
		InputIt2 first2, InputIt2 last2, Compare comp)
	{
		for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2) 
		{
			if (comp(*first1, *first2)) return true;
			if (comp(*first2, *first1)) return false;
		}
		return (first1 == last1) && (first2 != last2);
	}
}