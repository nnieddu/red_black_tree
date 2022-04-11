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

// https://www.youtube.com/watch?v=1HYIJtM6FAU
// https://www.youtube.com/watch?v=h1Z8_ebEqao

// https://www.geeksforgeeks.org/red-black-tree-set-1-introduction-2/
// https://proprogramming.org/red-black-treerb-tree-implementation-in-c/

// https://www.cs.usfca.edu/~galles/visualization/RedBlack.html // Simu

// https://fr.abcdef.wiki/wiki/Red%E2%80%93black_tree
// https://www.codesdope.com/course/data-structures-red-black-trees-insertion/

// Chaque nœud est rouge ou noir. 
// Tous les nœuds NIL sont considérés comme noirs. 
// Un nœud rouge n'a pas d'enfant rouge. 
// Chaque chemin d'un nœud donné à l'un de ses nœuds NIL descendants passe par le même nombre de nœuds noirs. 

#pragma once

#include<iostream>

namespace ft 
{
	template <class T>
	class rbtree
	{

		public:
			typedef std::size_t		size_type;

			struct node
			{
				T 			value;
				node 		*left;
				node 		*right;
				node 		*p;
				bool 		color; // true == red | false == black
				size_type	h;

			};

			node* nil;
			node* root;

		private:
			size_type	_size;
			// size_type	_height;

		public:
			rbtree() : nil(new node), root(nil), _size(0)//, _height(0)
			{ nil->left = NULL; nil->p = NULL; nil->right = NULL; nil->color = false; }

			~rbtree()
			{
				if(root != nil)
				{
					clean(root);
					delete root;
				}
				delete nil;
			}

			// -------------------------------- //
			// -------------Utils-------------- //
			// -------------------------------- //

			size_type	size() const { return _size; }
			// size_type	height() const { return _height; }

			node* search(T value)
			{
				node* x = root;
				while(x != nil && value != x->value)
				{
					if(value < x->value)
						x = x->left;
					else
						x = x->right;
				}
				if (x == nil)
					return NULL;
				return x;
			}
			
			// -------------------------------- //
			// ------------Insert-------------- //
			// -------------------------------- //

			void insert(T value)
			{
				node* t = new node;
				node* x = root;
				node* y = nil;

				t->h = 0;
				t->value = value;
				while(x != nil)
				{
					y = x;
					if(value < x->value)
						x = x->left;
					else
						x = x->right;
				}
				t->p = y;
				if(y == nil)
					root = t;
				else
				{
					if (t->value < y->value)
						y->left = t;
					else
						y->right = t;
				}
				t->left = nil;
				t->right = nil;
				t->color = true;

				rbInsertFixup(t);
				++_size;
			}

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

			void rbInsertFixup(node* z)
			{
				while(z->p->color == true)
				{
					if(z->p == z->p->p->left)
					{
						node* y = z->p->p->right;
						if(y->color == true)
						{
							z->p->color = false;
							y->color = false;
							z->p->p->color = true;
							z = z->p->p;
						}
						else
						{
							if(z == z->p->right)
							{
								z = z->p;
								leftRotate(z);
							}
							z->p->color = false;
							z->p->p->color = true;
							z->p->right->color = false;
							rightRotate(z->p->p);
						}
					}
					else
					{
						node* y = z->p->p->left;
						if(y->color == true)
						{
							z->p->color = false;
							y->color = false;
							z->p->p->color = true;
							z = z->p->p;
						}
						else
						{
							if(z == z->p->left)
							{
								z = z->p;
								rightRotate(z);
							}
							z->p->color = false;
							z->p->p->color = true;
							z->p->left->color = false;
							leftRotate(z->p->p);
						}
					}
				}
				root->color = false;
			}

			// -------------------------------- //
			// -------------Erase-------------- //
			// -------------------------------- //
			
			void erase(T value)
			{
				node* x = search(value);
				if(x != NULL)
					rbDelete(x);
				_size--;
			}

			node* treeSuccessor(node* x)
			{
				if(x->right != nil)
				{
					while(x->left != nil)
						x = x->left;
					return x;
				}
				node* y = x->p;
				while(y != nil && x == y->right)
				{
					x = y;
					y = y->p;
				}
				return y;
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
					z->value = y->value;
				if(y->color == false)
					rbDeleteFixup(x);
				delete y;
			}

			void rbDeleteFixup(node* x)
			{
				while(x != root && x->color == false)
				{
					node* w = 0;

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
			
			void clean(node* x)
			{
				if(x->right != nil)
				{
					clean(x->right);
					delete x->right;
				}

				if(x->left != nil)
				{
					clean(x->left);
					delete x->left;
				}
			}

			// -------------------------------- //
			// -------------Display------------ //
			// -------------------------------- //
			
			void _display(node* x)
			{
				if(x->left != nil)
					_display(x->left);
				if(x != nil)
				{
					std::cout << x->value << ' ';
					if(x->color == true)
						std::cout << "RED ";
					else
						std::cout << "BLACK ";
					if(x->p != nil)
						std::cout << "p:" << x->p->value << ' ';
					else
						std::cout << "p:" << "NULL ";
					if(x->left != nil)
						std::cout << "l:" << x->left->value << ' ';
					else
						std::cout << "l:" << "NULL ";
					if(x->right != nil)
						std::cout << "r:" << x->right->value << ' ';
					else
						std::cout << "r:" << "NULL ";
					if(x->p == nil)
						std::cout << " =ROOT=";
				}
				// std::cout << " h =" << x->h << std::endl;
				std::cout << std::endl;
				if(x->right != nil)
					_display(x->right);
			}

			void display()
			{
				if(root != nil)
					_display(root);
				else
					std::cout << "Tree is empty !" << std::endl;
			}




			void	printHelper(node* x, size_type flag, std::string padding, std::string spaces)
			{
				if(x != nil)
				{
					if (flag == 0)
					{
						for (size_type i = _size / 2 + 1; i > 0; i--)
							padding.erase(padding.end() - 1);
					}
					if (flag == 1)
					{
						for (size_type i = _size / 2 + 1; i > 0; i--)
							padding += " ";
					}

					if (flag == 1)
						std::cout << std::endl;

					std::cout << padding << x->value;

					if(x->color == true)
						std::cout << "(R)";
					else
						std::cout << "(B)";

					if (flag == 0)
					{

						printHelper(x->left, 0, padding, spaces);
						std::cout << std::endl;
						printHelper(x->right, 1, padding, spaces);
					}
					// std::cout << padding << "/"<< spaces << "\\";
				}
			}

			void	print()
			{
				std::string padding;
				std::string spaces;
				std::string tempPading;

				if(root != nil)
				{
					for (size_type i = _size ; i > 0; i--)
						padding += "   ";
					
					for (size_type i = _size ; i > 0; i--)
						tempPading += "  ";
					
					for (size_type i = _size; i > 0; i--)
							spaces += " ";
					std::cout << padding << "[" << root->value << "]" << std::endl;
					std::cout << padding << "/ " << std::endl;
					printHelper(root->left, 0, padding, spaces);
					std::cout << std::endl;
					std::cout << "----------------------------------------------------------" << std::endl;
					std::cout << std::endl;
					std::cout << tempPading << "[" << root->value << "]" << std::endl;
					std::cout << tempPading << "    \\" << std::endl;
					tempPading += spaces;
					printHelper(root->right, 0, tempPading, spaces);
				}
			}
	};
}
