/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rb_tree.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ninieddu <ninieddu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 13:47:54 by ninieddu          #+#    #+#             */
/*   Updated: 2022/03/31 00:01:42 by ninieddu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

// https://www.geeksforgeeks.org/red-black-tree-set-1-introduction-2/
// https://proprogramming.org/red-black-treerb-tree-implementation-in-c/

// https://www.cs.usfca.edu/~galles/visualization/RedBlack.html // Simu

// https://fr.abcdef.wiki/wiki/Red%E2%80%93black_tree
// https://www.codesdope.com/course/data-structures-rFR

// Chaque noeud est rouge ou noir. 
// Tous les noeuds NIL sont considérés comme noirs. 
// Un noeud rouge n'a pas d'enfant rouge. 
// Chaque chemin d'un noeud donné à l'un de ses noeuds NIL descendants passe par le même nombre de noeuds noirs.

#pragma once

#include <memory>

#include "ft_algorithm.hpp"
#include "ft_utility.hpp"
#include "ft_functional.hpp"
#include "ft_rbtree_iterator.hpp"

namespace ft 
{
	// Specialisation to use rb_tree without pair (default mode)
	template <class T, class Compare, bool isPair> 
	class rbtree_pair
	{
		protected:
			typedef T			key_type;
			typedef T		 	mapped_type;

			bool 		comp_binded(T& lhs, T& rhs) const { return _comp(lhs, rhs); }
			const T& 	value_binded(T& value) const { return value; }
			const T& 	value_second(T& value) const { return value; }
			Compare		_comp;
	};

	// Specialisation to use rb_tree with pair type (mainly for my map container):
	template <class T, class Compare>
	class rbtree_pair<T, Compare, true>
	{
		protected:
			typedef typename T::first_type 		key_type;
			typedef typename T::second_type 	mapped_type;

			bool 				comp_binded(T& lhs, T& rhs) const { return _comp(lhs.first, rhs.first); }
			const key_type&		value_binded(T& value) const { return value.first; }
			mapped_type& 		value_second(T& value) const { return value.second; }
			Compare				_comp;
	};

	// Rb_tree main class
	template <class T, class Compare = ft::less<T>, bool isPair = false, class ValueAlloc = std::allocator<T> >
	class rbtree : rbtree_pair<T, Compare, isPair>
	{
		public:
			struct node
			{
					typedef T		node_value;
					node_value 		value;
					node*			left;
					node*			right;
					node* 			p;
					bool 			color;
					// true == red | false == black
			};

			typedef std::size_t												size_type;
			typedef std::allocator<node> 									NodeAlloc;
			typedef typename rbtree_pair<T, Compare, isPair>::key_type		key_type;
			typedef typename rbtree_pair<T, Compare, isPair>::mapped_type	mapped_type;
			
			typedef typename ft::rbtree_iterator<node, T>					iterator;
			typedef typename ft::rbtree_iterator<node, const T>				const_iterator;
		
		private:
			ValueAlloc		_vAlloc;
			NodeAlloc		_nAlloc;
			Compare			_comp;
			size_type		_size;

			node* nil;
			node* root;

		public:
			rbtree() : _vAlloc(ValueAlloc()), _nAlloc(NodeAlloc()), _comp(Compare()), _size(0), nil(_nAlloc.allocate(1))
			{ 
				_nAlloc.construct(nil, node());
				root = nil;
			}

			rbtree (const rbtree& x) 
			: _vAlloc(x._vAlloc), _nAlloc(x._nAlloc), _comp(x._comp), _size(0), nil(_nAlloc.allocate(1))
			{
				_nAlloc.construct(nil, node());
				root = nil;
				if (x.root != x.nil)
					insert(x.root->value);
				if (root != nil)
					copy(x.root, x.nil);
			}

			rbtree& operator=(const rbtree& x)
			{
				if (&x == this)
					return *this;

				if (root != nil)
				{
					_vAlloc = x._vAlloc;
					_nAlloc = x._nAlloc;
					this->~rbtree();
					nil = _nAlloc.allocate(1);
					_nAlloc.construct(nil, node());
					root = nil;
				}

				if (x.root != x.nil)
					insert(x.root->value);
				if (root != nil)
					copy(x.root, x.nil);

				return *this;
			}

			~rbtree()
			{
				if(root != nil)
				{
					destroy(root);
					_vAlloc.destroy(&root->value);
					_nAlloc.deallocate(root, 1);
				}
				_nAlloc.deallocate(nil, 1);
				_size = 0;
			}

			node* begin() const
			{
				if (_size == 0)
					return root;
				node* x = root;
				while (x->left != nil)
					x = x->left;
				return x;
			}

			node* end() const
			{
				if (_size == 0)
					return root;
				node* x = root;
				while (x->right != nil)
					x = x->right;
				return x;
			}

			size_type	getSize() const { return _size; }
			node*		getNill() const { return nil; }
			size_type	max_size() const { return _nAlloc.max_size(); }

			node* searchNode(key_type value) const
			{
				node* n = root;
				while(n != nil && value != this->value_binded(n->value))
				{
					if(_comp(value, this->value_binded(n->value))) ///////
						n = n->left;
					else
						n = n->right;
				}
				return n;
			}

			void swap(rbtree& toSwap)
			{
				node* 		tmp_root = toSwap.root;
				node* 		tmp_nil = toSwap.nil;
				ValueAlloc	tmp_vAlloc = toSwap._vAlloc;
				NodeAlloc	tmp_nAlloc = toSwap._nAlloc;
				Compare		tmp_comp = toSwap._comp;
				size_type	tmp_size = toSwap._size;
			
				toSwap.root 	= this->root;
				toSwap.nil 		= this->nil;
				toSwap._vAlloc 	= this->_vAlloc;
				toSwap._nAlloc 	= this->_nAlloc;
				toSwap._comp 	= this->_comp;
				toSwap._size 	= this->_size;

				this->root 	 	= tmp_root;
				this->nil 		= tmp_nil;
				this->_vAlloc 	= tmp_vAlloc;
				this->_nAlloc 	= tmp_nAlloc;
				this->_comp 	= tmp_comp;
				this->_size 	= tmp_size;
			}
			
			// -------------------------------- //
			// -------------ForMap------------- //
			// -------------------------------- //
			size_type count(const key_type value) const ////////// test
			{
				node* n = root;
				while(n != nil && value != this->value_binded(n->value))
				{
					if(this->_comp(value, this->value_binded(n->value)))
						n = n->left;
					else
						n = n->right;
				}
				if (n == nil)
					return 0;
				return 1;
			}


			// -------------------------------- //
			// -------------Insert------------- //
			// -------------------------------- //
			pair<iterator, bool> insert(T value, bool allowSameKey = true, bool onlySameKey = false)
			{
				if (onlySameKey == true && _size > 0 && 
					((this->value_binded(value) != this->value_binded(root->value))))
						return ft::make_pair(iterator(root, nil), false);
				node* newNode = _nAlloc.allocate(1);
				_nAlloc.construct(newNode, node());
				node* x = root;
				node* y = nil;
		
				_vAlloc.construct(&newNode->value, value);

				while(x != nil)
				{
					y = x;
					if (this->comp_binded(value, x->value))
					{
						if (allowSameKey == false && this->value_binded(value) == this->value_binded(x->value))
						{
							_vAlloc.destroy(&newNode->value);
							_nAlloc.deallocate(newNode, 1);
							return ft::make_pair(iterator(x, nil), false);
						}	
						x = x->left;
					}
					else
					{
						if (allowSameKey == false && this->value_binded(value) == this->value_binded(x->value))
						{
							_vAlloc.destroy(&newNode->value);
							_nAlloc.deallocate(newNode, 1);
							return ft::make_pair(iterator(x, nil), false);
						}
						x = x->right;
					}
				}
				newNode->p = y;
				if (y == nil)
					root = newNode;
				else
				{
					if (this->comp_binded(newNode->value, y->value))
						y->left = newNode;
					else
						y->right = newNode;
				}
				newNode->left = nil;
				newNode->right = nil;
				newNode->color = true;
				rbInsertFixup(newNode);
				++_size;
				return ft::make_pair(iterator(newNode, nil), true);
			}

		private:
			void leftRotate(node* x)
			{
				node* y = x->right;
				if(x->p == nil)
					root = y;
				else
				{
					if(x == x->p->left)
						x->p->left = y;
					else
						x->p->right = y;
				}
				y->p = x->p;
				x->right = y->left;
				y->left->p = x;
				y->left = x;
				x->p = y;
			}

			void rightRotate(node* x)
			{
				node* y = x->left;
				if(x->p == nil)
					root = y;
				else
				{
					if(x == x->p->left)
						x->p->left = y;
					else
						x->p->right = y;
				}
				y->p = x->p;
				x->left = y->right;
				y->right->p = x;
				y->right = x;
				x->p = y;
			}

			void rbInsertFixup(node* nN)
			{
				while(nN->p->color == true)
				{
					if(nN->p == nN->p->p->left)
					{
						node* y = nN->p->p->right;
						if(y->color == true)
						{
							nN->p->color = false;
							y->color = false;
							nN->p->p->color = true;
							nN = nN->p->p;
						}
						else
						{
							if(nN == nN->p->right)
							{
								nN = nN->p;
								leftRotate(nN);
							}
							nN->p->color = false;
							nN->p->p->color = true;
							nN->p->right->color = false;
							rightRotate(nN->p->p);
						}
					}
					else
					{
						node* y = nN->p->p->left;
						if(y->color == true)
						{
							nN->p->color = false;
							y->color = false;
							nN->p->p->color = true;
							nN = nN->p->p;
						}
						else
						{
							if(nN == nN->p->left)
							{
								nN = nN->p;
								rightRotate(nN);
							}
							nN->p->color = false;
							nN->p->p->color = true;
							nN->p->left->color = false;
							leftRotate(nN->p->p);
						}
					}
				}
				root->color = false;
			}

			// -------------------------------- //
			// -------------Erase-------------- //
			// -------------------------------- //
		private:
			node* treeSuccessor(node* x)
			{
				node* y = nil;

				if (x->left != nil)
				{
					y = x->left;
					while (y->right!=nil)
						y = y->right;
				}
				else
				{
					y = x->right;
					while (y->left != nil)
						y = y->left;
				}
				return y;
			}

			void rbDeleteFixup(node* x)
			{
				while(x != root && x->color == false)
				{
					node* w = nil;

					if(x->p->left == x)
					{
						w = x->p->right;
						if(w->color == true)
						{
							w->color = false;
							x->p->color = true;
							leftRotate(x->p);
							w = x->p->right;
						}
						if(w->left->color == false && w->right->color == false)
						{
							w->color = true;
							x = x->p;
						}
						else
						{
							if(w->right->color == false)
							{
								w->left->color = false;
								w->color = true;
								rightRotate(w);
								w = x->p->right;
							}
							w->color = x->p->color;
							x->p->color = false;
							w->right->color = false;
							leftRotate(x->p);
							x = root;
						}
					}
					else
					{
						w = x->p->left;
						if(w->color == true)
						{
							w->color = false;
							x->p->color = true;
							rightRotate(x->p);
							w = x->p->left;
						}
						if(w->right->color == false && w->left->color == false)
						{
							w->color = true;
							x = x->p;
						}
						else
						{
							if(w->left->color == false)
							{
								w->right->color = false;
								w->color = true;
								leftRotate(w);
								w = x->p->left;
							}
							w->color = x->p->color;
							x->p->color = false;
							w->left->color = false;
							rightRotate(x->p);
							x = root;
						}
					}
				}
				x->color = false;
			}

			void rbDelete(node* z)
			{
				node* x = nil;
				node* y = nil;

				if(z->left == nil || z->right == nil)
					y = z;
				else
					y = treeSuccessor(z);
				if(y->left != nil)
					x = y->left;
				else
					x = y->right;
				x->p = y->p;
				if(y->p == nil)
					root = x;
				else
				{
					if(y == y->p->left)
						y->p->left = x;
					else
						y->p->right = x;
				}
				if(y != z)
					_vAlloc.construct(&z->value, y->value);
				if(x != nil && y->color == false)
					rbDeleteFixup(x);
				_vAlloc.destroy(&y->value);
				_nAlloc.deallocate(y, 1);
			}

		public:	
			size_type erase(key_type value)
			{
				node* x = searchNode(value);
				if(x != nil)
				{
					rbDelete(x);
					--_size;
					return 1;
				}
				return 0;
			}

			// -------------------------------- //
			// -------------Display------------ //
			// -------------------------------- //
		private:
			void displayHelper(node* x)
			{
				if(x->left != nil)
					displayHelper(x->left);
				if(x != nil)
				{
					std::cout << this->value_binded(x->value) << ' ';
					if(x->color == true)
						std::cout << "RED ";
					else
						std::cout << "BLACK ";
					if(x->p != nil)
						std::cout << "p:" << this->value_binded(x->p->value) << ' ';
					else
						std::cout << "p:" << "NULL ";
					if(x->left != nil)
						std::cout << "l:" << this->value_binded(x->left->value) << ' ';
					else
						std::cout << "l:" << "NULL ";
					if(x->right != nil)
						std::cout << "r:" << this->value_binded(x->right->value) << ' ';
					else
						std::cout << "r:" << "NULL ";
					if(x->p == nil)
						std::cout << " =ROOT=";
				}
				std::cout << std::endl;
				if(x->right != nil)
					displayHelper(x->right);
			}
		public:
			void display()
			{
				if(root != nil)
					displayHelper(root);
				else
					std::cout << "Tree is empty !" << std::endl;
			}

			// -------------------------------- //
			// -------------Utils-------------- //
			// -------------------------------- //
		private:
			void destroy(node* x)
			{
				if(x->right != nil)
				{
					destroy(x->right);
					_vAlloc.destroy(&x->right->value);
					_nAlloc.deallocate(x->right, 1);
				}

				if(x->left != nil)
				{
					destroy(x->left);
					_vAlloc.destroy(&x->left->value);
					_nAlloc.deallocate(x->left, 1);
				}
			}

		public:
			void clear()
			{ 
				if(root != nil)
				{
					destroy(root);
					_vAlloc.destroy(&root->value);
					_nAlloc.deallocate(root, 1);
					root = nil;
					_size = 0;
				}
			}
		private:
 
			void copy(node* x, node* nil)
			{
				if(x->left != nil)
				{
					insert(x->left->value);
					copy(x->left, nil);
				}

				if(x->right != nil)
				{
					insert(x->right->value);
					copy(x->right, nil);
				}
			}
	};
}
