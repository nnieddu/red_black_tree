/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterator_traits.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ninieddu <ninieddu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 13:02:19 by ninieddu          #+#    #+#             */
/*   Updated: 2022/03/30 11:24:12 by ninieddu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

// https://www.cplusplus.com/reference/iterator/
// https://www.cplusplus.com/reference/iterator/iterator_traits/
// https://www.fluentcpp.com/2018/05/08/std-iterator-deprecated/

#pragma once

#include <cstddef> // ptrdiff_t

namespace ft
{

	// Base iterator struct
	template <class Category, class T, class Distance = ptrdiff_t,
		class Pointer = T*, class Reference = T&> 
	struct iterator 
	{
		typedef T         value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
		typedef Category  iterator_category;
	};
	
	// Empty class to identify the category/tag of an iterator 
	// struct input_iterator_tag {};
	// struct output_iterator_tag {};
	// struct forward_iterator_tag : public input_iterator_tag {};
	// struct bidirectional_iterator_tag : public forward_iterator_tag {};
	// struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	// typedef std tag, using personnal/ft tag who are juste empty struct (like above),
	// don't allow to use std iterator in function like ditance, advance...
	// This permit to use range function like: constructor, insert.. with stl iterator.
	typedef struct std::input_iterator_tag input_iterator_tag;
	typedef struct std::output_iterator_tag output_iterator_tag;
	typedef struct std::forward_iterator_tag forward_iterator_tag;
	typedef struct std::bidirectional_iterator_tag bidirectional_iterator_tag;
	typedef struct std::random_access_iterator_tag random_access_iterator_tag;

  	// Generic iterator traits definition
	template <class iterator>
	struct iterator_traits
	{
		typedef typename iterator::difference_type		difference_type;
		typedef typename iterator::value_type 			value_type;
		typedef typename iterator::pointer 				pointer;
		typedef typename iterator::reference 			reference;
		typedef typename iterator::iterator_category 	iterator_category;
	};

	// T* specialization (Partial specialization for pointer types.)
	// This specialization lets you use a pointer as a random access iterator.
	template <class T>
	struct iterator_traits<T *>
	{
		typedef ptrdiff_t 									difference_type;
		typedef T 											value_type;
		typedef T*											pointer;
		typedef T&											reference;
		typedef typename ft::random_access_iterator_tag 	iterator_category;
	};

	// const T* specialization (Partial specialization for const pointer types.)
	// This specialization lets you use a pointer as a random access iterator.
	template <class T>
	struct iterator_traits<const T *>
	{
		typedef ptrdiff_t 									difference_type;
		typedef T 											value_type;
		typedef const T*									pointer;
		typedef const T&									reference;
		typedef typename ft::random_access_iterator_tag 	iterator_category;
	};

	// [ ITERATORS FTs ] 

	// https://www.cplusplus.com/reference/iterator/advance/
	// Advance iterator (function template )
	template <class InputIterator, class Distance>
	void advance(InputIterator &i, Distance n,
		ft::input_iterator_tag)
	{
		for (; n > 0; --n)
			++i;
	}

	template <class BidirectionalIterator, class Distance>
	void advance(BidirectionalIterator &i, Distance n,
		ft::bidirectional_iterator_tag)
	{
		if (n <= 0)
			for (; n > 0; --n)
				++i;
		else
			for (; n < 0; ++n)
				--i;
	}

	template <class RandomAccessIterator, class Distance>
	void advance(RandomAccessIterator &i, Distance n,
		ft::random_access_iterator_tag)
	{
		i += n;
	}

	template <class InputIterator, class Distance>
	void advance(InputIterator i, Distance n)
	{
		advance(i, n, typename iterator_traits<InputIterator>::iterator_category());
	}


	// https://www.cplusplus.com/reference/iterator/distance/
	// Distance (function template )
	template<class InputIterator>
	typename ft::iterator_traits<InputIterator>::difference_type
		distance(InputIterator& first, InputIterator& last, ft::input_iterator_tag)
	{
		typename ft::iterator_traits<InputIterator>::difference_type x = 0;

		while (first != last)
		{
			++first;
			++x;
		}
		return x;
	}

	template<class RandomAccessIterator>
	typename iterator_traits<RandomAccessIterator>::difference_type
		distance(RandomAccessIterator& first, RandomAccessIterator& last, ft::random_access_iterator_tag)
	{
		return last - first;
	}

	template<class Iterator>
	typename iterator_traits<Iterator>::difference_type
		distance(Iterator first, Iterator last)
	{
		return ft::distance(first, last, typename iterator_traits<Iterator>::iterator_category());
	}

	// [Iterator generators:]
	
	// back_inserter : Construct back insert iterator (function template )
	// template <class Container>
	// back_insert_iterator<Container> back_inserter (Container& x);

	// front_inserter : Constructs front insert iterator (function template )
	// template <class Container>
	// front_insert_iterator<Container> front_inserter (Container& x);
		
	// inserter : Construct insert iterator (function template )
	// template <class Container, class Iterator>
	// insert_iterator<Container> inserter (Container& x, Iterator it);
}
